#include <iostream>
#include <cstring>

#include "../base-files/base-structs.hpp"
#include "../base-files/functions-output.hpp"
#include "../base-files/std-mem-man.hpp"
#include "../base-files/lines-counter.hpp"

#define OUT_ALL -1
#define END_EXECUTION_FLAG -808

using namespace std;

//commands_list:
//	out, ins, w, rml, afl, cfn, rma, rmf, c, h, q, verc




void LOCAL__dropInformation(WorkState* work_state) {
	for(int i = 0 ; i < work_state->lines_amount ; ++i) {
		printf("%s\n", work_state->content[i].str);
		}
	}


int initializeStringsWithZero(WorkState* work_state, int length) {
	int status_code = 0;

	for (int i = 0 ; i < length ; ++i) {
		//printf("str %d\n", i);
		work_state->content[i].str = new char[1];
		work_state->content[i].length = 0;
		work_state->content[i].last_reallocation_size = 1;
		}
	
	return status_code;
	}

int commandList__outOpt(WorkState* work_state, int start_pos, int end_pos) {
	cout << endl;
	int status_code = 0;

	int local_start_pos;
	int local_end_pos;
	// these variables are needed in order to understand if there is something, that is less than 0
	if (start_pos < 0) {
		if (start_pos == OUT_ALL) {
				local_start_pos = 0;
				local_end_pos = work_state->lines_amount;
			} else {
			status_code = 1;
			goto fall_with_error__out;
			}
		}
	if(end_pos < 0) {
		if(end_pos == OUT_ALL) {
			local_start_pos = 0;
			local_end_pos = work_state->lines_amount - 1;
			} else {
			status_code = 1;
			goto fall_with_error__out;
			}
		}
	
	if (end_pos >=0 && start_pos >= 0) {
		if(end_pos < start_pos) {
			status_code = 2;
			goto fall_with_error__out;
			}
		local_start_pos = start_pos;
		local_end_pos = end_pos;
		}

	if (end_pos > work_state->lines_amount-1) {
		end_pos = work_state->lines_amount - 1;
		}

	for (int i = local_start_pos; i <= local_end_pos; ++i) {
		printf("%d.\t%s\n", i, work_state->content[i].str);
		}

	fall_with_error__out:
	return status_code;
	}

int commandList__insOpt(WorkState* work_state, int line, int position) {
	int status_code = 0;

	if (line < 0) {
		status_code = 1;
		goto fall_with_error__ins;
		}

	if (position < 0) {
		status_code = 2;
		goto fall_with_error__ins;
		}

	if (line > work_state->lines_amount) {
		line = work_state->lines_amount;
		}
	
	if (position > work_state->content[line].length) {
		printf("Position is greater than line length. Setting on line length as maximum possible position.\n");
		position = work_state->content[line].length;
		}
	
	if(status_code == 0) {
		int i = 0;
		char* new_string = (char*) malloc(sizeof(char));

		for (int j = 0 ; j < position ; ++j) {
			new_string = (char*) realloc(new_string, sizeof(char)*(i+1));
			new_string[i] = work_state->content[line].str[j];
			i++;
			}

		char c;
		while((c = getchar()) != EOF && c != '\n') {
			new_string = (char*) realloc(new_string, (1 + i)*sizeof(char));
			new_string[i] = c;
			i++;
			}

		for (int j = position ; j < work_state->content[line].length ; ++j) {
			new_string = (char*) realloc(new_string, sizeof(char)*(i+1));
			new_string[i] = work_state->content[line].str[j];
			i++;
			}
		new_string = (char*) realloc(new_string, sizeof(char)*(i+1));
		new_string[i] = '\0';

		//printf("new line: %s\n", new_string); // debug line. Added in order to check if the code cuts any part of line. In fact, line is built from 3 parts: old pre-position, new input, old post-position
		free(work_state->content[line].str);
		work_state->content[line].str = new_string;
		work_state->content[line].length = i;
		work_state->content[line].last_reallocation_size = i+1;
	}
	
	fall_with_error__ins:
	return status_code;
	}

int commandList__wOpt(WorkState* work_state) {
	int status_code = 0;
	FILE* file_stream = fopen(work_state->filename, "w");
	for (int i = 0 ; i < work_state->lines_amount; ++i) {
		fputs(work_state->content[i].str, file_stream);
		fputc('\n', file_stream);
		}
	
	return status_code;
	}

