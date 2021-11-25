#include <ctime>
#include <random>

#include "tetromino.h"

int Tetromino::forms[7][4] = {
    1,3,5,7,
    2,4,5,7,
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

int Tetromino::field[height][width] = { 0 };

Tetromino::Tetromino(void) : dx(0), rotate(false)
{
    set_color();
    rand_shape();
    init_points();
}

int Tetromino::get_shape_type(void)
{
    return shape;
}

void Tetromino::init_points(void)
{
    for (int i = 0; i < 4; ++i) {
        p[i].set_x(forms[shape][i] % 2);
        p[i].set_y(forms[shape][i] / 2);
    }
}

void Tetromino::init_q_points(void)
{
    for (int i = 0; i < 4; ++i) {
        q[i] = p[i];
    }
}

Point* Tetromino::get_points(void)
{
    return p;
}

Point* Tetromino::get_q_points(void)
{
    return q;
}

void Tetromino::set_rotate(bool rotate)
{
    this->rotate = rotate;
}

void Tetromino::set_dx(int dx)
{
    this->dx = dx;
}

void Tetromino::move(void)
{
    for (int i = 0; i < 4; ++i) {
        q[i] = p[i];
        p[i].set_x(p[i].get_x() + dx);
    }
    if (check() == false) {
        for (int i = 0; i < 4; ++i) {
            p[i] = q[i];
        }
    }
}

void Tetromino::rotating(void)
{
    if (rotate) {
        Point new_p = p[1];
        for (int i = 0; i < 4; ++i) {
            int x = p[i].get_y() - new_p.get_y();
            int y = p[i].get_x() - new_p.get_x();

            p[i].set_x(new_p.get_x() - x);
            p[i].set_y(new_p.get_y() + y);
        }
    }
    if (check() == false) {
        for (int i = 0; i < 4; ++i) {
            p[i] = q[i];
        }
    }
}

bool Tetromino::check(void)
{
    for (int i = 0; i < 4; ++i) {
        if (p[i].get_x() < 0 || p[i].get_x() >= width || p[i].get_y() >= height) {
            return false;
        } else if (field[p[i].get_y()][p[i].get_x()]) {
            return false;
        }
    }
    return true;
}

void Tetromino::rand_shape(void)
{
    srand(time(0));
    shape = rand() % 7;
}

void Tetromino::set_color(void)
{
    srand(time(0));
    color = rand() % 7 + 1;
}

int Tetromino::get_color(void)
{
    return color;
}

void Tetromino::delete_full_line(void)
{
    int k = height - 1;
    for (int i = height - 1; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < width; ++j) {
            if (field[i][j]) {
                ++count;
                field[k][j] = field[i][j];
            }
        }
        if (count < width) {
            --k;
        }
    }
}