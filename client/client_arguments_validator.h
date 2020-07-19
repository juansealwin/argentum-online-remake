#ifndef CLIENT_ARGUMENTS_VALIDATOR_H
#define CLIENT_ARGUMENTS_VALIDATOR_H
#include <iostream>
#include <string>

#include "arguments_exceptions.h"
#include "exception_messages.h"
#define CLI_ARGS 3
#define PORT_ARG 2
#define IP_ARG 1

class ClientArgumentsValidator {
 private:
  std::string ip;
  int argc;
  char** argv;
  std::string port;

 public:
  ClientArgumentsValidator(int, char**);
  ~ClientArgumentsValidator();
  void validate_arguments();
  /*
   * @brief Get the Ip to know where we want to connect
   *
   * @return const char* that is the ip value
   */
  const char* get_ip();
   /*
   * @brief Get the Port object
   *
   * @return const char*
   */
  const char* get_port();
};

#endif
