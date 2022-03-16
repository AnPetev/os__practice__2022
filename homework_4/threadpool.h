#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include <functional>
#include <vector>
#include <queue>
#include <pthread.h>

namespace RauOs{
    typedef void* Input;
    typedef void* Output;
    typedef std::function<Output(Input)> Work;
    typedef pthread_t Worker;
    std::vector<Worker> workers;
    std::queue<Work> tasks;
    typedef tpool_t;
         pthread_mutex_t  work_mutex;
         pthread_cond_t   work_cond;
         pthread_cond_t   working_cond;
         size_t           working_cnt;
         size_t           thread_cnt;
         bool             stop;

    class ThreadPool{
 public:
        ThreadPool(const std::size_t parallelismDegree);
        ThreadPool(const ThreadPool& other)            = delete;
        ThreadPool& operator=(const ThreadPool& other) = delete;
        ~ThreadPool();
        void run(const Work& work, const Input input);
        void wait();
        void wait(const std::size_t milliseconds);
        void exit();
    };
};

#endif
