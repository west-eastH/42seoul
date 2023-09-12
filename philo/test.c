#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
 
// init mutex container
pthread_mutex_t mutex_lock;

// share resource
int share = 0;
 
void *thread_function(void *data){
        int i;
        char *thread_name = (char *) data;
 
        // lock
        pthread_mutex_lock(&mutex_lock);
        // critical section start
        share = 0;
        for(i = 0; i < 3; i++){
                printf("%s Count : %d\n", thread_name, share);
                share++;
                sleep(2);
        }
        // critical section end
        // mutex unlock
        pthread_mutex_unlock(&mutex_lock);
}
 
int main(){
        pthread_t p_thread1, p_thread2;
        int status;
 
        // mutex container init
        pthread_mutex_init(&mutex_lock, NULL);
        pthread_create(&p_thread1, NULL, thread_function, (void *) "THREAD 1");
        pthread_create(&p_thread2, NULL, thread_function, (void *) "THREAD 2");
 
        pthread_join(p_thread1, (void *)&status);
        pthread_join(p_thread2, (void *)&status);
        return 0;
}
