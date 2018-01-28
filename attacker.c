#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include "math.h"
#include <time.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

//Use these definitions for the specific types
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;
typedef unsigned long int uint64_t;
unsigned char plaintext[16]={0};
unsigned char ciphertext[16];
unsigned char key[16]={0};
//unsigned long time1,time2;
unsigned int time1, time2;


//Flush Function: Flushes the address "p"
/*inline void clflush(volatile void * p){
	asm volatile ("clflush (%0)" :: "r"(p));
}*/
inline void clflush (volatile void *) __attribute__((always_inline));
inline void rdtsc(void *)  __attribute__((always_inline));

/*
inline void flush(volatile void * adrs) {
  asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
}
*/

inline unsigned long gettime() __attribute__((always_inline));


static char some_var = 0;

void main(void){
	char * p = &some_var;
	uint32_t value;
	int j;	
	int tot_time = 0;	

	int i = 0;	
	
	int x,y;

	int res_time[100000] = {0};

	for (int i = 0; i < 10000; ++i)
	{
		clflush(&x);
		//y=x;
 
		time1 = gettime();
		
		y=x;
		time2 = gettime();

		printf("%d\n", (time2 - time1)>2000?2000:(time2 - time1));
		res_time[i] = time2 - time1;//(time2 - time1)>2000?2000:(time2 - time1);
		i++;
		//printf("2\n");
	}

	//printf("address is: %p\n", sqlite3_open);

	for (int j = 0; j < i; ++j)
	{	
		//printf("%d\n",res_time[j]>2000?2000:res_time[j]); //get back
		printf("%d\n",res_time[j]);
		/* code */
	}
	//Output the ciphertext and the corresponding times to .txt file
	//printf("Total Time is: %d \n", tot_time);
	

}


inline void clflush(volatile void * p){
	asm volatile ("mfence\nclflush (%0)" :: "r"(p));
}

inline void rdtsc(void *m) {
	__asm__ __volatile__ ("lfence\nrdtscp" : "=a" (*((uint32_t *)(m))), "=d" (*((uint32_t *)(m+4))));
}

inline unsigned long gettime() {
  volatile unsigned long tl;
  asm __volatile__("lfence\nrdtsc" : "=a" (tl): : "%edx");
  return tl;
}
