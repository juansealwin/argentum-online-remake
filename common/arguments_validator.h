#ifndef ARGUMENTS_VALIDATOR_H
#define ARGUMENTS_VALIDATOR_H
#include <iostream>
#include <string>

class ArgumentsValidator {
 protected:
  int argc;
  char** argv;
  std::string port;

 public:
  ArgumentsValidator(int, char**);

  ~ArgumentsValidator();

  /*
   * @brief force to childs to implemente that function
   *
   */
  virtual void validate_arguments() = 0;

  /*
   * @brief Get the Port object
   *
   * @return const char*
   */
  const char* get_port();
};

#endif
