#include "iGraphics.h"

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//backgrounds
char photo[20][40] = { "images\\frontpagebackground.bmp", "images\\gamebg.bmp", "images\\tutorialbackground.bmp","images\\storybackground.bmp","images\\gameover.bmp", "images\\gameend.bmp", "images\\creditbg.bmp"};
//buttons
char button[10][40] = { "images\\playbutton.bmp", "images\\storybutton.bmp","images\\tutorialbutton.bmp", "images\\homebutton.bmp","images\\homebutton2.bmp","images\\creditbutton.bmp" };
//game materials 
char gamemat[10][40] = { "images\\spaceship.bmp", "images\\meteor.bmp", "images\\meteor1.bmp", "images\\Kepler.bmp", "images\\missile.bmp" };

//for render-
int mposx, mposy, ia, ja;
int imgpos[50];
char imgname[50][20] = { "ok\\1.bmp", "ok\\2.bmp", "ok\\3.bmp", "ok\\4.bmp", "ok\\5.bmp", "ok\\6.bmp", "ok\\7.bmp", "ok\\8.bmp", "ok\\9.bmp", "ok\\10.bmp", "ok\\11.bmp", "ok\\12.bmp", "ok\\13.bmp", "ok\\14.bmp", "ok\\15.bmp", "ok\\16.bmp", "ok\\17.bmp", "ok\\18.bmp", "ok\\19.bmp", "ok\\20.bmp", "ok\\21.bmp", "ok\\22.bmp", "ok\\23.bmp", "ok\\24.bmp", "ok\\25.bmp", "ok\\26.bmp", "ok\\27.bmp", "ok\\28.bmp", "ok\\29.bmp", "ok\\30.bmp", "ok\\31.bmp", "ok\\32.bmp", "ok\\33.bmp", "ok\\34.bmp", "ok\\35.bmp", "ok\\36.bmp", "ok\\37.bmp", "ok\\38.bmp", "ok\\39.bmp", "ok\\40.bmp", "ok\\41.bmp", "ok\\42.bmp", "ok\\43.bmp", "ok\\44.bmp", "ok\\45.bmp", "ok\\46.bmp", "ok\\47.bmp", "ok\\48.bmp", "ok\\49.bmp", "ok\\50.bmp" };
//-------------------------------------

//distance
char distanceText[50];
int distance=0;
int phase = 1;

//for pause
bool pause = true;
//for music
bool homemusic = true;


int i = 0; //background number
int b = 0;  //button number
int m = 0; //for missile

int buttonx = 750, buttony = 370; //button axis

//game
int rocketcordinateX = 470, rocketcordinateY = 10;
int meteorcordinateX=200, meteorcordinateY=900;
int meteorcordinateX1 = 500, meteorcordinateY1 = 900;
//int meteorcordinateX2 = 800, meteorcordinateY2 = 900;
int keplercordinateX = 100, keplercordinateY = 10800; //680
int missilecordinateX, missilecordinateY;


//user defined functions
void meteorcollision();
void missilecollision();
void keplerreach();
void distancemeasure();
void phasemeasure();


