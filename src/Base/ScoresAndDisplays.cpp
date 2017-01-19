/*************************************************/
/** Author        : @PrakashGautam               */
/** First Written : Dec 30, 2012                 */
/** Last Updated  : Oct 20, 2013                 */
/** fb.com/pranphy<>http://pranphy.wordpress.com */
/*************************************************/


#include "Base/ScoresAndDisplays.h"

/*
*   The Following function is not my own but was obtained somewhere from the internet
*   and I don't exactly remember the source. It was free to copy and use so I used  it
*/
void Cout(char *String,float x,float y,float z)
{
    char *CurrentCharacter=String;
    glRasterPos3f(x,y,z);
    for (; *CurrentCharacter != '\0'; CurrentCharacter++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *CurrentCharacter);
    }
}


Player::Player(char*name,int lives,int scores)
{
    int l=strlen(name);
    Name=new char[l];
    strcpy(Name,name);
    Lives=lives;
    Scores=scores;
}
