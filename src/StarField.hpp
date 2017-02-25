#ifndef StarField_hpp
#define StarField_hpp

// std
#include <array>

// my includes
#include "Maths/Vec3.hpp"

// my defines
#define NUM_STARS 20000

class RenderContext;

class StarField final {
public:
    StarField(RenderContext & renderContext, float speed, float spread);
    ~StarField() = default;

    void update(float delta);
    void render();

private:
    void initStar(int index);

private:
    float m_speed;
    float m_spread;
    std::array<Maths::Vec3, NUM_STARS> m_stars;
    RenderContext & m_rContext;
};
#endif /* StarField_hpp */