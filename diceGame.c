#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>


int winning_score;	// Global variable


void referee() {
	int tata_score, titi_score, toto_score, won=0;
	char msg[25];

	int fd = open("sharedFile.bin", O_RDONLY);
	if(fd < 0)
		return;

	// Read scores of all the players from the file
	lseek(fd, 0, SEEK_SET);
	read(fd, &tata_score, sizeof(int));
	read(fd, &titi_score, sizeof(int));
	read(fd, &toto_score, sizeof(int));

	printf("\n\nI'm referee reading the scores: (Tata: %d, Titi: %d, Toto: %d)\n", tata_score, titi_score, toto_score);

	if(tata_score >= winning_score)
	{
		sprintf(msg, "\nTata won with score %d\n", tata_score);
		won = 1;
	}
	else if(titi_score >= winning_score)
	{
		sprintf(msg, "\nTiti won with score %d\n", titi_score);
		won = 1;
	}
	else if(toto_score >= winning_score)
	{
		sprintf(msg, "\nToto won with score %d\n", toto_score);
		won = 1;
	}

	if(won == 1)
	{
		write(STDOUT_FILENO, msg, sizeof(msg));
		sleep(3);
		// Kill all the processes
		kill(0, SIGTERM);
	}
}


void no_action() {}


int getRandomInteger(int n)
{
	srand(time(NULL));
	return(rand() % n + 1);
}


void player(char *name, int playerId, int fd)
{
	int prev_score, dice_score, total_score;
	signal(SIGUSR1, referee);

	while(1)
	{
		pause();
		printf("\n\nI'm %s (Player ID: %d), and now playing the dice...\n", name, playerId);
		dice_score = getRandomInteger(10);
		printf("Got the dice score %d\n", dice_score);

		lseek(fd, playerId*sizeof(int), SEEK_SET);
		read(fd, &prev_score, sizeof(prev_score));
		printf("My score yet so far: %d\n", prev_score);

		total_score = prev_score + dice_score;
		printf("Total score: %d\n", total_score);
		lseek(fd, playerId*sizeof(int), SEEK_SET);
                write(fd, &total_score, sizeof(total_score));

		sleep(2);
		kill(getppid(), SIGUSR1);
	}
}


int main()
{
	int tata_score = 0, titi_score = 0, toto_score = 0;
	int tata_pid, titi_pid, toto_pid;

	// Open the file and retrieve the file descriptor
	int fd = open("sharedFile.bin", O_CREAT | O_RDWR, 0777);

	printf("This is a 3-player game with a referee\n");
	printf("Enter winning score: ");
	scanf("%d", &winning_score);


	// Write initial values 0 for each of the player to the file
	write(fd, &tata_score, sizeof(tata_score));
	write(fd, &titi_score, sizeof(titi_score));
	write(fd, &toto_score, sizeof(toto_score));

	sleep(2);

	// Create the child processes Tata, Titi, and Toto
	if((tata_pid=fork())==0) player("Tata", 0, fd);
	if((titi_pid=fork())==0) player("Titi", 1, fd);
	if((toto_pid=fork())==0) player("Toto", 2, fd);

	signal(SIGUSR1, no_action);

	while(1)
	{
		kill(tata_pid, SIGUSR1);
		pause();
		kill(titi_pid, SIGUSR1);
		pause();
		kill(toto_pid, SIGUSR1);
 		pause();
		sleep(2);
	}

	close(fd);
}
