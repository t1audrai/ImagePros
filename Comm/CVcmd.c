#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUF 1024

char buf[MAX_BUF];
int fd;


int main(int argc, char** argv) 
{
        char * myfifo = "/tmp/myfifo";
    	
	fd = open(myfifo, O_WRONLY);
	
	int i,j,k=0;

	for (i = 1; i < argc; i++){
		for( j=0; argv[i][j] != '\0'; j++){
			buf[k++] = argv[i][j];

		} 
		buf[k++] = ' ';
	}

  	write(fd, buf, sizeof(char)*MAX_BUF);
   	close(fd);

	

    return 0;
}
