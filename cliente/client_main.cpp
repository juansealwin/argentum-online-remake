#include "client.h"
#include "client_arguments_validator.h"
#include "../common/common_arguments_exceptions.h"
#include "../common/common_connection_exceptions.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        ClientArgumentsValidator validator(argc, argv);
        validator.validateArguments();
        Client client(validator.getIp(), validator.getPort());
        client.play();
        return EXIT_SUCCESS;
	} catch (ArgumentsException excep) {
		std::cout << excep.what() << std::endl;
	} catch(std::exception excep) {
		std::cout << excep.what() << std::endl;
	}
}
