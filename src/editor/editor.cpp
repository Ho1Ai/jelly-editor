#include <iostream>
#include <cstring>

#include "../base-files/base-structs.hpp"
#include "../base-files/functions-output.hpp"

using namespace std;

//commands_list:
//	out, ins, w, rml, afl, cfn, rma, rmf, c, h, q, verc


int recognizeCommand(WorkState* work_state, char* prompt) {
	int status_code = OK;
	bool recognized = false;

	if(strcmp(prompt, "out") == OUTPUT__STRCMP_SAMESTR) {
		cout << "out" << endl;
		} 

	if(!recognized) {
		cout << "Write h in order to get help list" << endl;
		}

	return status_code;
	}

// easier to keep these funcs in the end
int readFile(WorkState* work_state);
int freeAll(WorkState* work_state);

int editorControl() {
	int status_code = OK;

	return status_code;
	}

int readFile(WorkState* work_state) {
	int status_code = OK;

	return status_code;
	}

int freeAll(WorkState* work_state) {
	int status_code = OK;

	return status_code;
	}
