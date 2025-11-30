#include "vfs.h"

typedef struct file 
{
    char nome[30];
    char* data;
    struct folder* parent; 
} file;

typedef struct folder 
{
    char nome[30];
    struct folder* parent;
    
    file** files;  
    unsigned int filecount;
} folder; 

