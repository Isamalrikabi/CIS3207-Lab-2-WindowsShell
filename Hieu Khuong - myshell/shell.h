#ifndef SHELL_H
#define SHELL_H

#define BUF_SIZE 200

#define TRUE 1
#define FALSE 0

#define READ 0
#define WRITE 1

#define PIPE '|'
#define RIGHT '>'
#define LEFT '<'
#define AMP '&'

#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

// main shell program
void shell_loop();
// read line
char *read_line();
// split line
char **split_line(char *);
// process launch
int proc_launch(char **);
// shell execute
int sh_execute(char **);
// invoke pipe
int invoke_pipe(char **, char **);
// redirection
int redirect(char **, char **, int);
// detect symbols
int detect_symbol(char **);
// detect symbol with position
int detect_symbol_pos(char **);
// Fork wrapper
pid_t Fork(void);

// len of args array
int args_len(char **);

/**
 *
 * BUILT IN COMMANDS
 *
 */
int num_builtins();
// cd command
int sh_cd(char **);
// help command
int sh_help(char **);
// quit command
int sh_quit(char **);
// echo command
int sh_echo(char **);
// environ command
int sh_environ(char **);
// export command
int sh_export(char **);
// pause command
int sh_pause(char **);
// clear command
int sh_clr(char **);

#endif