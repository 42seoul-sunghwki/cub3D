#include <unistd.h>
#include <stdio.h>

int main()
{
	int	a = 1;
	int	b = 2;

	printf("a: [%p]\nb: [%p]\n", &a, &b);
}