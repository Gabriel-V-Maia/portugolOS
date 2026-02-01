#include "vfs.h"
#include "../mm/memory.h"
#include "../libs/string.h"
#include "../libs/kprintf.h"

static folder* root = NULL;

void init_vfs()
{
    root = (folder*)malloc(sizeof(folder));
    
    strcpy(root->nome, "/");
    root->parent = NULL;
    root->files = NULL;
    root->filecount = 0;
}

vfs_cursor* init_cursor()
{
    vfs_cursor* cursor = (vfs_cursor*)malloc(sizeof(vfs_cursor));

    cursor->busy = 0;
    strcpy(cursor->taskDescription, "");
    strcpy(cursor->currentPath, "/");
    cursor->current_folder = root;

    return cursor; 
}

void create_file(vfs_cursor* cursor, char* nome, char* conteudo)
{
    cursor->busy = 1;
    strcpy(cursor->taskDescription, "Criando arquivo...");
    
    folder* pasta = cursor->current_folder;
    
    pasta->filecount++;
    
    if (pasta->files == NULL) {
        pasta->files = (file**)malloc(sizeof(file*));
    } else {
        file** novo = (file**)malloc(pasta->filecount * sizeof(file*));
        
        for (int i = 0; i < pasta->filecount - 1; i++) {
            novo[i] = pasta->files[i];
        }
        
        free(pasta->files);
        pasta->files = novo;
    }
    
    file* novo_arquivo = (file*)malloc(sizeof(file));
    strcpy(novo_arquivo->nome, nome);
    novo_arquivo->parent = pasta;
    
    int tam = 0;
    while (conteudo[tam]) tam++;  
    
    novo_arquivo->data = (char*)malloc(tam + 1);
    strcpy(novo_arquivo->data, conteudo);
    
    pasta->files[pasta->filecount - 1] = novo_arquivo;
    
    cursor->busy = 0;
    strcpy(cursor->taskDescription, "");
}

void list_files(vfs_cursor* cursor)
{
    folder* pasta = cursor->current_folder;
    
    kprintf("Arquivos em %s:\n", cursor->currentPath);
    
    for (unsigned int i = 0; i < pasta->filecount; i++) {
        kprintf("  - %s\n", pasta->files[i]->nome);
    }
}

void test_vfs()
{
    
    init_vfs();
    
    if (root == NULL) {
        kprintf("ERRO: root eh NULL!\n");
        return;
    }
    
    kprintf("Root OK. Criando cursor...\n");
    
    vfs_cursor* cursor = init_cursor();
    
    if (cursor == NULL) {
        kprintf("ERRO: cursor eh NULL!\n");
        return;
    }
    
    kprintf("Cursor OK / ROOT OK.\n");
}
