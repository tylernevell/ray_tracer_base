#include <iostream>
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

Color ray_color(const Ray& r) {
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // rows written out from top to bottom
    for (int j  = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaing: " << j << std::flush;
        // pixels written out in rows with pixels left to right
        for (int i = 0; i < image_width; ++i) {
            
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            // blends white and blue depending on height of the y coordinate after
            // scaling  the ray direction to unit length
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);

            // Red goes from full off (black) to fully on (bright red) from left to right
            // Green goes from black at the bottom to fully on at the top
            // upper right corner should be yellow
        }
    }
    std::cerr << "\nDone.\n";
}

/* 
Ray tracer sends rays through pixels and computes the color seen in the direction of 
those rays

STEPS
(1) Calculate the ray from the eye to the pixel
(2) Determine which objects the ray intersects
(3) Compute a color for that intersection point
(4) Set up a virtual viewpoint to pass our scene rays through

Focal Length: Distance between projection plane and projection point

*/

