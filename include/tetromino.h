#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const unsigned int screen_resize = 4;
const unsigned int cell_size = 8;
const unsigned int width = 10;
const unsigned int height = 20;

const unsigned int frame_duration = 16667;

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
	bool rotate;
public:
	static int field[height][width];
	static Color color[9];
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
	bool border_check(void);
	void rand_shape(void);
	void delete_full_line(void);
	void reset_minos(void);
};