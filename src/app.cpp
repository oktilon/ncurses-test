#include <string>
#include <string.h>
#include <ncurses.h>
#include <time.h>

using namespace std;

enum ColorList {
	ColorBack = 1,
	ColorText1,
	ColorText2,
	ColorInfo,
	ColorRed,
	ColorOctal,
	ColorChar,
	ColorMagenta
};

#define BUF_SIZE 20

int main() {
	WINDOW *w;
	MEVENT ev;
	int sw,sh,ch,x,y,rm,i,sz;
	chtype bufKey[BUF_SIZE];
	time_t bufTime[BUF_SIZE];
	mmask_t bufMouse[BUF_SIZE];
	struct tm *stm;
	char buf[100];
	chtype styles[9] = {
		0,
		A_NORMAL,
		A_ITALIC,
		A_BLINK,
		A_DIM,
		A_UNDERLINE,
		A_BOLD,
		A_REVERSE,
		A_STANDOUT
	};

	string style_names[9] = {
		"   <None>   ",
		"  A_NORMAL  ",
		"  A_ITALIC  ",
		"   A_BLINK  ",
		"    A_DIM   ",
		" A_UNDERLINE",
		"   A_BOLD   ",
		"  A_REVERSE ",
		" A_STANDOUT "
	};

	short cTxt1Fore = COLOR_WHITE;
	short cTxt1Back = COLOR_BLACK;
	short cTxt1StyleIx = 0;
	short cTxt2Fore = COLOR_GREEN;
	short cTxt2Back = COLOR_BLACK;
	short cTxt2StyleIx = 0;

	for(i = 0; i < BUF_SIZE; i++) {
		bufKey[i] = 0;
		bufTime[i] = 0;
		bufMouse[i] = 0;
	}

	/* Initialize curses */
	initscr();
	nonl();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	mmask_t mmold, mmnew = ALL_MOUSE_EVENTS;
	mousemask(mmnew, &mmold);

	start_color();
	init_pair(ColorBack, COLOR_WHITE, COLOR_BLACK);
	init_pair(ColorText1, cTxt1Fore, cTxt1Back);
	init_pair(ColorText2, cTxt2Fore, cTxt2Back);
	init_pair(ColorInfo, COLOR_YELLOW, COLOR_BLACK);
	init_pair(ColorRed, COLOR_RED, COLOR_BLACK);
	init_pair(ColorOctal, COLOR_CYAN, COLOR_BLACK);
	init_pair(ColorChar, COLOR_BLUE, COLOR_BLACK);
	init_pair(ColorMagenta, COLOR_MAGENTA, COLOR_BLACK);

	sh = getmaxy(stdscr);
	sw = getmaxx(stdscr);

	chtype atBack = COLOR_PAIR(ColorBack);
	chtype atTxt1 = COLOR_PAIR(ColorText1);
	chtype atTxt2 = COLOR_PAIR(ColorText2);
	chtype atInfo = COLOR_PAIR(ColorInfo);
	chtype atRed = COLOR_PAIR(ColorRed) | A_BOLD;
	chtype atTime = COLOR_PAIR(ColorInfo) | A_ITALIC;
	chtype atOctal = COLOR_PAIR(ColorOctal);
	chtype atChar = COLOR_PAIR(ColorChar) | A_BOLD;
	chtype atMouse = COLOR_PAIR(ColorMagenta);


	w = newwin(22, 55, 12, 1);

	bkgd(atBack);
	attron(atBack);

	y = 0;
    mvprintw(y++, 60, "Upper left corner           "); addch(ACS_ULCORNER);
    mvprintw(y++, 60, "Lower left corner           "); addch(ACS_LLCORNER);
    mvprintw(y++, 60, "Lower right corner          "); addch(ACS_LRCORNER);
    mvprintw(y++, 60, "Tee pointing right          "); addch(ACS_LTEE);
    mvprintw(y++, 60, "Tee pointing left           "); addch(ACS_RTEE);
    mvprintw(y++, 60, "Tee pointing up             "); addch(ACS_BTEE);
    mvprintw(y++, 60, "Tee pointing down           "); addch(ACS_TTEE);
    mvprintw(y++, 60, "Horizontal line             "); addch(ACS_HLINE);
    mvprintw(y++, 60, "Vertical line               "); addch(ACS_VLINE);
    mvprintw(y++, 60, "Large Plus or cross over    "); addch(ACS_PLUS);
    mvprintw(y++, 60, "Scan Line 1                 "); addch(ACS_S1);
    mvprintw(y++, 60, "Scan Line 3                 "); addch(ACS_S3);
    mvprintw(y++, 60, "Scan Line 7                 "); addch(ACS_S7);
    mvprintw(y++, 60, "Scan Line 9                 "); addch(ACS_S9);
    mvprintw(y++, 60, "Diamond                     "); addch(ACS_DIAMOND);
    mvprintw(y++, 60, "Checker board (stipple)     "); addch(ACS_CKBOARD);
    mvprintw(y++, 60, "Degree Symbol               "); addch(ACS_DEGREE);
    mvprintw(y++, 60, "Plus/Minus Symbol           "); addch(ACS_PLMINUS);
    mvprintw(y++, 60, "Bullet                      "); addch(ACS_BULLET);
    mvprintw(y++, 60, "Arrow Pointing Left         "); addch(ACS_LARROW);
    mvprintw(y++, 60, "Arrow Pointing Right        "); addch(ACS_RARROW);
    mvprintw(y++, 60, "Arrow Pointing Down         "); addch(ACS_DARROW);
    mvprintw(y++, 60, "Arrow Pointing Up           "); addch(ACS_UARROW);
    mvprintw(y++, 60, "Board of squares            "); addch(ACS_BOARD);
    mvprintw(y++, 60, "Lantern Symbol              "); addch(ACS_LANTERN);
    mvprintw(y++, 60, "Solid Square Block          "); addch(ACS_BLOCK);
    mvprintw(y++, 60, "Less/Equal sign             "); addch(ACS_LEQUAL);
    mvprintw(y++, 60, "Greater/Equal sign          "); addch(ACS_GEQUAL);
    mvprintw(y++, 60, "Pi                          "); addch(ACS_PI);
    mvprintw(y++, 60, "Not equal                   "); addch(ACS_NEQUAL);
    mvprintw(y++, 60, "UK pound sign               "); addch(ACS_STERLING);

	attroff(atBack);

	attron(atTxt1);
	mvprintw(2, 2, "Demo text input 1");
	attroff(atTxt1);
	attron(atTxt2);
	mvprintw(3, 2, "Demo text input 2");
	attroff(atTxt2);

	attron(atInfo);
	mvprintw(6, 1, "TXT1 FC a/A (% 3u), BC s/S (% 3u), ST d/D (            )", cTxt1Fore, cTxt1Back);
	mvprintw(7, 1, "TXT2 FC z/Z (% 3u), BC x/X (% 3u), ST c/C (            )", cTxt2Fore, cTxt2Back);
	mvprintw(8, 1, "Exit = F10 (Mouse mask n/o = %d/%d)", mmnew, mmold);
	mvprintw(6, 42, "%s", style_names[cTxt1StyleIx].c_str());
	mvprintw(7, 42, "%s", style_names[cTxt2StyleIx].c_str());
	attroff(atInfo);
	attron(atRed);
	mvprintw(6, 9, "a/A"); mvprintw(6, 23, "s/S"); mvprintw(6, 37, "d/D");
	mvprintw(7, 9, "z/Z"); mvprintw(7, 23, "x/X"); mvprintw(7, 37, "c/C");
	mvprintw(8, 8, "F10");
	attroff(atRed);
	refresh();

	wbkgd(w, atBack);
	wattron(w, atBack);
	box(w, 0, 0);
	mvwprintw(w, 0, 2, " History ");
	wattroff(w, atBack);
	wrefresh(w);

	move(0, 0);
	refresh();

	x = getcurx(stdscr);
	y = getcury(stdscr);


	timeout(10);

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(10)) {
		rm = 1;
		if(ch > 0) {
			for(i = BUF_SIZE - 1; i > 0; i--) {
				bufKey[i] = bufKey[i-1];
				bufTime[i] = bufTime[i-1];
				bufMouse[i] = bufMouse[i-1];
			}
			bufKey[0] = ch;
			bufTime[0] = time(NULL);
			switch(ch) {
				case 'a': cTxt1Fore++; if(cTxt1Fore > 255) cTxt1Fore = 0; break;
				case 'A': cTxt1Fore--; if(cTxt1Fore < 0) cTxt1Fore = 255; break;
				case 's': cTxt1Back++; if(cTxt1Back > 255) cTxt1Back = 0; break;
				case 'S': cTxt1Back--; if(cTxt1Back < 0) cTxt1Back = 255; break;
				case 'd': cTxt1StyleIx++; if(cTxt1StyleIx > 8) cTxt1StyleIx = 0; break;
				case 'D': cTxt1StyleIx--; if(cTxt1StyleIx < 0) cTxt1StyleIx = 8; break;
				case 'z': cTxt2Fore++; if(cTxt2Fore > 255) cTxt2Fore = 0; break;
				case 'Z': cTxt2Fore--; if(cTxt2Fore < 0) cTxt2Fore = 255; break;
				case 'x': cTxt2Back++; if(cTxt2Back > 255) cTxt2Back = 0; break;
				case 'X': cTxt2Back--; if(cTxt2Back < 0) cTxt2Back = 255; break;
				case 'c': cTxt2StyleIx++; if(cTxt2StyleIx > 8) cTxt2StyleIx = 0; break;
				case 'C': cTxt2StyleIx--; if(cTxt2StyleIx < 0) cTxt2StyleIx = 8; break;
				case KEY_UP: y--; if(y < 0) y = sh - 1; break;
				case KEY_DOWN: y++; if(y >= sh) y = 0; break;
				case KEY_LEFT: x--; if(x < 0) x = sw - 1; break;
				case KEY_RIGHT: x++; if(x >= sw) x = 0; break;
				case KEY_HOME: x = 0; break;
				case KEY_END: x = sw-1; break;
				case KEY_MOUSE: rm = getmouse(&ev); break;
				default: break;
			}

			init_pair(ColorText1, cTxt1Fore, cTxt1Back);
			init_pair(ColorText2, cTxt2Fore, cTxt2Back);
			atTxt1 = COLOR_PAIR(ColorText1) | styles[cTxt1StyleIx];
			atTxt2 = COLOR_PAIR(ColorText2) | styles[cTxt2StyleIx];
			attron(atTxt1);
			mvprintw(2, 2, "Demo text input 1");
			attroff(atTxt1);

			attron(atTxt2);
			mvprintw(3, 2, "Demo text input 2");
			attroff(atTxt2);

			attron(atInfo);
			mvprintw(6, 1, "TXT1 FC a/A (% 3u), BC s/S (% 3u), ST d/D (            )", cTxt1Fore, cTxt1Back);
			mvprintw(7, 1, "TXT2 FC z/Z (% 3u), BC x/X (% 3u), ST c/C (            )", cTxt2Fore, cTxt2Back);
			if(ch) {
				mvprintw(9, 3, "KEY: 0x%x, 0%o, %d, %c                        ", ch, ch, ch, ch);
			} else {
				mvprintw(9, 3, "                                            ");
			}
			if(rm == OK) {
				bufMouse[0] = ev.bstate;
				if(ev.bstate & BUTTON1_CLICKED) {
					mvprintw(10, 3, "%03i B1   CLK [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				} else if(ev.bstate & BUTTON1_DOUBLE_CLICKED) {
					mvprintw(10, 3, "%03i B1 DBCLK [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				} else {
					mvprintw(10, 3, "%03i MOUSE EV [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				}
			} else {
				bufMouse[0] = 0;
				mvprintw(10, 3, "                                   ");
			}
			attron(styles[cTxt1StyleIx]);
			mvprintw(6, 42, "%s", style_names[cTxt1StyleIx].c_str());
			attroff(styles[cTxt1StyleIx]);
			attron(styles[cTxt2StyleIx]);
			mvprintw(7, 42, "%s", style_names[cTxt2StyleIx].c_str());
			attroff(styles[cTxt2StyleIx]);
			attroff(atInfo);

			attron(atRed);
			mvprintw(6, 9, "a/A"); mvprintw(6, 23, "s/S"); mvprintw(6, 37, "d/D");
			mvprintw(7, 9, "z/Z"); mvprintw(7, 23, "x/X"); mvprintw(7, 37, "c/C");
			mvprintw(8, 8, "F10");
			attroff(atRed);

			for(i = 0; i < BUF_SIZE; i++) {
				if(bufTime[i]) {
					stm = localtime(&bufTime[i]);
					strftime(buf, 100, "%T", stm);
					wattron(w, atTime);
					mvwprintw(w, 1+i, 1, buf);
					wattroff(w, atTime);
					wattron(w, atOctal);
					mvwprintw(w, 1+i, 10, "0%03o", bufKey[i]);
					wattroff(w, atOctal);
					wattron(w, atBack);
					mvwprintw(w, 1+i, 15, "%03u", bufKey[i]);
					wattroff(w, atBack);
					wattron(w, atChar);
					sz = sprintf(buf, "%c", bufKey[i]);
					while(sz++ < 4) strcat(buf, " ");
					mvwprintw(w, 1+i, 20, "%s", buf);
					wattroff(w, atChar);
				}
				if(bufMouse[i]) {
					wattron(w, atMouse);
					sprintf(buf, " ");
					if(bufMouse[i] & BUTTON1_RELEASED) strcat(buf, " B1_REL");
					if(bufMouse[i] & BUTTON1_PRESSED) strcat(buf, " B1_PRS");
					if(bufMouse[i] & BUTTON1_CLICKED) strcat(buf, " B1_CLK");
					if(bufMouse[i] & BUTTON1_DOUBLE_CLICKED) strcat(buf, " B1_DBCLK");
					if(bufMouse[i] & BUTTON1_TRIPLE_CLICKED) strcat(buf, " B1_TRCLK");
					if(bufMouse[i] & BUTTON2_RELEASED) strcat(buf, " B2_REL");
					if(bufMouse[i] & BUTTON2_PRESSED) strcat(buf, " B2_PRS");
					if(bufMouse[i] & BUTTON2_CLICKED) strcat(buf, " B2_CLK");
					if(bufMouse[i] & BUTTON2_DOUBLE_CLICKED) strcat(buf, " B2_DBCLK");
					if(bufMouse[i] & BUTTON2_TRIPLE_CLICKED) strcat(buf, " B2_TRCLK");
					if(bufMouse[i] & BUTTON3_RELEASED) strcat(buf, " B3_REL");
					if(bufMouse[i] & BUTTON3_PRESSED) strcat(buf, " B3_PRS");
					if(bufMouse[i] & BUTTON3_CLICKED) strcat(buf, " B3_CLK");
					if(bufMouse[i] & BUTTON3_DOUBLE_CLICKED) strcat(buf, " B3_DBCLK");
					if(bufMouse[i] & BUTTON3_TRIPLE_CLICKED) strcat(buf, " B3_TRCLK");
					if(bufMouse[i] & BUTTON4_RELEASED) strcat(buf, " B4_REL");
					if(bufMouse[i] & BUTTON4_PRESSED) strcat(buf, " B4_PRS");
					if(bufMouse[i] & BUTTON4_CLICKED) strcat(buf, " B4_CLK");
					if(bufMouse[i] & BUTTON4_DOUBLE_CLICKED) strcat(buf, " B4_DBCLK");
					if(bufMouse[i] & BUTTON4_TRIPLE_CLICKED) strcat(buf, " B4_TRCLK");
#ifdef BUTTON5_RELEASED
					if(bufMouse[i] & BUTTON5_RELEASED) strcat(buf, " B5_REL");
					if(bufMouse[i] & BUTTON5_PRESSED) strcat(buf, " B5_PRS");
					if(bufMouse[i] & BUTTON5_CLICKED) strcat(buf, " B5_CLK");
					if(bufMouse[i] & BUTTON5_DOUBLE_CLICKED) strcat(buf, " B5_DBCLK");
					if(bufMouse[i] & BUTTON5_TRIPLE_CLICKED) strcat(buf, " B5_TRCLK");
					if(bufMouse[i] & BUTTON_CTRL) strcat(buf, " CTRL");
					if(bufMouse[i] & BUTTON_SHIFT) strcat(buf, " SHIFT");
					if(bufMouse[i] & BUTTON_ALT) strcat(buf, " ALT");
#endif
					mvwprintw(w, 1+i, 22, "%s", buf);
					wattroff(w, atMouse);
				} else {
					mvwprintw(w, 1+i, 22, "                          ");
				}
			}
			wrefresh(w);

			move(y, x);

			refresh();
		}
	}

	/* Un post form and free the memory */

	endwin();
	return 0;
}