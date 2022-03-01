#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "blocking_queue.h"

size_t size(){
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
}
bool empty(){
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
}
blocking_queue_t* create_queue(const size_t size){
    blocking_queue_t* q = new blocking_queue_t(size);
    front=0;
    rear=-1;
    if(capacity<size){
        return NULL;
    }
}
bool push(blocking_queue_t* m_queue,const int item){
    std::unique_lock<std::mutex> lock(m_mutex);
    //cond takes unique_lock and waits the false condition
    while(m_queue.size() >= capacity){
        cond_not_full.wait(lock);
          if(count==MAX){
            return false;
        }
          else{
            return true;
        }
       m_queue.push(item);
       count++;
   }
    cond_not_empty.notify_all();
}
bool pop(blocking_queue_t* m_queue,int* dest){
    std::unique_lock<std::mutex> lock(m_mutex);
    //cond takes unique_lock and waits the false condition
    while(m_queue.size()==0){
        cond_not_empty.wait(lock);
    }
    dest=m_queue.front();
    m_queue.pop();
    count--;
    if(m_queue.empty()){
        return false;
    }
    return true;
}
bool destroy_queue(blocking_queue_t* m_queue){
    delete(m_queue);
}
