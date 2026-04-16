#include "File.h"

bool dirExistsA(const char dirName[150]) {
    DWORD ftyp = GetFileAttributesA(dirName);
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;
    return false;
}

bool dirExistsW(const TCHAR dirName[150]) {
    DWORD ftyp = GetFileAttributesW(dirName);
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;
    return false;
}

void DeleteFolderA(const char path[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAA FindData;
    char temp[200];
    strncpy_s(temp, path, sizeof(temp) - 1);
    char d[205];
    strncpy_s(d, temp, sizeof(d) - 1);
    strncat_s(d, "/*.*", sizeof(d) - strlen(d) - 1);
    Handle = FindFirstFileA(d, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
            strncpy_s(d, temp, sizeof(d) - 1);
            strncat_s(d, "/", sizeof(d) - strlen(d) - 1);
            strncat_s(d, FindData.cFileName, sizeof(d) - strlen(d) - 1);
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                DeleteFolderA(d);
            else
                DeleteFileA(d);
        }
    } while (FindNextFileA(Handle, &FindData) != 0);
    FindClose(Handle);
    RemoveDirectoryA(path);
}

void DeleteFolderW(const TCHAR path[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAW FindData;
    TCHAR temp[200];
    wcscpy_s(temp, 200, path);
    TCHAR d[205];
    wcscpy_s(d, 205, temp);
    wcscat_s(d, 205, L"/*.*");
    Handle = FindFirstFileW(d, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
            wcscpy_s(d, 205, temp);
            wcscat_s(d, 205, L"/");
            wcscat_s(d, 205, FindData.cFileName);
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                DeleteFolderW(d);
            else
                DeleteFileW(d);
        }
    } while (FindNextFileW(Handle, &FindData) != 0);
    FindClose(Handle);
    RemoveDirectoryW(path);
}

