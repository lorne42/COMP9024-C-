#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
f1(void) {
    char* src = "f1";
    char* dst=malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void
f2(void) {
    char* src = "f2";
    char* dst = malloc(strlen(src)+1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void
f3(void) {
    char* src = "f3";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void
f4(void) {
    char* src = "f4";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void
f5(void) {
    char* src = "f5";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

static void
myprintf(char* string) {
    printf("%s\n", string);
    free(string);
}

void
f6(void) {
    char* src = "f6";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    myprintf(dst);
   
}

void
f7(void) {
    char* src = "f7";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void
f8(void) {
    char* src = "f8";
    char* dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

int
main(void) {
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
    f7();
    f8();

    return 0;
}
