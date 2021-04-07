#include <windows.h> 
#include <gl/freeglut.h> 
#include <iostream>
using namespace std;

void init(void)  
{
    glClearColor(0.000, 0.392, 0.000, 1);

	glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); 
    glMatrixMode(GL_MODELVIEW);
}

int carX = 200, carY = 70;//variabile pentru coordonatele masinii principale
int carsX=200, carsY=230;//variabile pentru coordonatele masinii statice
int masiniX[4], masiniY[4];//vectorii pentru coordonatele masinilor din race
int marcX = 250, macrY = 4, movd;//variabilele pentru ajutatarea la generarea masinilor de race
bool collide = false;//variabila pentru terminarea race-ului

//functia pentru generarea copaciilor
void tree(int x, int y) {
    int x1 = x;
    int y1 = y;
    //tulpina
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1 + 110, y1 + 250);
    glVertex2f(x1 + 120, y1 + 250 - 100);
    glVertex2f(x1 + 100, y1 + 250 - 100);
    glEnd();
    //coroana
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1 + 110, y1 + 250 + 3);
    glVertex2f(x1 + 120 + 30, y1 + 250 - 30);
    glVertex2f(x1 + 100 - 30, y1 + 250 - 30);
    glEnd();
    glFlush();
}

//functiile pentru generarea drumului si a marcajului central
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
    glLoadIdentity();
    glTranslatef(0, movd, 0);
    for (int i = 1; i <= 10; i++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(marcX - 5, macrY * 15 * i + 18);
        glVertex2f(marcX - 5, macrY * 15 * i - 18);
        glVertex2f(marcX + 5, macrY * 15 * i - 18);
        glVertex2f(marcX + 5, macrY * 15 * i + 18);
        glEnd();
    }
    glLoadIdentity();
    glFlush();
}

//funtia pentru generarea masinii principale
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

//fuctia pentru generarea masinii statitce pentru partea de depasire
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
    glBegin(GL_POLYGON);
    glColor3f(0.99609, 0.83984, 0);
    glVertex2f(carsX - 25, carsY + 20);
    glVertex2f(carsX - 25, carsY - 20);
    glVertex2f(carsX + 25, carsY - 20);
    glVertex2f(carsX + 25, carsY + 20);
    glEnd();

    //partea de sus a masinii
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex2f(carsX - 23, carsY + 20);
    glVertex2f(carsX - 19, carsY + 40);
    glVertex2f(carsX + 19, carsY + 40);
    glVertex2f(carsX + 23, carsY + 20);
    glEnd();
    //partea de jos a masinii
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex2f(carsX - 23, carsY - 20);
    glVertex2f(carsX - 19, carsY - 35);
    glVertex2f(carsX + 19, carsY - 35);
    glVertex2f(carsX + 23, carsY - 20);
    glEnd();
    glFlush();
}
//functia pentru creea masinilor pentru partea de minigame
void masiniRace(void)
{
    for (int i = 0; i < 4; i++)
    {
        //roti
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glColor3f(0, 0, 0);
        glVertex2f(masiniX[i] - 25, masiniY[i] + 16);
        glVertex2f(masiniX[i] + 25, masiniY[i] + 16);
        glVertex2f(masiniX[i] - 25, masiniY[i] - 16);
        glVertex2f(masiniX[i] + 25, masiniY[i] - 16);
        glEnd();

        //partea de mijloc
        glBegin(GL_POLYGON);
        glColor3f(0.99609, 0.83984, 0);
        glVertex2f(masiniX[i] - 25, masiniY[i] + 20);
        glVertex2f(masiniX[i] - 25, masiniY[i] - 20);
        glVertex2f(masiniX[i] + 25, masiniY[i] - 20);
        glVertex2f(masiniX[i] + 25, masiniY[i] + 20);
        glEnd();

        //partea de sus
        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);
        glVertex2f(masiniX[i] - 23, masiniY[i] + 20);
        glVertex2f(masiniX[i] - 19, masiniY[i] + 40);
        glVertex2f(masiniX[i] + 19, masiniY[i] + 40);
        glVertex2f(masiniX[i] + 23, masiniY[i] + 20);
        glEnd();

        //partea de jos
        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);
        glVertex2f(masiniX[i] - 23, masiniY[i] - 20);
        glVertex2f(masiniX[i] - 19, masiniY[i] - 35);
        glVertex2f(masiniX[i] + 19, masiniY[i] - 35);
        glVertex2f(masiniX[i] + 23, masiniY[i] - 20);
        glEnd();

        masiniY[i] = masiniY[i] - 8;
        if (masiniY[i] > carY - 25 - 25 && masiniY[i] < carY + 25 + 25 && masiniX[i] == carX)
        {
            collide = true;
        }

        if (masiniY[i] < -25)
        {
            if (rand() % 2 == 0)
            {
                masiniX[i] = 200;
            }
            else
            {
                masiniX[i] = 300;
            }
            masiniY[i] = 600;
        }
    }
    
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

void depasire(void) {

    //apelarea merodelor ptr drum si masini
    drum();
    marcaj();
    masinaPrincipala();
    masinaDepasire();

}

void race(void)
{
    drum();
    marcaj();
    masinaPrincipala();
    masiniRace();
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

    depasire();
   
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