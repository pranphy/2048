#include "Utility/common.h"

#ifdef lnx
void cls(void)
{
    system("clear");
}
#endif

#ifdef windows
#include<windows.h>
void cls(void)
{
    system("CLS");
}
#endif


/* Below is a console function */

void locate(int x,int y)   // found this function somewhere in http://stackoverflow.com
{
    printf("%c[%d;%df",0x1B,y,x);
}
