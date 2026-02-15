void reallocCharPtr(char*& src, long long new_size) {
	char* new_src = new char[new_size];

	for(long long i = 0 ; i < new_size; ++i) {
		new_src[i] = src[i];
		}
	
	delete[]src;
	src = new_src;
	}
