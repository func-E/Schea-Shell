#include<stdio.h>
#include<stddef.h>

/*  put the functions for the commands here  */

void test(schea_user_cmd input) {
  
  printf("testing\n1...\n2...\n3...\n");
  return;
}

void tset(schea_user_cmd input) {
  
  printf("...3\n...2\n...1\ngnitset\n");
  return;
}


/*  define the command list here  */

schea_shell_cmd cmds[] = {

/*  name      description                callback   */
  {"test"  , "this is a test command"  , test       },
  {"tset"  , "dnammoc tset a si siht"  , tset       }
  
};

size_t cmds_len = sizeof(cmds)/sizeof(cmds[0]); //this should always be here
