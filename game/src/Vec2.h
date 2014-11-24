#ifndef VEC2_H
#define VEC2_H

// simple struct for representing positions
struct Vec2
{
    Vec2()
    {
	x = y = w = h = 0;
    }

    Vec2(int _x, int _y, int _w = 0, int _h = 0)
    {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
    }

    int x, y, w, h;
};

#endif
