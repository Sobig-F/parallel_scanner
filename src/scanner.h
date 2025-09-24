#include <netdb.h>
#include <arpa/inet.h>
#include "threads.h"
#include "sys/socket.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

void scanner(char *hostname);
const char *get_ip(char *hostname);