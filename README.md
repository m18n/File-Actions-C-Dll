# FILELIBRARY

A C library for file and directory operations on Windows systems, providing functions for both ANSI (A) and Unicode (W) character sets. This project was created in 2020. It is an older project and does not reflect my current coding standards.

## Overview

FileLibrary is a Windows-specific DLL that offers an API for common file system operations:
- File and directory existence checking
- File and directory creation and deletion
- File and directory copying and moving
- File and directory renaming
- Size querying for files and directories

## Data Structures

### FileptrA
```c
typedef struct FileptrA
{
    HANDLE File;
    char path[200];
    BY_HANDLE_FILE_INFORMATION basicInfo;
} FileptrA;
```

### FileptrW
```c
typedef struct FileptrW
{
    HANDLE File;
    TCHAR path[200];
    BY_HANDLE_FILE_INFORMATION basicInfo;
} FileptrW;
```

## API Reference

| Function | Description |
|----------|-------------|
| `dirExistsA` / `dirExistsW` | Check if a directory exists |
| `CreateFileptrA` / `CreateFileptrW` | Create a file or directory |
| `OpenFileptrA` / `OpenFileptrW` | Open a file or directory into a `Fileptr` |
| `CloseFileptrA` / `CloseFileptrW` | Close a `Fileptr` handle |
| `RemoveFileptrA` / `RemoveFileptrW` | Delete a file or directory via `Fileptr` |
| `DeleteFolderA` / `DeleteFolderW` | Recursively delete a directory by path |
| `ReNameFileptrA` / `ReNameFileptrW` | Rename a file or directory via `Fileptr` |
| `CopyFileptrA` / `CopyFileptrW` | Copy a file or directory via `Fileptr` |
| `TransferFileptrA` / `TransferFileptrW` | Move a file or directory via `Fileptr` |
| `GetSizePtrA` / `GetSizePtrW` | Get size (bytes) of a file or directory via `Fileptr` |

## Usage Notes

- Functions suffixed with `A` accept ANSI strings (`char*`)
- Functions suffixed with `W` accept Unicode strings (`TCHAR*`/`wchar_t*`)
- Path strings are limited to **200 characters**
- Directory name strings are limited to **150 characters**
- `OpenFileptrA`/`OpenFileptrW` with `dir = true` will create the directory if it does not exist

## Compatibility

Windows only. Requires linking against the Windows API.