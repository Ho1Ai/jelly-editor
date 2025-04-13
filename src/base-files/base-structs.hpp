#ifndef BASE_STRUCTS
#define BASE_STRUCTS

typedef struct {
	char* str;
	int length;
	int last_reallocation_size;
	} String;

typedef struct {
	String* content;
	char* filename;
	int lines_amount;
	} WorkState;

#endif
