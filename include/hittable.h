#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <memory> // ВАЖНО: нужно для std::shared_ptr

// Forward Declaration: говорим, что класс material существует
class material;

// Структура для хранения информации о попадании луча
struct hit_record {
    point3 p;      
    vec3 normal;
    std::shared_ptr<material> mat_ptr; // Ссылка на материал
    double t;      
};

// Абстрактный класс
class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif