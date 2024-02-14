#include <GL/glut.h>
#include <math.h>
GLfloat rotation = 90.0;
float posX = 0, posY = 0, posZ = 0;
float move_unit = 3;
float rate = 1.0f;
float angle = -0.0f;
float RotateX = 0.f, RotateY = 45.f;

float pos = 0, x = 0, col = 0, i, p, c, cf = 0, pr, pl = 0;
int screen = 0;

void putPixel(int x, int y, float r, float g, float b)
{
    glColor3f(0.5 + col, 0.3 + col, 0.2 + col);
    glPointSize(10.0f);
    glVertex2i(x, y);
}
void dda2(int x0, int y0, int xn, int yn)
{
    int dx = xn - x0;
    int dy = yn - y0;

    int step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float initial_pointX = (float)x0;
    float initial_pointY = (float)y0;
    glBegin(GL_POINTS);

    for (int i = 0; i <= step; i++)
    {
        // glVertex2i((int)x, (int)y);
        putPixel((int)initial_pointX, (int)initial_pointY, 1, 1, 1);
        initial_pointX += dx / step;
        initial_pointY += dy / step;
    }

    glEnd();
    glFlush();
}
void bresenHamCircle(int xc, int yc, int radius)
{
    int x = 0;
    int y = radius;
    int pk = 3 - 2 * radius;

    glBegin(GL_POINTS);
    glColor3f(0.97 + col, 0.68 + col, 0.13 + col);

    while (x <= y)
    {
        putPixel(xc + x, yc + y, 1, 0, 0);
        putPixel(xc + x, yc - y, 1, 0, 0);
        putPixel(xc - x, yc + y, 1, 0, 0);
        putPixel(xc - x, yc - y, 1, 0, 0);

        putPixel(xc + y, yc + x, 1, 0, 0);
        putPixel(xc - y, yc + x, 1, 0, 0);
        putPixel(xc + y, yc - x, 1, 0, 0);
        putPixel(xc - y, yc - x, 1, 0, 0);

        if (pk < 0)
        {
            pk = pk + 4 * x + 6;
        }
        else
        {
            pk = pk + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    glEnd();
}
void drawArc(float sa, float ea, float cx, float cy, float rd)
{
    float PI = 3.14;
    float step = 1.0;
    float angle, x = 0, y = 0, centerX = cx, centerY = cy, radius = rd;

    glBegin(GL_POLYGON);
    for (angle = sa; angle < ea; angle += step)
    {
        float rad;
        rad = PI * angle / 180;
        x = centerX + radius * cos(rad);
        y = centerY + radius * sin(rad);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
void drawElipse()
{

    glColor3f(1.0, 1.0, 1.0); // White color for the window frame
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int angle = 0; angle <= 360; angle += 5)
    {
        float x = 335 + 15 * cos(angle * 3.14159 / 180);
        float y = 180 + 8 * sin(angle * 3.14159 / 180);
        glVertex2f(x, y);
    }
    glEnd();
}
void drawArc2(float sa, float ea, float cx, float cy, float rd)
{ // moon drawing
    float PI = 3.14;
    float step = 1.0;
    float angle, x = 0, y = 0, centerX = cx, centerY = cy, radius = rd;

    glBegin(GL_POLYGON);
    for (angle = sa; angle < ea; angle += step)
    {
        float rad;
        rad = PI * angle / 180;
        x = centerX + radius * cos(rad);
        y = centerY + radius * sin(rad);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
void drawCircle(int x1, int y1, int radius)
{
    float x2, y2;
    float angle;
    glBegin(GL_POLYGON);
    for (angle = .1f; angle < 361.0f; angle += 1.0f)

    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }

    glEnd();
}
void midpointCircle(int xc, int yc, int radius)
{
    int x = 0;
    int y = radius;
    int pk = 1 - radius;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);

    while (x <= y)
    {
        putPixel(xc + x, yc + y, 1, 0, 0);
        putPixel(xc + x, yc - y, 1, 0, 0);
        putPixel(xc - x, yc + y, 1, 0, 0);
        putPixel(xc - x, yc - y, 1, 0, 0);

        putPixel(xc + y, yc + x, 1, 0, 0);
        putPixel(xc - y, yc + x, 1, 0, 0);
        putPixel(xc + y, yc - x, 1, 0, 0);
        putPixel(xc - y, yc - x, 1, 0, 0);

        if (pk < 0)
        {
            pk = pk + 2 * x + 3;
        }
        else
        {
            pk = pk + 2 * (x - y) + 5;
            y--;
        }
        x++;
    }

    glEnd();
}
void smoke(int m, int n)
{ // smoke for kushna
    for (c = p = 0; c < 31; c += 10, p -= 1)
    {
        glColor3f(0.5, 0.5, 0.5);
        drawArc2(0, 360, m + c, n, 10 + p);
    }
}
void ground()
{
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.34, 0.12);
    glVertex2f(00, 00);
    glVertex2f(00, 350);
    glVertex2f(1500, 350);
    glVertex2f(1500, 00);
    glEnd();
}
void mountain()
{
    glColor3f(0.4 + col, 0.2 + col, 0.0 + col);
    glBegin(GL_POLYGON);
    glVertex2f(-20, 200);
    glVertex2f(200, 200);
    glVertex2f(30, 500);
    glEnd();
    glColor3f(0.99, 0.99, 0.98);
    glBegin(GL_POLYGON);
    glVertex2f(0, 200);
    glVertex2f(390, 200);
    glVertex2f(200, 600);
    glEnd();
    glColor3f(0.4 + col, 0.2 + col, 0.0 + col);
    glBegin(GL_POLYGON);
    glVertex2f(0, 200);
    glVertex2f(390, 200);
    glVertex2f(270, 450);
    glVertex2f(220, 400);
    glVertex2f(200, 460);
    glVertex2f(140, 500);
    glEnd();
    glColor3f(0.4 + col, 0.2 + col, 0.0 + col);
    glBegin(GL_POLYGON);
    glVertex2f(200, 200);
    glVertex2f(580, 200);
    glVertex2f(450, 600);
    glEnd();
    glColor3f(0.4 + col, 0.2 + col, 0.0 + col);
    glBegin(GL_POLYGON);
    glVertex2f(350, 200);
    glVertex2f(650, 200);
    glVertex2f(500, 500);
    glEnd();
}
void river()
{
    glBegin(GL_POLYGON);
    glColor3f(0.03, 0.33, 0.71);
    glVertex2f(00, 00);
    glVertex2f(00, 50);
    glVertex2f(1500, 50);
    glVertex2f(1500, 00);
    glEnd();
}
void chisMawcha()
{

    glColor3f(0.48 + col, 0.27 + col, 0.44 + col);
    glBegin(GL_POLYGON);
    glVertex2f(350, 250);
    glVertex2f(350, 330);
    glVertex2f(330, 330);
    glColor3f(0.0 + col, 0.0 + col, 0.0 + col);
    glVertex2f(330, 270);
    glEnd();
    smoke(330, 330);
}
void mesob()
{

    glColor3f(0.5 + col, 0.3 + col, 0.2 + col); // Brown color for the base
    glBegin(GL_POLYGON);
    glVertex2f(470, 100);
    glVertex2f(530, 100);
    glVertex2f(510, 135);
    glVertex2f(490, 135);

    glEnd();
    glColor3f(0.5 + col, 0.3 + col, 0.2 + col); // Brown color for the base
    glBegin(GL_POLYGON);
    glVertex2f(470, 135);
    glVertex2f(530, 135);
    glVertex2f(530, 140);
    glVertex2f(470, 140);
    glEnd();
    glColor3f(0.5 + col, 0.3 + col, 0.2 + col); // Brown color for the base
    glBegin(GL_POLYGON);
    glVertex2f(470, 140);
    glVertex2f(530, 140);
    glVertex2f(500, 160);
    glEnd();
    for (int a = 7; a > 0; a = a - 1)
    {
        bresenHamCircle(500, 160, a);
    }
}
void drawFence(int a, int b)
{
    glColor3f(0.4, 0.2, 0.0);  // Brown color for the fence
    int fencePostSpacing = 15; // Adjust spacing as needed
    for (int i = a; i <= b; i += fencePostSpacing)
    {
        // Draw vertical posts
        glBegin(GL_POLYGON);
        glVertex2f(i, 70);
        glVertex2f(i + 5, 70);
        glVertex2f(i + 5, 140);
        glVertex2f(i, 140);
        glEnd();
        // Draw horizontal rails
        if (i > 100)
        {
            glBegin(GL_LINES);
            glVertex2f(i, 120);
            glVertex2f(i - fencePostSpacing, 120);
            glEnd();
        }
    }
}
void stand()
{
    // windmill stand
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.43, 0.314);
    glVertex2i(106, 298);
    glVertex2i(199, 296);
    glVertex2i(160, 420);
    glVertex2i(140, 420);
    glEnd();
    glFlush();
}
void windmill()
{

    // left 1st wing
    glBegin(GL_QUADS);
    glColor3f(0.69, 0.67, 0.57);
    glVertex2i(200, 400);
    glVertex2i(180, 450);
    glVertex2i(20, 570);
    glVertex2i(40, 520);
    // glEnd();
    glFlush();
    // 2nd wing
    glColor3f(0.69, 0.67, 0.57);
    glVertex2i(0, 400);
    glVertex2i(190, 520);
    glVertex2i(210, 570);
    glVertex2i(20, 450);
    glEnd();
    glFlush();
}

void cloud1()
{

    glColor3f(0.019, 0.35, 0.65);
    drawCircle(0, 40, 20);
    drawCircle(50, 40, 22);
    drawCircle(100, 42, 15);
    drawCircle(150, 42, 18);
    drawCircle(200, 42, 12);
    drawCircle(240, 42, 20);
    drawCircle(280, 40, 20);
    drawCircle(340, 40, 22);
    drawCircle(400, 42, 15);
    drawCircle(460, 42, 18);
    drawCircle(530, 42, 12);
    drawCircle(600, 42, 20);
    drawCircle(650, 42, 25);
    drawCircle(720, 42, 15);
    drawCircle(780, 42, 24);
}
void cloud2()
{
    glColor3f(0.94, 1.0, 0.94);
    drawCircle(45, 680, 20);
    drawCircle(75, 680, 40);
    drawCircle(90, 680, 45);
    drawCircle(120, 680, 35);
    drawCircle(140, 680, 20);

    drawCircle(200, 670, 25);
    drawCircle(220, 670, 35);
    drawCircle(260, 670, 50);
    drawCircle(290, 670, 35);
    drawCircle(320, 670, 20);
}
void tree()
{
    // right leaf
    glColor3f(0, 0.098, 0);
    drawCircle(1170, 288, 25);
    drawCircle(1190, 344, 45);
    drawCircle(1185, 320, 30);
    drawCircle(1245, 380, 55);
    drawCircle(1238, 310, 25);
    drawCircle(1259, 315, 30);
    drawCircle(1200, 295, 25);

    // left leaf

    glColor3f(0, 0.098, 0);
    drawCircle(956, 364, 20);
    drawCircle(990, 361, 25);
    drawCircle(1046, 361, 25);
    drawCircle(1070, 360, 20);

    glColor3f(0, 0.098, 0);
    drawCircle(980, 400, 25);
    drawCircle(1020, 387, 35);
    drawCircle(1065, 392, 25);

    glColor3f(0, 0.098, 0);
    drawCircle(999, 440, 30);
    drawCircle(1030, 435, 35);
}
void powerHouse()
{
    //******power house *********

    glBegin(GL_POLYGON);
    glColor3f(0.28, 0.29, 0.34);
    glVertex2i(559, 331);
    glVertex2i(559, 320);
    glVertex2i(660, 318);
    glVertex2i(660, 330);
    glVertex2i(565, 333);
    glEnd();
    glFlush();

    glBegin(GL_POLYGON);
    glColor3f(0.21, 0.15, 0.12);
    glVertex2i(554, 389);
    glVertex2i(564, 386);
    glVertex2i(565, 395);
    glVertex2i(607, 444);
    glVertex2i(607, 446);
    glEnd();
    glFlush();

    // phouse base ri8
    glBegin(GL_POLYGON);
    glColor3f(0.28, 0.29, 0.34);
    glVertex2i(660, 330);
    glVertex2i(660, 318);
    glVertex2i(685, 327);
    glVertex2i(685, 336);
    glVertex2i(678, 336);
    glEnd();
    glFlush();

    // phouse wall right side
    glBegin(GL_POLYGON);
    glColor3f(0.69, 0.407, 0.34);
    glVertex2i(659, 397);
    glVertex2i(659, 329);
    glVertex2i(679, 336);
    glVertex2i(679, 386);
    glVertex2i(669, 389);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(0, 0.01, 0.02);
    glVertex2i(660, 329);
    glVertex2i(660, 400);
    glEnd();
    glFlush();

    // phouse wall front
    glBegin(GL_POLYGON);
    glColor3f(0.69, 0.407, 0.34);
    glVertex2i(607, 443);
    glVertex2i(564, 396);
    glVertex2i(565, 333);
    glVertex2i(659, 329);
    glVertex2i(659, 397);
    glEnd();
    glFlush();

    // phouse door
    glBegin(GL_QUADS);
    glColor3f(0.37, 0.250, 0.12);
    glVertex2i(620, 391);
    glVertex2i(620, 331);
    glVertex2i(650, 331);
    glVertex2i(650, 390);
    glEnd();
    glFlush();

    // phouse window
    glBegin(GL_QUADS);
    glColor3f(0.909, 0.780, 0.486);
    glVertex2i(572, 390);
    glVertex2i(572, 354);
    glVertex2i(607, 354);
    glVertex2i(607, 390);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2i(578, 390);
    glVertex2i(578, 354);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2i(584, 390);
    glVertex2i(584, 353);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2i(590, 389);
    glVertex2i(590, 353);
    glEnd();
    glFlush();

    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2i(598, 389);
    glVertex2i(598, 353);
    glEnd();
    glFlush();

    // phouse top left
    glBegin(GL_QUADS);
    glColor3f(0.31, 0.31, 0.39);
    glVertex2i(545, 397);
    glVertex2i(554, 388);
    glVertex2i(607, 443);
    glVertex2i(607, 466);
    glEnd();
    glFlush();

    // phouse top right
    glBegin(GL_QUADS);
    glColor3f(0.28, 0.29, 0.34);
    glVertex2i(643, 447);
    glVertex2i(607, 466);
    glVertex2i(677, 401);
    glVertex2i(695, 394);
    glEnd();
    glFlush();

    // phouse top right
    glBegin(GL_QUADS);
    glColor3f(0.28, 0.29, 0.34);
    glVertex2i(607, 466);
    glVertex2i(607, 443);
    glVertex2i(668, 389);
    glVertex2i(677, 401);
    glEnd();
    glFlush();

    // phouse top right
    glBegin(GL_QUADS);
    glColor3f(0.28, 0.29, 0.34);
    glVertex2i(695, 394);
    glVertex2i(677, 401);
    glVertex2i(668, 389);
    glVertex2i(687, 386);
    glEnd();
    glFlush();
}
void treeBase()
{
    // tree base

    glBegin(GL_QUADS);
    glColor3f(0.313, 0.321, 0.258);
    glVertex2i(1230, 304);
    glVertex2i(1230, 169);
    glVertex2i(1260, 169);
    glVertex2i(1260, 304);
    glEnd();
    glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.313, 0.321, 0.258);
    glVertex2i(1230, 180);
    glVertex2i(1225, 170);
    glVertex2i(1265, 170);
    glVertex2i(1260, 180);
    glEnd();
    glFlush();

    // tree base 2

    glBegin(GL_QUADS);
    glColor3f(0.313, 0.321, 0.258);
    glVertex2i(1004, 360);
    glVertex2i(1004, 267);
    glVertex2i(1027, 267);
    glVertex2i(1027, 360);
    glEnd();
    glFlush();

    glBegin(GL_QUADS);
    glColor3f(0.313, 0.321, 0.258);
    glVertex2i(1004, 267);
    glVertex2i(1000, 265);
    glVertex2i(1029, 265);
    glVertex2i(1027, 267);
    glEnd();
    glFlush();

    tree();
}
void gojoBet()
{
    chisMawcha();
    // Draw the house base
    glColor3f(0.5 + col, 0.3 + col, 0.2 + col); // Brown color for the base
    glBegin(GL_POLYGON);
    glVertex2f(220, 100);
    glVertex2f(370, 100);
    glVertex2f(370, 200);
    glVertex2f(220, 200);
    glEnd();
    smoke(220, 100);
    smoke(300, 100);
    smoke(330, 100);

    // Draw the roof
    glColor3f(0.37 + col, 0.28 + col, 0.09 + col); // Red color for the roof
    glBegin(GL_TRIANGLES);
    glVertex2f(200, 200);
    glVertex2f(300, 300);
    glVertex2f(400, 200);
    glEnd();
    glColor3f(0.0, 0.0, 0.0); // Red color for the roof

    for (int a = 0; a <= 200; a = a + 20)
    {
        glBegin(GL_LINES);
        glVertex2f(300, 300);
        glVertex2f(200 + a, 200);
    }
    n

    glEnd();
    // Draw the arched door
    glColor3f(0.7, 0.5, 0.3); // Wood color for the door
    // Draw the bottom part of the door as a rectangle
    glBegin(GL_POLYGON);
    glVertex2f(250, 100);
    glVertex2f(300, 100);
    glVertex2f(300, 150);
    glVertex2f(250, 150);

    glEnd();
    dda2(275, 100, 275, 150);
    dda2(250, 140, 300, 140);
    dda2(250, 120, 300, 120);
    // Draw the arc on top of the door
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0); // Black color for the arc
    glBegin(GL_LINE_STRIP);
    for (int angle = 0; angle <= 180; angle += 5)
    {
        float x = 275 + 25 * cos(angle * 3.14159 / 180);
        float y = 150 + 15 * sin(angle * 3.14159 / 180);
        glVertex2f(x, y);
    }
    glEnd();

    glColor3f(1.0, 1.0, 1.0); // White color for the window frame
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int angle = 0; angle <= 360; angle += 5)
    {
        float x = 335 + 15 * cos(angle * 3.14159 / 180);
        float y = 180 + 8 * sin(angle * 3.14159 / 180);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw the window glass
    glColor4f(1.0, 1.0, 1.0, 0.5); // Light blue color for the glass
    glBegin(GL_POLYGON);
    for (int angle = 0; angle <= 360; angle += 5)
    {
        float x = 335 + 13 * cos(angle * 3.14159 / 180);
        float y = 180 + 6 * sin(angle * 3.14159 / 180);
        glVertex2f(x, y);
    }
    glEnd();
}
void road()
{
    glBegin(GL_POLYGON); // main road
    glColor3f(0.27, 0.26, 0.22);

    glVertex2i(690, 0);
    glVertex2i(830, 0);
    glVertex2i(910, 350);
    glVertex2i(880, 345);

    glEnd();
    glBegin(GL_POLYGON); // road middle white rectangle
    glColor3f(1, 1, 0.99);

    glVertex2i(747, 0);
    glVertex2i(763, 0);
    glVertex2i(900, 350);
    glVertex2i(895, 350);

    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.5);
    glPointSize(4.0);
    mountain();
    ground();
    road();
    river();
    gojoBet();
    mesob();
    drawFence(120, 210);
    drawFence(290, 700);

    if (i == 1)
    {
        glColor3f(0.9, 0.9, 0.5);
        drawArc(0, 360, 200, 700, 10);
    }
    if (i == 2)
    {
        glColor3f(0.8, 0.7, 0.4);
        drawArc(0, 360, 400, 700, 10);
    }
    if (i == 3)
    {
        glColor3f(1.0, 1.0, 1.0);
        drawArc(0, 360, 600, 700, 10);
    }
    if (i == 4)
    {
        glColor3f(1.0, 1.0, 1.0);
        drawArc(0, 360, 800, 700, 10);
    }
    stand();
    /////////rotatoin
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(150.0, 420.0f, 1);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    angle = angle - rate;
    glTranslatef(-100.0f, -500.0f, -2.0f);
    windmill();
    glPopMatrix();
    glFlush();
    powerHouse();
    treeBase();
    // glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    cloud2();
    cloud1();
    glPopMatrix();
    glutSwapBuffers();
}
void myInit(void)
{
    glClearColor(0.29, 0.46, 0.96, 1.0);

    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 768.0);
}
void update(int value)
{
    posX += move_unit;
    if (posX > 1000)
    {
        posX -= 1000;
    }
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'y':
        glClearColor(0.8, 0.5, 0.4, 1.0);
        col = -0.1;
        i = 0;
        glutPostRedisplay();
        break;
    case 'm':
        glClearColor(0.5, 0.5, 1.0, 1.0);
        i = 1;
        col = 0.2;
        glutPostRedisplay();
        break;
    case 'a':
        glClearColor(0.9, 0.9, 0.3, 1.0);
        i = 2;
        col = 0.3;
        glutPostRedisplay();
        break;
    case 'e':
        glClearColor(0.8, 0.5, 0.4, 1.0);
        col = -0.1;
        i = 0;
        glutPostRedisplay();
        break;
    case 'n':
        glClearColor(0.5, 0.5, 0.5, 1.0);
        i = 3;
        glutPostRedisplay();
        col = -0.2;
        break;
    case 'd':
        glClearColor(0.0, 0.0, 0.0, 0.0);
        i = 4;
        col = -0.3;
        glutPostRedisplay();
        break;
    }
}

int main(int argv, char **argc)
{
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Country Side Village");
    glutSwapBuffers();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutTimerFunc(1000, update, 0);
    myInit();
    glutMainLoop();
}
