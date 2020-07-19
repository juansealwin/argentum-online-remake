#include "client_arguments_validator.h"

ClientArgumentsValidator::ClientArgumentsValidator(int argc, char** argv)
    : argc(argc), argv(argv) {}

ClientArgumentsValidator::~ClientArgumentsValidator() {}

void ClientArgumentsValidator::validate_arguments() {
  if (argc != CLI_ARGS) throw ArgumentsException("%s", MSG_ERROR_QUANTITY_ARGS);
  ip = argv[IP_ARG];
  port = argv[PORT_ARG];
}

const char* ClientArgumentsValidator::get_ip() { return ip.c_str(); }

const char* ClientArgumentsValidator::get_port() { return port.c_str(); }
