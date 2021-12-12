#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Game {
protected:
	Game(void);
	~Game(void);
	unsigned int screen_resize;
	unsigned int cell_size;
	unsigned int width;
	unsigned int height;
	unsigned int frame_duration;
	int** field;
public:
	unsigned int get_screen_resize(void) { return screen_resize; }
	unsigned int get_cell_size(void) { return cell_size; }
	unsigned int get_width(void) { return width; }
	unsigned int get_height(void) { return height; }
	unsigned int get_frame_duration(void) { return frame_duration; }
	void set_screen_resize(unsigned int screen_resize) { this->screen_resize = screen_resize; }
	void set_cell_size(unsigned int cell_size) { this->cell_size = cell_size; }
	void set_width(unsigned int width) { this->width = width; }
	void set_height(unsigned int height) { this->height = height; }
	void set_frame_duration(unsigned int frame_duration) { this->frame_duration = frame_duration; }
	void field_init(void);
	void set_field(int i, int j, int value);
	int get_field(int i, int j);
};

class Point {
	int x;
	int y;
public:
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }
	int get_x(void) { return x; }
	int get_y(void) { return y; }
};

class Polyomino: public Game {
protected:
	int dx;
	bool rotate;
	Polyomino(void) : Game(), dx(0), rotate(false) {};
	Polyomino(int dx, bool rotate = false) : Game(), dx(0), rotate(rotate) {};
public:
	virtual void set_rotate(bool rotate) = 0;
	virtual void set_dx(int dx) = 0;
};

class Tetromino: public Polyomino {
	Point p[4];
	Point q[4];
	int shape;
public:
	// static int field[height][width];
	static Color color[9];
	Tetromino(void);
	Tetromino(int dx);
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