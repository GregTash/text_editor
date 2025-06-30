#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen("text.txt", "a+"); 

    if (file == NULL) {
        printf("Could not open file!\n");
    } else {
        printf("File opened!\n");
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length);

    if (buffer) {
        fread(buffer, sizeof(char), length, file);
    }

    printf("%s", buffer);

    fclose(file);
    
    return 0;
}