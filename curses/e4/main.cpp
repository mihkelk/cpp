/*
 *
 *
 *  Created on: 30.09.2013
 *
 */

//http://www.cplusplus.com/articles/D9j2Nwbp/ vaata
//http://pdcurses.sourceforge.net/doc/PDCurses.txt

//#include <stdlib.h>
#include <windows.h> //Vajalik fondi muutuste käskluse jaoks.
#include <curses.h>  //Vajalik PDCurses kasutamiseks.
#include <iostream>
#include <fstream>
#include <sstream>
#include "curses_game_funct.h"
using namespace std;

//int px = 248, py = 247; //mängija algkoordinaadid
int jsuurus = 25; //joonistatava vaatevälja suurus

BOOL WINAPI SetConsoleFont(HANDLE hOutput, DWORD fontIndex); //Defineeritud et hiljem kasutada fondimuutus käsku.

int ammount;
//cout << "hueuheuheuhueuh";

objekt* objektid[10];
objekt::objekt(int igs, int ygrek, int zee, char aprnc) {
	//objekt* objektid[10];

	x = igs;
	y = ygrek;
	z = zee;
	appearance = aprnc;

	for (int i = 0; i < 3; i++) {
		if (objektid[i] == 0) {
			objektid[i] = this;
			ammount = i;
			break;

		}
	}
}

objekt player(248, 247, 50, '\1'); // Creates the player and assigns starting coordinates.


objekt NPC(248, 248, 50, '\1');



//extern player.x;
//extern player.y;
//player.x = 248;
//player.y = 247;

//---------------------------Maailma-loomine-failist----------------------//
void maailm(char ***koordinaadid) {
	//addch(ACS_BOARD | COLOR_PAIR(5));
	//char koordinaadid[100][500][500]; //Toetab 100 korrust mille suuruseks umbes 500x500 tähemärki, reavahetus loeb samuti tähemärgina.
	char cz[10];
	int x, y, z;

	for (z = 49; z < 51; z++) {

		//cz =
		itoa(z, cz, 10); //itoa(arv mida teisaldan, string millesse teisaldan, arvusüsteem)
		//	printf("%s", cz); //[0], cz[1], cz[2]);

		FILE *korrus = fopen(cz, "r");
		char casukoht = '0';
		for (y = 0; casukoht != '-'; y++) {
			for (x = 0; casukoht != '\n'; x++) {

				casukoht = fgetc(korrus);

				koordinaadid[z][y][x] = casukoht;

			}
			casukoht = fgetc(korrus);
		};

	};

}
//------------------------------------------------------------------------//

