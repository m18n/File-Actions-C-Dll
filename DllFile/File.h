#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<string.h>
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
			  // used by C++ source code
#else//C
#include<stdbool.h>
#endif
typedef MATHLIBRARY_API  struct FileptrA
{
		HANDLE File;
		char path[200];
		BY_HANDLE_FILE_INFORMATION basicInfo;
}FileptrA;
typedef MATHLIBRARY_API  struct FileptrW
{
	HANDLE File;
	TCHAR path[200];
	BY_HANDLE_FILE_INFORMATION basicInfo;
}FileptrW;
MATHLIBRARY_API bool  dirExistsA(const char dirName[150]);
MATHLIBRARY_API bool  dirExistsW(const TCHAR dirName[150]);
MATHLIBRARY_API void  OpenFileptrA(FileptrA* f, const char path[200], bool dir);
MATHLIBRARY_API void  OpenFileptrW(FileptrW* f, const TCHAR path[200], bool dir);
MATHLIBRARY_API void  CloseFileptrA(FileptrA* f);
MATHLIBRARY_API void  CloseFileptrW(FileptrW* f);
MATHLIBRARY_API void  RemoveFileptrA(FileptrA* pt);
MATHLIBRARY_API void  RemoveFileptrW(FileptrW* pt);
MATHLIBRARY_API void  DeleteFolderA(const char path[200]);
MATHLIBRARY_API void  DeleteFolderW(const TCHAR path[200]);
MATHLIBRARY_API void  CreateFileptrA(const char path[200], bool dir);
MATHLIBRARY_API void  CreateFileptrW(const TCHAR path[200], bool dir);
MATHLIBRARY_API void  ReNameFileptrA(FileptrA * f, const char newname[50]);
MATHLIBRARY_API void  ReNameFileptrW(FileptrW * f, const TCHAR newname[50]);
MATHLIBRARY_API void  CopyFileptrA(FileptrA * f, const char path[200]);
MATHLIBRARY_API void  CopyFileptrW(FileptrW * f, const TCHAR path[200]);
MATHLIBRARY_API void  CopyFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]);
MATHLIBRARY_API void  CopyFolderA(const char papka[50], const char path[200], const char pathcopy[200]);
MATHLIBRARY_API void  TransferFileptrA(FileptrA * f, const char path[200]);
MATHLIBRARY_API void  TransferFileptrW(FileptrW * f, const TCHAR path[200]);
MATHLIBRARY_API void  TransferFolderA(const char papka[50], const char path[200], const char pathcopy[200]);
MATHLIBRARY_API void  TransferFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]);
MATHLIBRARY_API long long int   GetSizePtrA(FileptrA * f);
MATHLIBRARY_API long long int   GetSizePtrW(FileptrW * f);
MATHLIBRARY_API long long int   GetFolderSizeA(const char path[200]);
MATHLIBRARY_API long long int   GetFolderSizeW(const TCHAR path[200]);
#ifdef __cplusplus
}
#endif