#pragma once
#include <core/s3Settings.h>

class s3UtilsDirectoryWatch
{
public:
	s3UtilsDirectoryWatch();
	~s3UtilsDirectoryWatch();

	// return false if watching event failed
	bool watch(const std::string& path);
	void unwatch();

	// return true if any file in the directory has been modified
	bool hasChanged() const;
	bool isWatched() const;

private:
	bool bIsWatched = false;
	std::string path;
	HANDLE changeHandle;
};