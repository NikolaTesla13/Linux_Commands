#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

#include "../include/ls.h"

int main(int argc, char** argv) {
    if(argv[1]) {
        return list_dir(argv[1]);
    } else {
        char cwd[4096];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            return list_dir(cwd);
        }
    }
    return EXIT_FAILURE;
}


int is_file(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) {
      return EXIT_FAILURE;
   }

   char files[300], dirs[300];
   strcpy(files, "");
   while ((entry = readdir(dir)) != NULL) {
       if(is_file(entry->d_name)) {
            if(entry->d_name[0] != '.') {
                strcat(files, entry->d_name);
                strcat(files, "  ");
            }
       } else {
            if(entry->d_name[0] != '.') {
                strcat(dirs, entry->d_name);
                strcat(dirs, "  "); 
            }
       }
   }
   printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, files);
   printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, dirs);
   closedir(dir);

   return EXIT_SUCCESS;
}