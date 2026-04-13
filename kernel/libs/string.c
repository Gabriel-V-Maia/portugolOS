int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

char* strcpy(char* dest, const char* src)
{
    char* original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    

    *dest = '\0';  
    return original_dest;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

char* strcat(char* dst, const char* src)
{
    char* d = dst + strlen(dst);
    while ((*d++ = *src++) != '\0');
    return dst;
}

void* memset(void* ptr, int value, size_t size)
{
    char* p = (char*)ptr;
    for (size_t i = 0; i < size; i++)
        p[i] = (char)value;
    return ptr;
}

void* memcpy(void* dst, const void* src, size_t size)
{
    char* d = (char*)dst;
    const char* s = (const char*)src;
    for (size_t i = 0; i < size; i++)
        d[i] = s[i];
    return dst;
}

void* memmove(void* dst, const void* src, size_t size)
{
    char* d = (char*)dst;
    const char* s = (const char*)src;
    if (d < s) {
        for (size_t i = 0; i < size; i++)
            d[i] = s[i];
    } else {
        for (size_t i = size; i > 0; i--)
            d[i-1] = s[i-1];
    }
    return dst;
}
