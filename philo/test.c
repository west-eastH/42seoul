#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
int main()
{
    struct timeval startTime, endTime;
    double diffTime;
	double sec;
	double msec;
    gettimeofday(&startTime, NULL);
      // 특정 작업 수행
	usleep(1500000);
    gettimeofday(&endTime, NULL);
	sec = (endTime.tv_sec - startTime.tv_sec) * 1000000;
	printf("%fsec\n", sec);
	msec = ((double)endTime.tv_usec - startTime.tv_usec);
	printf("%fmsec\n", msec);
    diffTime = (sec + msec) / 1000;
    printf("%f s\n", diffTime);
    return 0;
}