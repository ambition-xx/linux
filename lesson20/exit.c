/*
    #include <stdlib.h>
    void exit(int status);

    #include <unistd.h>
    void _exit(int status);

    status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以获取到。
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("hello\n");
    printf("world");

    // exit(0); //标准c库的 退出之前会 1. 调用退出处理函数 2. 刷新io缓冲
    _exit(0); //直接退出 运行后不会打印world
    
    return 0;
}