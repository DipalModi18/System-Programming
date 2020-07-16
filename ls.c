#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	// The type DIR, which is defined in the header <dirent.h>, represents a directory stream,
	  //  which is an ordered sequence of all the directory entries in a particular directory.
	DIR *dp;
	struct dirent *dirp;

	if(argc == 1)
		dp = opendir("./");
	else
		dp = opendir(argv[1]);

	// Defination: struct dirent *readdir(DIR *dirp);
	while( (dirp=readdir(dp)) != NULL)
		// The readdir() function returns a pointer to a structure representing the
		 //directory entry at the current position in the directory stream specified
		 //by the argument dirp, and positions the directory stream at the next entry.
		 //It returns a null pointer upon reaching the end of the directory stream.
		printf("%s \n", dirp->d_name);

	closedir(dp);
	exit(0);
}
