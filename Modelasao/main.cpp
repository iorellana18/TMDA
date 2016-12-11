#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <math.h>
#include <iostream>
#include <random>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
using namespace std;
float traslacion_tierra = 0.0;
float rotacion_tierra = 0.0;
float traslacion_luna = 0.0;
float rotacion_luna = 0.0;
float G=6.674*pow(10,-11);
float numAst = 0;

bool modo_rotacion = true; // Por defecto
bool modo_traslacion = true;

static void resize(int width, int height)
{
const float ar = (float) width / (float) height;

glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho (-6.4,6.4,-4.8,4.8, 1.0, -1.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity() ;
}

static void display(void)
{


glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glColor3d(1,0,0);

const float dist_tierra_sol = 4.0;
const float dist_tierra_luna = 1.5;

// SOL
glColor3f (1.0, 1.0, 0.0);
glutSolidSphere(1,25,25);

for(int i=0;i<numAst;i++){
    
    glPushMatrix();
    glTranslatef (i*cos(traslacion_tierra),i*sin(traslacion_tierra),0);
    glRotatef(rotacion_tierra,0,0,1.0);
    glColor3f(0.0,0.0,1.0);
    glutSolidSphere(0.01,20,20);
    glPopMatrix();
}
/*

glPushMatrix();
glTranslatef (dist_tierra_sol*cos(traslacion_tierra),dist_tierra_sol*sin(traslacion_tierra),0);
glTranslatef (dist_tierra_luna*cos(traslacion_luna),dist_tierra_luna*sin(traslacion_luna),0);
glRotatef(rotacion_luna,0,0,1.0);
glColor3f(0.5,0.5,0.5);
glutSolidSphere(0.1,20,20);
glPopMatrix();
*/
glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
switch (key)
{
case 27 :
case 'q':
exit(0);
break;
case 'r':
modo_rotacion=true;
modo_traslacion=false;
break;
case 't':
modo_rotacion = false;
modo_traslacion=true;
break;
case 'n':
modo_rotacion = true;
modo_traslacion=true;
break;
}

glutPostRedisplay();
}

static void idle(void)
{
glutPostRedisplay();
}

static void timer(int x)
{
if (modo_traslacion) traslacion_tierra += 0.02;
if (traslacion_tierra>360.0) traslacion_tierra = traslacion_tierra - 360.0;
if (modo_rotacion) rotacion_tierra += 10.0;
if (rotacion_tierra>360.0) rotacion_tierra = rotacion_tierra - 360.0;
if (modo_rotacion) traslacion_luna += 0.05;
if (traslacion_luna>360.0) traslacion_luna = traslacion_luna - 360.0;
if (modo_rotacion) rotacion_luna += 5.0;
if (rotacion_luna>360.0) rotacion_luna = rotacion_luna - 360.0;

glutTimerFunc(25, timer,0);
}

/* Program entry point */

int main(int argc, char *argv[])
{

//////////////////
     ///Parámetros
  int burnin = 0; // burn-in iterations -> iteraciones previas para evitar mal punto de partida
  int lag = 1; // lag entre muestreo -> para distribuciones con baja tasa de aceptación
  int samples = 1000; // numero de muestras
  int sd; // desviación estándar
  double x = -1; // punto de partida
  char *ruta;
  //Variables getopt
  int c;
  int index;

    while ((c = getopt (argc, argv, "p:a:")) != -1)
    switch (c)
      {
      case 'p':
        ruta = optarg;
        break;
      case 'a':
        numAst=atoi(optarg);
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Opción incorrecta`-%c'.\n", optopt);
        else
          fprintf (stderr,"Opción desconocida `\\x%x'.\n",optopt);
        return 1;
          default:
            abort ();
      }


  for (index = optind; index < argc; index++)
    printf ("Argumento inválido %s\n", argv[index]);
/////////////


glutInit(&argc, argv);
glutInitWindowSize(2560,1600);
glutInitWindowPosition(0,0);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

glutCreateWindow("Hola Robin");
glutReshapeFunc(resize);
glutDisplayFunc(display);
glutKeyboardFunc(key);
glutIdleFunc(idle);
glutTimerFunc(25, timer,0);

glClearColor(0,0,0,1);

glEnable(GL_DEPTH_TEST);

glutMainLoop();

return
EXIT_SUCCESS;
} 