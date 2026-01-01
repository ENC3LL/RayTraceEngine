#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

struct hit_record;

// Абстрактный класс материала
class material {
public:
    virtual ~material() = default;

    // Функция scatter возвращает true, если луч отразился
    // r_in: входящий луч
    // rec: информация о попадании (нормаль, точка)
    // attenuation: сюда мы запишем цвет материала (насколько луч потускнел)
    // scattered: сюда мы запишем новый отраженный луч
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};

// --- МАТОВЫЙ МАТЕРИАЛ (Lambertian) ---
class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        // Отражаем в случайную сторону (как раньше)
        auto scatter_direction = rec.normal + random_unit_vector();

        // Защита от багов: если случайный вектор оказался строго противоположным нормали,
        // их сумма даст (0,0,0), что сломает математику дальше.
        if (scatter_direction.near_zero()) // near_zero добавим в vec3 чуть позже
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo; // Цвет поверхности
        return true;
    }

public:
    color albedo; // Отражающая способность (цвет)
};

// --- МЕТАЛЛ (Metal) ---
class metal : public material {
public:
    metal(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        // Отраженный вектор (Reflection)
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        
        // Металл отражает, только если луч уходит наружу (dot > 0)
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;
};

#endif