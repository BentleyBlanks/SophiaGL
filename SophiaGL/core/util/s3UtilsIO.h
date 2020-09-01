#pragma once
#include <core/s3Settings.h>
#include <core/s3Timer.h>

class s3UtilsDirectoryWatch
{
public:
	s3UtilsDirectoryWatch();
	~s3UtilsDirectoryWatch();

	// return false if watching event failed
	bool watch(const std::string& path, bool watchSubTree = false);
	bool watch(const std::vector<std::string>& paths, bool watchSubTree = false);
	void unwatch();

	// return true if any file in the directory has been modified
	// file change event could only be triggerred once
	bool hasChanged();
	bool isWatched() const;
	bool isWatchisSubtree() const;

private:
	bool bIsWatched        = false;
	bool bIsWatchedSubtree = false;
	std::vector<std::string> paths;
	std::vector<HANDLE> changeHandles;
	s3Timer timer;
};