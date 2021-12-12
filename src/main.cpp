#include "tetromino.h"

using namespace sf;
using namespace std;

int main()
{
    // Tetromino tetromino;
    Tetromino tetromino(0);

    RenderWindow window(VideoMode(tetromino.get_cell_size() * tetromino.get_width() * tetromino.get_screen_resize(), tetromino.get_cell_size() * tetromino.get_height() * tetromino.get_screen_resize()), "Trash Tetris", Style::Close | Style::Titlebar);
    window.setView(View(sf::FloatRect(0, 0, tetromino.get_cell_size() * tetromino.get_width(), tetromino.get_cell_size() * tetromino.get_height())));
    window.setFramerateLimit(120);

    float timer = 0, delay = 0.3;
    Clock clock;

    RectangleShape cell(Vector2f(tetromino.get_cell_size() - 1, tetromino.get_cell_size() - 1));
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    tetromino.set_rotate(true);
                }
                else if (event.key.code == Keyboard::Right) {
                    tetromino.set_dx(1);
                }
                else if (event.key.code == Keyboard::Left) {
                    tetromino.set_dx(-1);
                }
                else if (event.key.code == Keyboard::Down) {
                    delay = 0.005;
                }
            }
        }
        /*
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                cell.setPosition(cell_size * i, cell_size * j);
                if (Tetromino::field[j][i] == 0) {
                    cell.setFillColor(Color::Black);
                }
                else {
                    cell.setFillColor(Tetromino::color[tetromino.get_shape_type()]);
                }
                window.draw(cell);
            }
        }
        */
        tetromino.reset_minos();
        tetromino.move();
        tetromino.rotating();
        if (timer > delay) {
            tetromino.init_q_points();
            for (int i = 0; i < 4; ++i) {
                tetromino.get_points()[i].set_y(tetromino.get_points()[i].get_y() + 1);
            }
            if (tetromino.border_check() == false) {
                for (int i = 0; i < 4; ++i) {
                    // Tetromino::field[tetromino.get_q_points()[i].get_y()][tetromino.get_q_points()[i].get_x()] = 1;
                    tetromino.set_field(tetromino.get_q_points()[i].get_y(), tetromino.get_q_points()[i].get_x(), 1);
                }
                tetromino.rand_shape();
                tetromino.init_points();
            }
            timer = 0;
        }

        tetromino.delete_full_line();
        tetromino.set_dx(0);
        tetromino.set_rotate(false);
        delay = 0.3;

        window.clear(Color::Black);
        for (int i = 0; i < tetromino.get_height(); ++i) {
            for (int j = 0; j < tetromino.get_width(); ++j) {
                if (tetromino.get_field(i, j) == 0) {
                    continue;
                }
                cell.setFillColor(Tetromino::color[tetromino.get_shape_type()]);
                cell.setPosition(j * tetromino.get_cell_size(), i * tetromino.get_cell_size());
                window.draw(cell);
            }
        }

        for (int i = 0; i < 4; ++i) {
            cell.setFillColor(Tetromino::color[tetromino.get_shape_type()]);
            cell.setPosition(tetromino.get_points()[i].get_x() * tetromino.get_cell_size(), tetromino.get_points()[i].get_y() * tetromino.get_cell_size());
            window.draw(cell);
        }
        window.display();
    }

    return 0;
}