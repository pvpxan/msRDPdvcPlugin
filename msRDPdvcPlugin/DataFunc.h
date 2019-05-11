#pragma once
#include "stdafx.h"
#include "resource.h"

// ConvertULONGtoBYTEbuffer is a cross platform compatible converter to convert the value of a ULONG to a Byte array. Prevents weird endian issues. 
void ConvertULONGtoBYTEbuffer(BYTE* buffer[], ULONG value);

// BYTElen is just a simple ULONG version of strlen so I do not get complier warnings.
// Not using seems to cause 64/32 bit issues. Simple casting will still compile but causes warning C4311 and C4302.
// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4311?view=vs-2017
// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4302?view=vs-2017
ULONG BYTElen(BYTE* buffer);