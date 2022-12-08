#include "main.h"

std::vector<Snow> snow = {};

float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;

void generateObjects() {
    // generate all snow
    for (int i = 0; i <= SNOW_COUNT; i++) {
        snow.emplace_back();
    }
}

void drawScene() {
    int i, j;
    float x, y, z;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glRotatef(pan, 0.0, 1.0, 0.0);
    glRotatef(tilt, 1.0, 0.0, 0.0);

    // draw snow
    for (auto &it: snow) {
        it.draw();
    }

    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

void motionHandler(int x, int y) {}

void keyboardHandler(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q')   // quit the program
        exit(0);
    else if (key == 'w' || key == 'W') {
        zoom += 1.0;
    } else if (key == 's' || key == 'S') {
        zoom -= 1.0;
    } else if (key == 'd' || key == 'D') {
        pan += 1.0;
    } else if (key == 'a' || key == 'A') {
        pan -= 1.0;
    } else if (key == 'r' || key == 'R') {
        tilt -= 1.0;
    } else if (key == 't' || key == 'T') {
        tilt += 1.0;
    }

    glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
    glutCreateWindow("Weather System");
    glutSetCursor(GLUT_CURSOR_NONE);

    generateObjects();

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glutMouseFunc(mouseHandler);
    glutKeyboardFunc(keyboardHandler);
    glutMotionFunc(motionHandler);
    glutPassiveMotionFunc(motionHandler);
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawScene);

    glutTimerFunc(1000 / 60, timerHandler, 0);

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}