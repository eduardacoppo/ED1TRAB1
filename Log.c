#include <stdio.h>
#include <stdlib.h>
#include "Log.h"

void printLog2(char * msg, char *msg2) {
    FILE *log;
    log = fopen("log.txt", "a");

    if (log == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE LOG");
        return;
    }

    fprintf(log, "%s %s\n", msg, msg2);

    fclose(log);

    return;
}

void printLog3(char * msg, char *msg2, char *msg3) {
    FILE *log;
    log = fopen("log.txt", "a");

    if (log == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE LOG");
        return;
    }

    fprintf(log, "%s %s %s\n", msg, msg2, msg3);

    fclose(log);

    return;
}

void printLog4(char * msg, char *msg2, char *msg3, char *msg4) {
    FILE *log;
    log = fopen("log.txt", "a");

    if (log == NULL) {
        printf("ERRO AO ABRIR O ARQUIVO DE LOG");
        return;
    }

    fprintf(log, "%s %s %s %s\n", msg, msg2, msg3, msg4);

    fclose(log);

    return;
}