void RemoveFileptrA(FileptrA* pt) {
    if (pt->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        DeleteFolderA(pt->path);
    else
        DeleteFileA(pt->path);
}

void RemoveFileptrW(FileptrW* pt) {
    if (pt->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        DeleteFolderW(pt->path);
    else
        DeleteFileW(pt->path);
}

void CloseFileptrA(FileptrA* f) {
    if (f->File != NULL) {
        CloseHandle(f->File);
        f->File = NULL;
    }
}

void CloseFileptrW(FileptrW* f) {
    if (f->File != NULL) {
        CloseHandle(f->File);
        f->File = NULL;
    }
}

void OpenFileptrA(FileptrA* f, const char path[200], bool dir) {
    strncpy_s(f->path, path, sizeof(f->path) - 1);
    if (dir == true) {
        if (!dirExistsA(path))
            CreateDirectoryA(path, NULL);
    }
    f->File = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if (f->File == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open file", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    GetFileInformationByHandle(f->File, &f->basicInfo);
}

void OpenFileptrW(FileptrW* f, const TCHAR path[200], bool dir) {
    wcscpy_s(f->path, 200, path);
    if (dir == true) {
        if (!dirExistsW(path))
            CreateDirectoryW(path, NULL);
    }
    f->File = CreateFileW(
        path,
        GENERIC_READ,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if (f->File == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open file", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    GetFileInformationByHandle(f->File, &f->basicInfo);
}

void CreateFileptrA(const char path[200], bool dir) {
    if (dir == true) {
        CreateDirectoryA(path, 0);
    } else {
        HANDLE h = CreateFileA(
            path,
            GENERIC_READ,
            FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );
        if (h != INVALID_HANDLE_VALUE)
            CloseHandle(h);
    }
}

void CreateFileptrW(const TCHAR path[200], bool dir) {
    if (dir == true) {
        CreateDirectoryW(path, 0);
    } else {
        HANDLE h = CreateFileW(
            path,
            GENERIC_READ,
            FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );
        if (h != INVALID_HANDLE_VALUE)
            CloseHandle(h);
    }
}

int Search(char s, char* ch, int size) {
    for (int i = 0; i < size; i++) {
        if (ch[i] == s)
            return i;
    }
    return -1;
}

int SearchLast(char s, char* ch, int size) {
    for (int i = size; i >= 0; i--) {
        if (ch[i] == s)
            return i;
    }
    return -1;
}

int SearchLastW(TCHAR s, TCHAR* ch, int size) {
    for (int i = size; i >= 0; i--) {
        if (ch[i] == s)
            return i;
    }
    return -1;
}

void ReNameFileptrA(FileptrA* f, const char newname[50]) {
    int index = SearchLast('/', f->path, (int)strlen(f->path));
    if (index < 0) index = 0;
    int sizenewname = (int)strlen(newname);
    int size = index + 1 + sizenewname;
    char* n = (char*)malloc((size + 1) * sizeof(char));
    if (n == NULL) return;
    for (int i = 0; i < size - sizenewname; i++)
        n[i] = f->path[i];
    for (int i = size - sizenewname; i < size; i++)
        n[i] = newname[i - (size - sizenewname)];
    n[size] = '\0';
    MoveFileA(f->path, n);
    strncpy_s(f->path, n, sizeof(f->path) - 1);
    free(n);
}

void ReNameFileptrW(FileptrW* f, const TCHAR newname[50]) {
    int index = SearchLastW(L'/', f->path, (int)wcslen(f->path));
    if (index < 0) index = 0;
    int sizenewname = (int)wcslen(newname);
    int size = index + 1 + sizenewname;
    TCHAR* n = (TCHAR*)malloc((size + 1) * sizeof(TCHAR));
    if (n == NULL) return;
    for (int i = 0; i < size - sizenewname; i++)
        n[i] = f->path[i];
    for (int i = size - sizenewname; i < size; i++)
        n[i] = newname[i - (size - sizenewname)];
    n[size] = L'\0';
    MoveFileW(f->path, n);
    wcscpy_s(f->path, 200, n);
    free(n);
}

void CopyFolderA(const char papka[50], const char path[200], const char pathcopy[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAA FindData;
    char pathFile[255];
    char pathFile2[255];
    strncpy_s(pathFile, path, sizeof(pathFile) - 1);
    strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
    strncat_s(pathFile, "/*.*", sizeof(pathFile) - strlen(pathFile) - 1);
    Handle = FindFirstFileA(pathFile, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                strncpy_s(pathFile, pathcopy, sizeof(pathFile) - 1);
                strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                CreateDirectoryA(pathFile, NULL);
                strncpy_s(pathFile, papka, sizeof(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                CopyFolderA(pathFile, path, pathcopy);
            } else {
                strncpy_s(pathFile, path, sizeof(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                strncpy_s(pathFile2, pathcopy, sizeof(pathFile2) - 1);
                strncat_s(pathFile2, "/", sizeof(pathFile2) - strlen(pathFile2) - 1);
                strncat_s(pathFile2, papka, sizeof(pathFile2) - strlen(pathFile2) - 1);
                strncat_s(pathFile2, FindData.cFileName, sizeof(pathFile2) - strlen(pathFile2) - 1);
                CopyFileA(pathFile, pathFile2, TRUE);
            }
        }
    } while (FindNextFileA(Handle, &FindData) != 0);
    FindClose(Handle);
}

void CopyFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAW FindData;
    TCHAR pathFile[255];
    TCHAR pathFile2[255];
    wcscpy_s(pathFile, 255, path);
    wcscat_s(pathFile, 255, papka);
    wcscat_s(pathFile, 255, L"/*.*");
    Handle = FindFirstFileW(pathFile, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                wcscpy_s(pathFile, 255, pathcopy);
                wcscat_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, FindData.cFileName);
                CreateDirectoryW(pathFile, NULL);
                wcscpy_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, FindData.cFileName);
                CopyFolderW(pathFile, path, pathcopy);
            } else {
                wcscpy_s(pathFile, 255, path);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, FindData.cFileName);
                wcscpy_s(pathFile2, 255, pathcopy);
                wcscat_s(pathFile2, 255, L"/");
                wcscat_s(pathFile2, 255, papka);
                wcscat_s(pathFile2, 255, FindData.cFileName);
                CopyFileW(pathFile, pathFile2, TRUE);
            }
        }
    } while (FindNextFileW(Handle, &FindData) != 0);
    FindClose(Handle);
}

void CopyFileptrA(FileptrA* f, const char path[200]) {
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        CreateDirectoryA(path, NULL);
        CopyFolderA("", f->path, path);
    } else {
        CopyFileA(f->path, path, TRUE);
    }
}

void CopyFileptrW(FileptrW* f, const TCHAR path[200]) {
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        CreateDirectoryW(path, NULL);
        CopyFolderW(L"", f->path, path);
    } else {
        CopyFileW(f->path, path, TRUE);
    }
}

