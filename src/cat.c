#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    size_t read;

    if(!argv[1]) {
        printf("usage: <file>\n");
        return EXIT_FAILURE;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        return EXIT_FAILURE;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    
    printf("\n");

    return EXIT_SUCCESS;
}