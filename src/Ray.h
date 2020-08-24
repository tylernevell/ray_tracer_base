#ifndef _RAY_H_
#define _RAY_H_

#include "Vec3.h"

class Ray {
    public:
        Point3 orig;    // ray origin
        Vec3 dir;       // ray direction
        
        Ray() = default;
        Ray(const Point3& origin, const Vec3& direction);
        
        Point3 origin() const { return orig; }
        Vec3 direction() const { return dir; }

        // P(t) = A + tb
        // A is ray origin, b is ray direction
        Point3 at(double t) const;

    // public:
    //     Point3 orig;    // ray origin
    //     Vec3 dir;       // ray direction
};

#endif