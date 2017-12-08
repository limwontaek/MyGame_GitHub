#include "Termp.h"
#define CUBE_SIZE 50

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void getSpecialKeyboard(int key, int x, int y);
void InitSetUp();
void Motion(GLint x, GLint y);
//void MenuFunc(int button);

struct Camera_Utility {
	//camera
	int camera_rotate_X;
	int camera_rotate_Y;
	int camera_rotate_Z;

	bool camera_button_X;
	bool camera_button_Y;
	bool camera_button_Z;
	bool camera_button_x;
	bool camera_button_y;
	bool camera_button_z;

	//Rotate camera Mouse
	GLfloat view_x;
	GLfloat view_y;
	GLfloat view_z;
};
Camera_Utility cu;
struct Point {
	GLfloat x, y, z;
};
int Board[MIRO_SIZE][MIRO_SIZE];
struct Background_Utility {
	Point ball_vertex;
	bool ball_collide_button;
};
Background_Utility bu;

class Camera {
public:
	void camera_Init() {
		cu = { 0,0,0, false,false,false,false,false,false };
	}
	void camera_set_up()
	{
		if (cu.camera_button_X == true)
		{
			cu.camera_rotate_X += 5;
			cu.camera_button_X = false;
		}
		else if (cu.camera_button_x == true)
		{
			cu.camera_rotate_X -= 5;
			cu.camera_button_x = false;
		}

		if (cu.camera_button_Y == true)
		{
			cu.camera_rotate_Y += 5;
			cu.camera_button_Y = false;
		}
		else if (cu.camera_button_y == true)
		{
			cu.camera_rotate_Y -= 5;
			cu.camera_button_y = false;
		}

		if (cu.camera_button_Z == true)
		{
			cu.camera_rotate_Z += 5;
			cu.camera_button_Z = false;
		}
		else if (cu.camera_button_z == true)
		{
			cu.camera_rotate_Z -= 5;
			cu.camera_button_z = false;
		}
	}
	void camera_rotate()
	{
		glRotatef(cu.camera_rotate_X, 1, 0, 0);
		glRotatef(cu.camera_rotate_Y, 0, 1, 0);
		glRotatef(cu.camera_rotate_Z, 0, 0, 1);
	}
};
class Display {

};
class MIRO {
public:
	void Init() {

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
		glPushMatrix(); {
			glColor3f(0.5, 0.5, 0.5);
			glScalef(0.5, 1, 0.5);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
	}

};
class Ball {
public:
	void draw_ball()
	{
		glPushMatrix(); {
			// 위치 : 27 29 번쨰 배열
			glTranslatef(27 * 25+bu.ball_vertex.x, 0, 29 * 25+bu.ball_vertex.z);
			glColor3f(1, 1, 0);
			glutSolidSphere(10, 15, 15);
		}glPopMatrix();
	}
	void timer_ball()
	{
	
	}
};
class Update {
private:
	MIRO miro;
	Ball ball;
public:
	void draw_map()
	{

		//0:빈 곳 1:벽 2:아이템 or 몬스터 3:시작 4:도착지점
		for (int j = 0; j < MIRO_SIZE; ++j) {
			for (int i = 0; i < MIRO_SIZE; ++i) {
				if (Board[j][i] == 1)
				{
					glPushMatrix(); {
						glTranslatef(i * 25, 20, j * 25);
						miro.draw_Miro();
					}glPopMatrix();
				}
				//if (Board[j][i] == 2)
				//{

				//}
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
	
	glutMotionFunc(Motion);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(getSpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();

}

void InitSetUp()
{
	Camera camera;
	MIRO miro;
	// camera
	camera.camera_Init();

	miro.load_Miro();
}

GLvoid drawScene()
{
	Camera camera;
	Update update;
	glClearColor(0.0f, 1.0f, 0.8f, 0.7f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camera rotate
	camera.camera_rotate();


	glPushMatrix(); {
		//Q: 반바퀴밖에 돌아가지않음
		gluLookAt(-cu.view_x , -cu.view_y +10, 50,0, 0, 0, 0, 1, 0);
		glPushMatrix(); {
			glTranslatef(-750/2, 0, -750/2);
			update.draw_map();
		}glPopMatrix();
	}glPopMatrix();

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
	gluPerspective(60.0, 1.0, 1.0, 1500.0);
	glTranslatef(0.0, 0.0, -1000.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void TimerFunction(int value)
{
	Camera camera;

	//Camera_SetUp
	camera.camera_set_up();

	//timer_Setup

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{

}
void getSpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN) {
		cu.camera_button_X = true;
		cu.camera_button_x = false;
		cu.camera_button_Y = false;
		cu.camera_button_y = false;
	}
	else if (key == GLUT_KEY_UP) {
		cu.camera_button_x = true;
		cu.camera_button_X = false;
		cu.camera_button_Y = false;
		cu.camera_button_y = false;
	}
	else if (key == GLUT_KEY_RIGHT) {
		cu.camera_button_Y = true;
		cu.camera_button_y = false;
		cu.camera_button_x = false;
		cu.camera_button_X = false;
	}
	else if (key == GLUT_KEY_LEFT) {
		cu.camera_button_y = true;
		cu.camera_button_x = false;
		cu.camera_button_X = false;
		cu.camera_button_Y = false;
	}


	glutPostRedisplay();
}
void Motion(GLint x, GLint y)
{

	cu.view_x = x - (WINDOWWIDTH / 2);
	cu.view_y = -(y - (WINDOWHEIGHT / 2));


	glutPostRedisplay();
}