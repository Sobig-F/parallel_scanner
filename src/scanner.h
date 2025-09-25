#ifndef SCANNER_H
#define SCANNER_H

#include "pthread.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>

void scanner(char *hostname);
void parallel_scanner(char *hostname);

#endif