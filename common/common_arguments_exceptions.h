#ifndef __common_arguments_exceptions_H__
#define __common_arguments_exceptions_H__

#include <string>
#include <iostream>
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <typeinfo>
#define BUF_LEN 256


class ArgumentsException : public std::exception {
    private:
        int myerrno;
        char msg_error[BUF_LEN];

    public:
        explicit ArgumentsException(const char* fmt, ...) noexcept;
        
        virtual ~ArgumentsException() noexcept;
        
        /*
         * @brief tells what is the exception problem
         * 
         * @return const char* 
         */
        virtual const char* what() const noexcept;
};
#endif