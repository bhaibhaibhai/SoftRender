// my
#include "Vertex.hpp"

//------------------------------------------------------------
Vertex::Vertex(float x, float y, float z) :   
    position(x, y, z, 1.0f)
{
    // empty
}

//------------------------------------------------------------
Vertex::Vertex(Maths::Vec4 const & pos) :   
    position(pos)
{
    // empty
}

//------------------------------------------------------------
Vertex 
Vertex::transform(Maths::Mat4f & matrix) { 
    Maths::Vec4 pos = matrix * position;
    return Vertex(Maths::Vec4(pos.x, pos.y, pos.z, pos.w)); 
}

//------------------------------------------------------------
Vertex
Vertex::perspectiveDivide() {
    return Vertex(Maths::Vec4(position.x / position.w,
                  position.y / position.w,
                  position.z / position.w,
                  position.w));
}

//------------------------------------------------------------
float
Vertex::triangleAreaTimesTwo(Vertex const & b, Vertex const & c) {
    float x1 = b.position.x - position.x;
    float y1 = b.position.y - position.y;

    float x2 = c.position.x - position.x;
    float y2 = c.position.y - position.y;

    return x1 * y2 - x2 * y1;
}


