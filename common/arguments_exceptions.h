#ifndef ARGUMENTS_EXCEPTIONS_H
#define ARGUMENTS_EXCEPTIONS_H

#include <errno.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
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
