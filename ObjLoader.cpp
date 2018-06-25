// MainWnd.cpp: implementation of the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////
#include "ObjLoader.h"
//#include "MainWnd.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <gl/GL.h>
#include <glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;
//ʵ���ƶ����۲�ģ���������
extern float c;
extern float r;
extern float degreeX;
extern float degreeY;
extern int h;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMainWnd::CMainWnd(string path) :
	m_hWnd(NULL),
	m_fAngle(0.0f),
	m_hRC(NULL),
	m_path(path)
{

}

CMainWnd::~CMainWnd()
{
}

//
// GLCube()
// Renders a cube.
//
#define YU 50
void CMainWnd::GLCube()
{
	for (int i = 0; i<m_pic.F.size(); i++)
	{
		glBegin(GL_TRIANGLES);							// ����������
		if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[0]].TU, m_pic.VT[m_pic.F[i].T[0]].TV);  //����	
		if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[0]].NX, m_pic.VN[m_pic.F[i].N[0]].NY, m_pic.VN[m_pic.F[i].N[0]].NZ);//������
		glVertex3f(m_pic.V[m_pic.F[i].V[0]].X / YU, m_pic.V[m_pic.F[i].V[0]].Y / YU, m_pic.V[m_pic.F[i].V[0]].Z / YU);		// �϶���

		if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[2]].TU, m_pic.VT[m_pic.F[i].T[2]].TV);  //����
		if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[2]].NX, m_pic.VN[m_pic.F[i].N[2]].NY, m_pic.VN[m_pic.F[i].N[2]].NZ);//������
		glVertex3f(m_pic.V[m_pic.F[i].V[2]].X / YU, m_pic.V[m_pic.F[i].V[2]].Y / YU, m_pic.V[m_pic.F[i].V[2]].Z / YU);		// ����

		if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[1]].TU, m_pic.VT[m_pic.F[i].T[1]].TV);  //����
		if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[1]].NX, m_pic.VN[m_pic.F[i].N[1]].NY, m_pic.VN[m_pic.F[i].N[1]].NZ);//������
		glVertex3f(m_pic.V[m_pic.F[i].V[1]].X / YU, m_pic.V[m_pic.F[i].V[1]].Y / YU, m_pic.V[m_pic.F[i].V[1]].Z / YU);		// ����

		glEnd();										// �����λ��ƽ���	
	}
}

//
// InitScene()
// Called when the OpenGL RC has been created. Sets the initial state for
// the OpenGL scene.
//
void CMainWnd::InitScene()
{
	ReadPIC();
	//glClear��������OPENGL,��������ͨ��glClearʹ�ú죬�̣����Լ�AFAֵ�������ɫ�������ģ�
	//���Ҷ�����һ���ڣ�0��1��֮���ֵ����ʵ������յ�ǰ��������ɫ��
	glClearColor(0.000f, 0.000f, 0.000f, 1.0f); //Background color

	// TODO: Replace the following sample code with your initialization code.

	// Activate lighting and a light source
	//�������ø��ֹ��ܡ����幦���ɲ�����������glDisable���Ӧ��glDisable���Թرո���ܡ�
	glEnable(GL_LIGHT0);//����0�ŵƵ�7�ŵ�(��Դ)������ԴҪ���ɺ���glLight���������
	glEnable(GL_LIGHTING);//���õ�Դ
	glEnable(GL_DEPTH_TEST);//������Ȳ��ԡ��������������Զ���Զ����ر���ס��ͼ�Σ����ϣ�
	
	/*
	glEnable(GL_TEXTURE_2D);   // ���ö�ά����

	// Define material parameters
	static GLfloat glfMatAmbient[] = { 0.000f, 0.450f, 1.000f, 1.0f };
	static GLfloat glfMatDiffuse[] = { 0.000f, 0.000f, 0.580f, 1.0f };
	static GLfloat glfMatSpecular[] = { 1.000f, 1.000f, 1.000f, 1.0f };
	static GLfloat glfMatEmission[] = { 0.000f, 0.000f, 0.000f, 1.0f };
	static GLfloat fShininess = 128.000f;

	// Set material parameters
	//ָ�����ڹ��ռ���ĵ�ǰ�������ԡ�����face��ȡֵ������GL_FRONT��GL_BACK��GL_FRONT_AND_BACK��ָ���������Խ�Ӧ������������档
	//void glMaterial{if}(GLenum face, GLenum pname, TYPE param);
	glMaterialfv(GL_FRONT, GL_AMBIENT, glfMatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glfMatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glfMatSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, glfMatEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, fShininess);
	*/
}

