#include <ctime>
#include <random>

#include "tetromino.h"

int Tetromino::field[height][width] = { 0 };

Color Tetromino::color[9] = {
    Color(36, 36, 85),
    Color(0, 219, 255),
    Color(0, 36, 255),
    Color(255, 146, 0),
    Color(255, 219, 0),
    Color(0, 219, 0),
    Color(146, 0, 255),
    Color(219, 0, 0),
    Color(73, 73, 85)
};

Tetromino::Tetromino(void) : dx(0), rotate(false)
{
    rand_shape();
    init_points();
}

int Tetromino::get_shape_type(void)
{
    return shape;
}

void Tetromino::init_points(void)
{
    switch (shape) {
    // I shape
    case 0: {
        p[0].set_x(width / 2 - 2);
        p[0].set_y(0);
        p[1].set_x(width / 2 - 1);
        p[1].set_y(0);
        p[2].set_x(width / 2);
        p[2].set_y(0);
        p[3].set_x(width / 2 + 1);
        p[3].set_y(0);

        break;
    }
    // J shape
    case 1: {
        p[0].set_x(width / 2 - 2);
        p[0].set_y(0);
        p[1].set_x(width / 2);
        p[1].set_y(1);
        p[2].set_x(width / 2 - 1);
        p[2].set_y(1);
        p[3].set_x(width / 2 - 2);
        p[3].set_y(1);

        break;
    }
    // L shape
    case 2: {
        p[0].set_x(width / 2);
        p[0].set_y(0);
        p[1].set_x(width / 2);
        p[1].set_y(1);
        p[2].set_x(width / 2 - 1);
        p[2].set_y(1);
        p[3].set_x(width / 2 - 2);
        p[3].set_y(1);

        break;
    }
    // O shape
    case 3: {
        p[0].set_x(width / 2 - 1);
        p[0].set_y(0);
        p[1].set_x(width / 2);
        p[1].set_y(0);
        p[2].set_x(width / 2);
        p[2].set_y(1);
        p[3].set_x(width / 2 - 1);
        p[3].set_y(1);

        break;
    }
    // S shape
    case 4: {
        p[0].set_x(width / 2 - 1);
        p[0].set_y(0);
        p[1].set_x(width / 2);
        p[1].set_y(0);
        p[2].set_x(width / 2 - 1);
        p[2].set_y(1);
        p[3].set_x(width / 2 - 2);
        p[3].set_y(1);

        break;
    }
    // Z shape
    case 5: {
        p[0].set_x(width / 2 - 1);
        p[0].set_y(1);
        p[1].set_x(width / 2);
        p[1].set_y(1);
        p[2].set_x(width / 2 - 1);
        p[2].set_y(0);
        p[3].set_x(width / 2 - 2);
        p[3].set_y(0);

        break;
    }
    // T shape
    case 6: {
        p[0].set_x(width / 2 - 1);
        p[0].set_y(0);
        p[1].set_x(width / 2 - 1);
        p[1].set_y(1);
        p[2].set_x(width / 2);
        p[2].set_y(1);
        p[3].set_x(width / 2 - 2);
        p[3].set_y(1);

        break;
    }
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
    if (get_shape_type() != 3) {
        this->rotate = rotate;
    }
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
    if (border_check() == false) {
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
    if (border_check() == false) {
        for (int i = 0; i < 4; ++i) {
            p[i] = q[i];
        }
    }
}

bool Tetromino::border_check(void)
{
    for (int i = 0; i < 4; ++i) {
        if (p[i].get_x() < 0 || p[i].get_x() >= width || p[i].get_y() >= height) {
            return false;
        }
        else if (field[p[i].get_y()][p[i].get_x()]) {
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

void Tetromino::delete_full_line(void)
{
    int k = height - 1;
    for (int i = height - 1; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < width; ++j) {
            if (field[i][j]) {
                ++count;
            }
            field[k][j] = field[i][j];
        }
        if (count < width) {
            --k;
        }
    }
}

void Tetromino::reset_minos(void)
{
    for (int i = 0; i < 4; ++i) {
        if (field[0][p[i].get_x()] != 0) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < width; ++k) {
                    field[j][k] = 0;
                }
            }
        }
    }
}