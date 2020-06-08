#include "client_arguments_validator.h"

ClientArgumentsValidator::ClientArgumentsValidator(int argc, char** argv) : 
                          ArgumentsValidator(argc, argv) {}

ClientArgumentsValidator::~ClientArgumentsValidator() {}

//Cambiar los valores harcodeados
void ClientArgumentsValidator::validateArguments() {
    if (argc != CLI_ARGS) 
        throw ArgumentsException("%s", MSG_ERROR_QUANTITY_ARGS);

    port = argv[PORT_ARG]; 
    if ((std::string)argv[IP_ARG] != "localhost" && 
        (std::string)argv[IP_ARG] != "127.0.0.1")
        throw ArgumentsException("%s", MSG_ERROR_INVALID_IP);
    else
        ip = argv[IP_ARG];
}

const char* ClientArgumentsValidator::getIp() {
    return ip.c_str();
}
