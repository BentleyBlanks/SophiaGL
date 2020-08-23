#include <core/util/s3UtilsIO.h>
#include <core/log/s3Log.h>

s3UtilsDirectoryWatch::s3UtilsDirectoryWatch()
{
}

s3UtilsDirectoryWatch::~s3UtilsDirectoryWatch()
{
	unwatch();
}

//--!ref: https://docs.microsoft.com/en-us/windows/win32/fileio/obtaining-directory-change-notifications
bool s3UtilsDirectoryWatch::watch(const std::string& _path, bool watchSubTree)
{
	std::wstring wpath = std::wstring(_path.begin(), _path.end());

	paths.clear();
	paths.push_back(_path);

	changeHandles.clear();
	changeHandles.push_back(FindFirstChangeNotification(wpath.c_str(), (int)watchSubTree, FILE_NOTIFY_CHANGE_LAST_WRITE));

    if (changeHandles[0] == NULL)
    {
		s3Log::error("s3UtilsDirectoryWatch::watch watched file: %s failed\n", _path.c_str());
        return false;
    }

	bIsWatchedSubtree = watchSubTree;
	bIsWatched        = true;
    return true;
}

bool s3UtilsDirectoryWatch::watch(const std::vector<std::string>& _paths, bool watchSubTree)
{
	int size = (int)_paths.size();
	if (size <= 0) return false;

	changeHandles.clear();
	changeHandles.resize(size);

	paths.clear();
	paths.assign(_paths.begin(), _paths.end());

	for (int i = 0; i < size; i++)
	{
		auto& p      = paths[i];
		auto& handle = changeHandles[i];
		auto wpath   = std::wstring(p.begin(), p.end());

		handle = FindFirstChangeNotification(wpath.c_str(), (int)watchSubTree, FILE_NOTIFY_CHANGE_LAST_WRITE);

		if (handle == NULL)
		{
			s3Log::error("s3UtilsDirectoryWatch::watch watched file: %s failed\n", p.c_str());
			return false;
		}
	}

	bIsWatchedSubtree = watchSubTree;
	bIsWatched        = true;

	return true;
}

void s3UtilsDirectoryWatch::unwatch()
{
	paths.clear();

	if (bIsWatched)
	{
		for (auto& handle : changeHandles)
			FindCloseChangeNotification(handle);

		changeHandles.clear();
		bIsWatched = false;
	}
}

//--! ref: https://www.installsetupconfig.com/win32programming/windowsdirectoryapis3_5.html
bool s3UtilsDirectoryWatch::hasChanged() const
{
	if (!bIsWatched) return false;

	DWORD dwWaitStatus;
	for (int i = 0; i < changeHandles.size(); i++)
	{
		auto& handle = changeHandles[i];
		auto& path   = paths[i];

		// Wait for change notification 
		dwWaitStatus = WaitForMultipleObjects(1, &handle, FALSE, 0);

		switch (dwWaitStatus)
		{
		case WAIT_OBJECT_0:
			// restart the notification
			if (FindNextChangeNotification(handle) == FALSE)
				s3Log::error("s3UtilsDirectoryWatch::hasChanged() watched file: %s failed\n", path.c_str());
			return true;
		}
	}

	return false;
}

bool s3UtilsDirectoryWatch::isWatched() const
{
	return bIsWatched;
}

bool s3UtilsDirectoryWatch::isWatchisSubtree() const
{
	return bIsWatchedSubtree;
}
