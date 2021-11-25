#include <SFML/Graphics.hpp>

#include "header.h"
#include "tetromino.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(cell_size * width * screen_resize, cell_size * height * screen_resize), "Trash Tetris", Style::Close | Style::Titlebar);
    window.setView(View(sf::FloatRect(0, 0, cell_size * width, cell_size * height)));
    window.setFramerateLimit(120);

    float timer = 0, delay = 0.5;
    Clock clock;

    Tetromino tetromino;

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
                } else if (event.key.code == Keyboard::Right) {
                    tetromino.set_dx(1);
                } else if (event.key.code == Keyboard::Left) {
                    tetromino.set_dx(-1);
                } else if (event.key.code == Keyboard::Down) {
                    delay = 0.05;
                }
            }
        }

        window.clear(Color::Black);

        RectangleShape cell(Vector2f(cell_size - 1, cell_size - 1));
        /*
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                cell.setFillColor(Color::Blue);
                cell.setPosition(cell_size * i, cell_size * j);
                window.draw(cell);
            }
        }
        */

        tetromino.move();
        tetromino.rotating();
        if (timer > delay) {
            tetromino.init_q_points();
            for (int i = 0; i < 4; ++i) {
                tetromino.get_points()[i].set_y(tetromino.get_points()[i].get_y() + 1);
            }

            if (tetromino.check() == false) {
                for (int i = 0; i < 4; ++i) {
                    // Tetromino::field[tetromino.get_q_points()[i].get_y()][tetromino.get_q_points()[i].get_x()] = tetromino.get_color();
                    Tetromino::field[tetromino.get_q_points()[i].get_y()][tetromino.get_q_points()[i].get_x()] = 1;
                }
                // tetromino.set_color();
                tetromino.rand_shape();
                tetromino.init_points();
            }
            
            timer = 0;
        }

        /* Доделать метод delete_full_line */
        tetromino.delete_full_line();
        tetromino.set_dx(0);
        tetromino.set_rotate(false);
        delay = 0.5;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (tetromino.field[i][j] == 0) {
                    continue;
                }
                cell.setFillColor(Color::Magenta);
                cell.setPosition(j * cell_size, i * cell_size);
                window.draw(cell);
            }
        }

        for (int i = 0; i < 4; ++i) {
            cell.setFillColor(Color::Magenta);
            cell.setPosition(tetromino.get_points()[i].get_x() * cell_size, tetromino.get_points()[i].get_y() * cell_size);
            window.draw(cell);
        }
        window.display();
    }

    return 0;
}