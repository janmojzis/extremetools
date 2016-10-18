/*
20140420
Jan Mojzis
Public domain.
*/

#include <unistd.h>
#include <stdlib.h>
#include "numtostr.h"
#include "strtonum.h"
#include "e.h"
#include "die.h"

#define USAGE "extremesetuidgid: usage: extremeenvuidgid [options] program\n"
#define FATAL "extremeenvuidgid: fatal: "

static void die_usage(void) {
    die_1(100, USAGE);
}

static void die_fatal(const char *trouble, const char *fn) {
    if (errno) {
        if (fn) die_7(111, FATAL, trouble, " ", fn, ": ", e_str(errno), "\n");
        die_5(111, FATAL, trouble, ": ", e_str(errno), "\n");
    }
    if (fn) die_5(111, FATAL, trouble, " ", fn, "\n");
    die_3(111, FATAL, trouble, "\n");
}

static const char *baseidstr = "141500000";

int main(int argc, char **argv) {

    pid_t pid;
    long long id;
    char *x;

    if (argc < 2) die_usage();
    if (!argv[0]) die_usage();
    for (;;) {
        if (!argv[1]) break;
        if (argv[1][0] != '-') break;
        x = *++argv;
        if (x[0] == '-' && x[1] == 0) break;
        if (x[0] == '-' && x[1] == '-' && x[2] == 0) break;
        while (*++x) {
            if (*x == 'b') {
                if (x[1]) { baseidstr = x + 1; break; }
                if (argv[1]) { baseidstr = *++argv; break; }
            }

            die_usage();
        }
    }
    ++argv;

    if (!strtonum(&id, baseidstr) || id < 100000 || id > 300000000) die_fatal("baseid must be number > 100000 and < 300000000", 0);

    pid = getpid();
    if (pid < 0 || pid > 1000000000) pid = 0; /* XXX in this case UID=GID=baseid */
    id += pid;

    if (setenv("UID", numtostr(0, id), 1) == -1) die_fatal("unable to set env. variable $UID", 0);
    if (setenv("GID", numtostr(0, id), 1) == -1) die_fatal("unable to set env. variable $GID", 0);

    execvp(*argv, argv);
    die_fatal("unable to run", *argv);
    return 111;
}