void TransferFolderA(const char papka[50], const char path[200], const char pathcopy[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAA FindData;
    char pathFile[255];
    char pathFile2[255];
    strncpy_s(pathFile, path, sizeof(pathFile) - 1);
    strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
    strncat_s(pathFile, "/*.*", sizeof(pathFile) - strlen(pathFile) - 1);
    Handle = FindFirstFileA(pathFile, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                strncpy_s(pathFile, pathcopy, sizeof(pathFile) - 1);
                strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                CreateDirectoryA(pathFile, NULL);
                strncpy_s(pathFile, papka, sizeof(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                TransferFolderA(pathFile, path, pathcopy);
            } else {
                strncpy_s(pathFile, path, sizeof(pathFile) - 1);
                strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
                strncat_s(pathFile, FindData.cFileName, sizeof(pathFile) - strlen(pathFile) - 1);
                strncpy_s(pathFile2, pathcopy, sizeof(pathFile2) - 1);
                strncat_s(pathFile2, "/", sizeof(pathFile2) - strlen(pathFile2) - 1);
                strncat_s(pathFile2, papka, sizeof(pathFile2) - strlen(pathFile2) - 1);
                strncat_s(pathFile2, FindData.cFileName, sizeof(pathFile2) - strlen(pathFile2) - 1);
                MoveFileA(pathFile, pathFile2);
            }
        }
    } while (FindNextFileA(Handle, &FindData) != 0);
    FindClose(Handle);
    strncpy_s(pathFile, path, sizeof(pathFile) - 1);
    strncat_s(pathFile, "/", sizeof(pathFile) - strlen(pathFile) - 1);
    strncat_s(pathFile, papka, sizeof(pathFile) - strlen(pathFile) - 1);
    RemoveDirectoryA(pathFile);
}

void TransferFolderW(const TCHAR papka[50], const TCHAR path[200], const TCHAR pathcopy[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAW FindData;
    TCHAR pathFile[255];
    TCHAR pathFile2[255];
    wcscpy_s(pathFile, 255, path);
    wcscat_s(pathFile, 255, papka);
    wcscat_s(pathFile, 255, L"/*.*");
    Handle = FindFirstFileW(pathFile, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    do {
        if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                wcscpy_s(pathFile, 255, pathcopy);
                wcscat_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, FindData.cFileName);
                CreateDirectoryW(pathFile, NULL);
                wcscpy_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, FindData.cFileName);
                TransferFolderW(pathFile, path, pathcopy);
            } else {
                wcscpy_s(pathFile, 255, path);
                wcscat_s(pathFile, 255, L"/");
                wcscat_s(pathFile, 255, papka);
                wcscat_s(pathFile, 255, FindData.cFileName);
                wcscpy_s(pathFile2, 255, pathcopy);
                wcscat_s(pathFile2, 255, L"/");
                wcscat_s(pathFile2, 255, papka);
                wcscat_s(pathFile2, 255, FindData.cFileName);
                MoveFileW(pathFile, pathFile2);
            }
        }
    } while (FindNextFileW(Handle, &FindData) != 0);
    FindClose(Handle);
    wcscpy_s(pathFile, 255, path);
    wcscat_s(pathFile, 255, L"/");
    wcscat_s(pathFile, 255, papka);
    RemoveDirectoryW(pathFile);
}

