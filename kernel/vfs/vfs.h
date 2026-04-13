#ifndef VFS_H
#define VFS_H

typedef struct folder folder;

typedef struct
{
    char nome[32];
    char* data;
    folder* parent;
} file;

typedef struct folder {
    char nome[128];
    struct folder* parent;
    file** files;
    unsigned int filecount;
    struct folder** subfolders;      
    unsigned int subfoldercount;     
} folder;

typedef struct {
    char currentPath[64];
    int busy;
    char taskDescription[128];
    folder* current_folder;
} vfs_cursor;

void init_vfs();
vfs_cursor* init_cursor();
void create_file(vfs_cursor* cursor, char* nome, char* conteudo);
void list_files(vfs_cursor* cursor);

void test_vfs();

#endif
