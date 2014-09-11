#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_LEN 256
char buf[BUF_LEN];
int string_mod;

int main (){

	if ((string_mod = open("/dev/string", O_RDONLY)) <0) {
		perror("/dev/string");
		return(1);
	}
	
	if (read(string_mod, buf, BUF_LEN) <= 0) {
		perror("read");
		return(1);
	}
	printf("%s\n", buf);
	close(string_mod);
	return(0);
}
