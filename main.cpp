#include "main.h"

std::vector<Snow> snow;
std::vector<Rain> rain;
Camera camera;

int weather = 0;

void generateObjects() {
    for (int i = 0; i <= SNOW_COUNT; i++) {
        snow.emplace_back();
    }

    for (int i = 0; i <= RAIN_COUNT; i++) {
        rain.emplace_back();
    }
}

void initDraw() {
    GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat light_position[] = {0.0, 30.0, -15.0, 0.0};
    GLfloat light_ambient[] = {0.6, 0.6, 0.6, 1.0};
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_LIGHT0, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1.333333, 0.1, 1000);

    generateObjects();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.update();
    gluLookAt(22, 0, -20, 0, 0, -14, 0, 1, 0);

    switch (weather) {
        case SNOW:
            for (auto &it: snow) {
                it.draw();
            }
            break;
        case RAIN:
            for (auto &it: rain) {
                it.draw();
            }
            break;
        default:
            break;
    }

    Building::draw();

    Flag::draw();

    glFlush();
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
    else if (key == 't' || key == 'T')
        (weather += 1) %= 2;
    else if (key == 'h' || key == 'H')
        wind_velocity_x += 0.1;
    else if (key == 'j' || key == 'J')
        wind_velocity_x -= 0.1;
    else if (key == 'k' || key == 'K')
        wind_velocity_z += 0.1;
    else if (key == 'l' || key == 'L')
        wind_velocity_z -= 0.1;
}

void specialKeyHandler(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camera.rotateUp();
    else if (key == GLUT_KEY_DOWN)
        camera.rotateDown();
    else if (key == GLUT_KEY_LEFT)
        camera.rotateLeft();
    else if (key == GLUT_KEY_RIGHT)
        camera.rotateRight();
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

    initDraw();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyHandler);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}