#pragma once

#include <TinyCLR.h>

struct Interop_mscorlib_System_Object {
    static TinyCLR_Result Equals___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetHashCode___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result MemberwiseClone___OBJECT(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result ReferenceEquals___STATIC___BOOLEAN__OBJECT__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib___PrivateImplementationDetails_ {
    static const size_t FIELD_STATIC___30F2EDF187653C888CED20A5A3E3D6C361BBEC7C___PrivateImplementationDetailsStaticArrayInitTypeSize128 = 0;
    static const size_t FIELD_STATIC___7BD9FD6F0CA094855382F77F4352B6BC065CCDD4___PrivateImplementationDetailsStaticArrayInitTypeSize128 = 1;
    static const size_t FIELD_STATIC___B5E59333D76EAFE27EB9A74E9A408CA8D0FDF212___PrivateImplementationDetailsStaticArrayInitTypeSize128 = 2;
};

struct Interop_mscorlib_System_Runtime_CompilerServices_FormattableStringFactory__ConcreteFormattableString {
    static const size_t FIELD___format___STRING = 1;
    static const size_t FIELD___arguments___SZARRAY_OBJECT = 2;
};

struct Interop_mscorlib_System_Diagnostics_DebuggableAttribute {
    static const size_t FIELD___m_debuggingModes___SystemDiagnosticsDebuggableAttributeDebuggingModes = 1;
};

struct Interop_mscorlib_System_ValueType {
    static TinyCLR_Result Equals___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Collections_Hashtable {
    static const size_t FIELD____buckets___SZARRAY_SystemCollectionsHashtableEntry = 1;
    static const size_t FIELD____numberOfBuckets___I4 = 2;
    static const size_t FIELD____count___I4 = 3;
    static const size_t FIELD____loadFactor___I4 = 4;
    static const size_t FIELD____maxLoadFactor___I4 = 5;
    static const size_t FIELD____growthFactor___R8 = 6;
};

struct Interop_mscorlib_System_Collections_Hashtable__Entry {
    static const size_t FIELD___key___OBJECT = 1;
    static const size_t FIELD___value___OBJECT = 2;
    static const size_t FIELD___next___SystemCollectionsHashtableEntry = 3;
};

struct Interop_mscorlib_GHIElectronics_TinyCLR_Storage_Streams_Buffer {
    static const size_t FIELD___data___SZARRAY_U1 = 1;
    static const size_t FIELD___offset___I4 = 2;
    static const size_t FIELD___length___U4 = 3;
    static const size_t FIELD___Capacity__BackingField___U4 = 4;
};

struct Interop_mscorlib_System_Collections_Hashtable__HashtableEnumerator {
    static const size_t FIELD___ht___SystemCollectionsHashtable = 1;
    static const size_t FIELD___temp___SystemCollectionsHashtableEntry = 2;
    static const size_t FIELD___index___I4 = 3;
    static const size_t FIELD___returnType___SystemCollectionsHashtableEnumeratorType = 4;
};

struct Interop_mscorlib_System_Exception {
    static const size_t FIELD____message___STRING = 1;
    static const size_t FIELD___m_innerException___SystemException = 2;
    static const size_t FIELD___m_stackTrace___OBJECT = 3;
    static const size_t FIELD___m_HResult___I4 = 4;

    static TinyCLR_Result get_StackTrace___STRING(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_Marshal {
    static TinyCLR_Result ReadByte___STATIC___U1__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ReadInt16___STATIC___I2__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ReadInt32___STATIC___I4__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ReadInt64___STATIC___I8__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteByte___STATIC___VOID__I__U1(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteInt16___STATIC___VOID__I__I2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteInt32___STATIC___VOID__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result WriteInt64___STATIC___VOID__I__I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result AllocHGlobal___STATIC___I__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result FreeHGlobal___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_I4__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_CHAR__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_I2__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_I8__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_R4__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_R8__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_U1__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SZARRAY_I__I4__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_I2__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_I8__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_R4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_R8__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_U1__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__I__SZARRAY_I__I4__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_Marshal__InvokeHelper {
    static const size_t FIELD___Target___I = 1;

    static TinyCLR_Result InvokeIntPtr___STATIC___VOID__I__BYREF_I(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Collections_Hashtable__KeyCollection {
    static const size_t FIELD___ht___SystemCollectionsHashtable = 1;
};

struct Interop_mscorlib_System_Array {
    static TinyCLR_Result System_Collections_IList_get_Item___OBJECT__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result System_Collections_IList_set_Item___VOID__I4__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Length___I4(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result CreateInstance___STATIC___SystemArray__SystemType__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Copy___STATIC___VOID__SystemArray__I4__SystemArray__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Clear___STATIC___VOID__SystemArray__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result TrySZIndexOf___STATIC___BOOLEAN__SystemArray__I4__I4__OBJECT__BYREF_I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Array__SZArrayEnumerator {
    static const size_t FIELD____array___SystemArray = 1;
    static const size_t FIELD____index___I4 = 2;
    static const size_t FIELD____endIndex___I4 = 3;
    static const size_t FIELD____startIndex___I4 = 4;
    static const size_t FIELD____arrayLength___I4 = 5;
};

struct Interop_mscorlib_System_Globalization_Resources_CultureInfo {
    static const size_t FIELD_STATIC___manager___SystemResourcesResourceManager = 3;
};

struct Interop_mscorlib_System_Delegate {
    static TinyCLR_Result Equals___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Method___SystemReflectionMethodInfo(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Target___OBJECT(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result Combine___STATIC___SystemDelegate__SystemDelegate__SystemDelegate(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Remove___STATIC___SystemDelegate__SystemDelegate__SystemDelegate(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result op_Equality___STATIC___BOOLEAN__SystemDelegate__SystemDelegate(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result op_Inequality___STATIC___BOOLEAN__SystemDelegate__SystemDelegate(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_MulticastDelegate {
    static TinyCLR_Result op_Equality___STATIC___BOOLEAN__SystemMulticastDelegate__SystemMulticastDelegate(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result op_Inequality___STATIC___BOOLEAN__SystemMulticastDelegate__SystemMulticastDelegate(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_AppDomain {
    static const size_t FIELD___m_appDomain___OBJECT = 1;
    static const size_t FIELD___m_friendlyName___STRING = 2;

    static TinyCLR_Result GetAssemblies___SZARRAY_SystemReflectionAssembly(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LoadInternal___SystemReflectionAssembly__STRING__BOOLEAN__I4__I4__I4__I4(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result CreateDomain___STATIC___SystemAppDomain__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Unload___STATIC___VOID__SystemAppDomain(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_ArgumentException {
    static const size_t FIELD___m_paramName___STRING = 5;
};

struct Interop_mscorlib_System_AttributeUsageAttribute {
    static const size_t FIELD_STATIC___Default___SystemAttributeUsageAttribute = 4;

    static const size_t FIELD___m_attributeTarget___SystemAttributeTargets = 1;
    static const size_t FIELD___m_allowMultiple___BOOLEAN = 2;
    static const size_t FIELD___m_inherited___BOOLEAN = 3;
};

struct Interop_mscorlib_System_BitConverter {
    static TinyCLR_Result get_IsLittleEndian___STATIC___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DoubleToInt64Bits___STATIC___I8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__R4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__I2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__U4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__U8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___STATIC___SZARRAY_U1__U2(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Int64BitsToDouble___STATIC___R8__I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToBoolean___STATIC___BOOLEAN__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToChar___STATIC___CHAR__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToDouble___STATIC___R8__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToInt16___STATIC___I2__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToInt32___STATIC___I4__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToInt64___STATIC___I8__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToSingle___STATIC___R4__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToString___STATIC___STRING__SZARRAY_U1(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToString___STATIC___STRING__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToString___STATIC___STRING__SZARRAY_U1__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToUInt16___STATIC___U2__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToUInt32___STATIC___U4__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToUInt64___STATIC___U8__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Boolean {
    static const size_t FIELD_STATIC___FalseString___STRING = 5;
    static const size_t FIELD_STATIC___TrueString___STRING = 6;

    static const size_t FIELD___m_value___BOOLEAN = 1;
};

struct Interop_mscorlib_System_Byte {
    static const size_t FIELD___m_value___U1 = 1;
};

struct Interop_mscorlib_System_CLSCompliantAttribute {
    static const size_t FIELD___m_compliant___BOOLEAN = 1;
};

struct Interop_mscorlib_System_Char {
    static const size_t FIELD___m_value___CHAR = 1;
};

struct Interop_mscorlib_System_Collections_ArrayList {
    static const size_t FIELD____items___SZARRAY_OBJECT = 1;
    static const size_t FIELD____size___I4 = 2;

    static TinyCLR_Result get_Item___OBJECT__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result set_Item___VOID__I4__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Add___I4__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Clear___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Insert___VOID__I4__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result RemoveAt___VOID__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetCapacity___VOID__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Collections_DictionaryEntry {
    static const size_t FIELD___Key___OBJECT = 1;
    static const size_t FIELD___Value___OBJECT = 2;
};

struct Interop_mscorlib_System_Collections_Queue {
    static const size_t FIELD____array___SZARRAY_OBJECT = 1;
    static const size_t FIELD____head___I4 = 2;
    static const size_t FIELD____tail___I4 = 3;
    static const size_t FIELD____size___I4 = 4;

    static TinyCLR_Result Clear___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result CopyTo___VOID__SystemArray__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Enqueue___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Dequeue___OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Peek___OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Collections_Stack {
    static const size_t FIELD____array___SZARRAY_OBJECT = 1;
    static const size_t FIELD____size___I4 = 2;

    static TinyCLR_Result Clear___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Peek___OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Pop___OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Push___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_ComponentModel_EditorBrowsableAttribute {
    static const size_t FIELD___browsableState___SystemComponentModelEditorBrowsableState = 1;
};

struct Interop_mscorlib_System_Convert {
    static const size_t FIELD_STATIC___s_rgchBase64EncodingDefault___SZARRAY_CHAR = 7;
    static const size_t FIELD_STATIC___s_rgchBase64EncodingRFC4648___SZARRAY_CHAR = 8;
    static const size_t FIELD_STATIC___s_rgchBase64Encoding___SZARRAY_CHAR = 9;
    static const size_t FIELD_STATIC___s_rgbBase64Decode___SZARRAY_U1 = 10;
};

struct Interop_mscorlib_System_TimeZone {
    static const size_t FIELD___m_id___I4 = 1;

    static TinyCLR_Result GetTimeZoneOffset___STATIC___I8(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_CurrentSystemTimeZone {
    static const size_t FIELD___m_ticksOffset___I8 = 2;
};

struct Interop_mscorlib_System_DBNull {
    static const size_t FIELD_STATIC___Value___SystemDBNull = 11;
};

struct Interop_mscorlib_System_DateTime {
    static const size_t FIELD_STATIC___MinValue___SystemDateTime = 12;
    static const size_t FIELD_STATIC___MaxValue___SystemDateTime = 13;
    static const size_t FIELD_STATIC___ticksAtOrigin___I8 = 14;

    static const size_t FIELD___m_ticks___U8 = 1;

    static TinyCLR_Result ctor___VOID__I4__I4__I4__I4__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Day___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_DayOfWeek___SystemDayOfWeek(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_DayOfYear___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Hour___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Millisecond___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Minute___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Month___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Second___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Year___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToLocalTime___SystemDateTime(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToUniversalTime___SystemDateTime(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result DaysInMonth___STATIC___I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Now___STATIC___SystemDateTime(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_UtcNow___STATIC___SystemDateTime(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Today___STATIC___SystemDateTime(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Diagnostics_CodeAnalysis_SuppressMessageAttribute {
    static const size_t FIELD___category___STRING = 1;
    static const size_t FIELD___justification___STRING = 2;
    static const size_t FIELD___checkId___STRING = 3;
    static const size_t FIELD___scope___STRING = 4;
    static const size_t FIELD___target___STRING = 5;
    static const size_t FIELD___messageId___STRING = 6;
};

struct Interop_mscorlib_System_Diagnostics_ConditionalAttribute {
    static const size_t FIELD___m_conditionString___STRING = 1;
};

struct Interop_mscorlib_System_Diagnostics_Contracts_ContractClassAttribute {
    static const size_t FIELD____typeWithContracts___SystemType = 1;
};

struct Interop_mscorlib_System_Diagnostics_Contracts_ContractClassForAttribute {
    static const size_t FIELD____typeIAmAContractFor___SystemType = 1;
};

struct Interop_mscorlib_System_Diagnostics_Contracts_ContractOptionAttribute {
    static const size_t FIELD____category___STRING = 1;
    static const size_t FIELD____setting___STRING = 2;
    static const size_t FIELD____enabled___BOOLEAN = 3;
    static const size_t FIELD____value___STRING = 4;
};

struct Interop_mscorlib_System_Diagnostics_Contracts_ContractPublicPropertyNameAttribute {
    static const size_t FIELD____publicName___STRING = 1;
};

struct Interop_mscorlib_System_Diagnostics_Contracts_ContractVerificationAttribute {
    static const size_t FIELD____value___BOOLEAN = 1;
};

struct Interop_mscorlib_System_Diagnostics_Debugger {
    static TinyCLR_Result get_IsAttached___STATIC___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Break___STATIC___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Log___STATIC___VOID__I4__STRING__STRING(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Diagnostics_DebuggerBrowsableAttribute {
    static const size_t FIELD___state___SystemDiagnosticsDebuggerBrowsableState = 1;
};

struct Interop_mscorlib_System_Diagnostics_DebuggerDisplayAttribute {
    static const size_t FIELD___name___STRING = 1;
    static const size_t FIELD___value___STRING = 2;
    static const size_t FIELD___type___STRING = 3;
    static const size_t FIELD___targetName___STRING = 4;
    static const size_t FIELD___target___SystemType = 5;
};

struct Interop_mscorlib_System_Diagnostics_DebuggerTypeProxyAttribute {
    static const size_t FIELD___typeName___STRING = 1;
    static const size_t FIELD___targetName___STRING = 2;
    static const size_t FIELD___target___SystemType = 3;
};

struct Interop_mscorlib_System_Diagnostics_Trace {
    static const size_t FIELD_STATIC___Listeners__BackingField___SystemDiagnosticsTraceListenerCollection = 15;
};

struct Interop_mscorlib_System_Diagnostics_TraceListenerCollection {
    static const size_t FIELD___list___SystemCollectionsArrayList = 1;
};

struct Interop_mscorlib_System_Double {
    static const size_t FIELD___m_value___R8 = 1;

    static TinyCLR_Result CompareTo___STATIC___I4__R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IsInfinity___STATIC___BOOLEAN__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IsNaN___STATIC___BOOLEAN__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IsNegativeInfinity___STATIC___BOOLEAN__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IsPositiveInfinity___STATIC___BOOLEAN__R8(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Environment {
    static const size_t FIELD_STATIC___NewLine__BackingField___STRING = 16;
};

struct Interop_mscorlib_System_EventArgs {
    static const size_t FIELD_STATIC___Empty___SystemEventArgs = 17;
};

struct Interop_mscorlib_System_GC {
    static TinyCLR_Result AnyPendingFinalizers___STATIC___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SuppressFinalize___STATIC___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ReRegisterForFinalize___STATIC___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Collect___STATIC___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetTotalMemory___STATIC___I8__BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Globalization_CultureInfo {
    static const size_t FIELD_STATIC___InvariantCulture__BackingField___SystemGlobalizationCultureInfo = 18;

    static const size_t FIELD___numInfo___SystemGlobalizationNumberFormatInfo = 1;
    static const size_t FIELD___dateTimeInfo___SystemGlobalizationDateTimeFormatInfo = 2;
    static const size_t FIELD___m_name___STRING = 3;
    static const size_t FIELD___m_rm___SystemResourcesResourceManager = 4;
    static const size_t FIELD___m_parent___SystemGlobalizationCultureInfo = 5;

    static TinyCLR_Result get_CurrentUICultureInternal___STATIC___SystemGlobalizationCultureInfo(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result set_CurrentUICultureInternal___STATIC___VOID__SystemGlobalizationCultureInfo(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Globalization_DateTimeFormat {
    static TinyCLR_Result FormatDigits___STATIC___STRING__I4__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Globalization_DateTimeFormatInfo {
    static const size_t FIELD___amDesignator___STRING = 1;
    static const size_t FIELD___pmDesignator___STRING = 2;
    static const size_t FIELD___dateSeparator___STRING = 3;
    static const size_t FIELD___longTimePattern___STRING = 4;
    static const size_t FIELD___shortTimePattern___STRING = 5;
    static const size_t FIELD___generalShortTimePattern___STRING = 6;
    static const size_t FIELD___generalLongTimePattern___STRING = 7;
    static const size_t FIELD___timeSeparator___STRING = 8;
    static const size_t FIELD___monthDayPattern___STRING = 9;
    static const size_t FIELD___fullDateTimePattern___STRING = 10;
    static const size_t FIELD___longDatePattern___STRING = 11;
    static const size_t FIELD___shortDatePattern___STRING = 12;
    static const size_t FIELD___yearMonthPattern___STRING = 13;
    static const size_t FIELD___abbreviatedDayNames___SZARRAY_STRING = 14;
    static const size_t FIELD___dayNames___SZARRAY_STRING = 15;
    static const size_t FIELD___abbreviatedMonthNames___SZARRAY_STRING = 16;
    static const size_t FIELD___monthNames___SZARRAY_STRING = 17;
    static const size_t FIELD___m_cultureInfo___SystemGlobalizationCultureInfo = 18;
};

struct Interop_mscorlib_System_Globalization_DaylightTime {
    static const size_t FIELD___m_start___SystemDateTime = 1;
    static const size_t FIELD___m_end___SystemDateTime = 2;
    static const size_t FIELD___m_delta___SystemTimeSpan = 3;
};

struct Interop_mscorlib_System_Globalization_NumberFormatInfo {
    static const size_t FIELD___numberGroupSizes___SZARRAY_I4 = 1;
    static const size_t FIELD___positiveSign___STRING = 2;
    static const size_t FIELD___negativeSign___STRING = 3;
    static const size_t FIELD___numberDecimalSeparator___STRING = 4;
    static const size_t FIELD___numberGroupSeparator___STRING = 5;
    static const size_t FIELD___m_cultureInfo___SystemGlobalizationCultureInfo = 6;
};

struct Interop_mscorlib_System_Guid {
    static const size_t FIELD_STATIC___m_rand___SystemRandom = 19;
    static const size_t FIELD_STATIC___Empty___SystemGuid = 20;

    static const size_t FIELD___m_data___SZARRAY_I4 = 1;
};

struct Interop_mscorlib_System_IO_MemoryStream {
    static const size_t FIELD____buffer___SZARRAY_U1 = 1;
    static const size_t FIELD____origin___I4 = 2;
    static const size_t FIELD____position___I4 = 3;
    static const size_t FIELD____length___I4 = 4;
    static const size_t FIELD____capacity___I4 = 5;
    static const size_t FIELD____expandable___BOOLEAN = 6;
    static const size_t FIELD____writable___BOOLEAN = 7;
    static const size_t FIELD____exposable___BOOLEAN = 8;
    static const size_t FIELD____isOpen___BOOLEAN = 9;
};

struct Interop_mscorlib_System_Int16 {
    static const size_t FIELD___m_value___I2 = 1;
};

struct Interop_mscorlib_System_Int32 {
    static const size_t FIELD___m_value___I4 = 1;
};

struct Interop_mscorlib_System_Int64 {
    static const size_t FIELD___m_value___I8 = 1;
};

struct Interop_mscorlib_System_IntPtr {
    static const size_t FIELD_STATIC___Zero___I = 21;

    static const size_t FIELD___value___I4 = 1;
};

struct Interop_mscorlib_System_Math {
    static TinyCLR_Result Acos___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Asin___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Atan___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Atan2___STATIC___R8__R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Ceiling___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Cos___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Cosh___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IEEERemainder___STATIC___R8__R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Exp___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Floor___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Log___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Log10___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Pow___STATIC___R8__R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Round___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Sign___STATIC___I4__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Sin___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Sinh___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Sqrt___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Tan___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Tanh___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Truncate___STATIC___R8__R8(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Number {
    static TinyCLR_Result FormatNative___STATIC___STRING__OBJECT__CHAR__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_ObsoleteAttribute {
    static const size_t FIELD____message___STRING = 1;
    static const size_t FIELD____error___BOOLEAN = 2;
};

struct Interop_mscorlib_System_Random {
    static const size_t FIELD____random___OBJECT = 1;

    static TinyCLR_Result Next___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Next___I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result NextDouble___R8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result NextBytes___VOID__SZARRAY_U1(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_Assembly {
    static TinyCLR_Result get_FullName___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetType___SystemType__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetTypes___SZARRAY_SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetVersion___VOID__BYREF_I4__BYREF_I4__BYREF_I4__BYREF_I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetManifestResourceNames___SZARRAY_STRING(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result GetExecutingAssembly___STATIC___SystemReflectionAssembly(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LoadInternal___STATIC___SystemReflectionAssembly__STRING__BOOLEAN__I4__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Load___STATIC___SystemReflectionAssembly__SZARRAY_U1(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_AssemblyCompanyAttribute {
    static const size_t FIELD___m_company___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyConfigurationAttribute {
    static const size_t FIELD___m_configuration___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyCopyrightAttribute {
    static const size_t FIELD___m_copyright___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyCultureAttribute {
    static const size_t FIELD___m_culture___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyDefaultAliasAttribute {
    static const size_t FIELD___m_defaultAlias___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyDelaySignAttribute {
    static const size_t FIELD___m_delaySign___BOOLEAN = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyDescriptionAttribute {
    static const size_t FIELD___m_description___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyFileVersionAttribute {
    static const size_t FIELD____version___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyFlagsAttribute {
    static const size_t FIELD___m_flags___SystemReflectionAssemblyNameFlags = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyInformationalVersionAttribute {
    static const size_t FIELD___m_informationalVersion___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyKeyFileAttribute {
    static const size_t FIELD___m_keyFile___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyKeyNameAttribute {
    static const size_t FIELD___m_keyName___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyName {
    static const size_t FIELD____assembly___SystemReflectionAssembly = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyProductAttribute {
    static const size_t FIELD___m_product___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyTitleAttribute {
    static const size_t FIELD___m_title___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyTrademarkAttribute {
    static const size_t FIELD___m_trademark___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_AssemblyVersionAttribute {
    static const size_t FIELD___m_version___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_MethodBase {
    static TinyCLR_Result get_Name___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_DeclaringType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsPublic___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsStatic___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsFinal___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsVirtual___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsAbstract___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Invoke___OBJECT__OBJECT__SZARRAY_OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetParameters___SZARRAY_SystemReflectionParameterInfo(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_ConstructorInfo {
    static TinyCLR_Result Invoke___OBJECT__SZARRAY_OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_DefaultMemberAttribute {
    static const size_t FIELD___m_memberName___STRING = 1;
};

struct Interop_mscorlib_System_Reflection_FieldInfo {
    static TinyCLR_Result SetValue___VOID__OBJECT__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_ParameterInfo {
    static const size_t FIELD___ClassImpl___SystemType = 1;
    static const size_t FIELD___PositionImpl___I4 = 2;
};

struct Interop_mscorlib_System_Reflection_PropertyInfo {
    static TinyCLR_Result GetValue___OBJECT__OBJECT__SZARRAY_OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetValue___VOID__OBJECT__OBJECT__SZARRAY_OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_RuntimeFieldInfo {
    static TinyCLR_Result get_Name___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_DeclaringType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_FieldType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetValue___OBJECT__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Reflection_RuntimeMethodInfo {
    static TinyCLR_Result get_ReturnType___SystemType(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Resources_ResourceManager {
    static const size_t FIELD___origBaseName___STRING = 1;
    static const size_t FIELD___origAssembly___SystemReflectionAssembly = 2;
    static const size_t FIELD___currentUICultureName___STRING = 3;
    static const size_t FIELD___m_resourceFileId___I4 = 4;
    static const size_t FIELD___m_assembly___SystemReflectionAssembly = 5;
    static const size_t FIELD___m_baseAssembly___SystemReflectionAssembly = 6;
    static const size_t FIELD___m_baseName___STRING = 7;
    static const size_t FIELD___m_cultureName___STRING = 8;
    static const size_t FIELD___m_rmFallback___SystemResourcesResourceManager = 9;

    static TinyCLR_Result NativeGetObject___OBJECT__I2__I4__I4__BYREF_U4__BYREF_U4__BYREF_U4(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result NativeFindResource___STATIC___I4__STRING__SystemReflectionAssembly(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_CompilerServices_AccessedThroughPropertyAttribute {
    static const size_t FIELD___propertyName___STRING = 1;
};

struct Interop_mscorlib_System_Runtime_CompilerServices_InternalsVisibleToAttribute {
    static const size_t FIELD____assemblyName___STRING = 1;
};

struct Interop_mscorlib_System_Runtime_CompilerServices_MethodImplAttribute {
    static const size_t FIELD____val___SystemRuntimeCompilerServicesMethodImplOptions = 1;
    static const size_t FIELD___MethodCodeType___SystemRuntimeCompilerServicesMethodCodeType = 2;
};

struct Interop_mscorlib_System_Runtime_CompilerServices_RuntimeHelpers {
    static TinyCLR_Result InitializeArray___STATIC___VOID__SystemArray__SystemRuntimeFieldHandle(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetObjectValue___STATIC___OBJECT__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result RunClassConstructor___STATIC___VOID__SystemRuntimeTypeHandle(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_OffsetToStringData___STATIC___I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_Api {
    static const size_t FIELD___Author__BackingField___STRING = 1;
    static const size_t FIELD___Name__BackingField___STRING = 2;
    static const size_t FIELD___Version__BackingField___U8 = 3;
    static const size_t FIELD___Type__BackingField___SystemRuntimeInteropServicesApiType = 4;
    static const size_t FIELD___Implementation__BackingField___I = 5;
    static const size_t FIELD___State__BackingField___I = 6;

    static TinyCLR_Result Add___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Remove___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Find___STATIC___SystemRuntimeInteropServicesApi__STRING__SystemRuntimeInteropServicesApiType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetDefaultSelector___STATIC___STRING__SystemRuntimeInteropServicesApiType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetDefaultSelector___STATIC___VOID__SystemRuntimeInteropServicesApiType__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result FindAll___STATIC___SZARRAY_SystemRuntimeInteropServicesApi(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_ComVisibleAttribute {
    static const size_t FIELD____val___BOOLEAN = 1;
};

struct Interop_mscorlib_System_Runtime_InteropServices_DeviceInformation {
    static const size_t FIELD_STATIC___DeviceName__BackingField___STRING = 22;
    static const size_t FIELD_STATIC___ManufacturerName__BackingField___STRING = 23;
    static const size_t FIELD_STATIC___Version__BackingField___U8 = 24;

    static TinyCLR_Result cctor___STATIC___VOID(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_GuidAttribute {
    static const size_t FIELD____val___STRING = 1;
};

struct Interop_mscorlib_System_Runtime_InteropServices_Interop {
    static const size_t FIELD___Name__BackingField___STRING = 1;
    static const size_t FIELD___Checksum__BackingField___U4 = 2;
    static const size_t FIELD___Methods__BackingField___I = 3;

    static TinyCLR_Result Add___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Remove___STATIC___VOID__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result RaiseEvent___STATIC___VOID__STRING__STRING__U4__U8__U8__I(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result FindAll___STATIC___SZARRAY_SystemRuntimeInteropServicesInterop(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_NativeEventDispatcher {
    static const size_t FIELD_STATIC___instances___SystemCollectionsHashtable = 25;

    static const size_t FIELD___m_threadSpawn___SystemRuntimeInteropServicesNativeEventHandler = 1;
    static const size_t FIELD___m_callbacks___SystemRuntimeInteropServicesNativeEventHandler = 2;
    static const size_t FIELD___m_disposed___BOOLEAN = 3;
    static const size_t FIELD___m_NativeEventDispatcher___OBJECT = 4;
    static const size_t FIELD___name___STRING = 5;

    static TinyCLR_Result ctor___VOID__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result EnableInterrupt___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result DisableInterrupt___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Dispose___VOID__BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_InteropServices_StructLayoutAttribute {
    static const size_t FIELD____val___SystemRuntimeInteropServicesLayoutKind = 1;
    static const size_t FIELD___Pack___I4 = 2;
    static const size_t FIELD___Size___I4 = 3;
    static const size_t FIELD___CharSet___SystemRuntimeInteropServicesCharSet = 4;
};

struct Interop_mscorlib_System_Runtime_InteropServices_SystemTime {
    static TinyCLR_Result SetSystemTime___STATIC___VOID__U8__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_Remoting_RemotingServices {
    static TinyCLR_Result IsTransparentProxy___STATIC___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Runtime_Versioning_TargetFrameworkAttribute {
    static const size_t FIELD____frameworkName___STRING = 1;
    static const size_t FIELD____frameworkDisplayName___STRING = 2;
};

struct Interop_mscorlib_System_Type {
    static TinyCLR_Result get_DeclaringType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetMethod___SystemReflectionMethodInfo__STRING__SystemReflectionBindingFlags(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IsInstanceOfType___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result InvokeMember___OBJECT__STRING__SystemReflectionBindingFlags__SystemReflectionBinder__OBJECT__SZARRAY_OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetConstructor___SystemReflectionConstructorInfo__SZARRAY_SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetMethod___SystemReflectionMethodInfo__STRING__SZARRAY_SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetMethod___SystemReflectionMethodInfo__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsNotPublic___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsPublic___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsClass___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsInterface___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsValueType___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsAbstract___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsEnum___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsSerializable___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsArray___BOOLEAN(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result GetTypeInternal___STATIC___SystemType__STRING__STRING__BOOLEAN__SZARRAY_I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetTypeFromHandle___STATIC___SystemType__SystemRuntimeTypeHandle(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_RuntimeType {
    static TinyCLR_Result get_Assembly___SystemReflectionAssembly(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Name___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_FullName___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_BaseType___SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetMethods___SZARRAY_SystemReflectionMethodInfo__SystemReflectionBindingFlags(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetField___SystemReflectionFieldInfo__STRING__SystemReflectionBindingFlags(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetFields___SZARRAY_SystemReflectionFieldInfo__SystemReflectionBindingFlags(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetInterfaces___SZARRAY_SystemType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetElementType___SystemType(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_SByte {
    static const size_t FIELD___m_value___I1 = 1;
};

struct Interop_mscorlib_System_Single {
    static const size_t FIELD___m_value___R4 = 1;
};

struct Interop_mscorlib_System_String {
    static const size_t FIELD_STATIC___Empty___STRING = 26;

    static TinyCLR_Result CompareTo___I4__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Chars___CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToCharArray___SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToCharArray___SZARRAY_CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Length___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Split___SZARRAY_STRING__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Split___SZARRAY_STRING__SZARRAY_CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Substring___STRING__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Substring___STRING__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Trim___STRING__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result TrimStart___STRING__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result TrimEnd___STRING__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__SZARRAY_CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result CompareTo___I4__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOfAny___I4__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOfAny___I4__SZARRAY_CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOfAny___I4__SZARRAY_CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__STRING__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result IndexOf___I4__STRING__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOfAny___I4__SZARRAY_CHAR(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOfAny___I4__SZARRAY_CHAR__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOfAny___I4__SZARRAY_CHAR__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__STRING__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result LastIndexOf___I4__STRING__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToLower___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToUpper___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Trim___STRING(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result Equals___STATIC___BOOLEAN__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result op_Equality___STATIC___BOOLEAN__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result op_Inequality___STATIC___BOOLEAN__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Compare___STATIC___I4__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Concat___STATIC___STRING__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Concat___STATIC___STRING__STRING__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Concat___STATIC___STRING__STRING__STRING__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Concat___STATIC___STRING__SZARRAY_STRING(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Text_StringBuilder {
    static const size_t FIELD___m_MaxCapacity___I4 = 1;
    static const size_t FIELD___m_ChunkChars___SZARRAY_CHAR = 2;
    static const size_t FIELD___m_ChunkLength___I4 = 3;
    static const size_t FIELD___m_ChunkPrevious___SystemTextStringBuilder = 4;
    static const size_t FIELD___m_ChunkOffset___I4 = 5;
};

struct Interop_mscorlib_System_Text_UTF8Decoder {
    static TinyCLR_Result Convert___VOID__SZARRAY_U1__I4__I4__SZARRAY_CHAR__I4__I4__BOOLEAN__BYREF_I4__BYREF_I4__BYREF_BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Text_UTF8Encoding {
    static TinyCLR_Result GetBytes___SZARRAY_U1__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetBytes___I4__STRING__I4__I4__SZARRAY_U1__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetChars___SZARRAY_CHAR__SZARRAY_U1(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetChars___SZARRAY_CHAR__SZARRAY_U1__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetString___STRING__SZARRAY_U1__I4__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_WaitHandle {
    static TinyCLR_Result WaitOne___BOOLEAN__I4__BOOLEAN(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result WaitMultiple___STATIC___I4__SZARRAY_SystemThreadingWaitHandle__I4__BOOLEAN__BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_AutoResetEvent {
    static TinyCLR_Result ctor___VOID__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Reset___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Set___BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_Interlocked {
    static TinyCLR_Result Increment___STATIC___I4__BYREF_I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Decrement___STATIC___I4__BYREF_I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Exchange___STATIC___I4__BYREF_I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result CompareExchange___STATIC___I4__BYREF_I4__I4__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_ManualResetEvent {
    static TinyCLR_Result ctor___VOID__BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Reset___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Set___BOOLEAN(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_Monitor {
    static TinyCLR_Result Enter___STATIC___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Exit___STATIC___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_Thread {
    static const size_t FIELD___m_Delegate___SystemDelegate = 1;
    static const size_t FIELD___m_Priority___I4 = 2;
    static const size_t FIELD___m_Thread___OBJECT = 3;
    static const size_t FIELD___m_AppDomain___OBJECT = 4;
    static const size_t FIELD___m_Id___I4 = 5;

    static TinyCLR_Result ctor___VOID__SystemThreadingThreadStart(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Start___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Abort___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Suspend___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Resume___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Priority___SystemThreadingThreadPriority(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result set_Priority___VOID__SystemThreadingThreadPriority(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_ManagedThreadId___I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsAlive___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Join___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Join___BOOLEAN__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Join___BOOLEAN__SystemTimeSpan(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_ThreadState___SystemThreadingThreadState(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result Sleep___STATIC___VOID__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_CurrentThread___STATIC___SystemThreadingThread(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetDomain___STATIC___SystemAppDomain(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Threading_Timer {
    static const size_t FIELD___m_timer___OBJECT = 1;
    static const size_t FIELD___m_state___OBJECT = 2;
    static const size_t FIELD___m_callback___SystemThreadingTimerCallback = 3;

    static TinyCLR_Result Dispose___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__SystemThreadingTimerCallback__OBJECT__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__SystemThreadingTimerCallback__OBJECT__SystemTimeSpan__SystemTimeSpan(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Change___BOOLEAN__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Change___BOOLEAN__SystemTimeSpan__SystemTimeSpan(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_TimeSpan {
    static const size_t FIELD_STATIC___Zero___SystemTimeSpan = 27;
    static const size_t FIELD_STATIC___MaxValue___SystemTimeSpan = 28;
    static const size_t FIELD_STATIC___MinValue___SystemTimeSpan = 29;

    static const size_t FIELD___m_ticks___I8 = 1;

    static TinyCLR_Result Equals___BOOLEAN__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ToString___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__I4__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__I4__I4__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result CompareTo___I4__OBJECT(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result Compare___STATIC___I4__SystemTimeSpan__SystemTimeSpan(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Equals___STATIC___BOOLEAN__SystemTimeSpan__SystemTimeSpan(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_UInt16 {
    static const size_t FIELD___m_value___U2 = 1;
};

struct Interop_mscorlib_System_UInt32 {
    static const size_t FIELD___m_value___U4 = 1;
};

struct Interop_mscorlib_System_UInt64 {
    static const size_t FIELD___m_value___U8 = 1;
};

struct Interop_mscorlib_System_UIntPtr {
    static const size_t FIELD_STATIC___Zero___U = 30;

    static const size_t FIELD___value___U4 = 1;
};

struct Interop_mscorlib_System_Version {
    static const size_t FIELD____Major___I4 = 1;
    static const size_t FIELD____Minor___I4 = 2;
    static const size_t FIELD____Build___I4 = 3;
    static const size_t FIELD____Revision___I4 = 4;
};

struct Interop_mscorlib_System_WeakReference {
    static TinyCLR_Result get_IsAlive___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Target___OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result set_Target___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__OBJECT(const TinyCLR_Interop_MethodData md);
};

struct Interop_mscorlib_System_Collections_Hashtable__ValueCollection {
    static const size_t FIELD___ht___SystemCollectionsHashtable = 1;
};

extern const TinyCLR_Interop_Assembly Interop_mscorlib;
