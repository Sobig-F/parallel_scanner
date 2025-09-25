#include "scanner.h"

#define START_PORTS 1
#define END_PORTS 1000

const char *get_ip(char *hostname) {
    struct hostent *infobyhost = gethostbyname(hostname);
    const char *ip = inet_ntoa(*((struct in_addr *)infobyhost->h_addr_list[0]));

    return ip;
}

typedef struct arguments
{
    struct sockaddr_in serv_addr;
    int port;
} arguments; 

void *scan_port(void *arg) {
    arguments *local_arg = (arguments*)arg;
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = local_arg->serv_addr;
    int port = local_arg->port;

    serv_addr.sin_port = htons(port);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        // printf("port %d Lose\n", port);
    } else {
        printf("port %d Win\n", port);
    }

    close(sockfd);
    
    return NULL;
}

void scanner(char *hostname) {
    arguments arg;
    const char *ip = get_ip(hostname);

    printf("%s\n", ip);

    arg.serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &arg.serv_addr.sin_addr);
    
    printf("Start scan\n");
    for (int i = START_PORTS; i < END_PORTS; ++i) {
        arg.port = i;
        scan_port(&arg);
    }
}

void parallel_scanner(char *hostname) {
    arguments args[END_PORTS - START_PORTS];
    pthread_t threads[END_PORTS - START_PORTS];

    const char *ip = get_ip(hostname);

    printf("%s\n", ip);
    printf("Start parallel scan\n");
    for (int i = START_PORTS; i < END_PORTS; ++i) {
        args[i - 1].serv_addr.sin_family = AF_INET;
        args[i - 1].port = i;
        inet_pton(AF_INET, ip, &args[i - 1].serv_addr.sin_addr);

        if (pthread_create(&threads[i - 1], NULL, scan_port, &args[i - 1]) != 0) {
            printf("Failed to create thread for port %d\n", i);
        }
    }

    for (int i = START_PORTS; i < END_PORTS; ++i) {
        pthread_join(threads[i - 1], NULL);
    }

    free(ip);
}