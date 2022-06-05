#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#include "ipc.h"


int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Please, provide the child count.\n");
        return 1;
    }
    const int shm_id = create_shm();
    if (shm_id < 0)
        return 1;
    size_t child_count  = atoi(argv[1]);
    size_t segment_size = 1024 / child_count;
    pid_t  pids[child_count];
    for (size_t i = 0; i < child_count; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Unable to fork:");
            break;
        }       
        if (pids[i] > 0) {
            continue;
        }
        run_child(shm_id, i, segment_size);

        return 0;
    }
    wait_children(pids, child_count);
    run_parent(shm_id);
    destroy_shm(shm_id);

    return 0;
}
