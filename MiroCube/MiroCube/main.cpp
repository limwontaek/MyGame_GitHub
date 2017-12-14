#define _CRT_SECURE_NO_WARNINGS

#include "Termp.h"
#define CUBE_SIZE 10

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void getSpecialKeyboard(int key, int x, int y);
void InitSetUp();
void Motion(GLint x, GLint y);
void Mouse(int button, int state, int x, int y);
//void MenuFunc(int button);
struct Point {
	GLfloat x, y, z;
};
struct Camera_Utility  {
	//camera
	Point camera_rotate;
	int view_point;

	//Rotate camera Mouse
	Point view_vertex;
	GLfloat view_x;
	GLfloat view_y;
	GLfloat view_z;
};
Camera_Utility cu;
struct Background_Utility {
	Point ball_vertex;
	bool ball_trans_button[4];
	GLfloat ball_angle;

	Point wall_vertex[30][30];
	bool collide_button;
};
Background_Utility bu;
struct Display_Utility {
	short lightState = 0;
	float ambient[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float diffuse[4] = { 0.6f, 0.6f, 0.6f, 0.6f };
	float specular[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	bool  lightOn[5] = { false, false, false, false,false };
	bool nomarlize_on = false;

	Point light_vertex;
};
Display_Utility du;

int Board[MIRO_SIZE][MIRO_SIZE];
GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLubyte* bitmap;
BITMAPINFO* bitmapInfo; // 비트맵 헤더 저장할 변수 

class Camera {
public:
	void camera_rotate()
	{
		glRotatef(cu.camera_rotate.x, 1, 0, 0);
		glRotatef(cu.camera_rotate.y, 0, 1, 0);
		glRotatef(cu.camera_rotate.z, 0, 0, 1);
	}
};
class Display {
public:
	void ball_display()
	{
		glEnable(GL_LIGHTING);

		//material
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		GLfloat AmbientLight[] = { 0, 0, 0, 0.0f };
		GLfloat DiffuseLight[] = { 0.6, 0.6, 0.6, 0.0f };
		GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 0.0f };
		//glTranslatef(27 * 25 + bu.ball_vertex.x, 0, 29 * 25 + bu.ball_vertex.z);
		GLfloat lightPos[] = {bu.ball_vertex.x, 50, bu.ball_vertex.z, 1.0f };
		//GLfloat lightPos[] = { 100 , 100, 0, 1.0f };

		GLfloat direction[] = { 0,-1,0 };
		GLfloat angle[] = { 90.0 };
		GLfloat exponent[] = { 100 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, angle);
		glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, exponent);

		glEnable(GL_LIGHT0);


		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
		glMateriali(GL_FRONT, GL_SHININESS, 128);
	}
	void clear_display()
	{
		glEnable(GL_LIGHTING);

		//material
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		GLfloat AmbientLight[] = { 0, 0, 0, 0.0f };
		GLfloat DiffuseLight[] = { 0.6, 0.6, 0.6, 0.0f };
		GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 0.0f };
		//glTranslatef(27 * 25 + bu.ball_vertex.x, 0, 29 * 25 + bu.ball_vertex.z);
		//GLfloat lightPos[] = { bu.ball_vertex.x, 10, bu.ball_vertex.z, 1.0f };
		GLfloat lightPos[] = { 0 , 500, 0, 1.0f };


		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
		

