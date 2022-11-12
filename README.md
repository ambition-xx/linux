# linux
nowcoder linux study notes
牛客网 Linux课程学习笔记
## UDP通信
```
#include <sys/types.h>
#include <sys/socket.h>
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
const struct sockaddr *dest_addr, socklen_t addrlen);
- 参数：
- sockfd : 通信的fd
- buf : 要发送的数据
- len : 发送数据的长度
- flags : 0
- dest_addr : 通信的另外一端的地址信息
- addrlen : 地址的内存大小
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
struct sockaddr *src_addr, socklen_t *addrlen);
- 参数：
- sockfd : 通信的fd
- buf : 接收数据的数组
- len : 数组的大小
- flags : 0
- src_addr : 用来保存另外一端的地址信息，不需要可以指定为NULL
- addrlen : 地址的内存大小
```
## 广播
```
// 设置广播属性的函数
int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t
optlen);
- sockfd : 文件描述符
- level : SOL_SOCKET
- optname : SO_BROADCAST
- optval : int类型的值，为1表示允许广播
- optlen : optval的大小
```
## 组播
```
int setsockopt(int sockfd, int level, int optname,const void *optval,socklen_t ptlen);
// 服务器设置多播的信息，外出接口
- level : IPPROTO_IP
- optname : IP_MULTICAST_IF
- optval : struct in_addr

// 客户端加入到多播组：
- level : IPPROTO_IP
- optname : IP_ADD_MEMBERSHIP
- optval : struct ip_mreq

struct ip_mreq
{
    /* IP multicast address of group. */
    struct in_addr imr_multiaddr; // 组播的IP地址
    /* Local IP address of interface. */
    struct in_addr imr_interface; // 本地的IP地址
};

typedef uint32_t in_addr_t;
struct in_addr
{
    in_addr_t s_addr;
};

```
# 本地套接字
本地套接字的作用：本地的进程间通信
有关系的进程间的通信
没有关系的进程间的通信
本地套接字实现流程和网络套接字类似，一般呢采用TCP的通信流程。
```
// 本地套接字通信的流程 - tcp
// 服务器端
1. 创建监听的套接字
int lfd = socket(AF_UNIX/AF_LOCAL, SOCK_STREAM, 0);
2. 监听的套接字绑定本地的套接字文件 -> server端
struct sockaddr_un addr;
// 绑定成功之后，指定的sun_path中的套接字文件会自动生成。
bind(lfd, addr, len);
3. 监听
listen(lfd, 100);
4. 等待并接受连接请求
struct sockaddr_un cliaddr;
int cfd = accept(lfd, &cliaddr, len);
5. 通信
接收数据：read/recv
发送数据：write/send
6. 关闭连接
close();
// 客户端的流程
1. 创建通信的套接字
int fd = socket(AF_UNIX/AF_LOCAL, SOCK_STREAM, 0);
2. 监听的套接字绑定本地的IP 端口
struct sockaddr_un addr;
// 绑定成功之后，指定的sun_path中的套接字文件会自动生成。
bind(lfd, addr, len);
3. 连接服务器
struct sockaddr_un serveraddr;
connect(fd, &serveraddr, sizeof(serveraddr));
4. 通信
接收数据：read/recv
发送数据：write/send
5. 关闭连接
close();

```