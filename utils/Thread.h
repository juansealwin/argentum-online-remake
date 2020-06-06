#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
public:
    Thread();

    virtual ~Thread();

    void start();

    void join();

    virtual void run() = 0;

    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

    Thread(Thread &&other);

    Thread &operator=(Thread &&other);

private:
    std::thread thread;
};

#endif //THREAD_H
