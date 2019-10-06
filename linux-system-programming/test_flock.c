#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define USE_FCNTL
//#define USE_FLOCK

int main(void)
{
	int fd;
	int choice;

#ifdef USE_FCNTL
	struct flock fl;

	fl.l_type = F_WRLCK;	//type is write lock
	fl.l_whence = SEEK_SET;	//starting from the beginning of the file
	fl.l_start = 0;		//no offset
	fl.l_len = 0;		//to the end of the file. Note that 0 means to the EOF.
	fl.l_pid = getpid();	//current process id.
#endif /* USE_FCNTL */

	//Ask user for the type of lock
	printf("What type of lock do you want?\n");
	printf("1.write/exclusive lock\n2.read/shared lock\nAnswer: ");
	scanf("%d", &choice);
	getchar();

#ifdef USE_FCNTL
	if (choice == 2)
		fl.l_type = F_RDLCK;
#endif /* USE_FCNTL */

	fd = open("test.txt", O_RDWR);
	if (fd == -1) {
		perror("Unable to open file: ");
		exit(EXIT_FAILURE);
	}

	printf("Press <RETURN> to try to get lock: ");
	getchar();
	printf("Trying to get %s lock...\n", choice == 1 ? "write" : "read");

	//Acquire the lock using F_SETLW to wait for lock.
#ifdef USE_FCNTL
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
		perror("fcntl caused some error: ");
		exit(EXIT_FAILURE);
	}
#endif /* USE_FCNTL */

#ifdef USE_FLOCK
	if (flock(fd, LOCK_EX) == -1) {
		perror("lock err\n");
		exit(EXIT_FAILURE);
	}

#endif /* USE_FLOCK */

	printf("Locked\n");

	printf("Press <RETURN> to unlock: ");
	getchar();

	//Release the lock
#ifdef USE_FCNTL
	fl.l_type = F_UNLCK;	// set to unlock same region

	if (fcntl(fd, F_SETLK, &fl) == -1) {
		perror("fcntl caused some error: ");
		exit(EXIT_FAILURE);
	}
#endif /* USE_FCNTL */

#ifdef USE_FLOCK
	if (flock(fd, LOCK_UN) == -1) {
		perror("unlock err\n");
		exit(EXIT_FAILURE);
	}
#endif /* USE_FLOCK */

	printf("Unlocked.\n");

	close(fd);

	return EXIT_SUCCESS;
}
