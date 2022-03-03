#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ipc.h"

int create_shm(){
    const size_t size   = sizeof(shm_t);
    const key_t key= 9876;
    const int flag   = IPC_CREAT | 0660;
    int shm_id = shmget(key, size, flag | IPC_EXCL);
       if (shm_id < 0) {
          perror("shmget cant create shared memory");
          shm_id = shmget(key, size, flag);
          if (shm_id < 0) {
            perror("cant access already created shared memory");
            return NULL;
        }
    }
    sum_ = 0;
    for(int i=0;i<1024;i++){
        arr_[i]=1;
    }
}


void run_child(const int shm_id, const size_t child_number,  size_t size){
int pid;
pid=fork();
if(pid==0){
    printf("child having pid %d\n",getpid());
}
size = 1024 / child_number;
pid_t pids[size * child_number + size];
for(int i = size * child_number;i < size * child_number + size;i++){
  sum_+=pids[i];

}
}

 void run_parent(const int shm_id){
     int pid;
     pid=fork();
     if(pid>0){
         printf("parent having pid %d\n",getppid());
     }
     shm_t* sum_ = shmat(shm_id, NULL, 0);
    if (sum_ == (void*)-1) {
        perror("Unable to attach to the shared memory");
        return NULL;
    }   
        pthread_mutexattr_init(&sum_->attr_);
        pthread_mutexattr_setpshared(&sum_->attr_,PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&sum_->mutex_,&sum_->attr_);
    }
    return sum_;
}
 }
void wait_children(const pid_t* pids, const size_t count)
{
    for (size_t i = 0; i < count; i++)
        waitpid(pids[i], NULL, 0);
}
void destroy_shm(const int shm_id){
if (pthread_mutexattr_destroy(&sum_->attr_) != 0)
            perror("Unable to destroy the mutex attribute");

        if (pthread_mutex_destroy(&sum_->mutex_) != 0)
            perror("Unable to destroy the mutex");
        const int shm_id = shmget(9876, sizeof(shm_t), IPC_CREAT | 0660);
        if (shm_id < 0)
            perror("Unable to get shared memory ID for deletion");
        if (shmctl(shm_id, IPC_RMID, NULL) != 0)
            perror("Unable to delete shared memory");
    }
    if (shmdt(sum_) != 0)
        perror("Unable to detach from the shared memory");

}
