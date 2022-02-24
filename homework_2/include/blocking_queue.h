#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

typedef struct blocking_queue{
    size_t capacity;
    int front;
    int rear;
    std::queue<int> m_queue;
    std::mutex m_mutex;
    std::condition_variable cond_not_full;
    std::condition_variable cond_not_empty;
    int count=0;
    const int MAX{5};
} blocking_queue_t;

size_t size();
bool empty();
blocking_queue_t* create_queue(const size_t size);
bool push(blocking_queue_t* m_queue,const int item);
bool pop(blocking_queue_t* m_queue,int* dest);
bool destroy_queue(blocking_queue_t* m_queue);

#endif //end of blocking_queue.h
