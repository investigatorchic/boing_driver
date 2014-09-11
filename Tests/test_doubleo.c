#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_LEN 256
char buf[BUF_LEN];
int string_mod;

int main (){

        if ((string_mod = open("/dev/string", O_RDONLY)) <0) {
                perror("/dev/string");
                return(1);
        }

	if ((string_mod = open("/dev/string", O_RDONLY)) <0) {
                printf("Unable to open device twice. Success!\n");
                return(0);
        }

	close(string_mod);	
        return(1);
}

