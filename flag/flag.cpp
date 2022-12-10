#include "flag.h"

Cloth cloth(15, 10, 10, 5);
void Flag::draw() {

    cloth.windForce(Vec3(0.5, 0.1, 0.2) * TIME_STEPSIZE2);
    cloth.timeStep();

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(22.52, 10, 12.955); // move camera out and center on the cloth
    glScaled(0.2, 0.2, 0.2);
    cloth.drawShaded(); // finally draw the cloth with smooth shading

    glColor3f(0.875, 0.875, 0.875);
    glutSolidSphere(0.3, 50, 50);
    GLUquadricObj *quadratic;
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.1f, 0.1f, 19.0f, 32, 32);
    glPopMatrix();
}