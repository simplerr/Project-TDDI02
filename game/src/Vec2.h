#pragma once

// simple struct for representing positions
struct Vec2
{
    Vec2()
    {
	x = y = 0;
    }

    Vec2(float _x, float _y)
    {
	x = _x;
	y = _y;
    }

    float x, y;
};
