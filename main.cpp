#include <GL/glut.h>
#include "src/Globals.h"
#include "src/Renderer.h"
#include "src/Physics.h"
#include "src/Logic.h"
#include "src/KeyStates.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawSpikes();
    drawLevel();
    drawPlayer();
    glutSwapBuffers();
}

void timer(int v) {
    deltaTime = 0.016f;
    updatePhysics();
    trapPlat();

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Level Devil - Double Jump");
    glutFullScreen();
    
    gluOrtho2D(0, 160, 0, 90);
    glClearColor(0.55, 0.78, 0.75, 1.0);

    initKeys();
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyPressed);     
    glutSpecialUpFunc(specialKeyUp);        
    glutIgnoreKeyRepeat(1);

    glutDisplayFunc(display);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();

    return 0;
    
}