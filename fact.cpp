#include <assert.h>
#include <stdio.h>

long int fact(int x)
{
	long int r = x;
	while (--x >=2)
		r *= x;

	return r;
}

int main(void)
{
	int a, b, c = 7;

	while (scanf("%d", &a) > 0) {
		assert(a > 0);
		printf("fact: %lu\n", fact(a));
	}

	return 0;
}
