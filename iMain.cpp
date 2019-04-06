/*
    Original Author: S. M. Shahriar Nirjon
    Last Modified by: Mohammad Saifur Rahman
    last modified: October 13, 2015
    Version: 2.0
*/

# include "iGraphics.h"
#include <time.h>
#include <stdio.h>



#define bulletSpeed 20
#define boxNumber 40
int mposx,  mposy;

void collusion();
void boxMovement();
void burst();
void lives();

int width = 600;
int height = 690;

char gunImage[] = "image\\gun.bmp";
char tntbox[30][30] = { "image\\tntBox.bmp" };
char animation[4][30] = { "image\\1.bmp", "image\\2.bmp", "image\\3.bmp", "image\\4.bmp" };
int index = 0;

char bulletimage[] = "image\\bullet.bmp"; 
int gunposX = width/2;
int gunposY = 0;
int gunSpeed = 5;
bool gotoLeft = false;
bool gotoRight = false;
int gunwidth = 55;
int gunHeight = 75;

int boxHeight = 56;
int boxWidth = 56;

int bultotal = 9999999;
int bulWidth = 5;
int bulHeight = 15;
bool gotoUp = false;

int life = 3;

void xstrcpy(char *str1, char *str2)
{
	int i;
	for (i = 0; str2[i] != 0; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

struct bullet{
	
	int posX;
	int posY;
	int index;
	bool show;
	
};

bullet bul[10001];

void setBulletPos()
{
	for (int i = 0; i < 10001; i++)
	{
		bul[i].posX = gunposX + 21;
		bul[i].posY = gunposY;
		//bul[i].index = 0;
		bul[i].show = true;

	}
}

int numberOfBullets = 0;

void shoot()
{
	numberOfBullets++;
	bul[numberOfBullets].posX = gunposX + 21;
	bul[numberOfBullets].posY = gunposY + 55;
}


void move()
{
	for (int i = 0; i < numberOfBullets; i++)
	{
		bul[i].posX = gunposX+21;
		bul[i].posY += bulletSpeed;
	}
}



struct tntBox
{
	int boxposX;
	int boxposY;
	bool boxlife;
	int index;
	bool show;
	

	//void imageLocation(){
		//xstrcpy(boxImage, "image\\tntBox.bmp");
	//}
};

tntBox box[60];

void settntBox()
{
	int add = 0;
	for (int i = 0; i < boxNumber; i++) {
		
		box[i].boxposX = add;
		box[i].boxposY = 550;
		box[i].boxlife = false;
		box[i].index = 0;
		box[i].show = true;
		add -= 100;
	}
}



void collision()
{
	for (int i = 0; i < boxNumber; i++) {
		for (int j = 0; j < numberOfBullets; j++) {
			if (box[i].show && bul[j].show){
				if (((bul[j].posX >= box[i].boxposX && bul[j].posX <= box[i].boxposX + boxWidth) &&
					((bul[j].posY >= box[i].boxposY && bul[j].posY <= box[i].boxposY + boxHeight)
					/*(bul[j].posY == box[i].boxposY && bul[j].posY == box[i].boxposY - 60)*/))) {
					printf("boom!\n");
					PlaySound("sound\\Sound.wav", NULL, SND_ASYNC);
					box[i].show = false;
					bul[j].show = false;
					iShowBMP2(box[i].boxposX, box[i].boxposY, animation[index], 0);
				}
			}
		}
	}
}

bool flag1[60] = { false };

void boxmove()
{
	//int add = 200;
	for (int i = 0; i < boxNumber; i++) {
		if (box[i].boxposY == 550)
		box[i].boxposX += 20;
		lives();
		if (box[i].boxposX > width -100 ) {
			box[i].boxposX -= 15;
			box[i].boxposY -= 6;
			flag1[i] = false;
			lives();
		}
		if (box[i].boxposX < 16  && box[i].boxposY!=550) {
			box[i].boxposX += 15;
			//box[i].boxposY -= 6;
			flag1[i] = true;
			lives();
			
		}
		if (box[i].boxposX <= width - 100 && box[i].boxposY !=550 && !flag1[i] ) {
			box[i].boxposX -= 15;
			box[i].boxposY -= 6; 
			lives();
		}
		if (box[i].boxposX <= width - 100 && box[i].boxposX >=16 && box[i].boxposY != 550 && flag1[i]) {
			box[i].boxposX += 15;
			//box[i].boxposY -= 6;
			lives();
		}
		
	}
	
}

void gunMove()
{
	if (gunposX <= 0)
	{
		gunposX += gunSpeed;
		gotoLeft = false;
		gotoRight = false;
	}

	if (gunwidth + gunposX == width)
	{
		gunposX -= gunSpeed;
		gotoLeft = false;
		gotoRight = false;
	}
}

void burst()
{
	index++;
	if (index > 3)
		index = 0;
}

void lives(){
	for (int i = 0; i < boxNumber; i++){
		if (box[i].boxposY <= gunHeight){
			box[i].show = false;
			life--;
			settntBox();
		}
	}
}


/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here
	iClear();
	iShowBMP(0, 0, "image\\background2.bmp");

	for (int i = 0; i < numberOfBullets; i++)
	{
		if (bul[i].show)
			iShowBMP2(bul[i].posX, bul[i].posY, bulletimage, 0);
	}


	iShowBMP2(gunposX, gunposY, gunImage, 0);

	for (int i = 0; i < boxNumber; i++){
		if (box[i].show)
			iShowBMP(box[i].boxposX, box[i].boxposY, tntbox[box[i].index]);
	}
	
	gunMove();
	collision();
	burst();

	if (life == 0){
		for (int i = 0; i < boxNumber; i++){
			box[i].show = false;
		}
		iShowBMP(0, 0, "image\\game_over.bmp");
	}
}
	


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}
/*iPassiveMouseMove is called to detect and use
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here

 mposx = mx;
 mposy = my;
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	
		if (key == 'x')
		{
			shoot();
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
		if (gunposX > 0)
		{
			gunposX += gunSpeed;
			gotoLeft = false;
			gotoRight = true;
		}
	
	}

	if(key == GLUT_KEY_LEFT) 
	{
		if (gunposX < width - gunwidth)
		{
			gunposX -= gunSpeed;
			gotoLeft = true;
			gotoRight = false;

		}
	}
	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

int main()
{
	settntBox();
	setBulletPos();
	iSetTimer(1, boxmove);
	iSetTimer(50, move);
	iInitialize(width, height, "Boomm!");
	return 0;
}
