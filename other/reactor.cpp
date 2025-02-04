#define BUFFER_LENGTH 1024

typedef int (*RCALLBACK)(int fd);

int accept_cb(int fd)
int recv_cb(int fd)
int send_cb(int fd)

struct conn_item
{
    int fd;
    char buffer[BUFFER_LENGTH];
    int idx;

    union
    {
        RCALLBACK accept_callback;
        RCALLBACK recv_callback;
    }recv_t;
    
    RCALLBACK send_callback;
};

int epfd = 0;

struct conn_item connList[1024] = {0};

// struct reactor
// {
//     int epfd;
//     struct conn_item *connList;
// };

int set_event(int fd, int event, int flag)
{
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;

    if(flag)
        epoll_ctrl(epfd, EPOLL_CTL_ADD, fd, &ev);
    else
        epoll_ctrl(epfd, EPOLL_CTL_MOD, fd, &ev);
}

int accept_cb(int fd)
{
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);

    int clientfd = accept(fd, (struct sockaddr*)&clientaddr, &len);
    if(clientfd < 0)
    {
        return -1;
    }

    set_event(clientfd, EPOLLIN, 1);
    connList[clientfd].fd = clientfd;
    memset(connList[clientfd].buffer, 0, BUFFER_LENGTH);
    connList[clientfd].idx = 0;
    connList[clientfd].recv_t.recv_callback = recv_cb;
    connList[clientfd].send_callback = send_cb;

    return clientfd;
}

int recv_cb(int fd)
{
    char *buffer = connList[fd].buffer;
    int idx = connList[fd].idx;

    int count = recv(fd, buffer + idx, BUFFER_LENGTH - idx, 0);
    if(count == 0)
    {
        printf("disconnnect!\n");
        epoll_ctrl(epfd, EPOLL_CTL_DEL, fd, NULL);
        close(fd);

        return -1;
    }
    connList[fd].idx += count;

    set_event(fd, EPOLLOUT, 0);

    return count;
}

int send_cb(int fd)
{
    char *buffer = connList[fd].buffer;
    int idx = connList[fd].idx;

    int count = send(fd, buffer, idx, 0);
    
    set_event(fd, EPOLLIN, 0);

    return count;
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr_in));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(8080);

    if(-1 == bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)))
    {
        perror("bind\n");
        return -1;
    }

    listen(sockfd, 10);

    connList[sockfd].fd = sockfd;
    connList[sockfd].recv_t.accept_callback = accept_cb;

    epfd = epoll_create(1);

    set_event(sockfd, EPOLLIN, 1);

    struct epoll_event events[1024] = {0};
    while(1)
    {
        int nready = epoll_wait(epfd, events, 1024, -1);

        int i = 0;

        for(i = 0; i < nready; i++)
        {
            int connfd = events[i].data.fd;
            if(events[i].events & EPOLLIN)
            {
                int count = connList[connfd].recv_t.recv_callback.(connfd);

                printf("recv <-- buffer: %s\n", connList[connfd].buffer);
            }
            else if(events[i].events & EPOLLOUT)
            {
                int count = connList[connfd].send_callback.(connfd);

                printf("send --> buffer: %s\n", connList[connfd].buffer);
            }
        }
    }
}