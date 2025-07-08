# FileLibrary

A C library for file and directory operations on Windows systems, providing a comprehensive set of functions for both ANSI (A) and Unicode (W) character sets.

## Overview

FileLibrary is a Windows-specific library that offers a convenient API for common file system operations such as:
- File and directory existence checking
- File creation and deletion
- Directory creation and deletion
- File and directory copying
- File and directory moving/transferring
- File and directory renaming
- Size querying for files and directories

The library supports both ANSI and Unicode character sets, with parallel functions designated by 'A' and 'W' suffixes respectively.

## Data Structures

The library defines two main structures:

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

These structures serve as handles for file operations throughout the library.

## API Reference

### Directory Operations

* `dirExistsA`/`dirExistsW` - Check if a directory exists
* `DeleteFolderA`/`DeleteFolderW` - Delete a directory
* `CreateFileptrA`/`CreateFileptrW` - Create a file or directory
* `CopyFolderA`/`CopyFolderW` - Copy a directory
* `TransferFolderA`/`TransferFolderW` - Move a directory
* `GetFolderSizeA`/`GetFolderSizeW` - Get the size of a directory

### File Operations

* `OpenFileptrA`/`OpenFileptrW` - Open a file
* `CloseFileptrA`/`CloseFileptrW` - Close a file
* `RemoveFileptrA`/`RemoveFileptrW` - Delete a file
* `ReNameFileptrA`/`ReNameFileptrW` - Rename a file
* `CopyFileptrA`/`CopyFileptrW` - Copy a file
* `TransferFileptrA`/`TransferFileptrW` - Move a file
* `GetSizePtrA`/`GetSizePtrW` - Get the size of a file

## Usage Notes

- All functions with 'A' suffix work with ANSI character strings
- All functions with 'W' suffix work with Unicode (wide) character strings
- Functions with the `dir` parameter set to `true` operate on directories, otherwise on files
- Path strings are limited to 200 characters
- Directory names are limited to 150 characters

## Building

This library is designed to be built as a Windows DLL.

## Compatibility

This library is specifically designed for Windows systems and utilizes the Windows API for file operations.
