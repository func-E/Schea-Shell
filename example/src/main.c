#include"../../src/ScheaShell.h"
#include"commands.h"

int main(void) {
  
  schea_init_msg = "Test Shell Started!";
  schea_exit_msg = "Bye Bye!";
  schea_prompt = ":) > ";
  schea_cmd_pool = cmds;
  schea_cmd_pool_len = cmds_len;
  
  schea_init();

  while (!SCHEA_EXIT) {
    schea_run();
  }
  
  return 0;
}
