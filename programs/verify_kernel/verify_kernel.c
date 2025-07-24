#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define PB_SCHEDULER 0x40

int main(int argc, char **argv) {
    // exemplarische Testmengen
    size_t testlaengen[] = {
        1073741824ul,
        1077936128ul,
        1077940224ul,
        2097152ul,
        4198400ul,
        4096ul,
        0ul
    };

    for (size_t i = 0; i < sizeof(testlaengen) / sizeof(testlaengen[0]); i++) {
 	int PMD, PUD, tmp;
        //Zugriff auf die Systemdateien	
        FILE *f = fopen("/sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages", "r");
	FILE *ff = fopen("/sys/kernel/mm/hugepages/hugepages-2048kB/free_hugepages", "r");
	FILE *fff = fopen("/sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages", "r");
	FILE *ffff = fopen("/sys/kernel/mm/hugepages/hugepages-1048576kB/free_hugepages", "r");
	//Fehlerbehandlung, um weiteren Programmverlauf zu verifizieren
	if (!f || !ff || !fff || !ffff) {
	    perror("fopen");
    	return EXIT_FAILURE;
	}
	//mmap Aufruf ohne Hugepage Optionen
        void *addr = mmap(NULL, testlaengen[i], PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS | PB_SCHEDULER, -1, 0);
	//Fehlererkennung mmap
        if (addr == MAP_FAILED) {
            perror("mmap");
            return EXIT_FAILURE;
        }
        //Teste ob der Zugriff auf die gesamte Region funktioniert, gibt bei einem Fehler einen Segmentationfault zurück	
        int *int_array = (int *)addr; 
        for (size_t j = 0; j < testlaengen[i] / sizeof(int); j++) {
            int_array[j] = 42;
        }
	//Berechne verwende Hugepages für den Prozess und schließe die Systemdateien wieder
        fscanf(f, "%d", &PMD);	
	fscanf(ff, "%d", &tmp);
	PMD = PMD - tmp;
	tmp = 0;
        fscanf(fff, "%d", &PUD);
	fscanf(ffff, "%d", &tmp);
	PUD = PUD - tmp;
	fclose(f);
	fclose(ff);
	fclose(fff);
	fclose(ffff);

	
	//Ausgabe
	printf("PUD: %d, PMD: %d\n", PUD, PMD);
	//Fehlerbehandlung munmap
        int err = munmap(addr, testlaengen[i]);
        if (err == -1) {
            printf("munmap failed\n");
        }
    }

    return 0;
}


