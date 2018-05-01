#include <GL/glut.h>
#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;

bool condPairs(float x[][2],float y[][2]);

int t;
float xX = 0,yY = 0; //pointer used to move the boxes
int screen = 1;

int time_gap = 2;
time_t sec = time (NULL);
int start_time = (sec-1525195479) ;
int end_time = (sec-1525195479) + time_gap ;
int n_end_time = (sec-1525195479) + 2*time_gap ;

GLfloat p[4][2] = {
	{70.0,30.0},
	{70.0,25.0},
	{75.0,25.0},
	{75.0,30.0}
};

GLfloat b1[4][2] = {
	{50.0,45.0},
	{50.0,40.0},
	{55.0,40.0},
	{55.0,45.0}
};

GLfloat b2[4][2] = {
	{60.0,45.0},
	{60.0,40.0},
	{65.0,40.0},
	{65.0,45.0}
};

GLfloat b3[4][2] = {
	{65.0,45.0},
	{65.0,40.0},
	{70.0,40.0},
	{70.0,45.0}
};

GLfloat Rp[4][2];

GLfloat Rb1[4][2]; 

GLfloat Rb2[4][2]; 

GLfloat Rb3[4][2]; 

GLfloat g1[4][2] = {
	{25.0, 75.0},
	{25.0, 70.0},
	{30.0, 70.0},
	{30.0, 75.0}
};

GLfloat g2[4][2] = {
	{40.0, 45.0},
	{40.0, 40.0},
	{45.0, 40.0},
	{45.0, 45.0}
};

GLfloat g3[4][2] = {
	{70.0, 70.0},
	{70.0, 65.0},
	{75.0, 65.0},
	{75.0, 70.0}
};

int init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	gluOrtho2D(0,100.0,0,100.0);
}

void drawLogo(string s, float x, float y)
{
	glRasterPos2f(x,y);
	for (int c=0; c< s.size(); c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[c]);
	}
}

void drawBitmapText(string s, float x, float y)
{
	glRasterPos2f(x,y);
	for (int c=0; c< s.size(); c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[c]);
	}
}

void timerFunc(){
	printf("Hello Timer Function\n");
//	glClearColor(0.0,0.0,0.0,0.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	drawBitmapText("Press Left Mouse Button To Start",30,50);
	glFlush();
	printf("\nStart Time: %d",start_time);
	printf("\nEnd Time : %d",end_time);
	if(end_time - start_time >=0)
	{
		time_t sec = time(NULL);
		start_time = (sec-1525195479);
		timerFunc();	
	}
	end_time = start_time + time_gap;
	n
//	glutTimerFunc(10000,timerFunc,1000);
	glutPostRedisplay();
	printf("\nBYE Timer Function\n");
}

void displayMenu(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	if(time_value % 2 == 0)
		glColor3f(1.0,0.0,0.0);
//	else
		glColor3f(0.0,1.0,0.0);
	drawLogo("SOKOBAN",42,75);
	drawBitmapText("A Box Game",42.5,70);
//	glColor3f(0.0,1.0,0.0);
//	drawBitmapText("Press Left Mouse Button To Start",30,50);
	glColor3f(1.0,1.0,1.0);
	drawBitmapText("Akhil Chouhan",18,25);
	drawBitmapText("Akshat Trivedi",18,20);
	drawBitmapText("1PE15CS012",68,25);
	drawBitmapText("1PE15CS013",68,20);
	glColor3f(0.0,1.0,0.0);
	glFlush();
//	glutPostRedisplay();
}
void motion(float a[4][2], float q, float w)
{
	for(int i=0;i<4;i++){
		a[i][0] += q;
	}
	for(int i=0;i<4;i++){
		a[i][1] += w;
	}
}


void keys()
{
	switch (t)
	{
		case 1:
			xX = -5.0;
			break;
		case 2:
			xX = 5.0;
			break;
		case 3:
			yY = 5.0;
			break;
		case 4:
			yY = -5.0;
			break;
	}
}

void mouse(int btn,int state,int x,int y)
{
	if(btn == GLUT_LEFT_BUTTON)
	{
		screen++;
		printf("\nEnter Key Pressed");
		glutPostRedisplay();
	}
}

void k(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP :
			t = 3;
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT :
			t = 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN :
			t = 4;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT :
			t = 2;
			glutPostRedisplay();
			break;
	}
}

