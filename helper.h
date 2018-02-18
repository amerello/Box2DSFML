#ifndef BOX2DSFML_HELPER_H
#define BOX2DSFML_HELPER_H

#include <cmath>

inline float degToRad(float deg) { return deg * (float) M_PI / 180.f; }
inline float radToDeg(float rad) { return rad * 180.f / (float) M_PI; }

#endif //BOX2DSFML_HELPER_H
