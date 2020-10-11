#include "File.h"

bool dirExistsA(const char dirName[150]) {
		DWORD ftyp = GetFileAttributesA(dirName);
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!

		if (ftyp == FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!

		return false;    // this is not a directory!
	}
bool dirExistsW(const TCHAR dirName[150]) {
	DWORD ftyp = GetFileAttributesW(dirName);
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp == FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
void DeleteFolderA(const char path[200])
	{
		HANDLE Handle;
		WIN32_FIND_DATAA FindData;
		DWORDLONG Result = 0;
		char temp[200];
		strcpy(temp, path);
		char d[205];
		strcpy(d, temp);
		strcat(d, "/*.*");
		Handle = FindFirstFileA(d, &FindData);
		if (Handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Не удалось открыть файл",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		do
		{

			if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
				strcpy(d, temp);
				strcat(d, "/");
				strcat(d, FindData.cFileName);
				if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
					DeleteFolderA(d);
				else {
					DeleteFileA(d);
				}
			}
		} while (FindNextFileA(Handle, &FindData) != 0);
		FindClose(Handle);
		RemoveDirectoryA(path);
}
void DeleteFolderW(const TCHAR path[200])
{
	HANDLE Handle;
	WIN32_FIND_DATAW FindData;
	DWORDLONG Result = 0;
	TCHAR temp[200];
	wcscpy_s(temp, path);
	TCHAR d[205];
	wcscpy_s(d, temp);
	wcscat_s(d, L"/*.*");
	Handle = FindFirstFileW(d, &FindData);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось открыть файл",
			L"Ошибка",
			MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	do
	{

		if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
			wcscpy_s(d, temp);
			wcscat_s(d, L"/");
			wcscat_s(d, FindData.cFileName);
			if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				DeleteFolderW(d);
			else {
				DeleteFileW(d);
			}
		}
	} while (FindNextFileW(Handle, &FindData) != 0);
	FindClose(Handle);
	RemoveDirectoryW(path);
}
void RemoveFileptrA(FileptrA* pt) {
	if (pt->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			DeleteFolderA(pt->path);
	}
	else {
			DeleteFileA(pt->path);
	}
}
void RemoveFileptrW(FileptrW* pt) {
	if (pt->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		DeleteFolderW(pt->path);
	}
	else {
		DeleteFileW(pt->path);
	}
}
void CloseFileptrA(FileptrA* f) {
	if (f->File != NULL) {
		CloseHandle(f->File);
		f->File = NULL;
	}
}
void CloseFileptrW(FileptrW* f) {
	if (f->File != NULL){
		CloseHandle(f->File);
		f->File = NULL;
	}
}
void OpenFileptrA(FileptrA* f, const char path[200], bool dir) {
		strcpy(f->path, path);
		if (dir == true) {
			if (!dirExistsA(path)) {
				CreateDirectoryA(path, NULL);
			}
		}
		f->File = CreateFileA(path,
			GENERIC_READ,
			FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);
		if (f->File == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Не удалось открыть файл",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
		}
		GetFileInformationByHandle(f->File, &f->basicInfo);
	}
void OpenFileptrW(FileptrW* f, const TCHAR path[200], bool dir) {
	wcscpy_s(f->path, path);
	if (dir == true) {
		if (!dirExistsW(path)) {
			CreateDirectoryW(path, NULL);
		}
	}
	f->File = CreateFileW(path,
		GENERIC_READ,
		FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (f->File == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось открыть файл",
			L"Ошибка",
			MB_OK | MB_ICONEXCLAMATION);
	}
	GetFileInformationByHandle(f->File, &f->basicInfo);
}
void CreateFileptrA(const char path[200], bool dir) {
		if (dir == true)
			CreateDirectoryA(path, 0);
		else {
			HANDLE h = CreateFileA(path,
				GENERIC_READ,
				FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_ALWAYS,
				FILE_FLAG_BACKUP_SEMANTICS,
				NULL);
			CloseHandle(h);
		}
}
void CreateFileptrW(const TCHAR path[200], bool dir) {
	if (dir == true)
		CreateDirectoryW(path, 0);
	else {
		HANDLE h = CreateFileW(path,
			GENERIC_READ,
			FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);
		CloseHandle(h);
	}
}
int  Search(char s, char* ch, int size) {
		for (int i = 0; i < size; i++) {
			if (ch[i] == s)
				return i;
		}
	}
int  SearchLast(char s, char* ch, int size) {
		for (int i = size; i >= 0; i--) {
			if (ch[i] == s)
				return i;
		}
	}
int  SearchLastW(TCHAR s, TCHAR* ch, int size) {
	for (int i = size; i >= 0; i--) {
		if (ch[i] == s)
			return i;
	}
}
void ReNameFileptrA(FileptrA* f, const char newname[50]) {
		int index = SearchLast('/', f->path, strlen(f->path));
		int sizenewname = strlen(newname);
		int size = index + 1 + sizenewname;
		char* n = (char*)malloc(size + 1);
		for (int i = 0; i < size - sizenewname; i++) {
			n[i] = f->path[i];
		}
		for (int i = size - sizenewname; i < size; i++) {
			n[i] = newname[i - (size - sizenewname)];
		}
		n[size] = '\0';
		MoveFileA(f->path, n);
		strcpy(f->path, n);
		free(n);
	}
void ReNameFileptrW(FileptrW* f, const TCHAR newname[50]) {
	int index = SearchLastW('/', f->path, wcslen(f->path));
	int sizenewname = wcslen(newname);
	int size = index + 1 + sizenewname;
	TCHAR* n = (TCHAR*)malloc(size + 1);
	for (int i = 0; i < size - sizenewname; i++) {
		n[i] = f->path[i];
	}
	for (int i = size - sizenewname; i < size; i++) {
		n[i] = newname[i - (size - sizenewname)];
	}
	n[size] = '\0';
	MoveFileW(f->path, n);
	wcscpy_s(f->path, n);
	free(n);
}
void CopyFolderA(const char papka[50], const char path[200], const char pathcopy[200]) {
		HANDLE Handle;
		WIN32_FIND_DATAA FindData;
		DWORDLONG Result = 0;
		char pathFile[255];
		char pathFile2[255];
		strcpy(pathFile, path);
		strcat(pathFile, papka);
		strcat(pathFile, "/*.*");

		Handle = FindFirstFileA(pathFile, &FindData);
		if (Handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Не удалось открыть файл",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		do
		{
			if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {

				if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
					strcpy(pathFile, pathcopy);
					strcat(pathFile, papka);
					strcat(pathFile, "/");
					strcat(pathFile, FindData.cFileName);
					CreateDirectoryA(pathFile, NULL);
					strcpy(pathFile, papka);
					strcat(pathFile, "/");
					strcat(pathFile, FindData.cFileName);
					CopyFolderA(pathFile, path, pathcopy);
				}
				else {
					strcpy(pathFile, path);
					strcat(pathFile, "/");
					strcat(pathFile, papka);
					strcat(pathFile, FindData.cFileName);
					strcpy(pathFile2, pathcopy);
					strcat(pathFile2, "/");
					strcat(pathFile2, papka);
					strcat(pathFile2, FindData.cFileName);
					CopyFileA(pathFile,
						pathFile2, true);
				}
			}
		} while (FindNextFileA(Handle, &FindData) != 0);
		FindClose(Handle);

}
void CopyFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]) {
	HANDLE Handle;
	WIN32_FIND_DATAW FindData;
	DWORDLONG Result = 0;
	TCHAR pathFile[255];
	TCHAR pathFile2[255];
	wcscpy_s(pathFile, path);
	wcscat_s(pathFile, papka);
	wcscat_s(pathFile, L"/*.*");

	Handle = FindFirstFileW(pathFile, &FindData);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось открыть файл",
			L"Ошибка",
			MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	do
	{
		if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {

			if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				wcscpy_s(pathFile, pathcopy);
				wcscat_s(pathFile, papka);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, FindData.cFileName);
				CreateDirectoryW(pathFile, NULL);
				wcscpy_s(pathFile, papka);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, FindData.cFileName);
				CopyFolderW(pathFile, path, pathcopy);
			}
			else {
				wcscpy_s(pathFile, path);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, papka);
				wcscat_s(pathFile, FindData.cFileName);
				wcscpy_s(pathFile2, pathcopy);
				wcscat_s(pathFile2, L"/");
				wcscat_s(pathFile2, papka);
				wcscat_s(pathFile2, FindData.cFileName);
				CopyFileW(pathFile,
					pathFile2, true);
			}
		}
	} while (FindNextFileW(Handle, &FindData) != 0);
	FindClose(Handle);

}
void CopyFileptrA(FileptrA* f, const char path[200]) {
		if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			CreateDirectoryA(path, NULL);
			CopyFolderA("", f->path, path);
		}
		else
			CopyFileA(f->path, path, true);

}
void CopyFileptrW(FileptrW* f, const TCHAR path[200]) {
	if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		CreateDirectoryW(path, NULL);
		CopyFolderW(L"", f->path, path);
	}
	else
		CopyFileW(f->path, path, true);

}
void TransferFolderA(const char papka[50], const char path[200], const char pathcopy[200]) {
		HANDLE Handle;
		WIN32_FIND_DATAA FindData;
		DWORDLONG Result = 0;
		char pathFile[255];
		char pathFile2[255];
		strcpy(pathFile, path);
		strcat(pathFile, papka);
		strcat(pathFile, "/*.*");
		Handle = FindFirstFileA(pathFile, &FindData);
		if (Handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Не удалось открыть файл",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		do
		{
			if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
				if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
					strcpy(pathFile, pathcopy);
					strcat(pathFile, papka);
					strcat(pathFile, "/");
					strcat(pathFile, FindData.cFileName);
					CreateDirectoryA(pathFile, NULL);
					strcpy(pathFile, papka);
					strcat(pathFile, "/");
					strcat(pathFile, FindData.cFileName);
					TransferFolderA(pathFile, path, pathcopy);
				}
				else {
					strcpy(pathFile, path);
					strcat(pathFile, "/");
					strcat(pathFile, papka);
					strcat(pathFile, FindData.cFileName);
					strcpy(pathFile2, pathcopy);
					strcat(pathFile2, "/");
					strcat(pathFile2, papka);
					strcat(pathFile2, FindData.cFileName);
					MoveFileA(pathFile,
						pathFile2);
				}
			}
		} while (FindNextFileA(Handle, &FindData) != 0);
		FindClose(Handle);
		strcpy(pathFile, path);
		strcat(pathFile, "/");
		strcat(pathFile, papka);
		RemoveDirectoryA(pathFile);
	}
void TransferFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]) {
	HANDLE Handle;
	WIN32_FIND_DATAW FindData;
	DWORDLONG Result = 0;
	TCHAR pathFile[255];
	TCHAR pathFile2[255];

	wcscpy_s(pathFile, path);
	wcscat_s(pathFile, papka);
	wcscat_s(pathFile, L"/*.*");
	Handle = FindFirstFileW(pathFile, &FindData);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось открыть файл",
			L"Ошибка",
			MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	do
	{
		if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
			if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				wcscpy_s(pathFile, pathcopy);
				wcscat_s(pathFile, papka);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, FindData.cFileName);
				CreateDirectoryW(pathFile, NULL);
				wcscpy_s(pathFile, papka);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, FindData.cFileName);
				TransferFolderW(pathFile, path, pathcopy);
			}
			else {
				wcscpy_s(pathFile, path);
				wcscat_s(pathFile, L"/");
				wcscat_s(pathFile, papka);
				wcscat_s(pathFile, FindData.cFileName);
				wcscpy_s(pathFile2, pathcopy);
				wcscat_s(pathFile2, L"/");
				wcscat_s(pathFile2, papka);
				wcscat_s(pathFile2, FindData.cFileName);
				MoveFileW(pathFile,
					pathFile2);
			}
		}
	} while (FindNextFileW(Handle, &FindData) != 0);
	FindClose(Handle);
	wcscpy_s(pathFile, path);
	wcscat_s(pathFile, L"/");
	wcscat_s(pathFile, papka);
	RemoveDirectoryW(pathFile);
}
void TransferFileptrA(FileptrA* f, const char path[200]) {
		if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			CreateDirectoryA(path, NULL);
			TransferFolderA("", f->path, path);
		}
		else
			MoveFileA(f->path, path);
	}
