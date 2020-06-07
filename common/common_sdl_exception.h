#ifndef __COMMON_SDL_EXCEPTION_H__
#define __COMMON_SDL_EXCEPTION_H__
#include <string>
#include <iostream>
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <typeinfo>

class SdlException : public std::exception {
    private:
        int myerrno;
        std::string msg_error;

    public:
        SdlException(const char* , const char*);
        
        virtual ~SdlException() noexcept;
        
        /*
         * @brief tells what is the exception problem
         * 
         * @return const char* 
         */
        virtual const char* what() const noexcept;
};
#endif