		glEnable(GL_LIGHT1);


		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
		glMateriali(GL_FRONT, GL_SHININESS, 128);
	}
	

};
class MIRO {
public:
	void Init() {
		//glColor3f(0.45, 0.15, 0);
		glColor3f(0.3, 0.3, 0.3);
		for (int j = 0; j < 50; ++j) {
			for (int i = 0; i < 50; ++i) {
				glPushMatrix(); {
					glTranslatef(i*3, 0,j*3);
					glScalef(1, 0.01, 1);
					glutSolidCube(3);
				}glPopMatrix();
			}
		}
	}
	void load_Miro() {
		ifstream ReadFile("miro_beta.txt");
			
		try
		{
			if (ReadFile.is_open() == true)
			{
				cout << "파일 읽기 성공!" << endl;
				for (int j = 0; j < MIRO_SIZE; ++j) {
					for (int i = 0; i < MIRO_SIZE; ++i) {
						ReadFile >> Board[j][i];
					}
				}
				ReadFile.close();

				for (int j = 0; j < MIRO_SIZE; ++j) {
					for (int i = 0; i < MIRO_SIZE; ++i) {
						cout << Board[j][i] << " ";
					}
					cout << endl;
				}
			}
			else
			{
				throw false;
			}
		}

		catch (bool)
		{
			cout << "파일 읽기 실패!" << endl;
		}
	}
	void draw_Miro() {
		/*GLuint textures[3];
		glGenTextures(3, textures);
		for (int i = 0; i < 3; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			if (i == 0) bitmap = LoadDIBitmap("cube0.bmp", &bitmapInfo);
			if (i == 1) bitmap = LoadDIBitmap("cube1.bmp", &bitmapInfo);
			if (i == 2) bitmap = LoadDIBitmap("cube2.bmp", &bitmapInfo);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);*/

		glPushMatrix(); {
			//glColor3f(0.35,0.5, 0);
			glColor3f(0.3, 0.3, 0.3);
			glScalef(0.5, 0.8, 0.5);
			glutSolidCube(CUBE_SIZE);

			//draw wall cpu부족으로 렉이 너무 심하여 적용불가
			//glPushMatrix(); {
			//	//side (w,d,s,a)
			//	// front
			//	glBindTexture(GL_TEXTURE_2D, textures[1]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2);
			//	glTexCoord2f(0.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE/2, -CUBE_SIZE/2, CUBE_SIZE/2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE/2, -CUBE_SIZE/2, CUBE_SIZE/2);
			//	glEnd();

			//	// right
			//	glBindTexture(GL_TEXTURE_2D, textures[1]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
			//	glEnd();

			//	// back
			//	glBindTexture(GL_TEXTURE_2D, textures[1]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glEnd();

			//	//left
			//	glBindTexture(GL_TEXTURE_2D, textures[1]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
			//	glEnd();

			//	//up,down
			//	glBindTexture(GL_TEXTURE_2D, textures[0]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE/2, CUBE_SIZE/2, -CUBE_SIZE/2);
			//	glTexCoord2f(0.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE/2, CUBE_SIZE/2, -CUBE_SIZE/2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE/2, CUBE_SIZE/2, CUBE_SIZE/2);
			//	glEnd();

			//	glBindTexture(GL_TEXTURE_2D, textures[2]);
			//	glBegin(GL_QUADS);
			//	glTexCoord2f(1.0f, 1.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE/2, -CUBE_SIZE/2, -CUBE_SIZE/2);
			//	glTexCoord2f(0.0f, 1.0f);   // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE/2, -CUBE_SIZE / 2);
			//	glTexCoord2f(0.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE/2, CUBE_SIZE / 2);
			//	glTexCoord2f(1.0f, 0.0f);  // 텍스처 위치 설정
			//	glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE/2, CUBE_SIZE / 2);
			//	glEnd();
			//}glPopMatrix();
		}glPopMatrix();
	}
	void collide_box()
	{
		for (int j = 0; j < 30; ++j) {
			for (int i = 0; i < 30; ++i) {
				/*if (((bu.wall_vertex[j][i].x <= bu.ball_vertex.x) && (bu.ball_vertex.x <= bu.wall_vertex[j][i].x + 2.5)) &&
					((bu.wall_vertex[j][i].z <= bu.ball_vertex.z) && (bu.ball_vertex.z <= bu.wall_vertex[j][i].z + 2.5)))
					bu.collide_button = true;*/
				if (((bu.wall_vertex[j][i].x - bu.ball_vertex.x)*(bu.wall_vertex[j][i].x - bu.ball_vertex.x)) + ((bu.wall_vertex[j][i].z - bu.ball_vertex.z)*(bu.wall_vertex[j][i].z - bu.ball_vertex.z)) <= 3.5*3.5) // 1은 공의 반지름
					bu.collide_button = true;
			}
		}
	}

};
class Ghost {
public:

};
class Robot {

};
class Ball {
private:
	MIRO miro;
public:
	void Init()
	{
		bu.ball_vertex.x = 27 * 5;
		bu.ball_vertex.z = 29 * 5;

		cu.view_vertex.x = 27 * 5;
		cu.view_vertex.z = 29 * 5;
	}
	void draw_ball()
	{
		glPushMatrix(); {
			// 위치 : 27 29 번쨰 배열
			glTranslatef(bu.ball_vertex.x,1,bu.ball_vertex.z);

			glColor3f(1, 1, 0);
			glutSolidSphere(1, 15, 15);
		}glPopMatrix();
	}
	void timer()
	{
		// w
		if (bu.ball_trans_button[0] == true)
		{
			if (bu.collide_button == true) {
				bu.collide_button = false;
				bu.ball_trans_button[0] = false;
				bu.ball_vertex.z += 1;
			}
			else if (bu.collide_button == false) {
				bu.ball_vertex.z -= 1;
			}
			
		}
		// s
		if (bu.ball_trans_button[1] == true)
		{
			if(bu.collide_button == false)
				bu.ball_vertex.z += 1;
			if (bu.collide_button == true) {
				bu.ball_vertex.z -= 1;
				bu.collide_button = false;
				bu.ball_trans_button[1] = false;
			}
		}
		// a
		if (bu.ball_trans_button[2] == true)
		{
			if (bu.collide_button == false)
				bu.ball_vertex.x -= 1;
			if (bu.collide_button == true) {
				bu.ball_vertex.x += 1;
				bu.collide_button = false;
				bu.ball_trans_button[2] = false;
			}
		}
		// d
		if (bu.ball_trans_button[3] == true)
		{
			if (bu.collide_button == false)
				bu.ball_vertex.x += 1;
			if (bu.collide_button == true) {
				bu.ball_vertex.x -= 1;
				bu.collide_button = false;
				bu.ball_trans_button[3] = false;
			}
		}
	}
};
class Update {
private:
	MIRO miro;
	Ball ball;
	Display display;
public:
	void draw_map()
	{
		miro.Init();
		display.ball_display();
		//display.clear_display();		//도착시 조명
		miro.collide_box();

		//0:빈 곳 1:벽 2:아이템 or 몬스터 3:시작 4:도착지점
		for (int j = 0; j < MIRO_SIZE; ++j) {
			for (int i = 0; i < MIRO_SIZE; ++i) {
				if (Board[j][i] == 1)
				{
					glPushMatrix(); {
						glTranslatef(i * 5, 5, j * 5);

						//Input wall_vertex
						bu.wall_vertex[j][i].x = i * 5;
						bu.wall_vertex[j][i].y = 5;
						bu.wall_vertex[j][i].z = j * 5;

						miro.draw_Miro();
					}glPopMatrix();
				}
				if (Board[j][i] == 3)
				{
					glPushMatrix(); {
						glColor3f(0, 1, 0);
						glScalef(1,0.1,1);
						glTranslatef(27 * 5, 0, 29 * 5);
						glutSolidCube(3);
					}glPopMatrix();
				}
				if (Board[j][i] == 4)
				{
					glPushMatrix(); {
						glColor3f(1, 0, 0);
						glScalef(1, 0.1, 1);
						glTranslatef(2 * 5, 0, 0 * 5);
						glutSolidCube(3);
					}glPopMatrix();
				}
			}

		}
		ball.draw_ball();

	}
};
void main()
{


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("Cube drawing");
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);

	InitSetUp();	//상태 변수 초기화
	
	glutPassiveMotionFunc(Motion);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(getSpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();

}

