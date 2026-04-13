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
    root->subfolders = NULL;
    root->subfoldercount = 0;
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
        for (unsigned int i = 0; i < pasta->filecount - 1; i++)
            novo[i] = pasta->files[i];
        free(pasta->files);
        pasta->files = novo;
    }

    file* novo_arquivo = (file*)malloc(sizeof(file));
    strcpy(novo_arquivo->nome, nome);
    novo_arquivo->parent = pasta;

    int tam = strlen(conteudo);
    novo_arquivo->data = (char*)malloc(tam + 1);
    strcpy(novo_arquivo->data, conteudo);

    pasta->files[pasta->filecount - 1] = novo_arquivo;

    cursor->busy = 0;
    strcpy(cursor->taskDescription, "");
}

void create_folder(vfs_cursor* cursor, char* nome)
{
    folder* parent = cursor->current_folder;

    folder* nova = (folder*)malloc(sizeof(folder));
    strcpy(nova->nome, nome);
    nova->parent = parent;
    nova->files = NULL;
    nova->filecount = 0;
    nova->subfolders = NULL;
    nova->subfoldercount = 0;

    parent->subfoldercount++;

    if (parent->subfolders == NULL) {
        parent->subfolders = (folder**)malloc(sizeof(folder*));
    } else {
        folder** novo = (folder**)malloc(parent->subfoldercount * sizeof(folder*));
        for (unsigned int i = 0; i < parent->subfoldercount - 1; i++)
            novo[i] = parent->subfolders[i];
        free(parent->subfolders);
        parent->subfolders = novo;
    }

    parent->subfolders[parent->subfoldercount - 1] = nova;
}

int change_dir(vfs_cursor* cursor, char* nome)
{
    if (strcmp(nome, "..") == 0) {
        if (cursor->current_folder->parent != NULL) {
            cursor->current_folder = cursor->current_folder->parent;
            int len = strlen(cursor->currentPath);
            for (int i = len - 1; i > 0; i--) {
                if (cursor->currentPath[i] == '/') {
                    cursor->currentPath[i] = '\0';
                    break;
                }
            }
        }
        return 1;
    }

    folder* parent = cursor->current_folder;
    for (unsigned int i = 0; i < parent->subfoldercount; i++) {
        if (strcmp(parent->subfolders[i]->nome, nome) == 0) {
            cursor->current_folder = parent->subfolders[i];
            strcat(cursor->currentPath, "/");
            strcat(cursor->currentPath, nome);
            return 1;
        }
    }

    kprintf("pasta nao encontrada: %s\n", nome);
    return 0;
}

file* find_file(vfs_cursor* cursor, char* nome)
{
    folder* pasta = cursor->current_folder;
    for (unsigned int i = 0; i < pasta->filecount; i++) {
        if (strcmp(pasta->files[i]->nome, nome) == 0)
            return pasta->files[i];
    }
    return NULL;
}

char* read_file(vfs_cursor* cursor, char* nome)
{
    file* f = find_file(cursor, nome);
    if (!f) {
        kprintf("arquivo nao encontrado: %s\n", nome);
        return NULL;
    }
    return f->data;
}

void delete_file(vfs_cursor* cursor, char* nome)
{
    folder* pasta = cursor->current_folder;
    for (unsigned int i = 0; i < pasta->filecount; i++) {
        if (strcmp(pasta->files[i]->nome, nome) == 0) {
            free(pasta->files[i]->data);
            free(pasta->files[i]);
            for (unsigned int j = i; j < pasta->filecount - 1; j++)
                pasta->files[j] = pasta->files[j + 1];
            pasta->filecount--;
            return;
        }
    }
    kprintf("arquivo nao encontrado: %s\n", nome);
}

void list_files(vfs_cursor* cursor)
{
    folder* pasta = cursor->current_folder;
    kprintf("Arquivos em %s:\n", cursor->currentPath);
    for (unsigned int i = 0; i < pasta->subfoldercount; i++)
        kprintf("  [pasta] %s\n", pasta->subfolders[i]->nome);
    for (unsigned int i = 0; i < pasta->filecount; i++)
        kprintf("  [arquivo] %s\n", pasta->files[i]->nome);
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
