#include "arguments_validator.h"

ArgumentsValidator::ArgumentsValidator(int argc, char** argv)
    : argc(argc), argv(argv) {}

ArgumentsValidator::~ArgumentsValidator() {}

const char* ArgumentsValidator::get_port() { return port.c_str(); }
