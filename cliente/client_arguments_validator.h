#ifndef __client_arguments_validator_H__
#define __client_arguments_validator_H__
#include <iostream>
#include <string>
#include "../common/common_arguments_validator.h"
#include "../common/common_arguments_exceptions.h"
#include "../common/common_exception_messages.h"
#define CLI_ARGS 3
#define PORT_ARG 2
#define IP_ARG 1

class ClientArgumentsValidator : public ArgumentsValidator {
    private:
        std::string ip;

    public:
        ClientArgumentsValidator(int, char **);

        ~ClientArgumentsValidator();

        /*
         * @brief This is the polimoric function that ArgumentsValidator force *        to implement. It validate the arguments on the client side.
         * 
         */
        void validateArguments();

        /*
         * @brief Get the Ip to know where we want to connect
         * 
         * @return const char* that is the ip value
         */
        const char* getIp();
};

#endif
