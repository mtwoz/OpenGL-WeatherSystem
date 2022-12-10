#include "ground.h"

void Ground::drawGrass() {
    /*
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 11; j++) {
            glPushMatrix();
            glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
            glTranslatef((float) (j * 4), -10, (float) (i * 4));
            glRotated(90, 1, 0, 0);

            glBegin(GL_QUADS);
            glTexCoord2i(0, 0);
            glVertex2i(0, 0);
            glTexCoord2i(0, 1);
            glVertex2i(0, 4);
            glTexCoord2i(1, 1);
            glVertex2i(4, 4);
            glTexCoord2i(1, 0);
            glVertex2i(4, 0);
            glEnd();
            glLoadIdentity();
            glPopMatrix();
        }
    }
     */
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            glColor3fv(g_colors[i][j]);
            glVertex3f(g_points[j][i][0],
                       g_points[j][i][1],
                       g_points[j][i][2]);
            glColor3fv(g_colors[i][j]);
            glVertex3f(g_points[j][i][0],
                       g_points[j][i][1],
                       g_points[j][i][2]);
            glColor3fv(g_colors[i][j]);
            glVertex3f(g_points[j][i][0],
                       g_points[j][i][1],
                       g_points[j][i][2]);
            glColor3fv(g_colors[i][j]);
            glVertex3f(g_points[j][i][0],
                       g_points[j][i][1],
                       g_points[j][i][2]);
        }

    }
}

void Ground::drawRunway() {
    float radius = 22;
    float twoPI = 2 * M_PI;

    glPushMatrix();
    glColor3f(0.0 / 255.0, 0.0 / 255.0, 255.0 / 255.0);
    glTranslatef(0, -6.8, 14);
    glRotated(90, 1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (float i = M_PI; i <= twoPI; i += 0.001)
        glVertex2f((sinf(i) * radius), (cosf(i) * radius));
    glEnd();
    glLoadIdentity();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0 / 255.0, 0.0 / 255.0, 255.0 / 255.0);
    glTranslatef(44, -6.8, 14);
    glRotated(90, 1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (float i = 0.0; i <= M_PI; i += 0.001)
        glVertex2f((sinf(i) * radius), (cosf(i) * radius));
    glEnd();
    glLoadIdentity();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0 / 255.0, 0.0 / 255.0, 255.0 / 255.0);
    glTranslatef(0, -6.8, 8);
    glRotated(90, 1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, -16);
    glTexCoord2i(0, 1);
    glVertex2i(0, 28);
    glTexCoord2i(1, 1);
    glVertex2i(44, 28);
    glTexCoord2i(1, 0);
    glVertex2i(44, -16);
    glEnd();
    glLoadIdentity();
    glPopMatrix();

    glFlush();
}
