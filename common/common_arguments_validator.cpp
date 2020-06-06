#include "common_arguments_validator.h"

ArgumentsValidator::ArgumentsValidator(int argc, char** argv) : 
                    argc(argc), argv(argv) {} 

ArgumentsValidator::~ArgumentsValidator() {}

const char* ArgumentsValidator::getPort() {
    return port.c_str();
}
