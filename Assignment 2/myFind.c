#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

char *fileName;    // Name of the file to be searched

static int compare_file(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
	//printf("Display info called: fpath= %-40s  ||  ftwbuf->base=%d  ||  tflag=%d\n\t ftwbuf->level=%d  ||  "
	//	 "fpath + ftwbuf->base=%s\n", fpath, ftwbuf->base, tflag, ftwbuf->level, fpath + ftwbuf->base);

	// fpath = current path; sb = stats

	if (!strcmp(fileName,(fpath + ftwbuf->base)))   	// fpath + ftwbuf->base = current file name 
	{
		printf("Found at %s\n", fpath);
	}

	// return 0 so that nftw continues search
	return 0;
}



int main(int argc, char *argv[])
{
	int flags = FTW_MOUNT;		// FTW_MOUNT suggests to look into the current file system
	char *path;   			// target directory in which the file should be searched

	if (argc == 2) {
		fileName = argv[1];
		path = "./";    		// Look into the current directory if only the file name is specified
	} else if (argc == 3) {
		fileName = argv[1];	// Search file argv[1] in the target directory argv[2]
		path = argv[2];
	} else {
		printf("Invalid Input\n");
		printf("Usage: myFind <file-name> <target-directory>\n");
		exit(0);
	}

	printf("Searching file/directory %s in the path %s \n", fileName, path);

	// nftw (target_directory, function to be called for each path, max depth of the recursive call, flags)
	if(nftw(path, compare_file, 20, flags) == -1) {
		printf("Call to nftw failed\n");
		exit(0);
	}

	printf("Program completed\n");
}