void iDraw()
{
	
	iClear();
	
	//backgrounds
	if (i!=1)
	iShowBMP(0, 0, photo[i]);

	if (i == 1)
	{
		for (ia = 0; ia < 50; ia++)
		{
			if (pause)
			iShowBMP(0, imgpos[ia], imgname[ia]);
		}
		for (ia = 0; ia < 50; ia++)
		{
			if (pause)
			imgpos[ia] -= 13;
		}
		for (ia = 0; ia < 50; ia++)
		{
			if (imgpos[ia] < 0 && pause)
			{
				imgpos[ia] = 637;
			}
		}
	}
	
	//button
	
		if (i == 0)
		{
			iShowBMP2(750, 370, button[b], 255); //playbutton
			iShowBMP2(750, 240, button[b + 1], 255); //aboutbutton
			iShowBMP2(750, 110, button[b + 2], 255); //tutorialbutton
			iShowBMP2(50, 50, button[b + 5], 255); //creditbutton
		}

		//rocket and meteor
		if (i == 1)
		{
			iShowBMP2(keplercordinateX, keplercordinateY, gamemat[3], 255); //kepler
			iShowBMP2(rocketcordinateX, rocketcordinateY, gamemat[0], 0); //spaceship
			iShowBMP2(meteorcordinateX, meteorcordinateY, gamemat[1], 0); //meteor
			iShowBMP2(meteorcordinateX1, meteorcordinateY1, gamemat[2], 255); //meteor1
			
			if (m == 1) //for missile 
			{
				iShowBMP2(missilecordinateX + 50, missilecordinateY + 50, gamemat[4], 255); //rocketcordinate will be start of missile
			}
			
			
			sprintf_s(distanceText, "Distance Crossed = %d Light years", distance); 
			iText(50, 50, distanceText, GLUT_BITMAP_TIMES_ROMAN_24);

			sprintf_s(distanceText, "Phase = %d", phase);
			iText(850, 50, distanceText, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		
		
		if ((i == 2 || i == 3 || pause == false )&& i!=0) //for back button
		{
				iShowBMP2(870, 550, button[b + 3], 255);
		}
		
		
		if (i == 4 || i == 5 ) //for game end/ game over
		{
			iShowBMP2(50, 50, button[b + 4], 255);
		}

		

		meteorcollision(); //meteor collision check
		missilecollision(); //missile colliosion check 
		distancemeasure(); //for showing distance
		keplerreach(); //gamedone
		phasemeasure();
		
		
		/*
		if (i==1)
		printf("%d", distance);* //for distance check*/
		
		
}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	printf("%d\t%d\n", mx, my);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for play button
	{
		if (i == 0)
		{
			if (mx >= 763 && mx <= 935 && my >= 390 && my <= 454)
			{
				i = 1;
				pause = true; //so that game always start as true
			}
		}	
	}
	
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for tutorial button
	{
		if (i == 0)
		{
			if (mx >= 763 && mx <= 935 && my >= 130 && my <= 193)
			{
				i = 2;
				
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for story button
	{
		if (i == 0)
		{
			if (mx >= 763 && mx <= 935 && my >= 261 && my <= 322)
			{
				i = 3;

			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for credit button
	{
		if (i == 0)
		{
			if (mx >= 69 && mx <= 322 && my >= 86 && my <= 198)
			{
				i = 6;

			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for back(tutorial/story/game) button
	{
		if (i == 2 || i == 3 || pause==false)
		{
			if (mx >= 880 && mx <= 1008 && my >= 568 && my <= 627)
			{
				i = 0;	
				pause = true;
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //for back(gameover/gameend) button (Not working properly
	{
		if (i == 4 || i == 5)
		{
			if (mx >= 60 && mx <= 188 && my >= 68 && my <= 125)
			{
				i = 0;
			}
		}
	}

	
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{


	if (key == 'w')
	{
		if (rocketcordinateY<100)
		{
			if (pause == true)
				rocketcordinateY += 30;
		}
	}
	if (key == 's')
	{
		if (rocketcordinateY>30)
		{
			if (pause == true)
				rocketcordinateY -= 30;
		}
	}
	if (key == 'a')
	{
		if (rocketcordinateX > 30)
		{
			if (pause == true)
				rocketcordinateX -= 30;
		}
	}
	if (key == 'd')
	{
		if (rocketcordinateX < 900)
		{
			if (pause == true)
				rocketcordinateX += 30;
		}
	}

		if (key == 'p') //for pause
		{

			if (pause == true)
			{
				pause = false;
			}
			else
			{
				pause = true;
			}
		}
	

	if ((m == 0 || m == 1) && missilecordinateY >= 700 && pause==true) //for missile
	{
		if (key == 'f') 
		{
			missilecordinateX = rocketcordinateX;
			missilecordinateY = rocketcordinateY;
			m = 1;
		}
	}
	

	if (key == 'm') //for music control
	{
		if (homemusic == true)
		{
			homemusic = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			homemusic = true;
			PlaySound("music\\homemusic.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
				
	}
	if (key == GLUT_KEY_LEFT)
	{
		
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}
	
}


void meteormove()
{
	if (i == 1 &&	pause == true)
	{
		if (phase == 1 || phase == 2 || phase == 3)
		{
			if (phase==1)
				meteorcordinateY -= 3;
			else if (phase==2)
				meteorcordinateY -= 5;
			else if (phase == 3)
				meteorcordinateY -= 7;
		}

		if (meteorcordinateY <= 0)
		{
			meteorcordinateX = rand() % 1000;
			meteorcordinateY = 800;
		}


		if (phase == 1 || phase == 2 || phase == 3)
		{
			if (phase == 1)
				meteorcordinateY1 -= 7;
			else if (phase == 2)
				meteorcordinateY1 -= 9;
			else if (phase == 3)
				meteorcordinateY1 -= 11;
		}
		

		if (meteorcordinateY1 <= 0)
		{
			meteorcordinateX1 = rand() % 1000;
			meteorcordinateY1 = 800;
		}
	}

}
void keplermove()
{
	if (i == 1 && pause == true && keplercordinateY>30)
	{
		keplercordinateY -= 2;

	}

}

void missilemove()
{
	if (i == 1 && pause == true)
	{
		missilecordinateY += 10;
	}
	//printf("%d\t%d", missilecordinateX, missilecordinateY);
}

// for meteor-rocket collision
void meteorcollision()
{	
	//done-
	if ((meteorcordinateX >= rocketcordinateX && meteorcordinateX <= rocketcordinateX + 130) && ((meteorcordinateY >= rocketcordinateY && meteorcordinateY <= rocketcordinateY + 88)))
	{
		i = 4;
		//printf("Collision\n");
	}
	if ((meteorcordinateX1 >= rocketcordinateX && meteorcordinateX1 <= rocketcordinateX + 130) && ((meteorcordinateY1 >= rocketcordinateY && meteorcordinateY1 <= rocketcordinateY + 88)))
	{
		i = 4;
		//printf("Collision\n");
	}
}

//for missile-meteor collision
void missilecollision()
{
	if ((missilecordinateX >= meteorcordinateX && missilecordinateX < meteorcordinateX + 100) && (missilecordinateY+113 > meteorcordinateY && missilecordinateY+113 < meteorcordinateY + 100))
	{
		m = 0;
		meteorcordinateY = 800;
	}
	if ((missilecordinateX >= meteorcordinateX1 && missilecordinateX < meteorcordinateX1 + 100) && (missilecordinateY + 113 > meteorcordinateY1 && missilecordinateY + 113 < meteorcordinateY1 + 100))
	{
		m = 0;
		meteorcordinateY1 = 800;
	}
}
//for ending
void keplerreach()
{
	if (keplercordinateY <=35)
	{
		i = 5;
	}
}

void distancemeasure()
{
	if (pause == true && i==1)
	{
		distance+=1;
	}
	
}

void phasemeasure()
{
	if (distance >= 2000)
		phase=2;
	if (distance >= 4000)
		phase=3;
}

void imgposf() //for background render
{
	int ia, ja;
	
		for (ia = 0, ja = 0; ia <= 50; ia++)
		{
			imgpos[ia] = ja;
			
			ja += 13;
		}
}

int main()
{
	///srand((unsigned)time(NULL));
		iSetTimer(1, meteormove); // for moving meteor
		iSetTimer(10, keplermove); //for moving kepler 500
		iSetTimer(1, missilemove); //for missile move
		iSetTimer(1000000, imgposf);
		iSetTimer(900000000000000000, distancemeasure);
		
		if (homemusic) //for music
		{
			PlaySound("music\\homemusic.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		imgposf();
	iInitialize(1050, 650, "The Last Journey");
	
	///updated see the documentations
	iStart();
	return 0;
}