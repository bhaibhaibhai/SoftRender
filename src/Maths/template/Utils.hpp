#ifndef MathsUtils_hpp
#define MathsUtils_hpp

// std
#include <cstdlib> 

// defines
#define PI 3.14159265359

namespace djc_math {

inline constexpr float 
toRadians(float degrees);

inline float 
randFBetweenZeroOne();

inline unsigned char 
randUCBetween0N255();

inline float
normalise(float valToNormalise, float min, float max);

template <typename T>
inline T lerp(T v0, T v1, float t);

template<typename T>
inline T clamp(T v, T low, T hi);

} /* namespace djc_math */
#include "inline/Utils.inl"
#endif /* MathsUtils_hpp */