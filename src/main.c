#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#include"ScheaShell.h"


/*  the functions that do things  */


int schea_init() {
  
  printf("\n %s\n", schea_init_msg);
  
  SCHEA_EXIT = 0;
  
  if (!(schea_cmd_pool && schea_cmd_pool_len)) {
    perror("Command pool not set correctly!\n");
    return -1;
  }
  
  return 0;
}


#define SCHEA_SPLIT_CHARS " \n"

char *schea_input;

void schea_run() {
  
  printf(schea_prompt);
  
/* ==========[getting and parsing the command]=================================================== */
  
  schea_user_cmd current_cmd;
  size_t schea_input_len;
  size_t buffer_size = 0;

  schea_input_len = getline(&schea_input, &buffer_size, stdin);
  if (schea_input_len == -1) {perror("Error reading command\n"); current_cmd.argcount = 0;}
  
  if (schea_input_len < 2) {
    printf("You need to enter a command.\n");
    current_cmd.argcount = 0;
  } else {
    uint8_t i = 0; //i doubt that you will need to enter more then 256 args
    char *cmd_part;
    cmd_part = strtok(schea_input, SCHEA_SPLIT_CHARS);
    while (cmd_part != NULL) {
      current_cmd.args[i] = cmd_part;
      i++;
      cmd_part = strtok(NULL, SCHEA_SPLIT_CHARS);
    }
    current_cmd.argcount = i;
  }

/* ============================================================================================== */
  
  if (current_cmd.argcount == 0){return;} //if theres a problem just go to the next command
  
  if (!strcmp(current_cmd.args[0], schea_exit_cmd)) { //exit command
    printf("%s\n", schea_exit_msg);
    SCHEA_EXIT = 1;
    return;
  }
  
  if (!strcmp(current_cmd.args[0], schea_help_cmd)) { //help command
    
    for (unsigned int i = 0; i < schea_cmd_pool_len; i++) {
      
      printf(" %s", schea_cmd_pool[i].name);
      
      int dist = 12 - strlen(schea_cmd_pool[i].name);
      for (unsigned int d = 0; d < dist; d++) {
        printf(" ");
      }
      
      printf(" : ");
      
      printf("%s\n", schea_cmd_pool[i].desc);
    }
    return;
  }
  
  //checking which custom command it is
  for (unsigned int i = 0; i < schea_cmd_pool_len; i++) {
    if (!strcmp(current_cmd.args[0], schea_cmd_pool[i].name)) {
      if (fork() != 0) {wait(NULL); //parent waiting
      } else {
        schea_cmd_pool[i].func(current_cmd);
        exit(0);
      }
      return;
    }
  }
  printf("%s is not a valid command.\n", current_cmd.args[0]);
  return;
}
