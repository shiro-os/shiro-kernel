#ifndef __VECTORS_HPP_
#define __VECTORS_HPP_

struct vec2d {
    vec2d(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }

    double x;
    double y;
};

struct vec3d {
    vec3d(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double x;
    double y;
    double z;
};

struct vec2i {
    vec2i(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
};

struct vec3i {
    vec3i(int x = 0, int y = 0, int z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    int x;
    int y;
    int z;
};

#endif
