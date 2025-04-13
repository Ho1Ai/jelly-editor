#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static struct termios std_termios;

void disableRawMode(void) {

	}

void enableRawMode(void) {
	struct termios raw;
	}
