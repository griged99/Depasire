#include <windows.h> 
#include <gl/freeglut.h> 
#include <iostream>
#include <string> 
using namespace std;

void init(void)  
{
    glClearColor(0.000, 0.392, 0.000, 1);

	glMatrixMode(GL_PROJECTION); 
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

int carX = 200, carY = 70;//variabile pentru coordonatele masinii principale
int carsX=200, carsY=230;//variabile pentru coordonatele masinii statice
int masiniX[4], masiniY[4];//vectorii pentru coordonatele masinilor din race
int marcX = 250, macrY = 4, movd;//variabilele pentru ajutatarea la generarea masinilor de race
bool coliziune = false;//variabila pentru terminarea race-ului
int score = 0;

//functia pentru a putea avea text pe ecran
void text(string ch,int x, int y) 
{
    
    glLoadIdentity();
    glRasterPos2f(x, y);
    void* font = GLUT_BITMAP_HELVETICA_18;
    for (string::iterator  i=ch.begin(); i != ch.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

//functia de afisare pe display a numerelor, opengl nu permite afisarea cuvintelor pe ecran asa ca trebuia sa creez o functie in care mi se deseneaza
void numar(string ch, int numere, int x, int y)
{
    int l;
    int k;
    k = 0;
    glLoadIdentity();
    glRasterPos2f(x, y);
    l = numere - (int)ch.length();

    for (int i = 0; i != numere; ++i)
    {
        char c = i;
        if (i < l) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');//GLUT_BITMAP_HELVETICA_18 e fontul pe care il folosesc
        }
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }
    }
}

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
//functiile pentru soare, aici e si partea de compunere a operatiilor(rotatie+scale)

double i = 0.0;
double j = 0.0;
double alpha = 1.0;
double scale = 0.5;

void miscad(void)
{
    i = i + alpha;
    if (i > 750.0)
        alpha = -1.0;
    else if (i < 0.0)
        alpha = 1.0;
    j = j + 10;

    glutPostRedisplay();
}

int modDejoc = 0;//variabila care o folosesc pentru a schimba modurile de joc, 0 reprezinta meniul,1 depasirea si 2 race game-ul
//functia pentru a schimba modurile de joc
void controlkey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        modDejoc = 1;
        break;
    case 'r':
        modDejoc = 2;
        break;
    case 'w':
        alpha = 1.0; glutIdleFunc(miscad);
        scale = scale - 0.2;
        break;
    case 's':
        alpha = 1.0; glutIdleFunc(miscad);
        scale = scale + 0.2;
        break;
    case 27:exit(0);
    }
}

void raze(GLfloat x, GLfloat y) {
    
    glPushMatrix();
    glLoadIdentity();
    glTranslated(250, 375, 0);
    glScalef(scale, scale, 0);
    glRotated(j, 0, 0, 1);
    glTranslated(-250, -375, 0);

    GLfloat distanta = y + 70;
    //triunghiul de sus

    glBegin(GL_TRIANGLES);

    glColor3f(1, 1, 0);

    glVertex2f(x-20 , distanta);
    glVertex2f(x + 20, distanta );
    glVertex2f(x , distanta + 35.0);

    glEnd();

    

    //triunghiul de jos
    distanta = y - 70;
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);

    glVertex2f(x - 20, distanta);
    glVertex2f(x + 20, distanta);
    glVertex2f(x, distanta - 35.0);

    glEnd();

    //triunghiul din dreapta
    distanta = x + 70;
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);

    glVertex2f(distanta, y-20);
    glVertex2f(distanta, y+20);
    glVertex2f(distanta +35, y);

    glEnd();

    //triunghiul din stanga
    distanta = x - 70;
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);

    glVertex2f(distanta, y - 20);
    glVertex2f(distanta, y + 20);
    glVertex2f(distanta - 35, y);
    glEnd();


    glPopMatrix();
    
    glFlush();
}



void soare(GLfloat x, GLfloat y, GLfloat raza) {
    float i;
    int numarDeTriunghiuri = 25; //numarul de triunghiuri folosit ptr a creea cercul

    double doiPi = 2.0 * 3.142;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 0);
    glVertex2f(x, y);
    for (i = 0; i <= numarDeTriunghiuri; i++) {
        //glColor3f(1, 1, 0);
        glVertex2f(
            x + (raza * cos(i * doiPi / numarDeTriunghiuri)),
            y + (raza * sin(i * doiPi / numarDeTriunghiuri))
        );
        
    }
    glEnd();



    glFlush();
    //

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

