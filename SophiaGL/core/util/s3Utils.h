#pragma once

#include <core/s3Settings.h>
#include <core/s3Event.h>

// Log
// reporting that the given function is not implemented
#define s3FuncNotImplementedError()\
{\
    std::string error = "Unimplemented ";\
    error += __FUNCTION__;\
    error += "() method called\n";\
    s3Log::error(error.c_str());\
}

// reporting a warning that ptr is nullptr
#define s3NullPtrWarning(ptrName)\
{\
    std::string error;\
    error += __FUNCTION__;\
    error += "() given ";\
    error += ptrName;\
    error += "is null";\
    a3Log::warning(error.c_str());\
}