//motion only for boxes

void condMotion(float b[][2],float p[][2]){

	if((b[1][0] == p[0][0] && b[1][1] == p[0][1] && b[2][0] == p[3][0] && b[2][1] == p[3][1]) && (t==3)){
		motion(b,xX,yY);//up
	}
	if((b[0][0] == p[1][0] && b[0][1] == p[1][1] && b[3][0] == p[2][0] && b[3][1] == p[2][1]) && (t==4)){
		motion(b,xX,yY);//down
	}
	if((b[1][0] == p[2][0] && b[1][1] == p[2][1] && b[0][0] == p[3][0] && b[0][1] == p[3][1]) && (t==2)){
		motion(b,xX,yY);//right
	}
	if((b[2][0] == p[1][0] && b[2][1] == p[1][1] && b[3][0] == p[0][0] && b[3][1] == p[0][1]) && (t==1)){
		motion(b,xX,yY);//left
	}

}

//condtions for walls

bool condWall(float z[][2])
{

	if((z[0][1]==75 && z[3][1]==75 && t==3)	/*w1*/
			|| (z[0][0]==25 && z[1][0]==25 && t==1) /*w2*/
			|| (z[1][1]==25 && z[2][1]==25 && t==4) /*w3*/
			|| (z[2][0]==75 && z[3][0]==75 && t==2) /*w4*/
			|| (z[1][1]==65 && z[2][1]==65 && z[1][0]>=50 && z[2][0]>=55 && t==4) /*w5 down*/
			|| (z[2][0]==50 && z[2][1]==60 && z[3][0]==50 && z[3][1]==65 && t==2) /*w5 right*/
			|| (z[0][0]>=50 && z[0][1]==60 && z[3][0]>=55 && z[3][1]==60 && t==3) /*w5 up*/
			|| (z[1][0]<=45 && z[1][1]==50 && z[2][0]<=50 && z[2][1]==50 && t==4) /*w6 down*/	
			|| (z[0][0]==50 && z[0][1]>=40 && z[0][1]<=50 && z[1][0]==50 && z[1][1]>=35 && z[1][1]<=45 && t==1) /*w6,w7 left*/
			|| (z[0][0]==45 && z[0][1]==35 && z[3][0]==50 && z[3][1]==35 && t==3) /*w7 up*/
			|| (z[2][0]==45 && z[2][1]>=35 && z[2][1]<=50 && z[3][0]==45 && z[3][1]>=40 && z[3][1]<=45 && t==2) /*w7 right(see)*/
			|| (z[0][0]<=40 && z[0][1]==45 && z[3][0]<=45 && z[3][1]==45 && t==3) /*w6 up*/
	  )
		return false;
	else
		return true;
}

//condtion for one box over the other box
bool condOverP()
{
	if(condPairs(p,b1) || condPairs(p,b2) || condPairs(p,b3))
		return false;
	else
		return true;
}

bool condOverB()
{
	if(condPairs(b1,b2) || condPairs(b2,b3) || condPairs(b1,b3))
		return false;
	else
		return true;
}

//pair wise checking of one box over the other box
bool condPairs(float x[][2],float y[][2])
{
	if(x[0][0] == y[0][0] && x[0][1] == y[0][1] 			//A coordinates
			&& x[1][0] == y[1][0] && x[1][1] == y[1][1]	//B coordinates 
			&& x[2][0] == y[2][0] && x[2][1] == x[2][1]	//C coordinates
			&& x[3][0] == y[3][0] && x[3][1] == y[3][1]	//D coordinates
	  )	
		return true;
	else
		return false;
}

bool win()
{
	if((condPairs(b1,g1) || condPairs(b1,g2) || condPairs(b1,g3)) &&
			(condPairs(b2,g1) || condPairs(b2,g2) || condPairs(b2,g3)) &&
			(condPairs(b3,g1) || condPairs(b3,g2) || condPairs(b3,g3))
	  )
		return true;
	else 
		return false;
}

