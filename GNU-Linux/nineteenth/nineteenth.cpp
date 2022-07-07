#include <cstring>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>

void DumpDir(char *dir_name) {
    DIR *dir = 0;
    struct stat status;
    struct dirent *direnttry;
    char TempDir[8192];
    if ((dir = opendir(dir_name)) == 0) {
        fprintf(stdout, "Failed to get into %s \n", dir_name);
        return;
    }
    while ((direnttry = readdir(dir)) != 0) {

        strcpy(TempDir, dir_name);
        strcat(TempDir, "/");
        strcat(TempDir, direnttry->d_name);
        lstat(TempDir, &status);

        if (S_ISDIR(status.st_mode)) {
            // ignore . & ..
            if (direnttry->d_name[0] == '.')
                continue;
            fprintf(stdout, "DIR:: \t%s \n", direnttry->d_name);
        } else
            fprintf(stdout, "FILE:: \t%s\n", direnttry->d_name);
    }
    closedir(dir);
    return;
}

int main(int argc, char *argv[]) {
    const char *dirname = "/usr/lib/";
    DumpDir((char *)dirname);
    return 0;
}
