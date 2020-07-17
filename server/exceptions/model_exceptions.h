#ifndef MODEL_EXCEPTION_H
#define MODEL_EXCEPTION_H
#include <errno.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>

class ModelException : public std::exception {
 private:
  int myerrno;
  std::string msg_error;

 public:
  ModelException(const char*);

  virtual ~ModelException() noexcept;

  /*
   * @brief tells what is the exception problem
   *
   * @return const char*
   */
  virtual const char* what() const noexcept;
};
#endif
