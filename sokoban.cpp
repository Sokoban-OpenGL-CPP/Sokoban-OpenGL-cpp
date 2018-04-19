#include <GL/glut.h>
#include<iostream>

using namespace std;

bool condPairs(float x[][2],float y[][2]);

int t;
float xX = 0,yY = 0;

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

void k(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			t = 3;
			glutPostRedisplay();
			break;
		case 'a':
			t = 1;
			glutPostRedisplay();
			break;
		case's':
			t = 4;
			glutPostRedisplay();
			break;
		case'd':
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
	if( x[0][0] == y[0][0] && x[0][1] == y[0][1] 		//A coordinates
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
	for(int i=0;i<4;i++){
		for(int j=0;j<2;j++){
			if((b1[i][j]==g1[i][j] || b1[i][j]==g2[i][j] || b1[i][j]==g3[i][j])
			&& (b2[i][j]==g1[i][j] || b2[i][j]==g2[i][j] || b2[i][j]==g3[i][j])
			&& (b3[i][j]==g1[i][j] || b3[i][j]==g2[i][j] || b3[i][j]==g3[i][j])){

				return true;

			}
			else
			{
				return false;
			}
		}
	}
}

void display(void)
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

	if(condWall(p)==true /*&& condOverP(p, b1, b2, b3)==true*/)
		motion(p,xX,yY);//for player

	if(condOverP()==true && condOverB()==true){
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
	else
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
	glutKeyboardFunc(k);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
