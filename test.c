#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_LEN 256
char buf[BUF_LEN];
int string_mod;

int main (){
	printf("begin\n");
	if ((string_mod = open("/dev/string", O_RDONLY)) <0) {
		printf("open\n");	
		perror("/dev/string");
		return(1);
	}
	
	if (read(string_mod, buf, BUF_LEN) <= 0) {
		printf("read\n");
		perror("read");
		return(1);
	}
	printf("%s\n", buf);
	return(0);
}
