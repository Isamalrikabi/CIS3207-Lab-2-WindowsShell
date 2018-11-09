/*
 * Student: Hieu Khuong
*/

#define _GNU_SOURCE
#define _XOPEN_SOURCE

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

// environment variable
extern char **environ;

//length of argument
int args_len(char **args) {
    int i = 0;
    for (i = 0; args[i] != NULL; i++) {}
    return i;
}



// built in functinon for quit
int sh_quit(char **args) {
    // quit by just returning 0
    return 0;
}



// builtin function for cd
int sh_cd(char **args) {
    // if there is no argument, change to $HOME
    if (args[1] == NULL) {
        // to be filled
        char *home;
        if ((home = getenv("HOME")) == NULL)
            fprintf(stderr, "cannot get $HOME");
        else {
            if (chdir(home) == -1)
                fprintf(stderr, "cd: %s\n", strerror(errno));
        }
    } else {
        if (chdir(args[1]) == -1)
            fprintf(stderr, "cd: %s: %s\n", strerror(errno), args[1]);
    }

    return 1;
}





// built in function for help
int sh_help(char **args) {
    char *man[] = {"more", "readme", NULL};
    return proc_launch(man);
}




// built in function for pause
int sh_pause(char **args) {
    printf("Press 'Enter' to continue...");
    while (getchar() != '\n');
    return 1;
}



//Built in for echo
int sh_echo(char **args) {
    if (args[1] == NULL)
        fprintf(stdout, "\n");
    else {
        for (int i = 1; args[i] != NULL; i++)
            printf("%s ", args[i]);
        printf("\n");
    }
    return 1;
}



int sh_environ(char **args) {
    for (int i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
    return 1;
}

// built in function for export
int sh_export(char **args) {

    if (args[1] == NULL) {
        char *env[] = {"env", NULL};
        return proc_launch(env);
    } else {
        if (putenv(args[1]) != 0) {
            fprintf(stderr, "cannot export environment");
        }
    }
    return 1;
}



// detect '|', '<<', '>>', '<', '>'
int detect_symbol(char **args) {
    
    if (args[0] == NULL)
        return -1;

    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] == PIPE)
            return 0;
        if (args[i][0] == LEFT)
            return 1;
        if (args[i][0] == RIGHT)
            return 2;
    }

    return -1;
}

// built in function for clr
int sh_clr(char **args) {
    system("clear");
    return 1;
}

// return the position of the special character
int detect_symbol_pos(char **args) {

    if (args[0] == NULL)
        return -1;

    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] == PIPE ||
            args[i][0] == LEFT ||
            args[i][0] == RIGHT)
            return i;
    }

    // return -1 if nothing found
    return -1;
}


pid_t Fork(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return pid;
}