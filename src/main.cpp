#include "ray.h"
#include <iostream>
#include <fstream>

using namespace std;

// --- НОВАЯ ФУНКЦИЯ ---
bool hit_sphere(const point3& center, double radius, const ray& r) {
    // Вектор от начала луча к центру сферы
    vec3 oc = r.origin() - center;
    
    // Коэффициенты квадратного уравнения at^2 + bt + c = 0
    // a = dot(dir, dir)
    auto a = dot(r.direction(), r.direction());
    // b = 2 * dot(oc, dir)
    auto b = 2.0 * dot(oc, r.direction());
    // c = dot(oc, oc) - r^2
    auto c = dot(oc, oc) - radius * radius;
    
    // Считаем дискриминант
    auto discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0; // Не попали
    } else {
        // Возвращаем ближайший корень (ближнюю стенку сферы)
        // Формула: (-b - sqrt(D)) / 2a
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

// Обновленная функция цвета
color ray_color(const ray& r) {
    // Проверяем пересечение со сферой (центр 0,0,-1, радиус 0.5)
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    
    if (t > 0.0) {
        // 1. Находим точку пересечения
        point3 N = r.at(t) - vec3(0, 0, -1);
        
        // 2. Нормализуем вектор (превращаем в единичный)
        vec3 normal = unit_vector(N);
        
        // 3. Переводим координаты (-1..1) в цвет (0..1)
        return 0.5 * (color(normal.x()+1, normal.y()+1, normal.z()+1));
    }

    // Если не попали — рисуем фон (небо)
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void write_color(ostream &out, color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    ofstream outFile("image.ppm");
    outFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        // clog замедляет, можно убрать или делать реже, если комп мощный
        // clog << "\rScanlines remaining: " << y << ' ' << flush; 
        for (int x = 0; x < image_width; ++x) {
            auto u = double(x) / (image_width - 1);
            auto v = double(y) / (image_height - 1);
            
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            
            color pixel_color = ray_color(r);
            write_color(outFile, pixel_color);
        }
    }
    
    // Сообщение о готовности в конце
    clog << "\rDone.                 \n";
    outFile.close();
}