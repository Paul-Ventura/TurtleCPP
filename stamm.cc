#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

//Factory Method lets a class defer instantiation to subclasses.

class Tronco
{
  public:
    // Factory Method
    static Tronco *make_tronco(int choice);
    virtual void caracteristica() = 0;

	//Aquí se puede inicializar GLUT
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
/*
	void dibujar(void)
	{
		Tronco *t = t->getInstance();
		int a = t->getDataX();
		int b = t->getDataY();

		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINES);
			glVertex2i(100,100);
			glVertex2i(a,b);
		glEnd();
		glFlush();

	}
*/
};
class Plus_longitud: public Tronco
{
  public:
    void caracteristica()
    {
        cout << "Plus_longitud: tronco mas alto..." <<endl;
    }
};
class Plus_ancho: public Tronco
{
  public:
    void caracteristica()
    {
        cout << "Plus_ancho: tronco mas ancho..." <<endl;
    }
};
class Plus_normal: public Tronco
{
  public:
    void caracteristica()
    {
        cout << "Plus_normal: tronco normal..." <<endl;
    }
};
class Plus_void: public Tronco
{
  public:
    void caracteristica()
    {
        cout << "";
    }

};

Tronco *Tronco::make_tronco(int choice)
{
  if (choice == 1)
    return new Plus_longitud;
  else if (choice == 2)
    return new Plus_ancho;
  else if (choice == 3)
    return new Plus_normal;
  else cout <<"No existe esa opción"<<endl;
	return new Plus_void;
}

int main()
{
  vector<Tronco*> roles;
  int choice;
  while (true)
  {
    cout << "Plus_longitud(1) Plus_ancho(2) Plus_normal(3) Mostrar los objetos(0): ";
    cin >> choice;
    if (choice == 0)
      break;
    roles.push_back(Tronco::make_tronco(choice));
  }
  for (int i = 0; i < roles.size(); i++)
  {
    roles[i]->caracteristica();
	//roles[i]->saludo();
  }
  for (int i = 0; i < roles.size(); i++)
    delete roles[i];
}
