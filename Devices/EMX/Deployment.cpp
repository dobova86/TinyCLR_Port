// Copyright Microsoft Corporation
// Copyright GHI Electronics, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <LPC24.h>
#include "../../Drivers/AT49BV322DT_Flash/AT49BV322DT_Flash.h"

#define TOTAL_DEPLOYMENT_CONTROLLERS 1

const char* deploymentApiNames[TOTAL_DEPLOYMENT_CONTROLLERS] = {
    "GHIElectronics.TinyCLR.NativeApis.AT49BV322DT.StorageController\\0"
};

static TinyCLR_Storage_Controller deploymentControllers[TOTAL_DEPLOYMENT_CONTROLLERS];
static TinyCLR_Api_Info deploymentApi[TOTAL_DEPLOYMENT_CONTROLLERS];

struct DeploymentState {
    uint32_t controllerIndex;

    size_t regionCount;
    const uint64_t* regionAddresses;
    const size_t* regionSizes;

    TinyCLR_Storage_Descriptor storageDescriptor;
    TinyCLR_Startup_DeploymentConfiguration deploymentConfiguration;

    uint32_t initializeCount;
    bool tableInitialized = false;
};

static DeploymentState deploymentStates[TOTAL_DEPLOYMENT_CONTROLLERS];

void LPC24_Deployment_EnsureTableInitialized() {
    for (auto i = 0; i < TOTAL_DEPLOYMENT_CONTROLLERS; i++) {
        if (deploymentStates[i].tableInitialized)
            continue;

        deploymentControllers[i].ApiInfo = &deploymentApi[i];
        deploymentControllers[i].Acquire = &LPC24_Deployment_Acquire;
        deploymentControllers[i].Release = &LPC24_Deployment_Release;
        deploymentControllers[i].Open = &LPC24_Deployment_Open;
        deploymentControllers[i].Close = &LPC24_Deployment_Close;
        deploymentControllers[i].Read = &LPC24_Deployment_Read;
        deploymentControllers[i].Write = &LPC24_Deployment_Write;
        deploymentControllers[i].Erase = &LPC24_Deployment_Erase;
        deploymentControllers[i].IsErased = &LPC24_Deployment_IsErased;
        deploymentControllers[i].GetDescriptor = &LPC24_Deployment_GetDescriptor;

        deploymentApi[i].Author = "GHI Electronics, LLC";
        deploymentApi[i].Name = deploymentApiNames[i];
        deploymentApi[i].Type = TinyCLR_Api_Type::StorageController;
        deploymentApi[i].Version = 0;
        deploymentApi[i].Implementation = &deploymentControllers[i];
        deploymentApi[i].State = &deploymentStates[i];

        deploymentStates[i].controllerIndex = i;
        deploymentStates[i].initializeCount = 0;
        deploymentStates[i].regionCount = LPC24_DEPLOYMENT_SECTOR_NUM;

        deploymentStates[i].tableInitialized = true;
    }
}

void LPC24_Deployment_GetDeploymentApi(const TinyCLR_Api_Info*& api, const TinyCLR_Startup_DeploymentConfiguration*& configuration) {
    LPC24_Deployment_EnsureTableInitialized();

    auto state = &deploymentStates[0];

    api = &deploymentApi[0];
    configuration = &state->deploymentConfiguration;
}

void LPC24_Deployment_AddApi(const TinyCLR_Api_Manager* apiManager) {
    LPC24_Deployment_EnsureTableInitialized();

    for (auto i = 0; i < TOTAL_DEPLOYMENT_CONTROLLERS; i++) {
        apiManager->Add(apiManager, &deploymentApi[i]);
    }

    apiManager->SetDefaultName(apiManager, TinyCLR_Api_Type::StorageController, deploymentApi[0].Name);
}

TinyCLR_Result LPC24_Deployment_Acquire(const TinyCLR_Storage_Controller* self) {
    auto state = reinterpret_cast<DeploymentState*>(self->ApiInfo->State);

    TinyCLR_Result result = TinyCLR_Result::Success;

    if (state != nullptr) {
        if (state->initializeCount == 0) {
            result = AT49BV322DT_Flash_Acquire();
        }

        if (result == TinyCLR_Result::Success) {
            state->initializeCount++;
        }
    }

    return result = (state != nullptr) ? result : TinyCLR_Result::ArgumentNull;
}

