#include <stdio.h>

void func(int * a) {
	*a = *a +1;
}

int main()
{
	int b = 0;
	printf("%d\n", b);
	func(&b);
	printf("%d\n", b);
	return 0;
}
