#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include "test_array.h"
#include <errno.h>
#include <string.h>



int main(int argc, char **argv) {
	//Index von außen erhalten
    	int i = atoi(argv[1]);


	//mmap Aufruf ohne Hugepage Optionen und ohne PB_SCHEDULER flag
	void *addr = mmap(NULL, testlaengen[i], PROT_READ | PROT_WRITE,
		  MAP_PRIVATE | MAP_ANONYMOUS  , -1, 0);
	//Fehlererkennung mmap
	if (addr == MAP_FAILED) {
		fprintf(stderr, "mmap failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	//Beschreibe virtuellen Speicherbereich
	int *int_array = (int *)addr; 
	for (size_t j = 0; j < testlaengen[i] / sizeof(int); j++) {
	int_array[j] = 42;
	}
	//Munmap Test
	int err = munmap(addr, testlaengen[i]);
	if (err == -1) {
	printf("munmap failed\n");
	}

	    return 0;
}

