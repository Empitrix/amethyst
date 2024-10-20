#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef linux
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#else
#include <windows.h>
#include <conio.h>
#endif


void plat_cls(void){
#ifdef linux
	system("clear");
#elif _WIN32
	system("cls");
#endif
}


// show cursor
void enable_cursor(void){
	printf("\033[?25h");
	fflush(NULL);
}

// hide cursor
void disable_cursor(void){
	// setvbuf(stdout, NULL, _IONBF, 0);  // Disable buffering for stdout
	printf("\033[?25l");
	fflush(NULL);
}


#ifdef linux
static struct termios old, current;
#endif

// Disable Echo
void init_term(){                   // terminal i/o settings
#ifdef linux
	tcgetattr(0, &old);               // grab old terminal i/o settings
	current = old;                    // make new settings same as old settings
	current.c_lflag &= ~ICANON;       // disable buffered i/o
	current.c_lflag &= ~ECHO;         // set no echo mode
	tcsetattr(0, TCSANOW, &current);  // use these new terminal i/o settings now
#endif
}

// Enable Echo
void nrm_term(){
#ifdef linux
	tcgetattr(0, &old);
	current = old;
	current.c_lflag |= ICANON;
	current.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &current);
#endif
}

// Get a char without echo
char getl(void){
	char ch;
#ifdef linux
	init_term();
	ch = getchar();
	nrm_term();
#elif _WIN32
	ch = _getch();
#endif

	return ch;
}


/* clear terminal */
void cls_term(void){
	printf("\033[H");  // set position of cursor to [0, 0]
// #ifdef linux
// 	printf("\033[H");
// #else
// 	printf("\033[H");
// 	// printf("\033[1;1H\033[2J");
// #endif
}


static int tmp_y_siz = 0;
static int tmp_x_siz = 0;

/* ter_size: get terminal size [x, y] */
TERSIZ term_size(void){
	TERSIZ siz = {0, 0};
#ifdef linux
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	siz.x = w.ws_col;
	siz.y = w.ws_row;
#elif _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	siz.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	siz.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif

	// Clear terminal if user changes the window
	if(siz.x != tmp_x_siz || siz.y != tmp_y_siz){ plat_cls(); }
	tmp_y_siz = siz.y;
	tmp_x_siz = siz.x;

	return siz;
}

/* turn the echo on and make cursor visible */
void normal_terminal(void){
	plat_cls();
	enable_cursor();
	nrm_term();
	setvbuf(stdout, NULL, _IONBF, 0);  // Disable buffering for stdout
	fflush(NULL);
}


/* Hide terminal cursor and no echo */
void hidden_terminal(void){
	disable_cursor();  // Hide cursor block/line from the terminal
	init_term();       // No ouput from cursor
	fflush(NULL);
}

