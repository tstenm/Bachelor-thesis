#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include "test_array.h"
#define PB_SCHEDULER 0x40	

/* Aufrufskonvention : ./programmname <index_of_testarray> 
   Dieses Programm wird von einem Script aufgerufen und versorgt das Programm mit dem jeweiligen Index. */
int main(int argc, char **argv) {
	//get index from perf program
    	int i = atoi(argv[1]);


	//mmap Aufruf ohne Hugepage Optionen zum anfordern anonymen Speichers
	void *addr = mmap(NULL, testlaengen[i], PROT_READ | PROT_WRITE,
		  MAP_PRIVATE | MAP_ANONYMOUS | PB_SCHEDULER , -1, 0);
	//Fehlererkennung mmap
	if (addr == MAP_FAILED) {
		return EXIT_FAILURE;
	}
	//Schreibzugriff auf den angeforderten Bereich
	int *int_array = (int *)addr; 
	for (size_t j = 0; j < testlaengen[i] / sizeof(int); j++) {
		int_array[j] = 42;	
	}
	//Munmap, zur Wiederverwendung von Hugepages und zum Test der Munmap Funktionalität
	int err = munmap(addr, testlaengen[i]);
		if (err == -1) {
		printf("munmap failed\n");
	}

	    return 0;

}