void InitSetUp()
{
	MIRO miro;
	Ball ball;
	// camera

	miro.load_Miro();
	ball.Init();
}

GLvoid drawScene()
{
	Camera camera;
	Update update;
	Display display;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camera rotate
	camera.camera_rotate(); 

	//display
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glPushMatrix(); {
		//Q: 반바퀴밖에 돌아가지않음
		if (cu.view_point == 1) {
			gluLookAt(0, 0, 0, 0, -0.5, 1, 0, 1, 0);
			glTranslatef(0.0, -300.0, 0.0);
		}
		if(cu.view_point == 0)
			gluLookAt(bu.ball_vertex.x, 30, bu.ball_vertex.z+15, cu.view_vertex.x, cu.view_vertex.y/2, bu.ball_vertex.z/2, 0, 1, 0);
		glPushMatrix(); {
			update.draw_map();
		}glPopMatrix();
	}glPopMatrix();


	cout << bu.collide_button << endl;

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0, WINDOWWIDTH, WINDOWHEIGHT, 0.0, -1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	if(cu.view_point == 1)
		glTranslatef(0.0, 0.0, -300.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void TimerFunction(int value)
{
	Ball ball;
	//timer_Setup
	ball.timer();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		//bu.ball_vertex.z -= 1;
		bu.ball_trans_button[0] = true;
		bu.ball_trans_button[1] = false;
		bu.ball_trans_button[2] = false;
		bu.ball_trans_button[3] = false;
	}
	else if (key == 's')
	{
		//bu.ball_vertex.z += 1;
		bu.ball_trans_button[0] = false;
		bu.ball_trans_button[1] = true;
		bu.ball_trans_button[2] = false;
		bu.ball_trans_button[3] = false;

	}
	else if (key == 'a')
	{
		//bu.ball_vertex.x -= 1;
		bu.ball_trans_button[0] = false;
		bu.ball_trans_button[1] = false;
		bu.ball_trans_button[2] = true;
		bu.ball_trans_button[3] = false;

	}
	else if (key == 'd')
	{
		//bu.ball_vertex.x += 1;
		bu.ball_trans_button[0] = false;
		bu.ball_trans_button[1] = false;
		bu.ball_trans_button[2] = false;
		bu.ball_trans_button[3] = true;

	}
	else if (key == 'v' || key == 'V')
	{
		cu.view_point +=1;
		if (cu.view_point == 2)
			cu.view_point = 0;
	}

}
void getSpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN) {
		cu.camera_rotate.x += 5;
	}
	else if (key == GLUT_KEY_UP) {
		cu.camera_rotate.x -= 5;
	}
	else if (key == GLUT_KEY_RIGHT) {
		cu.camera_rotate.y += 5;

	}
	else if (key == GLUT_KEY_LEFT) {
		cu.camera_rotate.y -= 5;
	}


	glutPostRedisplay();
}
void Motion(GLint x, GLint y)
{
	cu.view_vertex.x = x - (WINDOWWIDTH / 2);
	cu.view_vertex.y = -(y - (WINDOWHEIGHT / 2));

	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{


}
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)   return NULL;

	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)    bitsize = ((*info)->bmiHeader.biWidth
		* (*info)->bmiHeader.biBitCount + 7) / 8.0
		* abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}