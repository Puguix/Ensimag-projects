#include <stdlib.h>
#include <signal.h>

/* Les commandes lancées en tache de fond sont stockés dans une jobList:
pid : le pid du processus
command : la ligne de commande
nextJob : le pointeur vers le processus suivant
depart : date de début du processus
*/

typedef struct jobList
{
    pid_t pid;
    char *command;
    struct jobList *nextJob;
    struct timeval depart;
} jobList;

// Insère un nouveau job dans list
jobList *createJob(pid_t pid, char *command, jobList *list);

// Supprime le job en tête de list
jobList *removeJob(jobList *list);

// Trouve le processus qui vient de terminer et calcule sa durée
void finished(int sig, siginfo_t *sig_info, void *ctx);