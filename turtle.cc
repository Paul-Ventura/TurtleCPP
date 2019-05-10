#include <GL/glut.h>
#include <iostream>

using namespace std;

class Singleton {
	static Singleton *instance;
	int data_x;
	int data_y;

	Singleton() {
		data_x = 100;
		data_y = 100;
	}

	public:
	static Singleton *getInstance() {
		if (!instance)
		instance = new Singleton;
		return instance;
	}
//getters
	int getDataX() {
		return this -> data_x;
	}

	int getDataY() {
		return this -> data_y;
	}

//setters
	void setDataX(int data) {
		this -> data_x = data;
	}

	void setDataY(int data) {
		this -> data_y = data;
	}

//forward, backward, up and down
	void forward(int data) {
		this -> data_x = data;
	}

	void up(int data) {
		this -> data_y = data;
	}

	void backward(int data) {
		int data2 = data*(-1);
		this -> data_x = data2;
	}

	void down(int data) {
		int data2 = data*(-1);
		this -> data_y = data2;
	}

//GLUT
	void init2D(float r, float g, float b)
	{
		glClearColor(r,g,b,0.0);  
		glMatrixMode (GL_PROJECTION);
		gluOrtho2D (0.0, 200.0, 0.0, 150.0);
	}

	int iniciar(int argc,char *argv[]){
		glutInit(&argc,argv);
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize (400, 400);
		glutInitWindowPosition (1, 1);
		glutCreateWindow ("points and lines");
		init2D(0.0,0.0,0.0);

		//glutDisplayFunc(display);
		//glutMainLoop();

		return 0;
	}

	void dibujar(void)
	{
		Singleton *s = s->getInstance();
		int a = s->getDataX();
		int b = s->getDataY();

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINES);
			glVertex2i(100,100);
			glVertex2i(a,b);
		glEnd();
		glFlush();

	}
};

Singleton *Singleton::instance = 0;

int main(int argc,char *argv[])
{
	Singleton *s = s->getInstance();

	s->iniciar(argc,argv);
	s->backward(50);
	s->dibujar();

	glutMainLoop();

	return 0;
}


