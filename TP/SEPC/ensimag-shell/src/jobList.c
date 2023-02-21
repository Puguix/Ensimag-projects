#include "jobList.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

jobList *jobs = NULL;

// Insère un nouveau job dans la jobList
jobList *createJob(pid_t pid, char *command, jobList *list) {
    jobList *newJob = malloc(sizeof(jobList));
    newJob->pid = pid;
    newJob->nextJob = list;
    newJob->command = malloc(sizeof(char) * strlen(command + 1));
    strcpy(newJob->command, command);
    struct timeval depart;
    if (gettimeofday(&depart, NULL)) {
        perror("Erreur gettimeofday");
    }
    newJob->depart = depart;
    return newJob;
}

// Supprime le job en tête de jobList
jobList *removeJob(jobList *list) {
    jobList *newHead = list->nextJob;
    free(list->command);
    free(list);
    return newHead;
}

// Trouve le processus qui vient de terminer et calcule sa durée
void finished(int sig, siginfo_t *siginfo, void *ctx) {
    for (jobList *job = jobs; job != NULL; job = job->nextJob) {
        if (job->pid == siginfo->si_pid) {
            struct timeval time;
            if (gettimeofday(&time, NULL)) {
                perror("Erreur gettimeofday");
            }
            float duration = (time.tv_sec - job->depart.tv_sec) + 1E-6 * (time.tv_usec - job->depart.tv_usec);
            printf("La commande %s du processus n°%d a terminé en : %f seconds\n", job->command, job->pid, duration);
        }
    }
}
