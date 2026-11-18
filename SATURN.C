
/*
   SATURN - COMPUTER GRAPHICS PROJECT
   Language: C
   Compiler: Turbo C++ with BGI

   FACULTY: Ms. Pratima Mall

   PROJECT MEMBERS:
   1. Raushan Kumar
   2. Suhail Ansari

   TRANSFORMATIONS:
   1. Scaling
   2. Translation
   3. Rotation
*/

#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265

/* Transformation variables */
float scale = 1.0;float angle = 25.0;
int tx = 0, ty = 0;

/* Planet center */
int cx, cy;

/* Draw a rotated ellipse */
void drawRing(int xc, int yc,
	      float rx, float ry,
	      float rotation, int color)
{
    float t, x, y, xr, yr;
    float a = rotation * PI / 180.0;
    int first = 1;

    setcolor(color);

    for (t = 0; t <= 360; t += 2)
    {
	x = rx * cos(t * PI / 180.0);
	y = ry * sin(t * PI / 180.0);

	/* Rotation transformation */
	xr = x * cos(a) - y * sin(a);
	yr = x * sin(a) + y * cos(a);

	if (first)
	{
	    moveto(xc + (int)xr, yc + (int)yr);
	    first = 0;
	}
	else
	{
	    lineto(xc + (int)xr, yc + (int)yr);
	}
    }
}

/* Draw stars in space */
void drawStars()
{
    int i, x, y;

    for (i = 0; i < 100; i++)
    {
	x = (i * 97 + 23) % getmaxx();
	y = (i * 61 + 17) % getmaxy();

	putpixel(x, y,
		 (i % 5 == 0) ? LIGHTCYAN : WHITE);
    }
}

/* Draw Saturn's sphere-like body */
void drawPlanet(int x, int y, int r)
{
    int i, yy, half, bandHalf, shade;

    /* Outer shadow */
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(x + 3, y + 3, r, r);

    /* Golden sphere */
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, r, r);

    /* Horizontal atmospheric bands */
    for (i = -5; i <= 5; i++)
    {
        yy = y + i * (r / 6);

        if (yy < y - r + 2 || yy > y + r - 2)
            continue;

        half = (int)sqrt((double)r * r -
                         (double)(yy - y) * (yy - y));

        bandHalf = half * 9 / 10;

        if (i % 2 == 0)
            shade = LIGHTRED;
        else
            shade = BROWN;

        setcolor(shade);
        line(x - bandHalf, yy, x + bandHalf, yy);
    }

    /* Highlight arc */
    setcolor(WHITE);
    arc(x - r / 5, y - r / 5, 110, 250, r * 3 / 4);

    /* Planet outline */
    setcolor(LIGHTGRAY);
    circle(x, y, r);
}

/* Draw the complete Saturn scene */
void drawSaturn()
{
    int x, y, r;
    char info[100];

    /* Translation transformation */
    x = cx + tx;
    y = cy + ty;

    /* Scaling transformation */
    r = (int)(65 * scale);

    setbkcolor(BLACK);
    cleardevice();

    /* Space background */
    drawStars();

    /* Rings behind the planet */
    drawRing(x, y, 125 * scale, 38 * scale,
             angle, DARKGRAY);

    drawRing(x, y, 117 * scale, 32 * scale,
             angle, BROWN);

    drawRing(x, y, 108 * scale, 27 * scale,
             angle, LIGHTGRAY);

    drawRing(x, y, 98 * scale, 22 * scale,
             angle, YELLOW);

    /* Saturn body */
    drawPlanet(x, y, r);

    /* Rings in front of the planet */
    drawRing(x, y, 125 * scale, 38 * scale,
             angle, LIGHTGRAY);

    drawRing(x, y, 117 * scale, 32 * scale,
             angle, BROWN);

    drawRing(x, y, 108 * scale, 27 * scale,
             angle, YELLOW);

    /* Project heading */
    setcolor(WHITE);
    outtextxy(10, 10,
              "SATURN - COMPUTER GRAPHICS PROJECT");

    /* Faculty name */
    setcolor(YELLOW);
    outtextxy(10, 30,
              "FACULTY: Ms. Pratima Mall");

    /* Project members */
    setcolor(LIGHTCYAN);
    outtextxy(10, 50, "PROJECT MEMBERS:");
    outtextxy(10, 65, "1. Raushan Kumar");
    outtextxy(10, 80, "2. Suhail Ansari");

    /* Keyboard controls */
    setcolor(YELLOW);
    outtextxy(10, 105, "KEYBOARD CONTROLS");

    setcolor(WHITE);
    outtextxy(10, 125, "TRANSLATION:");
    outtextxy(10, 140, "Arrow Keys - Move Saturn");

    outtextxy(10, 160, "SCALING:");
    outtextxy(10, 175, "+ : Zoom In");
    outtextxy(10, 190, "- : Zoom Out");

    outtextxy(10, 210, "ROTATION:");
    outtextxy(10, 225, "A : Rotate Left");
    outtextxy(10, 240, "D : Rotate Right");

    outtextxy(10, 260, "R : Reset All");
    outtextxy(10, 275, "ESC : Exit");

    /* Display transformation values */
    setcolor(LIGHTGREEN);

    sprintf(info, "Scale: %.1f  Angle: %.0f",
            scale, angle);

    outtextxy(10, 295, info);
}

/* Main function */
int main()
{
    int gd = DETECT, gm;
    int key, result;

    /* Initialize BGI graphics */
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    result = graphresult();

    if (result != grOk)
    {
        printf("Graphics initialization failed!");
        printf("\nCheck your BGI folder path.");
        getch();
        return 1;
    }

    /* Set screen center */
    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    /* Initial display */
    drawSaturn();

    /* Keyboard interaction loop */
    while (1)
    {
        key = getch();

        /* Exit program */
        if (key == 27)
            break;

        /* Arrow-key translation */
        if (key == 0 || key == 224)
        {
            key = getch();

            switch (key)
            {
                case 72: ty -= 10; break; /* Up */
                case 80: ty += 10; break; /* Down */
                case 75: tx -= 10; break; /* Left */
                case 77: tx += 10; break; /* Right */
            }
        }
        else
        {
            switch (key)
            {
                /* Scaling */
                case '+':
                case '=':
                    scale += 0.1;

                    if (scale > 1.5)
                        scale = 1.5;
                    break;

                case '-':
                case '_':
                    scale -= 0.1;

                    if (scale < 0.5)
                        scale = 0.5;
                    break;

                /* Rotation */
                case 'a':
                case 'A':
                    angle -= 10;
                    break;

                case 'd':
                case 'D':
                    angle += 10;
                    break;

                /* Reset all transformations */
                case 'r':
                case 'R':
                    scale = 1.0;
                    angle = 25.0;
                    tx = 0;
                    ty = 0;
                    break;
            }
        }

        /* Redraw the updated scene */
        drawSaturn();
    }

    closegraph();
    return 0;
}
