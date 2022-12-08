#include "main.h"

std::vector<Snow> snow = {};
Camera camera;

Point mouse_pointer = {0, 0};

void generateObjects() {
    for (int i = 0; i <= SNOW_COUNT; i++) {
        snow.emplace_back();
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.update();

    for (auto &it: snow) {
        it.draw();
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    // avoid division by zero
    if (h == 0) h = 1;

    // set viewport
    glViewport(0, 0, w, h);

    // set coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) w / (float) h, 0.1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timerHandler(int value) {
    // update snow
    for (auto &it: snow) {
        it.update();
    }

    // let OpenGL to redraw the current window
    glutPostRedisplay();

    // enter the loop
    glutTimerFunc(1000 / 60, timerHandler, value + 1000 / 60);
}

void keyboardHandler(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q')
        exit(0);
    else if (key == 'w' || key == 'W')
        camera.moveForward();
    else if (key == 's' || key == 'S')
        camera.moveBackward();
    else if (key == 'a' || key == 'A')
        camera.moveLeft();
    else if (key == 'd' || key == 'D')
        camera.moveRight();
    else if (key == 'z' || key == 'Z')
        camera.moveUp();
    else if (key == 'x' || key == 'X')
        camera.moveDown();
}

void mouseHandler(int button, int state, int x, int y) {

}

void passiveMotionHandler(int x, int y) {
//    mouse_pointer.x = (float) x / (float) glutGet(GLUT_WINDOW_WIDTH) * WIDTH;
//    mouse_pointer.y = (float) y / (float) glutGet(GLUT_WINDOW_HEIGHT) * HEIGHT;
    camera.rotate(x, y);
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
    glutCreateWindow("Weather System");
    glutSetCursor(GLUT_CURSOR_NONE);

    generateObjects();

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glutKeyboardFunc(keyboardHandler);
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawScene);
//    glutMouseFunc(mouseHandler);
//    glutPassiveMotionFunc(passiveMotionHandler);

    glutTimerFunc(1000 / 60, timerHandler, 0);

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}