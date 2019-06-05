#pragma once
#include "stdafx.h"
#include "resource.h"

#define HEADER_LENGTH 200 // Defines header size. 200 is a pretty good number for that or anything else the header might be used for.
#define FILENAME_BUFFER 100 // First 100 bytes of header reserved for filename.

// Saves server file to disk.
void SaveServerFile(ULONG cbSize, BYTE *pBuffer, const char* fullPath);

// Reads a data stream containing a file. The first HEADER_LENGTH bytes represent a header containing the filename.
void ReadDataStream(ULONG cbSize, BYTE *pBuffer, const char* savePath);

// ConvertULONGtoBYTEbuffer is a cross platform compatible converter to convert the value of a ULONG to a Byte array. Prevents weird endian issues. 
void ConvertULONGtoBYTEbuffer(BYTE* buffer[], ULONG value);

// BYTElen is just a simple ULONG version of strlen so I do not get complier warnings.
// Not using seems to cause 64/32 bit issues. Simple casting will still compile but causes warning C4311 and C4302.
// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4311?view=vs-2017
// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4302?view=vs-2017
ULONG BYTElen(BYTE* buffer);