#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    // Open file with write permission (create if doesn't exist).
    int fd = open("integer.txt", O_CREAT | O_WRONLY, 0777);
    int val = 5;
    if (fd != -1) {
        write(fd, &val, sizeof(val));
        close(fd);
    }

    // Test read.
    fd = open("integer.txt", O_RDONLY);
    int new_val;
    if (fd != -1) {
        read(fd, &new_val, sizeof(new_val));
        printf("new_val = %d\n", new_val);
        close(fd);
    }
    return 0;
}
