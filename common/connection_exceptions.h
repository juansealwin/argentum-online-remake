#ifndef CONNECTION_EXCEPTION_H
#define CONNECTION_EXCEPTION_H

#include <errno.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>
#define BUF_LEN 256

class ConnectionException : public std::exception {
 private:
  int myerrno;
  char msg_error[BUF_LEN];

 public:
  explicit ConnectionException(const char* fmt, ...) noexcept;

  virtual ~ConnectionException() noexcept;

  /*
   * @brief tells what is the exception problem
   *
   * @return const char*
   */
  virtual const char* what() const noexcept;
};

#endif
