#include "getopt.h"
#include "scanner.h"

#define HELP_MESSAGE printf("Use: ./scanner [OPTIONS] <ARGUMENT>\n\
-h : Show this help message\n\
-s <link> : Scan <link>\n")

#define FLAGS "phs:"

int main(int argc, char *argv[]) {
    char *hostname = NULL;
    int parse = 0;

    while ((parse = getopt(argc, argv, FLAGS)) != -1) {
        switch (parse)
        {
        case 'h':
            HELP_MESSAGE;
            break;
        case 'p':
            hostname = optarg;
            parallel_scanner(hostname);
            break;
        default:
            break;
        }
    }
}