void TransferFileptrA(FileptrA* f, const char path[200]) {
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        CreateDirectoryA(path, NULL);
        TransferFolderA("", f->path, path);
    } else {
        MoveFileA(f->path, path);
    }
}

void TransferFileptrW(FileptrW* f, const TCHAR path[200]) {
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        CreateDirectoryW(path, NULL);
        TransferFolderW(L"", f->path, path);
    } else {
        MoveFileW(f->path, path);
    }
}

long long int GetFolderSizeA(const char path[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAA FindData;
    DWORDLONG Result = 0;
    char temp[205];
    strncpy_s(temp, path, sizeof(temp) - 1);
    strncat_s(temp, "/*.*", sizeof(temp) - strlen(temp) - 1);
    Handle = FindFirstFileA(temp, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }
    do {
        if (strcmp(FindData.cFileName, ".") != 0 && strcmp(FindData.cFileName, "..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                strncpy_s(temp, path, sizeof(temp) - 1);
                strncat_s(temp, "/", sizeof(temp) - strlen(temp) - 1);
                strncat_s(temp, FindData.cFileName, sizeof(temp) - strlen(temp) - 1);
                Result = Result + GetFolderSizeA(temp);
            } else {
                Result = Result + ((long long int)FindData.nFileSizeHigh << 32) + FindData.nFileSizeLow;
            }
        }
    } while (FindNextFileA(Handle, &FindData) != 0);
    FindClose(Handle);
    return Result;
}

long long int GetFolderSizeW(const TCHAR path[200]) {
    HANDLE Handle;
    WIN32_FIND_DATAW FindData;
    DWORDLONG Result = 0;
    wchar_t temp[205];
    wcscpy_s(temp, 205, path);
    wcscat_s(temp, 205, L"/*.*");
    Handle = FindFirstFileW(temp, &FindData);
    if (Handle == INVALID_HANDLE_VALUE) {
        MessageBoxW(NULL, L"Failed to open folder", L"Error", MB_OK | MB_ICONEXCLAMATION);
        return -1;
    }
    do {
        if (wcscmp(FindData.cFileName, L".") != 0 && wcscmp(FindData.cFileName, L"..") != 0) {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                wcscpy_s(temp, 205, path);
                wcscat_s(temp, 205, L"/");
                wcscat_s(temp, 205, FindData.cFileName);
                Result = Result + GetFolderSizeW(temp);
            } else {
                Result = Result + ((long long int)FindData.nFileSizeHigh << 32) + FindData.nFileSizeLow;
            }
        }
    } while (FindNextFileW(Handle, &FindData) != 0);
    FindClose(Handle);
    return Result;
}

long long int GetSizePtrA(FileptrA* f) {
    long long int dwSize = 0;
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        dwSize = GetFolderSizeA(f->path);
    } else {
        DWORD dwHighSize = 0;
        DWORD dwLowSize = GetFileSize(f->File, &dwHighSize);
        if (dwLowSize == INVALID_FILE_SIZE) {
            MessageBoxW(NULL, L"Failed to get file size", L"Error", MB_OK | MB_ICONEXCLAMATION);
            return -1;
        }
        dwSize = ((long long int)dwHighSize << 32) | dwLowSize;
    }
    return dwSize;
}

long long int GetSizePtrW(FileptrW* f) {
    long long int dwSize = 0;
    if (f->basicInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        dwSize = GetFolderSizeW(f->path);
    } else {
        DWORD dwHighSize = 0;
        DWORD dwLowSize = GetFileSize(f->File, &dwHighSize);
        if (dwLowSize == INVALID_FILE_SIZE) {
            MessageBoxW(NULL, L"Failed to get file size", L"Error", MB_OK | MB_ICONEXCLAMATION);
            return -1;
        }
        dwSize = ((long long int)dwHighSize << 32) | dwLowSize;
    }
    return dwSize;
}