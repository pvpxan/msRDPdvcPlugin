// 

#include "stdafx.h"
#include "resource.h"
#include "DataFunc.h"

// Converts data to file.
extern void SaveServerFile(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer, const char* fullPath)
{
	int total_length;
	total_length = (int)cbSize; // Defines the size used for the file buffer.

	// Define the file buffer.
	char* file_buffer;
	file_buffer = new char[total_length];
	try
	{
		std::copy_n(pBuffer, total_length, file_buffer); // Fill the file buffer.
		std::ofstream outfile(fullPath, std::ios::binary | std::ios::trunc);
		if (outfile.is_open())
		{
			outfile.write(file_buffer, total_length);
			outfile.close();
		}

		// Invoke work with file here.
	}
	catch (...)
	{
		MessageBoxA(NULL, "There was a problem saving file from virtual channel.", "Error...", MB_OK | MB_ICONERROR);
		// TODO (DB): Add logging to this.
	}

	delete[] file_buffer;
	file_buffer = NULL;
}

// Converts data to file. Data must contains a 200 byte header containing a filename.
extern void ReadDataStream(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer, const char* savePath)
{
	const char* generic_message = "There was a problem saving file from virtual channel.";
	const char* generic_caption = "Error...";

	if (cbSize <= HEADER_LENGTH) // Data less than or equal to 200 bytes indicates a problem since the header is 200 bytes.
	{
		MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
		// TODO (DB): Add logging to this.
		return;
	}

	char filename[FILENAME_BUFFER]; // Filename buffer
	try
	{
		std::copy_n(pBuffer, FILENAME_BUFFER - 1, filename); // Fills buffer from portion of header that represents file name. It will fill 'FILENAME_BUFFER - 1' to allow for terminating \0 at the end.
	}
	catch (...)
	{
		MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
		// TODO (DB): Add logging to this.
		return;
	}

	char full_file_path[HEADER_LENGTH]; // Full filepath buffer
	try
	{
		errno_t err;

		err = strcpy_s(full_file_path, HEADER_LENGTH, savePath); // Fills the full_filepath buffer with the base path where the file will be saved.
		if (err > 0) // failed to append full_filepath buffer.
		{
			MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
			// TODO (DB): Add logging to this.
			return;
		}

		err = strcat_s(full_file_path, HEADER_LENGTH, filename); // This will append the filepath with the filename parsed from the header.
		if (err > 0) // failed to append full_filepath buffer.
		{
			MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
			// TODO (DB): Add logging to this.
			return;
		}
	}
	catch (...)
	{
		MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
		// TODO (DB): Add logging to this.
		return;
	}

	int total_length;
	total_length = (int)cbSize; // Defines the size used for the file buffer.

	// Define the file buffer.
	char* file_buffer;
	file_buffer = new char[total_length];
	try
	{
		std::copy_n(pBuffer, total_length, file_buffer); // Fill the file buffer.
		std::ofstream outfile(full_file_path, std::ios::binary | std::ios::trunc);
		if (outfile.is_open())
		{
			outfile.write(file_buffer, total_length);
			outfile.close();
		}

		// Invoke work with file here.
	}
	catch (...)
	{
		MessageBoxA(NULL, generic_message, generic_caption, MB_OK | MB_ICONERROR);
		// TODO (DB): Add logging to this.
	}

	delete[] file_buffer;
	file_buffer = NULL;
}

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