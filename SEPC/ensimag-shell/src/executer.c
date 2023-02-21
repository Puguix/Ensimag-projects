#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include "jobList.h"
#include "readcmd.h"
#include "variante.h"

extern jobList *jobs;

// pour limiter le temps de calcul d'un processus
static unsigned long timeLimit = 0;
bool has_limit = false;

void executer(struct cmdline *l) {
    char **command;
    char **command2;
    if ((command = l->seq[0])) {
        // commande interne jobs qui donne les taches de fond
        if (!strcmp(command[0], "jobs")) {
            // affiche tous les jobs en cours avec leur pid
            for (jobList *job = jobs; job != NULL; job = job->nextJob) {
                printf("La commande %s du processus n°%d est en cours!\n", job->command, job->pid);
            }
        }
        // commande interne ulimit
        else if (!strcmp(command[0], "ulimit")) {
            timeLimit = atoi(command[1]);
            has_limit = true;
            printf("time limit changed to %ld seconds\n", timeLimit);
        }

        // commandes de base
        else {
            pid_t pid = fork();

            switch (pid) {
                case -1:
                    perror("fork");  // error
                    break;

                case 0:  // processus fils

                    // si on a deux commandes liées par un pipe
                    if ((command2 = l->seq[1])) {
                        int tuyau[2];
                        if (pipe(tuyau)) {
                            perror("Error pipe 28");
                        }

                        pid_t pid2 = fork();

                        switch (pid2) {
                            case -1:
                                perror("fork 27");  // error
                                break;

                            case 0:
                                // on est dans la seconde commande du pipe
                                if (close(tuyau[1])) {
                                    perror("Erreur close 26");
                                    exit(EXIT_FAILURE);
                                }
                                if (dup2(tuyau[0], STDIN_FILENO)) {
                                    perror("Erreur dup2 25");
                                    exit(EXIT_FAILURE);
                                }
                                if (close(tuyau[0])) {
                                    perror("Erreur close 24");
                                    exit(EXIT_FAILURE);
                                }

                                // si on doit connecter la sortie à un fichier
                                if (l->out) {
                                    int fd = open(l->out, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                                    if (fd == -1) {
                                        perror("Erreur open 23");
                                        exit(EXIT_FAILURE);
                                    }
                                    if (ftruncate(fd, 0)) {
                                        perror("Erreur ftruncate 22");
                                        exit(EXIT_FAILURE);
                                    }
                                    if (dup2(fd, STDOUT_FILENO)) {
                                        perror("Erreur dup2 21");
                                        exit(EXIT_FAILURE);
                                    }

                                    if (close(fd)) {
                                        perror("Erreur close 20");
                                        exit(EXIT_FAILURE);
                                    }
                                }

                                // si on a définit une limite du temps de calcul
                                if (has_limit) {
                                    struct rlimit limit = {timeLimit, timeLimit + 5};
                                    if (setrlimit(RLIMIT_CPU, &limit)) {
                                        perror("Erreur setrlimit 19");
                                        exit(EXIT_FAILURE);
                                    }
                                }

                                if (execvp(command2[0], command2)) {
                                    perror("Erreur execvp 18");
                                    exit(EXIT_FAILURE);
                                }
                                break;

                            default:
                                // on est dans la première commande du pipe
                                if (close(tuyau[0])) {
                                    perror("Erreur close 17");
                                    exit(EXIT_FAILURE);
                                }
                                if (dup2(tuyau[1], STDOUT_FILENO)) {
                                    perror("Erreur dup2 16");
                                    exit(EXIT_FAILURE);
                                }
                                if (close(tuyau[1])) {
                                    perror("Erreur close 15");
                                    exit(EXIT_FAILURE);
                                }

                                // si on doit connecter l'entrée à un fichier
                                if (l->in) {
                                    int fd = open(l->in, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                                    if (dup2(fd, STDIN_FILENO)) {
                                        perror("Erreur dup2 14");
                                        exit(EXIT_FAILURE);
                                    }
                                    if (close(fd)) {
                                        perror("Erreur close 13");
                                        exit(EXIT_FAILURE);
                                    }
                                }

                                // si on a définit une limite du temps de calcul
                                if (has_limit) {
                                    struct rlimit limit = {timeLimit,
                                                           timeLimit + 5};
                                    if (setrlimit(RLIMIT_CPU, &limit)) {
                                        perror("Erreur setrlimit 12");
                                        exit(EXIT_FAILURE);
                                    }
                                }

                                if (execvp(command[0], command)) {
                                    perror("Erreur execvp 11");
                                    exit(EXIT_FAILURE);
                                }
                                break;
                        }
                    }

                    // si on a qu'une commande
                    else {
                        // si on doit connecter l'entrée à un fichier
                        if (l->in) {
                            int fd = open(l->in, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                            if (fd == -1) {
                                perror("Erreur open 10");
                                exit(EXIT_FAILURE);
                            }
                            if (dup2(fd, STDIN_FILENO)) {
                                perror("Erreur dup2 9");
                                exit(EXIT_FAILURE);
                            }
                            if (close(fd)) {
                                perror("Erreur close 8");
                                exit(EXIT_FAILURE);
                            }
                        }

                        // si on doit connecter la sortie à un fichier
                        if (l->out) {
                            int fd = open(l->out, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                            if (fd == -1) {
                                perror("Erreur open 7");
                                exit(EXIT_FAILURE);
                            }
                            if (ftruncate(fd, 0)) {
                                perror("Erreur ftruncate 6");
                                exit(EXIT_FAILURE);
                            }
                            if (dup2(fd, STDOUT_FILENO)) {
                                perror("Erreur dup2 5");
                                exit(EXIT_FAILURE);
                            }
                            if (close(fd)) {
                                perror("Erreur close 4");
                                exit(EXIT_FAILURE);
                            }
                        }

                        if (has_limit) {
                            struct rlimit limit = {timeLimit, timeLimit + 5};

                            if (setrlimit(RLIMIT_CPU, &limit)) {
                                perror("Erreur setrlimit 3");
                                exit(EXIT_FAILURE);
                            }
                        }
                        if (execvp(command[0], command)) {
                            perror("Erreur execvp 2");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    }
                default:  // processus père

                    // si la commande est une tache de fond
                    if (l->bg) {
                        jobs = createJob(pid, command[0], jobs);
                    }

                    // sinon
                    else {
                        int status;
                        if (waitpid(pid, &status, 0)) {
                            perror("Erreur waitpid");
                        }
                    }
                    break;
            }
        }
    }
}