/*
 * curses_game_funct.h
 *
 *  Created on: 22.09.2013
 *      Author: Miku
 */

//#ifndef CURSES_GAME_FUNCT_H_
//#define CURSES_GAME_FUNCT_H_
 //Vajalik fondi muutuste käskluse jaoks.
#include <curses.h>  //Vajalik PDCurses kasutamiseks.
#include <sstream>
//#include "main.cpp"
using namespace std;

//class objekt {
//public:
//	objekt(int, int, int, char);
//	//int i;
//	int x, y, z;
//	//objekt objektid[10];
//	char appearance;

//};

class objekt {
public:
	objekt(int, int, int, char);
	//int i;
	int x, y, z;
	//objekt objektid[10];
	char appearance;

};
void print_int(WINDOW *aken, int number){
	wclear(aken);
	string s_to_c = static_cast<ostringstream*>( &(ostringstream() << number) )->str();
	const char* output_const_char = s_to_c.c_str();
	wprintw(aken, output_const_char);
	wrefresh(aken);

};

BOOL inscreen(int pz, int py, int px, int jsuurus, objekt* objekt, int *movey, int *movex) // genereates screen coordinates
		//int movey, movex;
		{

			if((*objekt).z == pz)
			{
				//cout<<px;
				refresh();
				if(((*objekt).y <= py+jsuurus)&&((*objekt).y >= py-jsuurus)&&((*objekt).x <= px+jsuurus)&&((*objekt).x >= px-jsuurus))
				{
					if (((*objekt).y) < py)
					{
					*movey = jsuurus - (py  % ((*objekt).y));
					//cout<<movey;
					}
					else if((*objekt).y > py)
					{
					*movey = jsuurus + ((*objekt).y % py);
					}

					if((*objekt).x < px)
					{
					*movex = jsuurus - (px % (*objekt).x);
					}
					else
					{
					*movex = jsuurus + ((*objekt).x % px);
					}
					//cout<<movey;
							refresh();
					return TRUE;
				}
			}

			return FALSE;
		};



//#endif /* CURSES_GAME_FUNCT_H_ */
