#pragma once

class s3NonCopyable
{
public:
	s3NonCopyable() {}

private:
	s3NonCopyable(const s3NonCopyable&);
	s3NonCopyable& operator=(const s3NonCopyable&);
};