#include <iostream>

#include "arguments_exceptions.h"
#include "connection_exceptions.h"
#include "client.h"
#include "client_arguments_validator.h"

int main(int argc, char *argv[]) {
    try {
        ClientArgumentsValidator validator(argc, argv);
        validator.validateArguments();
        Client client(validator.getIp(), validator.getPort());
        client.play();
        return EXIT_SUCCESS;
    } catch (ArgumentsException excep) {
        std::cout << excep.what() << std::endl;
    } catch (std::exception excep) {
        std::cout << excep.what() << std::endl;
    }
}
