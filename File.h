#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string.h>

#ifdef FILELIBRARY_EXPORTS
#define FILELIBRARY_API __declspec(dllexport)
#else
#define FILELIBRARY_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

typedef FILELIBRARY_API struct FileptrA
{
    HANDLE File;
    char path[200];
    BY_HANDLE_FILE_INFORMATION basicInfo;
} FileptrA;

typedef FILELIBRARY_API struct FileptrW
{
    HANDLE File;
    TCHAR path[200];
    BY_HANDLE_FILE_INFORMATION basicInfo;
} FileptrW;

FILELIBRARY_API bool          dirExistsA(const char dirName[150]);
FILELIBRARY_API bool          dirExistsW(const TCHAR dirName[150]);
FILELIBRARY_API void          OpenFileptrA(FileptrA* f, const char path[200], bool dir);
FILELIBRARY_API void          OpenFileptrW(FileptrW* f, const TCHAR path[200], bool dir);
FILELIBRARY_API void          CloseFileptrA(FileptrA* f);
FILELIBRARY_API void          CloseFileptrW(FileptrW* f);
FILELIBRARY_API void          RemoveFileptrA(FileptrA* pt);
FILELIBRARY_API void          RemoveFileptrW(FileptrW* pt);
FILELIBRARY_API void          DeleteFolderA(const char path[200]);
FILELIBRARY_API void          DeleteFolderW(const TCHAR path[200]);
FILELIBRARY_API void          CreateFileptrA(const char path[200], bool dir);
FILELIBRARY_API void          CreateFileptrW(const TCHAR path[200], bool dir);
FILELIBRARY_API void          ReNameFileptrA(FileptrA* f, const char newname[50]);
FILELIBRARY_API void          ReNameFileptrW(FileptrW* f, const TCHAR newname[50]);
FILELIBRARY_API void          CopyFileptrA(FileptrA* f, const char path[200]);
FILELIBRARY_API void          CopyFileptrW(FileptrW* f, const TCHAR path[200]);
FILELIBRARY_API void          TransferFileptrA(FileptrA* f, const char path[200]);
FILELIBRARY_API void          TransferFileptrW(FileptrW* f, const TCHAR path[200]);
FILELIBRARY_API long long int GetSizePtrA(FileptrA* f);
FILELIBRARY_API long long int GetSizePtrW(FileptrW* f);

#ifdef __cplusplus
}
#endif