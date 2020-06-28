#include <iostream>
#include "arguments_exceptions.h"
#include "client.h"
#include "client_arguments_validator.h"
#include "connection_exceptions.h"
#include "texture_manager.h"

TextureManager& texture_manager = TextureManager::get_instance();

int main(int argc, char *argv[]) {
  try {
    ClientArgumentsValidator validator(argc, argv);
    validator.validate_arguments();
    Client client(validator.get_ip(), validator.get_port());
    client.play();
    return EXIT_SUCCESS;
  } catch (ArgumentsException excep) {
    std::cout << excep.what() << std::endl;
  } catch (std::exception excep) {
    std::cout << excep.what() << std::endl;
  }
}
