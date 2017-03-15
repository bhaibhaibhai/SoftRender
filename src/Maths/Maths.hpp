#ifndef Maths_hpp
#define Maths_hpp

// c std
#include <cstdlib> 

// my
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4f.hpp"
#include "Transform.hpp"

// defines
#define PI 3.14159265359

namespace Maths {

//------------------------------------------------------------
inline constexpr float 
toRadians(float degrees) {
    return (degrees * PI) / 180;
}

//------------------------------------------------------------
inline float 
randFBetweenZeroOne() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

//------------------------------------------------------------
inline float
normalise(float valToNormalise, float min, float max) {
    return (valToNormalise - min) / (max - min);
}

//------------------------------------------------------------
template <typename T>
inline T lerp(T v0, T v1, float t) {
    return (1 - t) * v0 + t * v1;
}

//------------------------------------------------------------
template<typename T>
inline T clamp(T v, T low, T hi) {
    if(v < low) {
        return low;
    } else if(v > hi){
        return hi;
    }
    return v;
}


    
} /* namespace Maths */
#endif /*Maths_hpp */ 
