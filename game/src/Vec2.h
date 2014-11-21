#ifndef VEC2_H
#define VEC2_H

// simple struct for representing positions
struct Vec2
{
    Vec2()
    {
	x = y = 0;
    }

    Vec2(int _x, int _y)
    {
	x = _x;
	y = _y;
    }

    int x, y;
};

#endif
