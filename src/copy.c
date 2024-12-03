#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * @brief 文件复制
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    char buf[1024] = {0};

    if (argc != 3)
    {
        fprintf(stderr, "ERROR: Usage: %s <source> <destination>\n", argv[0]);
        return -1;
    }

    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
    {
        perror("ERROR: Failed to open source file");
        return -1;
    }

    int fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_new == -1)
    {
        perror("ERROR: Failed to open destination file");
        close(fd_src);
        return -1;
    }

    int len = 0;
    while ((len = read(fd_src, buf, sizeof(buf))) > 0)
    {
        if (write(fd_new, buf, len) != len)
        {
            perror("ERROR: Failed to write to destination file");
            close(fd_src);
            close(fd_new);
            return -1;
        }
    }

    if (len < 0)
    {
        perror("ERROR: Failed to read from source file");
    }

    close(fd_src);
    close(fd_new);

    if (len == 0)
    {
        printf("File copy completed successfully.\n");
    }

    return (len < 0) ? -1 : 0;
}
