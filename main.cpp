#include "ObjLoader.h"
#include <glut.h>
#include <stdio.h>
#include <iostream>
//#include "MainWnd.h"
using namespace std;

//ģ��·��
string filePath = "ChargerBar.obj";

CMainWnd obj = CMainWnd(filePath);

//ʵ���ƶ����۲�ģ���������
float c = 3.1415926 / 180.0f;
float r = 5.0f;
float degreeX = 90;
float degreeY = 90;
float ratio = 0.1;
int h = 0.0;

static int oldPosX = -1;
static int oldPosY = -1;
// settings
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;
//���ù�Դ
void setLightRes() {
	GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHTING); //���ù�Դ
	glEnable(GL_LIGHT0);   //ʹ��ָ���ƹ�
}

//��ʼ��
void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutInitWindowPosition(500, 250);
	glutCreateWindow("ObjLoader");

	glClearDepth(1.0f);				//  ��Ȼ�������
	glEnable(GL_DEPTH_TEST);		//  ����Ȳ���
	glDepthFunc(GL_LEQUAL);         //  ������Ȳ�������
	glShadeModel(GL_SMOOTH);
	//setLightRes();
}

void display()
{
	//cout << "enter display" << endl;
	//glColor3f(0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -5.0f);
	//setLightRes();
	//glPushMatrix();

	obj.DrawScene();//����objģ��
	//glPopMatrix();
	glutSwapBuffers();
	//cout << "out display" << endl;
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

//�ƶ����360�۲�ģ��
void moseMove(int button, int state, int x, int y)
{
	//cout << "enter moseMove" << endl;
	if (button != GLUT_LEFT_BUTTON) {
		return;
	}
	if (state == GLUT_DOWN) {
		oldPosX = x;
		oldPosY = y;
		return;
	}
	
	cout << x << endl;
	cout << y << endl;

	GLint viewport[4];
	
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//��ͼ����
	glGetDoublev(GL_PROJECTION_MATRIX, projection);//ͶӰ����
	glGetIntegerv(GL_VIEWPORT, viewport);//�ӿ�
	winX = (float)x;//OGL�еĴ���x����
	winY = (float)viewport[3] - (float)y;//OGL�еĴ���y����

	glReadPixels(x, //x����
		int(winY), //y����
		1, 1,//��ȡһ������
		GL_DEPTH_COMPONENT,//��������Ϣ
		GL_FLOAT,//��������Ϊ������
		&winZ);//��õ����ֵ������winZ��
	cout << winZ << endl;
	
	GLfloat* pDepth = new GLfloat[SCR_HEIGHT*SCR_WIDTH];
	glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, pDepth);
	/*
	ofstream fileMat("C:\\Users\\wangquan\\Documents\\Visual Studio 2015\\Projects\\glut2\\glut2\\2.txt");
	for (int i = SCR_HEIGHT; i > 0; i--) {
		for (int j = 0; j < SCR_WIDTH; j++) {
			if (pDepth[j+ SCR_WIDTH*i] == 1) {
				fileMat << 0 << " ";
			}
			else {
				fileMat << 255 << " ";
			}
		}
	}
	*/
	/*
	for (int y1 = 0; y1 < SCR_HEIGHT; y1++) {
		for (int x1 = 0; x1 < SCR_WIDTH; x1++) {
			winY = (float)viewport[3] - (float)y1;
			glReadPixels(x1, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			if (winZ == 1) {
				fileMat << 0 << " ";
			}
			else {
				fileMat << 255 << " ";
			}
		}
	}
	*/
	//fileMat.close();

	cout << "out moseMove" << endl;
}
void changeViewPoint(int x, int y)
{
	/*
	degree += x - oldPosX;
	h += 0.03*(y - oldPosY);
	if (h > 1.0) {
		h = 1.0;
	} else if (h < -1.0) {
		h = -1.0;
	}
	*/
	//cout << "enter changeViewPoint" << endl;
	degreeX += ratio*(x - oldPosX);
	degreeY -= ratio*(y - oldPosY);
		
	//oldPosX	= x;
	//oldPosY = y;
	//cout << "out changeViewPoint" << endl;
}

void myIdle()
{
	glutPostRedisplay();
}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(moseMove);
	glutMotionFunc(changeViewPoint);
	/*
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("��һ��OpenGL����");
	*/
	glutIdleFunc(myIdle);
	glutMainLoop();


	return 0;
}