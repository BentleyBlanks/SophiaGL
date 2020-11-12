#pragma once
#include <core/s3Settings.h>
#include <core/log/s3Log.h>
#include <3d/s3Mesh.h>
#include <3d/s3ModelImporter.h>

int main()
{
	// Ref: https://docs.microsoft.com/en-us/windows/win32/devnotes/-getmodulefilename
	TCHAR pathPtr[MAX_PATH]; 
	GetModuleFileName(NULL, pathPtr, MAX_PATH);

	std::wstring pathStr = (std::wstring)(pathPtr);
	int index = (int)pathStr.find_last_of(TEXT("\\"));

	// Ref: https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setcurrentdirectory
	std::wstring directoryPathStr = pathStr.substr(0, index);
	SetCurrentDirectory(directoryPathStr.c_str());

	//char pathStr[1024];
	//char* directoryPathStr;
	//if (GetModuleFileNameA(NULL, pathStr, sizeof(pathStr)))
	//{
	//	// Ref: http://www.cplusplus.com/reference/cstring/strrchr/
	//	directoryPathStr = strrchr(pathStr, '\\');

	//	// Change the last \\ into \0. Instead of get rid of 
	//	if (directoryPathStr) *directoryPathStr = '\0';
	//	SetCurrentDirectoryA(pathStr);
	//}

	s3Mesh* mesh = s3ModelImporter::load("../../resources/models/cube/cube.obj");

	return 0;
}