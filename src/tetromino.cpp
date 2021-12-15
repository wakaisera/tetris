#include <ctime>
#include <random>

#include "tetromino.h"

// int Tetromino::field[height][width] = { 0 };

Game::Game(void)
{
    set_screen_resize(4);
    set_cell_size(8);
    set_width(10);
    set_height(20);
    set_frame_duration(16667);
    field_init();
}

Game::~Game(void)
{
    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;
}

void Game::field_init(void)
{
    field = new int* [height];
    for (int i = 0; i < height; ++i) {
        field[i] = new int[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field[i][j] = 0;
        }
    }
}

void Game::set_field(int i, int j, int value)
{
    field[i][j] = value;
}

int Game::get_field(int i, int j)
{
    return field[i][j];
}

Color Tetromino::color[9] = {
    Color::White,
    Color::Red,
    Color::Green,
    Color::Blue,
    Color::Magenta,
    Color::Yellow,
    Color::Cyan,
    Color(73, 73, 85),
    Color(219, 0, 0)
    /*
    Color(36, 36, 85),
    Color(0, 219, 255),
    Color(0, 36, 255),
    Color(255, 146, 0),
    Color(255, 219, 0),
    Color(0, 219, 0),
    Color(146, 0, 255),
    Color(219, 0, 0),
    Color(73, 73, 85)
    */
};

Tetromino::Tetromino(void) : Polyomino()
{
    rand_shape();
    init_points();
}

Tetromino::Tetromino(int dx) : Polyomino(dx)
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
        q[i] = p[i]; // перемещаем координаты в вспомогательный массив
        p[i].set_x(p[i].get_x() + dx); // делаем шаг влево или вправо
    }
    /* проверка на выход за границы */
    if (border_check() == false) {
        /* если вышли возвращаем старые координаты */
        for (int i = 0; i < 4; ++i) {
            p[i] = q[i];
        }
    }
}

void Tetromino::rotating(void)
{
    if (rotate == true) {
        Point new_p = p[1]; // центр вращения
        for (int i = 0; i < 4; ++i) {
            /*
            *   уравнения вращения вокруг заданной точки с координатами (x0, y0)
            *   X = x0 - (y - y0);  Y = y0 + (x - x0);
            */
            int x = p[i].get_y() - new_p.get_y(); // y - y0
            int y = p[i].get_x() - new_p.get_x(); // x - x0

            p[i].set_x(new_p.get_x() - x);
            p[i].set_y(new_p.get_y() + y);
        }
    }
    /* проверка на выход за границы */
    if (border_check() == false) {
        /* если вышли возвращаем старые координаты */
        for (int i = 0; i < 4; ++i) {
            p[i] = q[i];
        }
    }
}

bool Tetromino::border_check(void)
{
    for (int i = 0; i < 4; ++i) {
        /* не вышли ли мы за границы поля слева, справа и снизу? */
        if (p[i].get_x() < 0 || p[i].get_x() >= width || p[i].get_y() >= height) {
            return false;
        }
        /* свободна ли ячейка расположенная на пути движения или занята другими тетрамино? */
        else if (field[p[i].get_y()][p[i].get_x()] != 0) {
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
    /* идем по массиву field снизу вверх */
    for (int i = height - 1; i > 0; --i) {
        int count = 0; // счетчик занятых полей игрового поля
        for (int j = 0; j < width; ++j) {
            if (field[i][j]) {
                ++count;
            }
            field[k][j] = field[i][j];
        }
        /*
        *   Если есть свободное место, то уменьшаем счетчик k,
        *   чтобы текущая строка не изменилась.
        *   Иначе при очередном присваивании field[k][j] = field[i][j]
        *   индекс k не будет равен i и элементы верхней строки 
        *   будут присвоены элементам нижней строки,
        *   т.е. произойдет сдвиг вниз на одну строку
        */
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
