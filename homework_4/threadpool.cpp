#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>
#include <functional>

#include "threadpool.h"

ThreadPool::ThreadPool(size_t parallelismDegree){
    tpool_t  *tm;
    size_t i;
    tm = new int(sizeof(*tm));
    tm->thread_cnt = parallelismDegree;
    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);
    for (i = 0; i < parallelismDegree; i++) {
        pthread_create(&Worker, NULL, workers, tm);
    }
    return tm;
}
ThreadPool::~ThreadPool(){
    pthread_t work2;
    pthread_mutex_lock(&Worker->work_mutex));
    while (workers != NULL) {
        work2 = workers->next;
        exit(work);
        work = work2;
    }
    pthread_mutex_unlock(&Worker->work_mutex));
    tpool_wait(Worker);
    pthread_mutex_destroy(&Worker->work_mutex));
    pthread_cond_destroy(&Worker->work_cond));
    pthread_cond_destroy(&Worker->working_cond));
    delete []tm;
}

void run(const Work& work, const Input input){
    std::vector<Worker> workers;
    std::queue<Work> tasks;
    tasks.push(work);
    while (true) {
            pthread_mutex_lock(&work_mutex);
    while(tasks.empty()){
            pthread_cond_wait(&work_cond, &work_mutex);
            input = tasks.front();
            tasks.pop();
            pthread_mutex_unlock(&work_mutex);
        }
    }
}

void wait(){
    pthread_mutex_lock(&work_mutex);
    while (true) {
        if ((!Worker->stop && Worker->working_cnt != 0) || (Worker->stop && Worker->thread_cnt != 0)) {
            pthread_cond_wait(&Worker->working_cond, &Worker->work_mutex);
        }  
        else {
            break;
        }
    }
    pthread_mutex_unlock(&Worker->work_mutex);
    return nullptr;
}

                          
void exit(){
    void* return_value;
    pthread_exit(return_value);
    pthread_join(thread, &return_value);
}
