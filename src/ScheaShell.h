#ifndef __SCHEASHELL_H__
#define __SCHEASHELL_H__

#include<stdint.h>

uint8_t SCHEA_EXIT = 0; //set this to one for the shell to exit


/*  defining custom types  */

#define MAX_ARGS 128
typedef struct { //the command after it's been separated and organized
  uint8_t argcount;
  char *args[MAX_ARGS];
} schea_user_cmd;

typedef struct { //how the commands are stored in the command pool
  char *name;
  char *desc;
  void (*func)(schea_user_cmd);
} schea_shell_cmd;


schea_shell_cmd *schea_cmd_pool; //a pointer to the pool of commands
unsigned int schea_cmd_pool_len; //how big the pool is

//custom text stuff;  these are just the defaults, the programmer can set these manually
char *schea_init_msg = "ScheaShell Started!";
char *schea_exit_msg = "Exiting ScheaShell!";
char *schea_prompt = "> ";
char *schea_exit_cmd = "exit";
char *schea_help_cmd = "help";


int schea_init();

void schea_run();

#endif
