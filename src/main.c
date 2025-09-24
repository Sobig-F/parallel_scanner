#include "getopt.h"
#include "scanner.h"

#define HELP_MESSAGE printf("Use: ./scanner [OPTIONS] <ARGUMENT>\n\
-h : Show this help message\n\
-s <link> : Scan <link>\n")

#define FLAGS "hs:"

int main(int argc, char *argv[]) {
    char *hostname = NULL;
    int parse = 0;
    struct hostent *infobyhost;
    char *addr = NULL;

    while ((parse = getopt(argc, argv, FLAGS)) != -1) {
        switch (parse)
        {
        case 'h':
            HELP_MESSAGE;
            break;
        case 's':
            hostname = optarg;
            scanner(hostname);
            // printf("%s\n", hostname);
            // infobyhost = gethostbyname(hostname);
            // addr = inet_ntoa(*((struct in_addr *)infobyhost->h_addr_list[0]));
            // printf("-");
            // printf("%s", addr);
            // scanner(hostname);
            break;
        default:
            break;
        }
    }
}