//-------------------------------joonistamine-----------------------------//
void joonistamine(WINDOW *PORTRAIT, WINDOW *world, char ***koordinaadid) {

	int x, y;
	int reavahetus = -1;
	int movex = 0, movey = 0;

	for (y = player.y - jsuurus; y < (player.y + jsuurus); y++) {
		reavahetus++;
		wmove(world, reavahetus, 0);
		for (x = player.x - jsuurus; x < (player.x + jsuurus); x++) {

			if ((*objektid[0]).x == x && (*objektid[0]).y == y) {
				waddch(world,
						(*objektid[0]).appearance | COLOR_PAIR(4) | A_ALTCHARSET);

			} else {
				switch (koordinaadid[player.z][y][x]) {
				case '0': //Tühjus
					waddch(world, ACS_BLOCK | COLOR_PAIR(6)); // Sümbolid laiendatud ascii tabelist pdcursesiga nimetused ACS_*
					break;
				case '1': //Sein
					waddch(world, ACS_BLOCK | COLOR_PAIR(1)); // Värve võetakse paaridena mis on defineeritud peafunktsioonis.
					break;
				case '2': //Muru
					waddch(world, ACS_CKBOARD | COLOR_PAIR(2));
					break;
				case '3': //Mängija
					waddch(world, '\1' | COLOR_PAIR(4) | A_ALTCHARSET); // Altcharset vajalik naerunäeo näitamiseks.
					break;
				case '4': //Heledam muru
					waddch(world, ACS_BOARD | COLOR_PAIR(5));
					break;
				case '5': //Trepp alla
					waddch(world, 'v' | COLOR_PAIR(4));
					break;
				case '6': //Trepp üles
					waddch(world, '^' | COLOR_PAIR(4));
					break;
				case '7': //Kivipõrand
					waddch(world, ACS_CKBOARD | COLOR_PAIR(7));
					break;
				default:
					wprintw(world, "%d", koordinaadid[player.z][y][x]);
					break;

				};
			};
		};

	};
	for (int i = 1; i < ammount + 1; i++) { //after the world has been drawn all objects are cycled and checked if they are on screen, if so they get drawn to the their position relative from the player character
		if (inscreen(player.z, player.y, player.x, jsuurus, objektid[i], &movey,&movex)) {

			wmove(world, movey, movex);
			waddch(world,(*objektid[i]).appearance | COLOR_PAIR(4) | A_ALTCHARSET);

		}
		print_int(PORTRAIT, movey);

	};

	wrefresh(world);
	wrefresh(PORTRAIT);

	SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 2);	// Vahetab fondi suurust, vajalik kuna kaotab ära jooned suuremat vilkumist põhjustamatta.

}
//------------------------------------------------------------------------//

//-------------------------------Peafunktsioon----------------------------//
int main() {
	char klahv;
	int z;

	char ***koordinaadid = new char**[100]; //////////////////////////////////////////////////////////////
	for (int i = 0; i < 100; ++i) {	// Creating a 3 dimensional array and reserving space for it//
		koordinaadid[i] = new char*[501];//															//
		for (int j = 0; j < 500; ++j) {	//															//
			koordinaadid[i][j] = new char[501];	//////////////////////////////////////////////////////////////
		}
	}

	maailm(koordinaadid);
	//koordinaadid =
	//getch();
	initscr() && curs_set(0) && noecho(); // Starts using pdcurses, hides the cursor, hides console input



	resize_term(jsuurus * 2, jsuurus * 2 + 30);
	move(55, 0);
//PDCurses värvindus.
	start_color();				//Begin using colours.
//---------Assigning-colour-pairs.---------//
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_WHITE);
	init_pair(5, COLOR_GREEN, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
//-----------------------------------------//
	z = 50;
	//WINDOW *UI;
	WINDOW *PORTRAIT;
	WINDOW *world;
	world = newwin(jsuurus * 2, jsuurus * 2, 0, 0);
	//UI = newwin(20, 20, 20, jsuurus * 2 + 1);
	PORTRAIT = newwin(16, 20, 0, jsuurus * 2 + 1);

	joonistamine(PORTRAIT, world, koordinaadid);

	BOOL lopp = FALSE;				//

	while (lopp == FALSE) {

//----------Klahvivajutuste-järgi-mängija-koordinaatide-muutmine----------//

		klahv = getch();
		//beep();

		if (klahv == 'd' && (koordinaadid[z][player.y][player.x + 1] != '1')) {
			player.x++;

		} else if (klahv == 'a'
				&& (koordinaadid[z][player.y][player.x - 1] != '1')) {
			player.x--;

		} else if (klahv == 'w'
				&& (koordinaadid[z][player.y - 1][player.x] != '1')) {
			player.y--;

		} else if (klahv == 's'
				&& (koordinaadid[z][player.y + 1][player.x] != '1')) {
			player.y++;

		} else if (klahv == 'q') {
			lopp = TRUE;
		}

		switch (koordinaadid[player.z][player.y][player.x]) { //Kui on tegu treppidega.
		case '5':
			player.z--;
			break;
		case '6':
			player.z++;
			break;
		}
		//------------------------------------------------------------------------//

		joonistamine(PORTRAIT, world, koordinaadid);


	};
	return 0;
}
//------------------------------------------------------------------------//

