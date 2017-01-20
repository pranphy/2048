/********************************************/
/** Author       : @PrakashGautam           */
/** Date Written : Sunday July 20  2014     */
/** Last Updated : Tuesday July 22 2014     */
/********************************************/

/*
*	This header forms the core of the popular game 2048. This handles every mechanisms
*	going on inside the 2048 game except the graphical appearence. Unlike 2048 it can
*	without any effort be extended to higher order like 5*5 and so on beyond limit. It is
*	dependent upon the PML updated on 16 March 2014  or later to work. The PML is
*	is available to download free from http://pranphy.wordpress.com/programming .

*	You can use this program in whatever way you like, except chagnge the name of author
*	as is and claim it to be yours. You can modify it and put on your own genuine idea
*	to extend it and then claim the extension is yours and use it as the part of that.
*	I would be very grateful if you could make it use in your project or whatever.
*	Let me know if it is helpful, or if you have any queries you can mail me at
*	pranphy@gmail.com or you can find me on facebook on fb.com/pranphy or you can find
*	me on twitter on @pranphy.

*/
#pragma once
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include "PML/MatrixPrakash.h"

#define LEFT		0x04
#define RIGHT		0x03
#define UP			0x02
#define DOWN		0x01

class Core
{
	public:
		int Points;
		Matrix<int> Array;
		int DownPressed();
		int ArrowPressed(int);
		Core(int=4,int=4);
		void Display();
};

int Random(int);
void initrand(void);
