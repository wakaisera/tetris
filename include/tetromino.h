#pragma once

#include "header.h"

using namespace std;

class Point {
	int x;
	int y;
public:
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }
	int get_x(void) { return x; }
	int get_y(void) { return y; }
};

class Tetromino {
	Point p[4];
	Point q[4];
	int dx;
	int shape;
	int color;
	bool rotate;
public:
	static int forms[7][4];
	static int field[height][width];
	Tetromino(void);
	int get_shape_type(void);
	void init_points(void);
	void init_q_points(void);
	Point* get_points(void);
	Point* get_q_points(void);
	void set_rotate(bool rotate);
	void set_dx(int dx);
	void move(void);
	void rotating(void);
	bool check(void);
	void rand_shape(void);
	void set_color(void);
	int get_color(void);
	void delete_full_line(void);
};

