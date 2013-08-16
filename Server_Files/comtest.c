#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char* argv[]) {

    struct termios serial;
    char* str = "Hello";
    char buffer[10];

    if (argc == 1) {
        printf("Usage: %s [device]\n\n", argv[0]);
        return -1;
    }

    printf("Opening %s\n", argv[1]);

    int fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror(argv[1]);
        return -1;
    }

    if (tcgetattr(fd, &serial) < 0) {
        perror("Getting configuration");
        return -1;
    }

    // Set up Serial Configuration
    serial.c_iflag = 0;
    serial.c_oflag = 0;
    serial.c_lflag = 0;
    serial.c_cflag = 0;

    serial.c_cc[VMIN] = 0;
    serial.c_cc[VTIME] = 0;

    serial.c_cflag = B9600 | CS8 | CREAD;

    tcsetattr(fd, TCSANOW, &serial); // Apply configuration

    // Attempt to send and receive
    printf("Sending: %s\n", str);

    int wcount = write(fd, str, strlen(str));
    if (wcount < 0) {
        perror("Write");
        return -1;
    }
    else {
        printf("Sent %d characters\n", wcount);
    }


    int rcount;
    while(1) {
	rcount = read(fd, buffer, sizeof(buffer));
	if (rcount != 0) {
		char* two = "2";
		if (strcmp(buffer, two) == 0) {
			system("./test.sh");
			printf("DB updated!\n");
		}
		
    		buffer[rcount] = '\0';
		printf("Received: %s\n", buffer);
	}
    }
    

    close(fd);
}