#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void findFile(char[]);

/** Global variable fileName **/
char *fileName;

int main(int argc, char *argv[]){
	struct dirent *dirp;
	char path[] = ".";  /** searches the file within the current directory **/

	fileName = argv[1];  /** filename to be searched is provided in the command line arguments **/

	findFile(path);

	exit(0);
}

void findFile(char *path) {
    	// printf("Finding file in path: %s ...\n", path);
   	DIR *dp = opendir(path);
	struct dirent *dirp;
	while( (dirp=readdir(dp)) != NULL) {
        	if(strcmp(dirp->d_name,".") && strcmp(dirp->d_name,"..")) {
			/** Ignoring the dirp . and .. **/
            		if(dirp->d_type == 8) {
                		/** dirp->d_type==4 for file and dirp->d_type==8 for directory **/
                		if(!strcmp(dirp->d_name,fileName)) {
                    			printf("File found: %s at %s\n",dirp->d_name, path);
                       		}
			} else {
				/** Make recursive call if the dirp->d_name is a directory **/
                		char newPath[sizeof(path)+sizeof(dirp->d_name)+1];
                		strcpy(newPath, path);
                		strcat(newPath, "/");
                		strcat(newPath, dirp->d_name);
				findFile(newPath);
            		}
        	}

	}
	closedir(dp);
}
