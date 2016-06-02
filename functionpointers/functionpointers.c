#include <stdio.h>

typedef void (*void_noargs)();

void foo() {
	printf("Hello,");
}

void bar() {
	printf(" offset");
}

int main(int argc, char *argv[]) {
	void_noargs foo_ptr = foo;
	long offset = (long) bar - (long) foo;

	foo_ptr();
	(foo_ptr + offset)();
	printf(" %ld!\n", offset);
	
	return 0;
}
