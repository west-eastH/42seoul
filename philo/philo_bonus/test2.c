#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */


int main (){
    int i;                        /*      loop variables          */
    sem_t *sem;                   /*      synch semaphore         *//*shared */
    pid_t pid;                    /*      fork pid                */
    int n;               /*      fork count              */
    unsigned int value;           /*      semaphore value         */
	int p = 1;

    printf ("How many children do you want to fork?\n");
    printf ("Fork count: ");
    scanf ("%u", &n);

    printf ("What do you want the semaphore value to be?\n");
    printf ("Semaphore value: ");
    scanf ("%u", &value);

    /* initialize semaphores for shared processes */
    sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644, value); 
    /* name of semaphore is "pSem", semaphore is reached using this name */
    sem_unlink ("pSem");      
    /* unlink prevents the semaphore existing forever */
    /* if a crash occurs during the execution         */
    printf ("semaphores initialized.\n\n");


    /* fork child processes */
    for (i = 0; i < n; i++){
        pid = fork ();
        if (pid < 0)              /* check for error      */
            printf ("Fork error.\n");
        else if (pid == 0)
            break;                  /* child processes */
    }


    /******************************************************/
    /******************   PARENT PROCESS   ****************/
    /******************************************************/
    if (pid != 0){
        /* wait for all children to exit */
        while ((pid = waitpid (-1, NULL, 0)) > 0){
           if (errno == ECHILD)
                break;
        }

        printf ("\nParent: All children have exited.\n");

        /* cleanup semaphores */
        sem_unlink("pSem");
        sem_close(sem);

        exit (0);
    }

    /******************************************************/
    /******************   CHILD PROCESS   *****************/
    /******************************************************/
    else{
        sem_wait (sem);           /* P operation */
        printf ("  Child(%d) is in critical section.\n", i);
        sleep (1);
        p += i % 3;              /* increment *p by 0, 1 or 2 based on i */
        printf ("  Child(%d) new value of *p=%d.\n", i, p);
        sem_post (sem);           /* V operation */
        exit (0);
    }
}