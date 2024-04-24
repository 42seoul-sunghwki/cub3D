#include <stdlib.h>

void	check()
{
	system("leaks a.out");
}

int main()
{
	atexit(check);
    char *c = malloc(1);

    // system("leaks a.out");
    return (0);
}
