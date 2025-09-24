#include "scanner.h"

const char *get_ip(char *hostname) {
    struct hostent *infobyhost = gethostbyname(hostname);
    const char *ip = inet_ntoa(*((struct in_addr *)infobyhost->h_addr_list[0]));

    return ip;
}

void scanner(char *hostname) {
    int sockfd;
    struct sockaddr_in serv_addr;
    const char *ip = get_ip(hostname);

    printf("%s\n", ip);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd > 0) {
        printf("Socket create successfull\n");
    }

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    
    printf("Start scan\n");
    for (int i = 1; i < 445; ++i) {
        serv_addr.sin_port = htons(i);
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("port %d Lose\n", i);
        } else {
            printf("port %d Win\n", i);
        }
    }
    close(sockfd);
}