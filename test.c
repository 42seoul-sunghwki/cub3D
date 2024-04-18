#include <stdio.h>
#include <unistd.h>

int main() {
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_cores < 0) {
        perror("sysconf");
        return 1;
    }
    printf("Number of CPU cores: %ld\n", num_cores);
    return 0;
}
