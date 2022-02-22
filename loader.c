#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#define _GNU_SOURCE         /* See feature_test_macros(7) */
#define BUFF_SIZE 1024

int memfd_create(const char *name, unsigned int flags);


void usage(char* prog)
{
	char *use = "USAGE: %1$s /path/to/binary arg_to_binary1 arg_to_binary2 ...\n";
	printf(use, prog);
}

void die(char* msg)
{
	printf("[ - ] %s\n", msg);
	printf("[ ? ] %s", strerror(errno));
	exit(errno);
}


int main(int argc, char* argv[], char* envp[])
{
	int fd1, fd2;
	char buff[BUFF_SIZE] = {0};

	if (argc < 2) {
		usage(argv[0]);
		exit(1);
	}
	
	// Create mem file (fd1)
	printf("[ * ] Trying to create a mem file...\n");
	fd1 = memfd_create("testfd", 0);
	if (fd1 < 0) die("Can't create memfd file");
	
	printf("[ + ] Created mem file and attached to fd = %d\n", fd1);
	


	// Read a local binary (fd2) and write to mem file (fd1)
	printf("[ * ] Reading %s file\n", argv[1]);
	if ((fd2 = open(argv[1], O_RDONLY)) == -1)       die("Can't open file");
	


	printf("\n ----------------------------------- \n");
	int i = 0, j = 0;
	int read_count = 0, write_count = 0;
	while( (read_count = read(fd2, buff, BUFF_SIZE)) != 0 ) {
		if( (write_count = write(fd1, buff, read_count)) == -1)
			die("Failed to write to mem file");
		
		i += read_count;
		j += write_count;
		printf("\rRead count = %6d  |  Write count = %3d", i, j);
	}
	printf("\n ----------------------------------- \n");
	
	printf("[ + ] Starting execution...\n");

	// Change argv params
	// printf("%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
	for(int i=0; i<argc; ++i)
		argv[i]  = argv[i+1];
	// printf("%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);
	
	// Execute fd1 - with new argv 
	fexecve(fd1, argv, envp);	
	
	// If fexecve returns, then it is failed.
	printf("Failed Executing....\n"); 

	return errno;
}
