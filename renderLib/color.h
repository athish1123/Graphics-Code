#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using namespace std;
using color = Vec3;

void write_color(ostream &out, const color &pixel_color, int samples_per_pixel)
{
  //Might need to be Auto instead of double
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();
  
  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif// COLOR_H
