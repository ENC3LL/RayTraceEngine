#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// Структура для хранения информации о попадании луча
struct hit_record {
    point3 p;      // Точка пересечения в 3D
    vec3 normal;   // Нормаль в этой точке (куда смотрит поверхность)
    double t;      // Дистанция от начала луча до точки p
};

// Абстрактный класс (интерфейс) для всех объектов сцены
class hittable {
public:
    // Виртуальный деструктор обязателен для базовых классов
    virtual ~hittable() = default;

    // Чисто виртуальная функция (pure virtual)
    // t_min и t_max ограничивают диапазон поиска (чтобы не рисовать объекты за спиной)
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif