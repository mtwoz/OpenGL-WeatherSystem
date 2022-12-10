#include "building.h"

void Building::draw() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(25, -8, 15);
    glRotated(230, 0, 1, 0);
    glScaled(4.0f, 4.0f, 4.0f);

    // Floor
    glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(0, -0.7, 0.8);
    glScalef(0.8, 0.15, 0.8);
    glutSolidCube(1);
    glPopMatrix();

    // Wall
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(-0.3, 0.8, 0.8);
    glScalef(0.1, 3, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(0.3, 0.8, 0.8);
    glScalef(0.1, 3, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(-0.55, 0.8, 0);
    glScalef(0.1, 3, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(-1.06, 0.8, 0);
    glScalef(0.1, 3, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    //  Low roof
    glColor3f(0.55, 0.19, 0.07);
    glPushMatrix();
    glRotatef(180, 0.0, 1.0, 1.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(0.57, 0.57, 2.3);
    glScalef(0.42, 0.42, 0.35);
    glutSolidCone(1, 1, 4, 10);
    glPopMatrix();

    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
    glTranslatef(0, 2.3, 0.8);
    glScalef(0.7, 0.02, 0.7);
    glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.75, 0.75, 0.75);
    glPushMatrix();
    glTranslatef(0, 2.65, 0.8);
    glScalef(0.45, 0.5, 0.40);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
    glTranslatef(0, 2.9, 0.8);
    glScalef(0.5, 0.02, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // Pillars
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0, 3.1, 0.95);
    glScalef(0.08, 0.4, 0.08);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0.18, 3.1, 0.95);
    glScalef(0.06, 0.4, 0.06);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(-0.18, 3.1, 0.95);
    glScalef(0.06, 0.4, 0.06);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0, 3.1, 0.65);
    glScalef(0.08, 0.4, 0.08);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0.18, 3.1, 0.65);
    glScalef(0.06, 0.4, 0.06);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(-0.18, 3.1, 0.65);
    glScalef(0.06, 0.4, 0.06);
    glutSolidCube(1);
    glPopMatrix();

    // Between high roof and pillars
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0, 3.3, 0.8);
    glScalef(0.42, 0.1, 0.42);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
    glTranslatef(0, 3.35, 0.8);
    glScalef(0.5, 0.02, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // High roof
    glColor3f(0.55, 0.19, 0.07);
    glPushMatrix();
    glRotatef(180, 0.0, 1.0, 1.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(0.57, 0.57, 3.35);
    glScalef(0.35, 0.35, 0.7);
    glutSolidCone(1, 1, 4, 10);
    glPopMatrix();

    glPopMatrix();
}
