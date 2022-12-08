#include "main.h"

std::vector<Snow> snow = {};
Camera camera;

std::vector<char> singleRow;
std::vector<std::vector<char>> listOfRows;

Point mouse_pointer = {0, 0};
uint texture[2];

std::vector<GLubyte *> p;

void ReadImage(const char path[256], GLint &image_w, GLint &image_h, GLint &pixel_l) {
    GLubyte *pixeldata;
    FILE *p_file;
    p_file = fopen(path, "rb");
    if (p_file == nullptr) exit(0);
    fseek(p_file, 0x0012, SEEK_SET);
    fread(&image_w, sizeof(image_w), 1, p_file);
    fread(&image_h, sizeof(image_h), 1, p_file);
    pixel_l = image_w * 3;
    while (pixel_l % 4 != 0)pixel_l++;
    pixel_l *= image_h;
    pixeldata = (GLubyte *) malloc(pixel_l);
    if (pixeldata == nullptr) exit(0);
    fseek(p_file, 54, SEEK_SET);
    fread(pixeldata, pixel_l, 1, p_file);
    p.push_back(pixeldata); // Similar to glDrawPixels for program 3
    fclose(p_file);
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

    int image_width, image_height, pixel_length;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);
    ReadImage("../grass.bmp", image_width, image_height, pixel_length);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // set pixel storage modes (in the memory)
    glGenTextures(1, &texture[0]); // number of texture names to be generated and an array of texture names
    glBindTexture(GL_TEXTURE_2D, texture[0]); // target to which texture is bound and name of a texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image_width, image_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

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
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            glPushMatrix();
            glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
            glTranslatef((float) (j * 4), -6.8, (float) (i * 4));
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
            glLoadIdentity();
            glPopMatrix();
        }
    }
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.update();
    gluLookAt(0, 0, -10, -10, 0, 0, 0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    drawMap();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
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

    initDraw();
    generateObjects();
//    generateMap();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(keyboardHandler);
    glutReshapeFunc(reshape);
//    glutPassiveMotionFunc(passiveMotionHandler);
    glutTimerFunc(1000 / 60, timerHandler, 0);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}