TinyCLR_Result LPC24_Deployment_Release(const TinyCLR_Storage_Controller* self) {
    auto state = reinterpret_cast<DeploymentState*>(self->ApiInfo->State);

    TinyCLR_Result result = TinyCLR_Result::Success;

    if (state != nullptr) {
        if (state->initializeCount == 0)
            return TinyCLR_Result::InvalidOperation;

        result = AT49BV322DT_Flash_Release();

        if (result == TinyCLR_Result::Success) {
            state->initializeCount--;
        }
    }

    return result = (state != nullptr) ? result : TinyCLR_Result::ArgumentNull;
}

TinyCLR_Result LPC24_Deployment_Open(const TinyCLR_Storage_Controller* self) {
    auto state = reinterpret_cast<DeploymentState*>(self->ApiInfo->State);

    state->storageDescriptor.CanReadDirect = true;
    state->storageDescriptor.CanWriteDirect = false;
    state->storageDescriptor.CanExecuteDirect = true;
    state->storageDescriptor.EraseBeforeWrite = true;
    state->storageDescriptor.Removable = false;
    state->storageDescriptor.RegionsContiguous = true;
    state->storageDescriptor.RegionsEqualSized = true;

    size_t regionCount;

    AT49BV322DT_Flash_GetSectorMap(state->regionAddresses, state->regionSizes, regionCount);

    if (regionCount < state->regionCount)
        return TinyCLR_Result::ArgumentOutOfRange;

    state->regionAddresses += LPC24_DEPLOYMENT_SECTOR_START;
    state->regionSizes += LPC24_DEPLOYMENT_SECTOR_START;

    state->storageDescriptor.RegionCount = state->regionCount;
    state->storageDescriptor.RegionAddresses = reinterpret_cast<const uint64_t*>(state->regionAddresses);
    state->storageDescriptor.RegionSizes = reinterpret_cast<const size_t*>(state->regionSizes);

    state->deploymentConfiguration.RegionCount = state->storageDescriptor.RegionCount;
    state->deploymentConfiguration.RegionAddresses = state->storageDescriptor.RegionAddresses;
    state->deploymentConfiguration.RegionSizes = state->storageDescriptor.RegionSizes;
    state->deploymentConfiguration.RegionsContiguous = state->storageDescriptor.RegionsContiguous;
    state->deploymentConfiguration.RegionsEqualSized = state->storageDescriptor.RegionsEqualSized;

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Deployment_Close(const TinyCLR_Storage_Controller* self) {
    // Close internal flash
    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Deployment_Read(const TinyCLR_Storage_Controller* self, uint64_t address, size_t& count, uint8_t* data, uint64_t timeout) {
    return AT49BV322DT_Flash_Read(address, count, data);
}

TinyCLR_Result LPC24_Deployment_Write(const TinyCLR_Storage_Controller* self, uint64_t address, size_t& count, const uint8_t* data, uint64_t timeout) {
    return AT49BV322DT_Flash_Write(address, count, data);;
}

TinyCLR_Result LPC24_Deployment_Erase(const TinyCLR_Storage_Controller* self, uint64_t address, size_t& count, uint64_t timeout) {
    auto sector = address;

    sector += LPC24_DEPLOYMENT_SECTOR_START;

    return AT49BV322DT_Flash_EraseBlock(sector);
}

TinyCLR_Result LPC24_Deployment_IsErased(const TinyCLR_Storage_Controller* self, uint64_t address, size_t count, bool& erased) {
    auto sector = address;

    sector += LPC24_DEPLOYMENT_SECTOR_START;

    return AT49BV322DT_Flash_IsBlockErased(sector, erased);
}

TinyCLR_Result LPC24_Deployment_GetBytesPerSector(const TinyCLR_Storage_Controller* self, uint32_t address, int32_t& size) {
    return AT49BV322DT_Flash_GetBytesPerSector(address, size);
}

TinyCLR_Result LPC24_Deployment_GetDescriptor(const TinyCLR_Storage_Controller* self, const TinyCLR_Storage_Descriptor*& descriptor) {
    auto state = reinterpret_cast<DeploymentState*>(self->ApiInfo->State);

    descriptor = &state->storageDescriptor;

    return descriptor->RegionCount > 0 ? TinyCLR_Result::Success : TinyCLR_Result::NotAvailable;
}

const TinyCLR_Startup_DeploymentConfiguration* LPC24_Deployment_GetDeploymentConfiguration() {
    auto state = &deploymentStates[0];

    return reinterpret_cast<const TinyCLR_Startup_DeploymentConfiguration*>(&state->deploymentConfiguration);
}

