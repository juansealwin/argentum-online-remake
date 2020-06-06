#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include "Socket.h"
#include <iostream>

void Socket::connect(const char *host, const char *port) {
    bool connected = false;
    struct addrinfo *addrinfo_list;
    addrinfo_list = getAddr(host, port, CLIENT_FLAGS);
    int fd = -1;
    struct addrinfo *addr = addrinfo_list;
    while (addr && !connected) {
        fd = socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);
        if (::connect(fd, addr->ai_addr, addr->ai_addrlen) == -1)
            connected = true;
        addr = addr->ai_next;
    }
    this->fd = fd;
    freeaddrinfo(addrinfo_list);
}

void Socket::bind_and_listen(const char *port) {
    bool binded = false;
    struct addrinfo *addrinfo_list;
    addrinfo_list = getAddr(nullptr, port, SERVER_FLAGS);
    int fd = -1;
    struct addrinfo *addr = addrinfo_list;
    while (addr && !binded) {
        fd = socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);
        if (::bind(fd, addr->ai_addr, addr->ai_addrlen) == -1)
            binded = true;
        addr = addr->ai_next;
    }
    freeaddrinfo(addrinfo_list);
    this->fd = fd;
    ::listen(this->fd, MAX_CLIENTS);
}

Socket Socket::accept() {
    int fd = ::accept(this->fd, nullptr, nullptr);
    if (fd == -1)
        throw std::invalid_argument("closed socket!");
    Socket skt;
    skt.fd = fd;
    return std::move(skt);
}

void Socket::close() {
    ::shutdown(this->fd, SHUT_RDWR);
    ::close(this->fd);
}

void Socket::send(const void *msg, const size_t length) const {
    if (length == 0) return;
    uint remaining_bytes = length;
    uint total_bytes_sent = 0;
    ssize_t bytes = 0;
    const char *buffer = static_cast<const char *>(msg);
    do {
        bytes = ::send(this->fd, &buffer[total_bytes_sent],
                       remaining_bytes, MSG_NOSIGNAL);
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    } while (total_bytes_sent < length && bytes > 0);
}

void Socket::recv(void *response, const size_t length) const {
    if (length == 0) return;
    uint remaining_bytes = length;
    uint total_bytes_received = 0;
    ssize_t bytes = 0;
    char *buffer = static_cast<char *>(response);
    do {
        bytes = ::recv(this->fd, &buffer[total_bytes_received],
                       remaining_bytes, 0);
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    } while (total_bytes_received < length && bytes > 0);
}

struct addrinfo *Socket::getAddr(const char *host, const char *service,
                                 int flags) const {
    struct addrinfo *addrinfo_list;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = FAMILY;
    hints.ai_socktype = SOCK_TYPE;
    hints.ai_flags = flags;
    int addr_err = 0;
    if ((addr_err = getaddrinfo(host, service, &hints, &addrinfo_list)) != 0)
        return nullptr;
    return addrinfo_list;
}

Socket::~Socket() {
    if (this->fd == -1) return;
    ::shutdown(this->fd, SHUT_RDWR);
    ::close(this->fd);
}

Socket::Socket(Socket &&other) {
    this->fd = other.fd;
    other.fd = -1;
}

Socket &Socket::operator=(Socket &&other) {
    this->fd = other.fd;
    other.fd = -1;
    return *this;
}