//
// KillScene()
// Called when the OpenGL RC is about to be destroyed. 
//
void CMainWnd::KillScene()
{
	// TODO: Use KillScene to free resources.
}

//
// DrawScene()
// Called each time the OpenGL scene has to be drawn.
//
void CMainWnd::DrawScene()
{
	// TODO: Replace the following sample code with your code to draw the scene.
	InitScene();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers  // �����Ļ����Ȼ���

	glLoadIdentity(); // Load identity matrix	// ����ģ�͹۲����
	//gluLookAt(r*cos(c*degree), 0, r*sin(c*degree), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	// Add a light source
	//GLfloat glfLight[] = { -4.0f, 4.0f, 4.0f, 0.0f };
	//GLfloat glfLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, glfLight);

	// Position and rotate the camera
	//glTranslatef(0.0f, 0.0f, -5.0f);	// ������Ļ 5.0
	//glTranslatef(0.0f, 0.0f, -8.0f);
	//glRotatef(30.0f, 1.0f, 0.0f, 0.0f);	//��X����ת
	//glRotatef(m_fAngle, 0.0f, 1.0f, 0.0f);

	//gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//gluLookAt(r*cos(c*degree), 0, r*sin(c*degree), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0, 1.0, 0.0);												//��ɫ
	
	gluLookAt(r*sin(c*degreeY)*cos(c*degreeX), r*cos(c*degreeY), r*sin(c*degreeY)*sin(c*degreeX), 
				0.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f);		//�ƶ����
	//gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Draw a cube
	GLCube();

	glFlush();
}

//
// Tick()
// The applications "heartbeat" function. Called before another frame needs
// to be drawn. Use this function to calculate new positions for objects in 
// the scene, for instance. Set bRedrawScene = FALSE if the scene should not be 
// redrawn.
//
void CMainWnd::Tick(BOOL &bRedrawScene)
{
	m_fAngle += 0.1; // Add some rotation to the cube
}

void CMainWnd::ReadPIC()
{
	ifstream ifs(m_path);//cube bunny Eight
	string s;
	Mian *f;
	POINT3 *v;
	FaXiangLiang *vn;
	WenLi	*vt;
	while (getline(ifs, s))
	{
		if (s.length()<2)continue;
		if (s[0] == 'v') {
			if (s[1] == 't') {//vt 0.581151 0.979929 ����
				istringstream in(s);
				vt = new WenLi();
				string head;
				in >> head >> vt->TU >> vt->TV;
				m_pic.VT.push_back(*vt);
			}
			else if (s[1] == 'n') {//vn 0.637005 -0.0421857 0.769705 ������
				istringstream in(s);
				vn = new FaXiangLiang();
				string head;
				in >> head >> vn->NX >> vn->NY >> vn->NZ;
				m_pic.VN.push_back(*vn);
			}
			else {//v -53.0413 158.84 -135.806 ��
				istringstream in(s);
				v = new POINT3();
				string head;
				in >> head >> v->X >> v->Y >> v->Z;
				m_pic.V.push_back(*v);
			}
		}
		else if (s[0] == 'f') {//f 2443//2656 2442//2656 2444//2656 ��
			for (int k = s.size() - 1; k >= 0; k--) {
				if (s[k] == '/')s[k] = ' ';
			}
			istringstream in(s);
			f = new Mian();
			string head;
			in >> head;
			int i = 0;
			while (i<3)
			{
				if (m_pic.V.size() != 0)
				{
					in >> f->V[i];
					f->V[i] -= 1;
				}
				if (m_pic.VT.size() != 0)
				{
					in >> f->T[i];
					f->T[i] -= 1;
				}
				if (m_pic.VN.size() != 0)
				{
					in >> f->N[i];
					f->N[i] -= 1;
				}
				i++;
			}
			m_pic.F.push_back(*f);
		}
	}
}