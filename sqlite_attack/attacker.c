#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include "math.h"
#include <time.h>
#include <stdio.h>
#include "sqlite3.h"
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

int addition_function(int a, int b){
	int i = 0;
	int j = 0;
	int c = 0;
	for (int i = 0; i < 100; ++i)
	{
		j += i;
	}
	c = a + b; 
	return c;
}

static char some_var = 0;


int *get_shared_memory() {
  key_t shm_key = 6166523;
  const int shm_size = 1024;

  int shm_id;
  int* shmaddr, *ptr;
  int* shared_memory[3];
  int *p;

  /* Allocate a shared memory segment. */
  shm_id = shmget (shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Attach the shared memory segment. */
  shmaddr = (int*) shmat (shm_id, 0, 0);
  return shmaddr;
}

int* sharedMemAddr;

void main(void){
	char * p = &some_var;
	uint32_t value;
	int j;	
	int tot_time = 0;	

	int offset = 3904;
	int gdb_offset = 37;

	int res_time[100000] = {0};

	for (int i = 0; i < 10000; ++i)
	{		
		clflush(0xb7f515ec - gdb_offset + offset); //VdbeExe : we want start of case statement in order to get that you need to look at objdump


		//Measure the timing for the reload of the first cache line with rdtsc function. 
		time1 = gettime();

		//clflush(0xb7f5160d);
		// to reload: Assembly call to return of the SQLITE3VBEExec

		time2 = gettime();

		res_time[i] = time2 - time1;//(time2 - time1)>2000?2000:(time2 - time1);

	}


	//printf("address is: %p\n", sqlite3_open);

	for (int j = 0; j < 10000; ++j)
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