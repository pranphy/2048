/********************************************/
/** Author       : @PrakashGautam           */
/** Date Written : Sunday July 20  2014     */
/** Last Updated : Tuesday July 22 2014     */
/********************************************/

/*
*	This definition file corresponding to COre.h forms the core of the popular game 2048.
*	This handles every mechanisms
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

#include "Core.h"

Core::Core(int Row,int Col)
{
    initrand();
    Points=0;
    Matrix A(Row,Col);
	Array=A;
	for(int i=0;i<Array.Row;i++)
		for(int j=0;j<Array.Col;j++)
			Array[i][j]=0;

}

void Core::Display()
{

	system("clear");
	cout<<" Points "<<Points<<endl;
	cout<<" "<<endl;
	int Width=8;
	cout<<setw(Width);
	for(int i=0;i<Array.Row;i++)
	{
		for(int j=0;j<Array.Col;j++)
		{
			if(Array[i][j]!=0)
				cout<<Array[i][j]<<setw(Width);
			else
				cout<<" "<<setw(Width);
		}
		cout<<endl;
	}

}


int Core::DownPressed()
{
	static bool flag=true;
	bool GameSituation=false;
	/*********Add Block********/

	for(int j=Array.Col-1;j>=0;j--)
	{
		for(int i=Array.Row-1;i>=0;i--)
		{
			int t=Array[i][j];                     //The content of a cell, lets call Active Cell
			for(int k=i-1;k>=0;k--)            //move upwards along the column to find any equal value so as to add to it
			{
				if(Array[k][j]==0) continue;   //if thre is zero the cell is empty so go to next cell
				if(Array[k][j]==t)            //but if the cell has the  value equal to the Active Cell
				{
					Array[i][j]*=2;           //double the value of active cell
					Points+=2*t;              //increase the point
					flag=true;               //this flag indicates that there has been at least one movement,
					Array[k][j]=0;           // clear the found cell equal to active cell,
					break;                    //goto next cell for a active cell
				}
				else                     //but if the cell is not empty and also not equal to active cell
				{
					i=k+1;               //then we have to search upward from the cell, thus this is the active cell
					break;               // to  the row k shouldbe actice cell now so, increase i to ome more than k and break
										//which causes the next i value to be k since the loop will decrease the value of k
				}
			}

		}
	}
	/***********Move Block*********************/
	for(int j=Array.Col-1;j>=0;j--)
	{
		for(int i=Array.Row-1;i>=0;i--)
		{
			int t=Array[i][j];       // check the cell content, call it Active cell
			if(t) continue;          //if this is filled do nothing, go to next cell up the column
			else                     //but if the cell is empty this needs to be filled
			{
				GameSituation=true;     // if there is a empty cell, this indicates the game is still not over
				for(int k=i-1;k>=0;k--) // search upward from the active cell
				{
					if(Array[k][j])   //if the cell is not empty
					{
						Array[i][j]=Array[k][j]; // move the cell to active cell which was empty
						Array[k][j]=0; // and clear this cell illusioning it as moved
						flag=true;     // thre has been a movement, this is kept track to determine whether to add new block at random position
						//i=k+1;  bug found here no need to do this one.
						break;
					}
					else continue;  // if the cell is empty just continue
				}
			}
		}

	}
	/**************Create Block At random position***************/
	if(flag)  // if flag is set there has been at least one movement or at least one coelsec
	{
		int *ZeroPos=new int[Array.Row*Array.Col]; //create maximum position to count the empty cells
		int Counter=0;
		for(int i=0;i<Array.Row;i++)
			for(int j=0;j<Array.Col;j++)
			{
				if(Array[i][j]==0) //if any cell is empty
					ZeroPos[Counter++]=10*i+j; // multiplex the row and col value into two digit numeber // this works for one digit row or col value only. whcih needs to be improved
			}
		int Rand=Random(Counter)-1; //create a random nimber
		int p=ZeroPos[Rand]; // select any random position
		int Row=p/10; //extract row
		int Col=p%10; //extract column
		Array[Row][Col]=2; // but a two block there, which is already random. I am not sure when to put four in the block, in original version four appears sometimes as well
		delete[]ZeroPos; //free the memory
		flag=false; //reset the flag
	}
	if (!GameSituation)
	{
		cout<<" Game over "<<endl; // if no movement has occoured then the game is over
	}

	return 0;
}

int Core::ArrowPressed(int KeyID)
{
    if(KeyID==DOWN)
	{
		//cout<<" Down "<<endl;
		DownPressed();
	}
	else if(KeyID==LEFT)
	{
		//cout<<" Left"<<endl;

		Array=Transpose(Array);
		Array=ReflectX(Array);
		DownPressed();
		Array=ReflectX(Array);
		Array=Transpose(Array);
	}
	else if(KeyID==RIGHT)
	{
		//cout<<" Right "<<endl;
		Array=Transpose(Array);
		Array=ReflectY(Array);
		DownPressed();
		Array=ReflectY(Array);
		Array=Transpose(Array);
	}
	else if(KeyID==UP)
	{
		//cout<<"UP"<<endl;
		Array=ReflectX(Array);
		DownPressed();
		Array=ReflectX(Array);
	}
	else
		return 0;
	return 1;
}



int Random(int range)
{
    return (rand()%range+1);
}

void initrand(void)
{
    srand((unsigned)time(0));
}
