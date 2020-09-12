#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FD_COUNT 600000

int main(void) {
    int i;
    int fds[FD_COUNT];
    int fd_count;

    char *filename = malloc(128);
    for (i = 0; i < FD_COUNT; i++)
    {
        snprintf(filename, 128, "/tmp/testfd%d", i);
        printf("%s\n",filename);
        fds[i] = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        write(fds[i], "test", sizeof("test"));
        if (fds[i] == -1)
        {
            printf("Error: %s\n", strerror(errno));
            break;
        }
        if ((i % 100) == 0) {
            printf("%d fds created.\n", i);
        }
    }
    sleep(20);
    fd_count = i;
    for (i = 0; i < fd_count; i++)
    {
        close(fds[i]);
    }
    free(filename);
    printf("Result: %d fds created.\n", fd_count);
    return 0;
}