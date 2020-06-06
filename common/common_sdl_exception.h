#ifndef __COMMON_SDL_EXCEPTION_H__
#define __COMMON_SDL_EXCEPTION_H__
#include <string>
#include <iostream>
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <typeinfo>
#define BUF_LEN 256

class SdlException : public std::exception {
    private:
        int myerrno;
        char msg_error[BUF_LEN];

    public:
        explicit SdlException(const char* fmt, ...) noexcept;
        
        virtual ~SdlException() noexcept;
        
        /*
         * @brief tells what is the exception problem
         * 
         * @return const char* 
         */
        virtual const char* what() const noexcept;
};
#endif
