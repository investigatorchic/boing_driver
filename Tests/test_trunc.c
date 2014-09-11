#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN 256
char buf[BUF_LEN];
int string_mod;

int main (){
	if ((string_mod = open("/dev/string", O_RDWR)) <0) {
		perror("/dev/string");
		return(1);
	}
	strncpy(buf, "Twiddlebugs!+Twiddlebugs!+Twiddlebugs!+Twiddlebugs!", 51);
	if (write(string_mod, buf, BUF_LEN) <= 0) {
		perror("/dev/string");
		return(1);
	}
	lseek(string_mod, 0, SEEK_SET);
	memset(&buf[0], 0, sizeof(buf));
	if (read(string_mod, buf, BUF_LEN) <= 0) {
		perror("read");
		return(1);
	}
	printf("%s\n", buf);	
	return(0);
}
