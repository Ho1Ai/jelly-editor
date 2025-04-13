#include <stdio.h>
#include "./base-structs.hpp"

int countLines(WorkState* work_state) {
	long long length = 1;
	FILE* f_tmp = fopen(work_state->filename, "r");

	if(!f_tmp) {
		printf("There's no file with this name\n");
		FILE* n_tmp = fopen(work_state->filename, "w");
		printf("New file created\n");
	} else {
		
		char c;
		while((c = fgetc(f_tmp))!= EOF){
			//putchar(c);
			if (c == '\n') {
				//puts("incr");
				length++;
				}
			}
		}
	
	return length;
	}
