#include <iostream>
#include <cstring>

#include "base-files/functions-output.hpp"
#include "help-list/help.hpp"

using namespace std;

int main (int argc, char** argv) {
	int status_code = OK;

	if (argc < 2) {
		cout << "Not enough arguments." << endl;
		status_code = MAIN__NOT_ENOUGH_ARGUMENTS;
		goto error_fall;
		}

	if (strcmp(argv[1], "--help") == OUTPUT__STRCMP_SAMESTR) {
		cout << HELP_LIST_OUTPUT << endl;
		}

	return status_code;
error_fall:
	cout << "Jelly fell with code: " << status_code << endl;
	return 1;
	}
