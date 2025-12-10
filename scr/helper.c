#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void clear_s(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exit_p(){
    exit(0);
}

void getDate(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(buffer, size, "%Y-%m-%d", t);
}
int getDay(){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_mday; 
}

int getTime(){
    time_t  now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_hour;
}
void trim_leading_spaces(char *s) {
    if (s == NULL) return;
    char *p = s;
    while (*p == ' ' || *p == '\t')
        p++;

    if (p != s)
        memmove(s, p, strlen(p) + 1);
}

unsigned long long simple_hash(const char *s) {
    unsigned long long h = 1469598103934665603ULL; // FNV offset basis
    while (*s) {
        h ^= (unsigned char)(*s);
        h *= 1099511628211ULL; // FNV prime
        s++;
    }
    return h;
}

