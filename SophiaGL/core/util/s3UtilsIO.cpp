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
bool s3UtilsDirectoryWatch::watch(const std::string& _path)
{
	std::wstring wpath = std::wstring(_path.begin(), _path.end());
	changeHandle = FindFirstChangeNotification(wpath.c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

    if (changeHandle == NULL)
    {
		s3Log::error("s3UtilsDirectoryWatch::watch watched file: %s failed\n", _path.c_str());
        return false;
    }

	bIsWatched = true;
	path = _path;
    return true;
}

void s3UtilsDirectoryWatch::unwatch()
{
	if (bIsWatched)
	{
		FindCloseChangeNotification(changeHandle);
		bIsWatched = false;
	}
}

//--! ref: https://www.installsetupconfig.com/win32programming/windowsdirectoryapis3_5.html
bool s3UtilsDirectoryWatch::hasChanged() const
{
	// Wait for notification 
	DWORD dwWaitStatus;
	dwWaitStatus = WaitForMultipleObjects(1, &changeHandle, FALSE, 0);
	switch (dwWaitStatus)
	{
	case WAIT_OBJECT_0:
		// restart the notification
		if (FindNextChangeNotification(changeHandle) == FALSE)
		{
			s3Log::error("s3UtilsDirectoryWatch::hasChanged() watched file: %s failed\n", path.c_str());
		}
		return true;
	}
	return false;
}

bool s3UtilsDirectoryWatch::isWatched() const
{
	return bIsWatched;
}
