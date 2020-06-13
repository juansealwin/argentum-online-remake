#include "sdl_exception.h"

SdlException::SdlException(const char* description, const char* sdlError)
    : std::exception(), msg_error(description) {
  msg_error.append("\n SDL_ERROR: ").append(sdlError);
}

SdlException::~SdlException() {}

const char* SdlException::what() const noexcept { return msg_error.c_str(); }
