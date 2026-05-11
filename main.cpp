#include <GL/glut.h>
#include "src/common/Constants.h"
#include "src/common/Structs.h"
#include "src/core/GameManager.h"
#include "src/core/InputHandler.h"
#include "src/physics/PhysicsEngine.h"
#include "src/game/GameLogic.h"
#include "src/graphics/Renderer.h"

void gameLoop() {
    updatePhysics();
    updateTrapPlatforms();
    updateSpikes();
    checkGoalReached();
    renderScene();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Level Devil - Double Jump");
    glutFullScreen();

    gluOrtho2D(0, 160, 0, 90);
    glClearColor(0.55, 0.78, 0.75, 1.0);

    loadLevel(1);
    initInput();

    glutKeyboardFunc(onKeyPressed);
    glutKeyboardUpFunc(onKeyReleased);
    glutSpecialFunc(onSpecialKeyPressed);
    glutSpecialUpFunc(onSpecialKeyReleased);
    glutIgnoreKeyRepeat(1);

    glutDisplayFunc(renderScene);
    glutIdleFunc(gameLoop);
    glutMainLoop();

    return 0;
}