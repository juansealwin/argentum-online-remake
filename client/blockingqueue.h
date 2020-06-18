#ifndef BLOCKING_H
#define BLOCKING_H
#include <deque>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "event.h"
//enum {KEEP_WORKING = true, STOP_WORKING = false};

class BlockingQueue {
    private:
        std::deque<Event> queue;
        std::mutex block_queue;
        std::condition_variable cv;
        bool no_more_events = false;
        
    public:
        BlockingQueue();
        ~BlockingQueue();
        BlockingQueue(BlockingQueue&) = delete;
        void pushEvent(const Event);
        Event& popEvent();
        void noMoreEvents();
        BlockingQueue& operator=(const BlockingQueue&) = delete;
};
#endif
