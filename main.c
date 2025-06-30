#include <stdio.h>


int main(int argc, char *argv[]) {
    FILE *file = fopen("text.txt", "r"); 

    fclose(file);
    
    return 0;
}