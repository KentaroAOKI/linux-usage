#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MEM_COUNT 1024*10
#define MEM_ALLC 1024*1024

int main(void) {
    int i;
    char *allocs[MEM_COUNT];
    int alloc_count;

    for (i = 0; i < MEM_COUNT; i++)
    {
        allocs[i] = malloc(MEM_ALLC);
        if (allocs[i] == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            break;
        }
        memset(allocs[i], 0, MEM_ALLC);
        if ((i % 100) == 0) {
            printf("%dMB memory allocated.\n", i);
            sleep(1);
        }
    }
    alloc_count = i;
    for (i = 0; i < alloc_count; i++)
    {
        free(allocs[i]);
    }
    printf("Result: %dkB memory allocated.\n", alloc_count * 1000);
    return 0;
}