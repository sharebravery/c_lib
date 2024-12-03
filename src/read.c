#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief read 会自动递增文件描述符的偏移量 lseek重置文件指针
 *
 * @return int
 */
int main()
{
    int fd = open("example.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    if (write(fd, "HelloWorld", 10) == -1)
    {
        perror("write error");
        close(fd);
        return -1;
    }

    // 将文件指针重置到文件开始位置
    lseek(fd, 0, SEEK_SET);

    // 读取并打印前5个字节
    char buf[6] = {0}; // 缓冲区
    if (read(fd, buf, 5) == -1)
    {
        perror("read error");
        close(fd);
        return -1;
    }
    printf("Read 1: %s\n", buf);

    // 再读取并打印接下来的5个字节
    if (read(fd, buf, 5) == -1)
    {
        perror("read error");
        close(fd);
        return -1;
    }
    printf("Read 2: %s\n", buf);

    close(fd);
    return 0;
}
