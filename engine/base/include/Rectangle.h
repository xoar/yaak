#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

typedef struct
{
    int posX;
    int posY;

    int width;
    int height;

} Rectangle;

typedef struct
{
    double posX;
    double posY;
} Point;

typedef struct
{
    double dx;
    double dy;
} Vector;



#endif