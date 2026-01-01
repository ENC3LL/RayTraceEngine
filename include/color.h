#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

// Функция записи цвета с учетом сглаживания и гамма-коррекции
// pixel_color: сумма цветов всех лучей
// samples_per_pixel: сколько лучей мы пустили
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Делим цвет на количество сэмплов (находим среднее)
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Гамма-коррекция (Gamma 2.0)
    // Возводим в степень 1/2 (извлекаем корень)
    // Это нужно, чтобы на мониторе картинка выглядела натурально, а не темно
    r = sqrt(r);
    g = sqrt(g);
    b = sqrt(b);

    // Записываем значения [0,255]
    // clamp (ограничение) нужен, чтобы случайно не уйти за 255
    out << static_cast<int>(256 * (r > 0.999 ? 0.999 : (r < 0.0 ? 0.0 : r))) << ' '
        << static_cast<int>(256 * (g > 0.999 ? 0.999 : (g < 0.0 ? 0.0 : g))) << ' '
        << static_cast<int>(256 * (b > 0.999 ? 0.999 : (b < 0.0 ? 0.0 : b))) << '\n';
}

#endif