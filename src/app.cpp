#include <string>
#include <ncurses.h>
#include <time.h>

using namespace std;

enum ColorList {
	ColorBack = 1,
	ColorText1,
	ColorText2,
	ColorInfo
};

int main() {
	WINDOW *w;
	MEVENT ev;
	int sw,sh,ch,x,y,rm;
	chtype bufKey[200];
	time_t bufTime[200];
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
		"None",
		"A_NORMAL",
		"A_ITALIC",
		"A_BLINK",
		"A_DIM",
		"A_UNDERLINE",
		"A_BOLD",
		"A_REVERSE",
		"A_STANDOUT"
	};

	short cTxt1Fore = COLOR_WHITE;
	short cTxt1Back = COLOR_BLACK;
	short cTxt1StyleIx = 0;
	short cTxt2Fore = COLOR_GREEN;
	short cTxt2Back = COLOR_BLACK;
	short cTxt2StyleIx = 0;

	/* Initialize curses */
	initscr();
	nonl();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	mmask_t mmold, mmnew = BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED;
	mousemask(mmnew, &mmold);

	start_color();
	init_pair(ColorBack, COLOR_WHITE, COLOR_BLACK);
	init_pair(ColorText1, cTxt1Fore, cTxt1Back);
	init_pair(ColorText2, cTxt2Fore, cTxt2Back);
	init_pair(ColorInfo, COLOR_YELLOW, COLOR_BLACK);

	sh = getmaxy(stdscr);
	sw = getmaxx(stdscr);

	w = newwin(10, 75, 13, 0);

	chtype atBack = COLOR_PAIR(ColorBack);
	chtype atTxt1 = COLOR_PAIR(ColorText1);
	chtype atTxt2 = COLOR_PAIR(ColorText2);
	chtype atInfo = COLOR_PAIR(ColorInfo);

	wbkgd(w, atBack);
	wattron(w, atBack);
	box(w, 0, 0);
	mvwprintw(w, 0, 0, "Window");
	wattroff(w, atBack);
	wrefresh(w);

	bkgd(atBack);
	attron(atBack);

	y = 0;
    mvprintw(y++, 80, "Upper left corner           "); addch(ACS_ULCORNER);
    mvprintw(y++, 80, "Lower left corner           "); addch(ACS_LLCORNER);
    mvprintw(y++, 80, "Lower right corner          "); addch(ACS_LRCORNER);
    mvprintw(y++, 80, "Tee pointing right          "); addch(ACS_LTEE);
    mvprintw(y++, 80, "Tee pointing left           "); addch(ACS_RTEE);
    mvprintw(y++, 80, "Tee pointing up             "); addch(ACS_BTEE);
    mvprintw(y++, 80, "Tee pointing down           "); addch(ACS_TTEE);
    mvprintw(y++, 80, "Horizontal line             "); addch(ACS_HLINE);
    mvprintw(y++, 80, "Vertical line               "); addch(ACS_VLINE);
    mvprintw(y++, 80, "Large Plus or cross over    "); addch(ACS_PLUS);
    mvprintw(y++, 80, "Scan Line 1                 "); addch(ACS_S1);
    mvprintw(y++, 80, "Scan Line 3                 "); addch(ACS_S3);
    mvprintw(y++, 80, "Scan Line 7                 "); addch(ACS_S7);
    mvprintw(y++, 80, "Scan Line 9                 "); addch(ACS_S9);
    mvprintw(y++, 80, "Diamond                     "); addch(ACS_DIAMOND);
    mvprintw(y++, 80, "Checker board (stipple)     "); addch(ACS_CKBOARD);
    mvprintw(y++, 80, "Degree Symbol               "); addch(ACS_DEGREE);
    mvprintw(y++, 80, "Plus/Minus Symbol           "); addch(ACS_PLMINUS);
    mvprintw(y++, 80, "Bullet                      "); addch(ACS_BULLET);
    mvprintw(y++, 80, "Arrow Pointing Left         "); addch(ACS_LARROW);
    mvprintw(y++, 80, "Arrow Pointing Right        "); addch(ACS_RARROW);
    mvprintw(y++, 80, "Arrow Pointing Down         "); addch(ACS_DARROW);
    mvprintw(y++, 80, "Arrow Pointing Up           "); addch(ACS_UARROW);
    mvprintw(y++, 80, "Board of squares            "); addch(ACS_BOARD);
    mvprintw(y++, 80, "Lantern Symbol              "); addch(ACS_LANTERN);
    mvprintw(y++, 80, "Solid Square Block          "); addch(ACS_BLOCK);
    mvprintw(y++, 80, "Less/Equal sign             "); addch(ACS_LEQUAL);
    mvprintw(y++, 80, "Greater/Equal sign          "); addch(ACS_GEQUAL);
    mvprintw(y++, 80, "Pi                          "); addch(ACS_PI);
    mvprintw(y++, 80, "Not equal                   "); addch(ACS_NEQUAL);
    mvprintw(y++, 80, "UK pound sign               "); addch(ACS_STERLING);

	attroff(atBack);

	attron(atTxt1);
	mvprintw(2, 2, "Demo text input 1");
	attroff(atTxt1);
	attron(atTxt2);
	mvprintw(3, 2, "Demo text input 2");
	attroff(atTxt2);

	attron(atInfo);
	mvprintw(6, 1, "Text1 fore color a/A (%d), back color s/S (%d), style d/D (%s)", cTxt1Fore, cTxt1Back, style_names[cTxt1StyleIx].c_str());
	mvprintw(7, 1, "Text2 fore color z/Z (%d), back color x/X (%d), style c/C (%s)", cTxt2Fore, cTxt2Back, style_names[cTxt2StyleIx].c_str());
	mvprintw(8, 1, "Exit = F10 (Mouse mask n/o = %d/%d)", mmnew, mmold);
	attroff(atInfo);
	refresh();

	x = getcurx(stdscr);
	y = getcury(stdscr);

	timeout(10);

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(10)) {
		rm = 1;
		if(ch > 0) {
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
			mvprintw(6, 1, "Text1 fore color a/A (%d), back color s/S (%d), style d/D (%s)", cTxt1Fore, cTxt1Back, style_names[cTxt1StyleIx].c_str());
			mvprintw(7, 1, "Text2 fore color z/Z (%d), back color x/X (%d), style c/C (%s)", cTxt2Fore, cTxt2Back, style_names[cTxt2StyleIx].c_str());
			if(ch) {
				mvprintw(9, 3, "KEY: 0x%x, 0%o, %d, %c                        ", ch, ch, ch, ch);
			} else {
				mvprintw(9, 3, "                                            ");
			}
			if(rm == OK) {
				if(ev.bstate & BUTTON1_CLICKED) {
					mvprintw(10, 3, "%03i B1   CLK [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				} else if(ev.bstate & BUTTON1_DOUBLE_CLICKED) {
					mvprintw(10, 3, "%03i B1 DBCLK [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				} else {
					mvprintw(10, 3, "%03i MOUSE EV [%03i, %03i, %03i]       ", ev.id, ev.x, ev.y, ev.z);
				}
			} else {
				mvprintw(10, 3, "                                   ");
			}
			attroff(atInfo);

			move(y, x);

			refresh();
		}
	}

	/* Un post form and free the memory */

	endwin();
	return 0;
}