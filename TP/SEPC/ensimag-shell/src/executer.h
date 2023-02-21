#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variante.h"
#include "readcmd.h"

#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "jobList.h"

void executer(struct cmdline *l);