int commandList__aflOpt(WorkState* work_state, int line) {
	int status_code = 0;
	/*work_state->content = (String*) realloc(work_state->content, (1 + work_state->lines_amount++)*sizeof(String))
	
	for(int i = work_state->lines_amount-1; i >= line ; --i) {
		
		}*/
	if(line>=work_state->lines_amount) {
		line = work_state->lines_amount;
		}
	
	if(line < 0) {
		status_code = 1;
		goto fall_with_error__afl;
		}
	
	if(status_code == 0) {
		work_state->content = (String*)realloc(work_state->content, (1+work_state->lines_amount++)*sizeof(String));

		String empty_line{(char*) malloc(sizeof(char)), 0, 1};

		for (int i = work_state->lines_amount-1 ; i  > line ; --i) {
			if (i != 0) 
				work_state->content[i] = work_state->content[i-1];
			else
				{
				printf("Setting 0 line on \\0");
				String empty{(char*)malloc(sizeof(char)), 0, 1};
				empty.str[0] = '\0';
				work_state->content[0] = empty;	
				}
		}
	
		work_state->content[line] = empty_line;
	/*
	String new_str;
	new_str.str = (char*)malloc(1*sizeof(char));
	new_str.str[0] = '\0';
	new_str.length = 0;
	new_str.last_reallocation_size = 1;
	work_state->content[line] = new_str;
*/
	}

	fall_with_error__afl:
	return status_code;
	}


int commandList__rmlOpt(WorkState* work_state, int line) {
	int status_code = 0;

	if(status_code == 0){
		free(work_state->content[line].str); // making string free. Now it is ready to be removed. Writing in order not to forget why did I write this line;
		for(int i = line; i < work_state->lines_amount-1; ++i) {
			work_state->content[i] = work_state->content[i+1];
			}
		work_state->lines_amount--;
		work_state->content = (String*)realloc(work_state->content, sizeof(String)*work_state->lines_amount);
		}

	fall_with_error_rml:
	return status_code;
	}







int recognizeCommand(WorkState* work_state, char* prompt) {
	int status_code = OK;
	int recognized = -1; // -1 - unrecognized; 0 - recognized, but no function provided at the moment (only for in-dev versions); 1 - recognized

	if(strcmp(prompt, "out") == OUTPUT__STRCMP_SAMESTR) {
		int start_pos;
		int end_pos;

		printf("Enter start position and end position (lines):\n");
		cin >> start_pos >> end_pos;

		char c_fix; // fix, which removes \n char from input. Bugfix for cin.
		while((c_fix = getchar())!=EOF && c_fix != '\n');

		int status = commandList__outOpt(work_state, start_pos, end_pos);

		switch (status) {
			case 1:
				cout << "One of the arguments is less than -1" << endl;
				break;
			case 2:
				cout << "end position is less than start position" << endl;
			}

		recognized = 1;
		} 







	if(strcmp(prompt, "q") == OUTPUT__STRCMP_SAMESTR) {
		cout << "Stopping text editor" << endl;
		
		status_code = END_EXECUTION_FLAG;

		recognized = 1;
		}








	if(strcmp(prompt, "ins") == OUTPUT__STRCMP_SAMESTR) {
		recognized = 1;
		
		int line, position;
		
		printf("Enter line number and position:\n");
		cin >> line >> position;
		
		char c_fix;
		while((c_fix = getchar())!=EOF && c_fix != '\n');
		
		int status = commandList__insOpt(work_state, line, position);
		switch(status_code) {
			case 1:
			
			case 2:;
			}
		}

	if(strcmp(prompt, "w") == OUTPUT__STRCMP_SAMESTR) {
		recognized = 1;

		int status = commandList__wOpt(work_state);
		}


	if(strcmp(prompt, "afl") == OUTPUT__STRCMP_SAMESTR) {
		recognized = 1;

		int line;
		cin >> line;

		char c_fix;
		while((c_fix = getchar()) != EOF && c_fix != '\n');

		int status = commandList__aflOpt(work_state, line);
		}


		if(strcmp(prompt, "rml") == OUTPUT__STRCMP_SAMESTR) {
			recognized = 1;

			printf("Enter number of line, which you want to remove:\n");
			int line;
			cin >> line;

			char c_fix;
			while((c_fix = getchar()) != EOF && c_fix != '\n');

			int status = commandList__rmlOpt(work_state, line);
			
			switch(status) {
				
				}
			} 

		
		if(strcmp(prompt, "raw") == OUTPUT__STRCMP_SAMESTR) {
			recognized = 1;
			//realization for raw mode editor
			}




	if (strcmp(prompt, "DEBUG__DROP") == OUTPUT__STRCMP_SAMESTR) {
		LOCAL__dropInformation(work_state);

		recognized = 1;
		}




	if(recognized == -1) {
		cout << "Write h in order to get help list" << endl;
		}

	return status_code;
	}

