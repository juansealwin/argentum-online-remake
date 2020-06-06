#ifndef __common_arguments_validator_H__
#define __common_arguments_validator_H__
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
        virtual void validateArguments() = 0;
        
        /*
         * @brief Get the Port object
         * 
         * @return const char* 
         */
        const char* getPort();
};

#endif