void displayGame(void)
{
	xX = 0;
	yY = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_POLYGON); 	//w1
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(20.0, 80.0);
	glVertex2f(20.0, 75.0);
	glVertex2f(80.0, 75.0);
	glVertex2f(80.0, 80.0);
	glEnd();

	glBegin(GL_POLYGON);	//w2
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(20.0, 75.0);
	glVertex2f(20.0, 25.0);
	glVertex2f(25.0, 25.0);
	glVertex2f(25.0, 75.0);
	glEnd();

	glBegin(GL_POLYGON);	//w3
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(20.0, 25.0);
	glVertex2f(20.0, 20.0);
	glVertex2f(80.0, 20.0);
	glVertex2f(80.0, 25.0);
	glEnd();

	glBegin(GL_POLYGON);	//w4
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(75.0, 75.0);
	glVertex2f(75.0, 25.0);
	glVertex2f(80.0, 25.0);
	glVertex2f(80.0, 75.0);
	glEnd();

	glBegin(GL_POLYGON);    //w5
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(50.0, 65.0);
	glVertex2f(50.0, 60.0);
	glVertex2f(75.0, 60.0);
	glVertex2f(75.0, 65.0);
	glEnd();

	glBegin(GL_POLYGON);    //w6
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(25.0, 50.0);
	glVertex2f(25.0, 45.0);
	glVertex2f(50.0, 45.0);
	glVertex2f(50.0, 50.0);
	glEnd();

	glBegin(GL_POLYGON);    //w7
	glColor3f(0.543, 0.0, 0.0);
	glVertex2f(45.0, 45.0);
	glVertex2f(45.0, 35.0);
	glVertex2f(50.0, 35.0);
	glVertex2f(50.0, 45.0);
	glEnd();

	glBegin(GL_POLYGON);//g1
	glColor3f(0.0, 0.0, 1.0);
	for(int i = 0; i < 4 ;i++){
		glVertex2fv(g1[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);    //g2
	glColor3f(0.0, 0.0, 1.0);
	for(int i = 0; i < 4 ;i++){
		glVertex2fv(g2[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);    //g3
	glColor3f(0.0, 0.0, 1.0);
	for(int i = 0; i < 4 ;i++){
		glVertex2fv(g3[i]);
	}

	glEnd();

	for(int i=0;i<4;i++){
		for(int j=0;j<2;j++){
			Rp[i][j]=p[i][j];
			Rb1[i][j]=b1[i][j];
			Rb2[i][j]=b2[i][j];
			Rb3[i][j]=b3[i][j];
		}
	}

	keys();

	if(condWall(b1)==true)
		condMotion(b1,p);//box1

	if(condWall(b2)==true)
		condMotion(b2,p);//box2

	if(condWall(b3)==true)
		condMotion(b3,p);//box3

	if(condWall(p)==true)
		motion(p,xX,yY);//for player

	if(condOverP()==true && condOverB()==true){ //normal movement condtion
		glBegin(GL_POLYGON); //b1
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4 ;i++){
			glVertex2fv(b1[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //b2
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4; i++){
			glVertex2fv(b2[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //b3
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4; i++){
			glVertex2fv(b3[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //p
		glColor3f(1.0, 0.5, 0.0);
		for(int i = 0; i < 4 ;i++){
			glVertex2fv(p[i]);
		}
		glEnd();

	}
	else //reach towards previous condition if next state is wrong
	{
		glBegin(GL_POLYGON); //b1
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4 ;i++){
			glVertex2fv(Rb1[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //b2
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4; i++){
			glVertex2fv(Rb2[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //b3
		glColor3f(0.0, 1.0, 0.0);
		for(int i = 0; i < 4; i++){
			glVertex2fv(Rb3[i]);
		}
		glEnd();

		glBegin(GL_POLYGON); //p
		glColor3f(1.0, 0.5, 0.0);
		for(int i = 0; i < 4 ;i++){
			glVertex2fv(Rp[i]);
		}
		glEnd();

		for(int i=0;i<4;i++){
			for(int j=0;j<2;j++){
				p[i][j]=Rp[i][j];
				b1[i][j]=Rb1[i][j];
				b2[i][j]=Rb2[i][j];
				b3[i][j]=Rb3[i][j];
			}
		}

	}

	if(win()==true){
		cout<<" YOU WIN \n";
	}
	glEnable(GL_TEXTURE_2D);
}

void display(void){
	printf("\nScreen:%d\n",screen);
	if(screen==1){
		displayMenu();
//		glutTimerFunc(1000,timerFunc,0);
		timerFunc();
	}
	else
		displayGame();
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sokoban Solver");
	init();
	glutMouseFunc(mouse);
	glutSpecialFunc(k);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
