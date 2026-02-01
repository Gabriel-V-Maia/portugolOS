#include "shell.h"
#include "../libs/kprintf.h"
#include "../libs/string.h"
#include "../vfs/vfs.h"

void cmd_info() {
    kprintf("PORTUGOL OS #1\n");
}

void process_command(char* cmd) {
    if (strcmp(cmd, "info") == 0) {
        cmd_info();
    }
    else if (strcmp(cmd, "testvfs") == 0) {
        test_vfs();
    }
}
