#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

unsigned long long **readCpu();
void ctrlC(int sig);

int ctrlc = 0;

int main(){
	printf("USER PROC\t");
	printf("SYSTEM PROC\t");
	printf("IDLE PROC\t");

	printf("\n");

	while(1){

        signal(SIGINT, ctrlC);

		if(ctrlc) 
            break;

		unsigned long long **p_cpu_array = readCpu();
		sleep(1);
		unsigned long long **n_cpu_array = readCpu();

		printf("%lu\t\t", n_cpu_array[0] - p_cpu_array[0]);
		printf("%lu\t\t", n_cpu_array[2] - p_cpu_array[2]);
		printf("%lu\t", n_cpu_array[3] - p_cpu_array[3]);
			
		printf("\n");
		
		free(p_cpu_array);
		free(n_cpu_array);
	}
	
	return 0;
}

unsigned long long **readCpu(){
	FILE *fp;
	unsigned long long **procArr;
	unsigned long long delArr[6];

	procArr = (unsigned long long **)malloc((2) * sizeof(unsigned long long));

	fp = fopen("/proc/stat", "r");

	int i;

	for(i = 0; i<2; i++){
		procArr[i] = (unsigned long long *)malloc(4 * sizeof(unsigned long long));
		fscanf(fp, "%*s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu ", &procArr[i][0], &procArr[i][1], &procArr[i][2], &procArr[i][3], &delArr[0], &delArr[1], &delArr[2], &delArr[3], &delArr[4], &delArr[5]);
		sleep(0.01);
	}
	
	fclose(fp);
	return procArr; // = {USER_PROC, NICE_PROC, SYSTEM_PROC, IDLE_PROC}
}

void ctrlC(int sig){
    ctrlc = 1;
}
