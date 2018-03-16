#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include "math.h"

/*return the direction in degrees, 
  by looking from the sourcePoint to a tragetPoint */
int getDirection(Position sourcePoint,Position targetPoint)
{
    #define PI 3.1415926535

    int degree = 0;

    int dx = targetPoint.posX - sourcePoint.posX;
    int dy = targetPoint.posY - sourcePoint.posY;

    /* first we transfer dx,dy to the cartesion system. 
       in our system 0.0 is in the left corner and b grow against the bottom. */
    dy = -dy;

    /* use the fact dy/dx = tan(a) =>  a = tan^-1 (dy/dx)*/

    /*elimnate the simple cases. the tangens goes to infinit by them */
    if (dx == 0)
    {
        if (dy > 0) degree = 90;
        else degree = 270;

        return degree;
    }

    /* not need to be catched but faster */
    if (dy == 0)
    {
        if (dx>0) degree = 0;
        else degree = 180;

        return degree;
    }

    /* no we must use tan^-1. There are four regions/quadrant in the euclidean system.
       map lines of the 2-4 region to a case of the first. */

    if (dx>0)
    {
        /* first quadrant */
        /*use 180/PI to tranform radian into degree*/
        if (dy > 0) 
        { 
            double m = (double) dy/ (double) dx;
            double firstQuadrantDegree = atan(m)*180.0/PI;
            degree = (int) firstQuadrantDegree; 
            return degree; 
        }
        /*forth quadrant*/
        else 
        { 
            /*transform it to the first quadrant*/
            dy = -dy ;
            double m = (double) dy/ (double) dx;
            double firstQuadrantDegree = atan(m)*180.0/PI;
            degree = 360 - (int) firstQuadrantDegree;  
            return degree;
        }
    }
    else
    {
        /* second quadrant */
        if (dy > 0) 
        { 
            dx = -dx;
            double m = (double) dy/ (double) dx;
            double firstQuadrantDegree = atan(m)*180.0/PI;
            degree = 180 - (int) firstQuadrantDegree; 
            return degree; }
    }

    /* third quadrant. we dont calc it in the else case to let the compiler now
       we return something for sure */
     dx = -dx; 
     dy = -dy;
     double m = (double) dy/ (double) dx;
     double firstQuadrantDegree = atan(m)*180.0/PI;
     degree = 180 + firstQuadrantDegree; 
     return degree;

}

#endif