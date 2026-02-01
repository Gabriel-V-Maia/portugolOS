#ifndef SHELL_H
#define SHELL_H

void cmd_info();
void cmd_meminfo();
void cmd_memtest();
void cmd_clear();
void cmd_help();
void cmd_testvfs();

void process_command(char* cmd);

#endif
