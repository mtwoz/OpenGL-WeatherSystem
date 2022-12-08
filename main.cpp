#include "main.h"

std::vector<Snow> snow = {};
Camera camera;

std::vector<char> singleRow;
std::vector<std::vector<char>> listOfRows;

Point mouse_pointer = {0, 0};
uint textureGrass;

GLuint loadBMP(const char *fileName) {
    FILE *file;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int size;
    unsigned int width, height;
    unsigned char *data;


    file = fopen(fileName, "rb");

    if (file == NULL) {
        std::cout << "Invalid file 1" << std::endl;
        return false;
    }

    if (fread(header, 1, 54, file) != 54) {
        std::cout << "Invalid file 2" << std::endl;
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Invalid file 3" << std::endl;
        return false;
    }

    dataPos = *(int *) &(header[0x0A]);
    size = *(int *) &(header[0x22]);
    width = *(int *) &(header[0x12]);
    height = *(int *) &(header[0x16]);

    if (size == 0)
        size = width * height * 3;
    if (dataPos == 0)
        dataPos = 54;

    data = new unsigned char[size];

    fread(data, 1, size, file);

    fclose(file);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    return texture;
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
}

void generateObjects() {
    for (int i = 0; i <= SNOW_COUNT; i++) {
        snow.emplace_back();
    }
}

void generateMap() {
    std::ifstream ifs("../map.txt");
    std::string line;

    while (getline(ifs, line)) {
        singleRow.clear();
        for (char &i: line) {
            singleRow.push_back(i);
        }
        listOfRows.push_back(singleRow);
    }
}

void drawMap() {
    float gameZ = 0;
    float gameX = 0;
    // Enable and load textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    textureGrass = loadBMP("../grass.bmp");
    for (size_t i = 0; i < listOfRows.size(); i++) {
        for (size_t j = 0; j < 16; j++) {
            switch (listOfRows[i][j]) {
                // Grass
                case '0':
                    glPushMatrix();
                    glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -6.8, (static_cast<int>(i) * 4));
                    glScalef(1, .15, 1);
                    glRotated(90, 1, 0, 0);

                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 0);
                    glVertex2i(-2, -2);
                    glTexCoord2i(0, 1);
                    glVertex2i(-2, 2);
                    glTexCoord2i(1, 1);
                    glVertex2i(2, 2);
                    glTexCoord2i(1, 0);
                    glVertex2i(2, -2);
                    glEnd();

                    glPopMatrix();
                    break;
                    // Tree - large
                case '1':

                    glPushMatrix();
                    glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -6.8, (static_cast<int>(i) * 4));
                    glScalef(1, .15, 1);
                    glRotated(90, 1, 0, 0);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 0);
                    glVertex2i(-2, -2);
                    glTexCoord2i(0, 1);
                    glVertex2i(-2, 2);
                    glTexCoord2i(1, 1);
                    glVertex2i(2, 2);
                    glTexCoord2i(1, 0);
                    glVertex2i(2, -2);
                    glEnd();
                    glPopMatrix();

                    glPushMatrix();
                    glColor3f(142.0 / 255.0, 84.0 / 255.0, 80.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -5, (static_cast<int>(i) * 4));
                    glScalef(1, 1, 1);
                    glutSolidCube(2);
                    glPopMatrix();

                    glPushMatrix();
                    glColor4f(183.0 / 255.0, 214.0 / 255.0, 33.0 / 255.0, 1.0f);
                    glTranslatef((static_cast<int>(j) * 4), -1.8, (static_cast<int>(i) * 4));
                    glScalef(.7, 1.25, .7);
                    glutSolidCube(4);
                    glPopMatrix();

                    break;

                    // Road
                case '2':
                    glPushMatrix();
                    glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -7, (static_cast<int>(i) * 4));
                    glScalef(1, 0, 1);
                    glutSolidCube(4);
                    glPopMatrix();

                    glPushMatrix();
                    glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -7, (static_cast<int>(i) * 4));
                    glScalef(.5, .1, .08);
                    glutSolidCube(4);
                    glPopMatrix();
                    break;

                    // Water
                case '3':
                    glPushMatrix();
                    glColor3f(128.0 / 255.0, 245.0 / 255.0, 255.0 / 255.0);
                    glTranslatef((static_cast<int>(j) * 4), -7, (static_cast<int>(i) * 4));
                    glScalef(1, 0, 1);
                    glutSolidCube(4);
                    glPopMatrix();

                    break;

            }
        }
    }

}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.update();
    gluLookAt(0, 0, -10, -10, 0, 0, 0, 1, 0);

    drawMap();

    for (auto &it: snow) {
        it.draw();
    }

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

void passiveMotionHandler(int x, int y) {
    camera.m_lon = (float) ((WIDTH / 2.0) - x) * 100 / WIDTH;
    camera.m_lat = (float) ((HEIGHT / 2.0) - y) * 100 / HEIGHT;
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

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardHandler);
    glutReshapeFunc(reshape);
//    glutPassiveMotionFunc(passiveMotionHandler);
    glutTimerFunc(1000 / 60, timerHandler, 0);
    glutIdleFunc(idle);

    initDraw();
    generateObjects();
    generateMap();

    glutMainLoop();
    return 0;
}