#pragma once

#include <TinyCLR.h>

struct Interop_GHIElectronics_TinyCLR_IO___PrivateImplementationDetails_ {
    static const size_t FIELD_STATIC___02238EAE0F35A646D395C25C02100357EE9909E1___PrivateImplementationDetailsStaticArrayInitTypeSize74 = 0;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileSystemManager {
    static const size_t FIELD_STATIC___m_openFiles___mscorlibSystemCollectionsArrayList = 1;
    static const size_t FIELD_STATIC___m_lockedDirs___mscorlibSystemCollectionsArrayList = 2;
    static const size_t FIELD_STATIC___CurrentDirectory___STRING = 3;
    static const size_t FIELD_STATIC___m_currentDirectoryRecord___OBJECT = 4;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileSystemManager__FileRecord {
    static const size_t FIELD___FullName___STRING = 1;
    static const size_t FIELD___NativeFileStream___GHIElectronicsTinyCLRIOIFileStream = 2;
    static const size_t FIELD___Share___I4 = 3;
};

struct Interop_GHIElectronics_TinyCLR_IO_GHIElectronics_TinyCLR_IO_FileSystem {
    static TinyCLR_Result FlushAll___STATIC___VOID__I__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Initialize___STATIC___VOID__I__I4__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Uninitialize___STATIC___BOOLEAN__I__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_IO_GHIElectronics_TinyCLR_IO_FileSystemEntry {
    static const size_t FIELD___Attributes__BackingField___SystemIOFileAttributes = 1;
    static const size_t FIELD___CreationTime__BackingField___mscorlibSystemDateTime = 2;
    static const size_t FIELD___LastAccessTime__BackingField___mscorlibSystemDateTime = 3;
    static const size_t FIELD___LastWriteTime__BackingField___mscorlibSystemDateTime = 4;
    static const size_t FIELD___Size__BackingField___I8 = 5;
    static const size_t FIELD___FileName__BackingField___STRING = 6;
};

struct Interop_GHIElectronics_TinyCLR_IO_GHIElectronics_TinyCLR_IO_NativeFileSystemEntryFinder {
    static const size_t FIELD___implPtr___I = 1;
    static const size_t FIELD___m_ff___OBJECT = 2;

    static TinyCLR_Result GHIElectronics_TinyCLR_IO_IFileSystemEntryFinder_Close___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GHIElectronics_TinyCLR_IO_IFileSystemEntryFinder_GetNext___GHIElectronicsTinyCLRIOFileSystemEntry(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__STRING__STRING(const TinyCLR_Interop_MethodData md);

    static TinyCLR_Result GetFileInfo___STATIC___GHIElectronicsTinyCLRIOFileSystemEntry__STRING(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_IO_GHIElectronics_TinyCLR_IO_FileSystem__NativeDriveProvider {
    static const size_t FIELD___Name__BackingField___STRING = 1;

    static TinyCLR_Result get_DriveType___SystemIODriveType(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_DriveFormat___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_IsReady___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_AvailableFreeSpace___I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_TotalFreeSpace___I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_TotalSize___I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_VolumeLabel___STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result CreateDirectory___VOID__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Delete___VOID__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetAttributes___SystemIOFileAttributes__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result GetFileSystemEntry___GHIElectronicsTinyCLRIOFileSystemEntry__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Move___BOOLEAN__STRING__STRING(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result SetAttributes___VOID__STRING__SystemIOFileAttributes(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_IO_GHIElectronics_TinyCLR_IO_FileSystem__NativeFileStream {
    static const size_t FIELD___impl___I = 1;
    static const size_t FIELD___obj___OBJECT = 2;

    static TinyCLR_Result get_CanWrite___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_CanRead___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_CanSeek___BOOLEAN(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result get_Length___I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result set_Length___VOID__I8(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Close___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Flush___VOID(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Read___I4__SZARRAY_U1__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Seek___I8__I8__mscorlibSystemIOSeekOrigin(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result Write___I4__SZARRAY_U1__I4__I4__I4(const TinyCLR_Interop_MethodData md);
    static TinyCLR_Result ctor___VOID__STRING__I4(const TinyCLR_Interop_MethodData md);
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileSystemInfo {
    static const size_t FIELD___m_fullPath___STRING = 1;
    static const size_t FIELD____nativeFileInfo___GHIElectronicsTinyCLRIOFileSystemEntry = 2;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_DriveInfo {
    static const size_t FIELD_STATIC___driveProviders___mscorlibSystemCollectionsHashtable = 5;
    static const size_t FIELD_STATIC___driveNames___mscorlibSystemCollectionsStack = 6;

    static const size_t FIELD___provider___GHIElectronicsTinyCLRIOIDriveProvider = 1;
    static const size_t FIELD___Name__BackingField___STRING = 2;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileEnum {
    static const size_t FIELD___m_findFile___GHIElectronicsTinyCLRIOIFileSystemEntryFinder = 1;
    static const size_t FIELD___m_currentFile___GHIElectronicsTinyCLRIOFileSystemEntry = 2;
    static const size_t FIELD___m_flags___SystemIOFileEnumFlags = 3;
    static const size_t FIELD___m_path___STRING = 4;
    static const size_t FIELD___m_disposed___BOOLEAN = 5;
    static const size_t FIELD___m_openForReadHandle___OBJECT = 6;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileEnumerator {
    static const size_t FIELD___m_path___STRING = 1;
    static const size_t FIELD___m_flags___SystemIOFileEnumFlags = 2;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_FileStream {
    static const size_t FIELD____nativeFileStream___GHIElectronicsTinyCLRIOIFileStream = 1;
    static const size_t FIELD____fileRecord___SystemIOFileSystemManagerFileRecord = 2;
    static const size_t FIELD____fileName___STRING = 3;
    static const size_t FIELD____seekLimit___I8 = 4;
    static const size_t FIELD____disposed___BOOLEAN = 5;
    static const size_t FIELD___isReadOnly___BOOLEAN = 6;
    static const size_t FIELD___wantsRead___BOOLEAN = 7;
    static const size_t FIELD___wantsWrite___BOOLEAN = 8;
    static const size_t FIELD___drive___GHIElectronicsTinyCLRIOIDriveProvider = 9;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_Path {
    static const size_t FIELD_STATIC___DirectorySeparatorChar___CHAR = 7;
    static const size_t FIELD_STATIC___InvalidPathChars___SZARRAY_CHAR = 8;
    static const size_t FIELD_STATIC___m_illegalCharacters___SZARRAY_CHAR = 9;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_StreamReader {
    static const size_t FIELD___m_stream___mscorlibSystemIOStream = 1;
    static const size_t FIELD___m_decoder___mscorlibSystemTextDecoder = 2;
    static const size_t FIELD___m_singleCharBuff___SZARRAY_CHAR = 3;
    static const size_t FIELD___m_disposed___BOOLEAN = 4;
    static const size_t FIELD___m_buffer___SZARRAY_U1 = 5;
    static const size_t FIELD___m_curBufPos___I4 = 6;
    static const size_t FIELD___m_curBufLen___I4 = 7;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_TextWriter {
    static const size_t FIELD___CoreNewLine___SZARRAY_CHAR = 1;
};

struct Interop_GHIElectronics_TinyCLR_IO_System_IO_StreamWriter {
    static const size_t FIELD___m_stream___mscorlibSystemIOStream = 2;
    static const size_t FIELD___m_disposed___BOOLEAN = 3;
    static const size_t FIELD___m_buffer___SZARRAY_U1 = 4;
    static const size_t FIELD___m_curBufPos___I4 = 5;
};

extern const TinyCLR_Interop_Assembly Interop_GHIElectronics_TinyCLR_IO;
