#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random> // Deep C++: Современная библиотека случайных чисел

// Usings (чтобы не писать std:: везде в cpp)
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Константы
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Утилиты
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Генератор случайных чисел (Thread-safe вариант для будущего)
inline double random_double() {
    // static означает, что генератор инициализируется один раз
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator; // Mersenne Twister engine
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Возвращает случайное число в диапазоне [min, max)
    return min + (max-min)*random_double();
}

// Подключаем наши общие хедеры
#include "ray.h"
#include "vec3.h"

// Функции генерации векторов (ОНИ ДОЛЖНЫ БЫТЬ ЗДЕСЬ)
inline vec3 random_vec3() {
    return vec3(random_double(), random_double(), random_double());
}

inline vec3 random_vec3(double min, double max) {
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

#endif