//functia pentru marcajul central care in modul de race se va genera incontinuu
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

//functia pentru a putea schimba random asezarea masinilor din race game pe sosea
void random(void)
{
    glClearColor(0, 0, 1, 0);
    for (int i = 0; i < 4; i++)
    {
        if (rand() % 2 == 0)
        {
            masiniX[i] = 200;
        }
        else
        {
            masiniX[i] = 300;
        }
        masiniY[i] = 1000 - i * 160;
    }
}

//functia pentru creea masinilor pentru partea de minigame
void masiniRace(void)
{
    for (int i = 0; i < 3; i++)
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
            coliziune = true;
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
//masina face depasirea in sus
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
//functia pentru modul depasire in care masina principala revine la modul initial
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

//ne permite sa miscam masina principala masina principala
void raceKey(int key,int x,int y)
{
    switch (key)
    {
    case GLUT_KEY_UP://incetineste rularea masinilor 
        for (int i = 0; i < 4; i++)
        {
            masiniY[i] = masiniY[i] - 10;
        }
        movd = movd - 20;
    case GLUT_KEY_DOWN://creste viteza de generare a masinilor
        for (int i = 0; i < 4; i++)
        {
            masiniY[i] = masiniY[i] + 10;
        }
        movd = movd + 20;
        break;
    case GLUT_KEY_LEFT: //masina principala se misca la stanga
        carX = 200;
        break;
    case GLUT_KEY_RIGHT://masina principala se misca la stanga
        carX = 300;
        break;
    }
}

void depasire(void) {

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

}

//functia pentru race game
void race(void)
{
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

    
    drum();
    marcaj();
    masinaPrincipala();
    masiniRace();

    movd = movd - 16;
    if (movd < -60)
    {
        movd = 0;
    }
    

    glColor3f(1, 1, 1);
    text("Score:", 360, 455);
    numar(to_string(score), 6, 420, 455);//transform un intreg intr un string pentru a putea afisa numarul pe ectan
    for (int incetinire = 0; incetinire <= 10000000; incetinire++) { ; }//pentru a ingreuna procesul de afisarea a masinilor
    if (coliziune == true)
    {
        glColor3f(0, 0, 0);
        text("Game Over", 360, 420);
        //getchar();//ar trebui sa mi opreasca masinile, dar nu merge asa cum as vrea
    }
    else {
        score = score + 1;//scorul va creste cat timp masina principala nu a atins alta masina
    }
}

//Functia pentru controlul masini din mouse
void mouse1(int button, int state, int x, int y)
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


//meniul se va afisa la inceput de rulare a programului, apoi va disparea
void meniu(void) {
    text("Car Project", 150, 250);
    text("Pentru modul de depasire trebuie apasata tasta D", 100, 200);
    text("Pentru modul de game trebuie apasata tasta R", 100, 180);

    text("In modul de depasire",0,80);
    text("pentru ca masina sa poate",0,65);
    text("face depasire in sus",0,50);
    text("trebuie apasat pe click dreapta",0,35);
    text("iar pentru depasire in jos",0,20);
    text("trebuie apasat pe click stanga", 0, 5);

    text("in modul game",380,80);
    text("masina se controleaza",380,65);
    text("din sageti left and right",380,50);
    text("si se vor genera masini",380,35);
    text("de care trebuie" ,380,20);
    text("sa te feresti",380,5);

    text("Pentru a roti razele",0,470);
    text("si a le micsora apasa W",0,450);
    text("iar pentru a le mari ",0,430);
    text("apasa S",0,410);

    soare(250,375,50);
    raze(250.0, 375.0);
    carX = 250;
    masinaPrincipala();
}
 
void desen(void) // procedura desenare  
{
    glClear(GL_COLOR_BUFFER_BIT);
     
    switch (modDejoc)
    {
    case 0:
        meniu();
        break;
    case 1:
        depasire();
        break;
    case 2:
        race();
    default:
        break;
    }
    
    
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

    random();
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
    glutKeyboardFunc(controlkey);
    glutMouseFunc(mouse1);    
    glutSpecialFunc(raceKey);
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
    
}