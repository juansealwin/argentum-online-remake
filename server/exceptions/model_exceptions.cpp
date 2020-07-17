#include "model_exceptions.h"

ModelException::ModelException(const char* description)
    : std::exception(), msg_error(description) {
  //msg_error.append("\n MODEL_ERROR: ").append(modelError);
}

ModelException::~ModelException() {}

const char* ModelException::what() const noexcept { return msg_error.c_str(); }
