#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
using namespace std;

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
    glMatrixMode(GL_MODELVIEW);
}

int carX = 200, carY = 70;
int carsX=200, carsY=230;
int masiniX[4], masiniY[4];
int divx = 250, divy = 4, movd;
bool collide = false;

void tree(int x, int y) {
    int x1 = x;
    int y1 = y;
    //Tree Left
            //Bottom
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1 + 110, y1 + 250);
    glVertex2f(x1 + 120, y1 + 250 - 100);
    glVertex2f(x1 + 100, y1 + 250 - 100);
    glEnd();
    //Up
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1 + 110, y1 + 250 + 3);
    glVertex2f(x1 + 120 + 30, y1 + 250 - 30);
    glVertex2f(x1 + 100 - 30, y1 + 250 - 30);
    glEnd();
    glFlush();
}

void drum(void) {
    //drumul
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(250 - 100, 500);
    glVertex2f(250 - 100, 0);
    glVertex2f(250 + 100, 0);
    glVertex2f(250 + 100, 500);
    glEnd();

    glFlush();
}
void marcaj(void)
{
    
    for (int i = 1; i <= 10; i++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(divx - 5, divy * 15 * i + 18);
        glVertex2f(divx - 5, divy * 15 * i - 18);
        glVertex2f(divx + 5, divy * 15 * i - 18);
        glVertex2f(divx + 5, divy * 15 * i + 18);
        glEnd();
    }
    glFlush();
}
void masinaPrincipala(void) {
    
    //rotile
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(carX - 25, carY + 16);
    glVertex2f(carX + 25, carY + 16);
    glVertex2f(carX - 25, carY - 16);
    glVertex2f(carX + 25, carY - 16);
    glEnd();
    //partea de mijloc
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex2f(carX - 25, carY + 20);
    glVertex2f(carX - 25, carY - 20);
    glVertex2f(carX + 25, carY - 20);
    glVertex2f(carX + 25, carY + 20);
    glEnd();
    //partea de sus a masinii
    glBegin(GL_POLYGON);
    glColor3f(0.678, 1.000, 0.184);
    glVertex2f(carX - 23, carY + 20);
    glVertex2f(carX - 19, carY + 40);
    glVertex2f(carX + 19, carY + 40);
    glVertex2f(carX + 23, carY + 20);
    glEnd();
    //partea de jos a masinii
    glBegin(GL_POLYGON);
    glColor3f(0.000, 0.545, 0.545);
    glVertex2f(carX - 23, carY - 20);
    glVertex2f(carX - 19, carY - 35);
    glVertex2f(carX + 19, carY - 35);
    glVertex2f(carX + 23, carY - 20);
    glEnd();
    glFlush();
}

void masinaDepasire(void)
{
    //roti
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(carsX - 25, carsY + 16);
    glVertex2f(carsX + 25, carsY + 16);
    glVertex2f(carsX - 25, carsY - 16);
    glVertex2f(carsX + 25, carsY - 16);
    glEnd();
    //partea de mijloc
    glBegin(GL_QUADS);
    glColor3f(0.99609, 0.83984, 0);
    glVertex2f(carsX - 25, carsY + 20);
    glVertex2f(carsX - 25, carsY - 20);
    glVertex2f(carsX + 25, carsY - 20);
    glVertex2f(carsX + 25, carsY + 20);
    glEnd();

    //partea de sus a masinii
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex2f(carsX - 23, carsY + 20);
    glVertex2f(carsX - 19, carsY + 40);
    glVertex2f(carsX + 19, carsY + 40);
    glVertex2f(carsX + 23, carsY + 20);
    glEnd();
    //partea de jos a masinii
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex2f(carsX - 23, carsY - 20);
    glVertex2f(carsX - 19, carsY - 35);
    glVertex2f(carsX + 19, carsY - 35);
    glVertex2f(carsX + 23, carsY - 20);
    glEnd();
    glFlush();
}
//Functiile ptr depasire
void miscareInSus(void)
{
   /* boolean poateReveni = false;
    
    switch (carX) {
    case 300:
        break;
    default:
        carX = carX + 5;
        break;
    }
    switch (carY) {
    case 400:
        poateReveni = true;
        break;
    default:
        carY = carY + 5;
        break;
    }
    if (poateReveni == true) {
        switch (carX) {
        case 200:
            poateReveni = false;
            break;
        default:
            carX = carX - 10;
            break;
        }
    }*/
    if (carX < 300 && carY<290) {
        carX += 3 ;
    }
    if (carY < 400 ) {
        carY += 3;
        if (carY > 290 && carX >200) {
            carX -= 3;
            //cout << "x:" << carX << " " << "y: " << carY << endl;
        }
    }

    glutPostRedisplay();
    
}

void miscareInJos(void) 
{
    //boolean poateReveni = false;

   /* switch (carX) {
    case 300:
        break;
    default:
        carX = carX + 5;
        break;
    }*/
   /* else if(carX>200){
        carX -= 5;
    }*/
    //switch (carY) {
    //case 70:
    //   poateReveni = true;
    //    break;
    //default:
    //    carY = carY - 5;
    //    break;
    //}
    /*if (poateReveni == true) {
        switch (carX) {
        case 200:
            poateReveni = false;
            break;
        default:
            carX = carX - 10;
            break;
        }
    }*/
    
    if (carX < 300 && carY>180) {
        carX += 3;
    }
    if (carY > 70) {
        carY -= 3;
        if (carY < 180 && carX >200) {
            carX -= 3;
            //cout<<"x:" << carX << " " <<"y: "<< carY<<endl;
        }
    }

    glutPostRedisplay();
}


//Functia pentru controlul masini din mouse
void mouse(int button, int state, int x, int y) 
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(miscareInSus);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(miscareInJos);
        break;
    default:
        break;
    }
}

void desen(void) // procedura desenare  
{
    glClear(GL_COLOR_BUFFER_BIT);
    //generarea copacillor pentru partea stanga a drumului
    tree(-75, -150);
    tree(5, -150);
    tree(-40, 0);
    tree(-75, 150);
    tree(5, 150);

    //generarea copacillor pentru partea dreapta a drumului
    tree(270, -150);
    tree(360, -150);
    tree(320, 0);
    tree(275, 150);
    tree(360, 150);

    //apelarea merodelor ptr drum si masini
    drum();
    marcaj();
    masinaPrincipala();
    masinaDepasire();
   
    glutSwapBuffers();
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid


}
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("Depasire");

	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
    glutMouseFunc(mouse);
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}