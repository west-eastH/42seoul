#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void (*old_fun)( int);

void sigint_handler( int signo)
{
	(void)signo;
   printf( "Ctrl-C 키를 눌루셨죠!!\n");
   printf( " 종료됩니다.\n");
}

int main( void)
{
   old_fun = signal( SIGINT, sigint_handler);
   while(1 ){
      printf( "badayak.com\n");
      sleep( 1);
   }
}