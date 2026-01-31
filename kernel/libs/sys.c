
void process_command(char* cmd) {
    if (cmd[0] == '\0') {
        return;
    }
    
    kprintf("\nComando recebido: '%s'\n", cmd);
    
    if (strcmp(cmd, "info") == 0) {
        kprintf("PORTUGOL #1\n");
        mem_debug();
    }
    else {
        kprintf("Comando nao reconhecido: '%s'\n", cmd);
    }
}