// easier to keep these funcs in the end
int readFile(WorkState* work_state, char* filename);
int freeAll(WorkState* work_state);

int readConfig(WorkState* work_state);

int editorControl(char** start_props) {
	int status_code = OK;

	//enableRawMode(); // decided to make it as an option
	//printf("start_props: %s\n", start_props[1]); // checking if it gets argv. Debug

	WorkState* work_state = (WorkState*) malloc(sizeof(WorkState)); // wow, it works... Understood after 12 hours of coding
	readFile(work_state, start_props[1]);

	bool loop_flag = true;
	while(loop_flag) {
		cout << "$ "; // to be sure that it starts prompt and program didn't fall into infinite cycle somewhere
		char c;
		char* input_str;
		int curr_size = 1;
		int curr_pos = 0;
		input_str = new char[sizeof(char)];
		while((c = getchar()) != EOF && c != '\n'){
			if(curr_pos == curr_size-1){
				reallocCharPtr(input_str, curr_size+32);
				curr_size+=32;
				//printf("reallocated: %d - %s\n", curr_size, input_str); // debug line
				}
			input_str[curr_pos] = c;
			//printf("%c - %s\n", c, input_str); // debug line
			curr_pos++;
			}

		reallocCharPtr(input_str, curr_pos+1);
		input_str[curr_pos] = '\0'; // end of string

		//printf("calling with: %s\n", input_str);
		int recognize_status;
		if(strcmp(input_str, "\0") == OUTPUT__STRCMP_SAMESTR) goto empty_str_fix;
		//c = getchar(); // fix
		recognize_status = recognizeCommand(work_state, input_str);
		if(recognize_status == END_EXECUTION_FLAG) {
			loop_flag = false;
			}

empty_str_fix:

		curr_size = 1;
		curr_pos = 0;

		delete[]input_str;

		if(c == EOF) {
			loop_flag = false;
			cout << "^D\n";
			}
		}

	freeAll(work_state);

	return status_code;
	}

int readFile(WorkState* work_state, char* filename) {
	int status_code = OK;

	work_state->filename = new char[strlen(filename) + 1];

	for(int i = 0 ; i < strlen(filename) ; ++i) {
		work_state->filename[i] = filename[i];
		}
	work_state->filename[strlen(filename)] = '\0';



	int lines_amount = countLines(work_state);
	//printf("%d\n", lines_amount);
	FILE* f_thread = fopen(work_state->filename, "r");
	work_state->content = (String*) malloc(sizeof(String) * lines_amount);
	work_state->lines_amount = lines_amount;

	char c;
	// #define ll long long
	int string_index = 0;
	int string_column = 0;
	
	initializeStringsWithZero(work_state, lines_amount);

	while((c=fgetc(f_thread)) != EOF) {
		if (c != '\n') {
			if (work_state->content[string_index].last_reallocation_size <= string_column + 1) {
				reallocCharPtr(work_state->content[string_index].str, work_state->content[string_index].last_reallocation_size+32);
				work_state->content[string_index].last_reallocation_size += 32;
				//printf("reallocating\n");
				}
			work_state->content[string_index].str[string_column] = c;
			string_column++;
			work_state->content[string_index].length++;
			} else {
			reallocCharPtr(work_state->content[string_index].str, work_state->content[string_index].length+1);
			work_state->content[string_index].last_reallocation_size = work_state->content[string_index].length+1;
			work_state->content[string_index].str[work_state->content[string_index].length] = '\0';
			work_state->content[string_index].length++;


			string_column = 0;
			string_index++;
			}
		}

	return status_code;
	}

int freeAll(WorkState* work_state) {
	int status_code = OK;

	//printf("%s\n", work_state->filename);

	for (int i = 0 ; i < work_state->lines_amount ; ++i) {
		free(work_state->content[i].str);
		}


	free(work_state->content);
	free(work_state->filename);
	free(work_state);

	return status_code;
	}

int readConfig(WorkState* work_state) {
	int status_code = 0; // 0 - OK, 1 - no config, 2 - couldn't read config (unknown error)
	
	return status_code;
	}
