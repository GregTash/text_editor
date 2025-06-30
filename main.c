/*** includes ***/

#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*** data ***/

//Create a terminal state that replicates the default state
struct termios original_termios;

/*** terminal ***/

void die(const char *s) {
    perror(s);
    exit(1);
}

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        die("tcsetattr");
}

void enable_raw_mode() {
    //Get current flags
    if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
        die("tcgetattr");
    
    atexit(disable_raw_mode);
    
    //Change a bunch of flags for the 'raw' state
    struct termios raw = original_termios;
    raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0; //Sets minimum bytes needed before read() can return
    raw.c_cc[VTIME] = 1; //Sets amount of time in 1/10th of a second before read() returns automatically
    
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

/*** init ***/

int main() {
    enable_raw_mode();
    
    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            die("read");

        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }

        if (c == 'q') break;
    }

    return 0;
}