// 

#include "stdafx.h"
#include "resource.h"
#include "DataFunc.h"

// This will take a ULONG and do a bit convertion and output a 4 BYTE wide array.
extern void ConvertULONGtoBYTEbuffer(BYTE* buffer[], ULONG value)
{
	*buffer = new BYTE[4];

	(*buffer)[3] = (value >> 24) & 0xFF;
	(*buffer)[2] = (value >> 16) & 0xFF;
	(*buffer)[1] = (value >> 8) & 0xFF;
	(*buffer)[0] = value & 0xFF;
}

// ULONG version of strlen so I do not get complier warnings.
extern ULONG BYTElen(BYTE* buffer)
{
	ULONG len = 0;
	while (buffer[len] != 0)
		len++;
	return len;
}