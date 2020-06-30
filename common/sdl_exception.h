#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H
#include <errno.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>
#include "exception_messages.h"

class SdlException : public std::exception {
 private:
  int myerrno;
  std::string msg_error;

 public:
  SdlException(const char*, const char*);

  virtual ~SdlException() noexcept;

  /*
   * @brief tells what is the exception problem
   *
   * @return const char*
   */
  virtual const char* what() const noexcept;
};
#endif