void TransferFileptrW(FileptrW* f, const TCHAR path[200]) {
	if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		CreateDirectoryW(path, NULL);
		TransferFolderW(L"", f->path, path);
	}
	else
		MoveFileW(f->path, path);
}
long long int  GetFolderSizeA(const char path[200])
	{
		HANDLE Handle;
		WIN32_FIND_DATAA FindData;
		DWORDLONG Result = 0;
		char temp[205];
		strcpy(temp, path);
		strcat(temp, "/*.*");
		Handle = FindFirstFileA(temp, &FindData);
		if (Handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, L"Не удалось открыть файл",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}

		do
		{
			if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
				if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
					strcpy(temp, path);
					strcat(temp, "/");
					strcat(temp, FindData.cFileName);
					Result = Result + GetFolderSizeA(temp);
				}
				else
					Result = Result + ((long long int)FindData.nFileSizeHigh << 32) + FindData.nFileSizeLow;
			}
		} while (FindNextFileA(Handle, &FindData) != 0);
		FindClose(Handle);
		return Result;
	}
long long int  GetFolderSizeW(const TCHAR path[200])
{
	HANDLE Handle;
	WIN32_FIND_DATAW FindData;
	DWORDLONG Result = 0;
	wchar_t temp[205];
	wcscpy_s(temp, path);
	wcscat_s(temp, L"/*.*");
	Handle = FindFirstFileW(temp, &FindData);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось открыть файл",
			L"Ошибка",
			MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	do
	{
		if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
			if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				wcscpy_s(temp, path);
				wcscat_s(temp, L"/");
				wcscat_s(temp, FindData.cFileName);
				Result = Result + GetFolderSizeW(temp);
			}
			else
				Result = Result + ((long long int)FindData.nFileSizeHigh << 32) + FindData.nFileSizeLow;
		}
	} while (FindNextFileW(Handle, &FindData) != 0);
	FindClose(Handle);
	return Result;
}
long long int  GetSizePtrA(FileptrA* f) {
		long long int dwSize;
		if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			dwSize = GetFolderSizeA(f->path);
		}
		else {
			dwSize = GetFileSize(f->File, NULL);
			if (dwSize == INVALID_FILE_SIZE)
			{
				DWORD dwError = GetLastError();
				MessageBox(NULL, L"Не удалось определить размер файла",
					L"Ошибка",
					MB_OK | MB_ICONEXCLAMATION);
			}
		}
		return dwSize;
	}
long long int  GetSizePtrW(FileptrW* f) {
	long long int dwSize;
	if (f->basicInfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
		dwSize = GetFolderSizeW(f->path);
	}
	else {
		dwSize = GetFileSize(f->File, NULL);
		if (dwSize == INVALID_FILE_SIZE)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, L"Не удалось определить размер файла",
				L"Ошибка",
				MB_OK | MB_ICONEXCLAMATION);
		}
	}
	return dwSize;
}