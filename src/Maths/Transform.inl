
namespace Maths {

//-------------------
/*      Mat3       */
//-------------------

// creates new

//------------------------------------------------------------
template<typename T> inline Mat3<T>
createMat3IdentityMatrix() {
    return Mat3<T>(std::array<T, 9> {{1, 0, 0,
                                      0, 1, 0,
                                      0, 0, 1}});
}

//------------------------------------------------------------
template<typename T> inline Mat3<T>
createMat3RotationMatrix(Vec3 const & rotation) {

    auto xSin = std::sin(rotation.x);
    auto xCos = std::cos(rotation.x);

    auto ySin = std::sin(rotation.y);
    auto yCos = std::cos(rotation.y);

    auto zSin = std::sin(rotation.z);
    auto zCos = std::cos(rotation.z);
    
    Mat3<T> rotX(std::array<T, 9> {{
        1,     0,    0,
        0,  xCos, xSin,
        0, -xSin, xCos,
    }});

    Mat3<T> rotY(std::array<T, 9>{{
        yCos, 0, -ySin,
           0, 1,     0,
        ySin, 0,  yCos
    }});

    Mat3<T> rotZ(std::array<T, 9>{{
         zCos, zSin, 0,
        -zSin, zCos, 0,
            0,   0,  1
    }});
   
    return rotX * rotY * rotZ;
}

// use existing

//-------------------
/*      Mat4       */
//-------------------

// create new

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4IdentityMatrix() {
    return Mat4<T>(std::array<T, 16>{{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4TranslationMatrix(Vec3 const & vec) {
    return Mat4<T>(std::array<T, 16>{{
        1, 0, 0, vec.x,
        0, 1, 0, vec.y,
        0, 0, 1, vec.z,
        0, 0, 0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4RotationMatrix(Vec3 const & rotation) {
    auto xSin = std::sin(rotation.x);
    auto xCos = std::cos(rotation.x);

    auto ySin = std::sin(rotation.y);
    auto yCos = std::cos(rotation.y);

    auto zSin = std::sin(rotation.z);
    auto zCos = std::cos(rotation.z);

    // perf : change this to mat3 then put into mat4 on return

    Mat4<T> rotX(std::array<T, 16>{{
        1,     0,    0, 0,
        0,  xCos, xSin, 0,
        0, -xSin, xCos, 0,
        0,     0,    0, 1
    }});

    Mat4<T> rotY(std::array<T, 16>{{
        yCos, 0, -ySin, 0,
           0, 1,     0, 0,
        ySin, 0,  yCos, 0,
           0, 0,     0, 1
    }});

    Mat4<T> rotZ(std::array<T, 16>{{
         zCos, zSin, 0, 0,
        -zSin, zCos, 0, 0,
            0,    0, 1, 0,
            0,    0, 0, 1
    }});

    return rotX * rotY * rotZ;
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ScaleMatrix(Vec3 const & vec) {
     return Mat4<T>(std::array<T, 16>{{
        vec.x,     0,     0, 0,
            0, vec.y,     0, 0,
            0,     0, vec.z, 0,
            0,     0,     0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale) {
    Mat4<T> _translation = createMat4TranslationMatrix<T>(position);
    Mat4<T> _rotation    = createMat4RotationMatrix<T>(rotation);
    Mat4<T> _scale       = createMat4ScaleMatrix<T>(scale);

    return _translation * _rotation * _scale;
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ProjectionMatrix(float fov, float near, float far, float aspect) {
    float range = std::tan(fov / 2.0f) * near;
    float    Sx = (2 * near) / (range * aspect + range * aspect);
    float    Sy = near / range;
    float    Sz = -(far + near) / (far - near);
    float    Pz = -(2 * far * near) / (far - near);

    return Mat4<T>(std::array<T, 16>{{
        Sx, 0,  0,  0,
        0, Sy,  0,  0,
        0,  0, Sz, -1,
        0,  0, Pz,  0
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ScreenSpaceTransform(float halfWidth, float halfHeight) {
    return Mat4<T>(std::array<T, 16>{{
               halfWidth,                 0, 0, 0,
                       0,       -halfHeight, 0, 0,
                       0,                 0, 1, 0,
        halfWidth - 0.5f, halfHeight - 0.5f, 0, 1
    }});
}

// use existing

//------------------------------------------------------------
template<typename T> inline void 
setMat4Identity(Mat4<T> & matrix) {
    matrix = Mat4<T>(std::array<T, 16>{{ 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }});
}

//-------------------
/*      Mat4f       */
//-------------------

//------------------------------------------------------------
inline Mat4f
createIdentityMatrix() {
    Mat4f matrix;
    matrix[0]  = 1;  
    matrix[5]  = 1; 
    matrix[10] = 1; 
    matrix[15] = 1;
    return matrix;
}

//------------------------------------------------------------
inline Mat4f 
createProjectionMatrix(float fov, float near, float far, float aspect) {
    Mat4f matrix;

    float range = std::tan(fov / 2.0f) * near;

    float Sx = (2 * near) / (range*aspect + range*aspect);
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2 * far * near) / (far - near);

    matrix[0] = Sx;
    matrix[5] = Sy;
    matrix[10] = Sz;
    matrix[11] = -1;
    matrix[14] = Pz;

    return matrix;
}

//------------------------------------------------------------
inline Mat4f 
createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale) {
    Mat4f translationMat = createIdentityMatrix();
    translationMat[12] = position.x;
    translationMat[13] = position.y;
    translationMat[14] = position.z;

    Mat4f rotX = createIdentityMatrix();
    setRotationX(rotX, rotation.x);
    Mat4f rotY = createIdentityMatrix();
    setRotationY(rotY, rotation.y);
    Mat4f rotZ = createIdentityMatrix();
    setRotationZ(rotZ, rotation.z);

    Mat4f rotationMat(rotZ * rotY * rotX);

    Mat4f scaleMat;
    scaleMat[0]  = scale.x;
    scaleMat[5]  = scale.y;
    scaleMat[10] = scale.z;
    scaleMat[15] = 1;

    return translationMat * rotationMat * scaleMat;
}

//------------------------------------------------------------
inline Mat4f
createTranslationMatrix(Vec3 const & position) {
    Mat4f translation = createIdentityMatrix();
    translation[12] = position.x;
    translation[13] = position.y;
    translation[14] = position.z;
    return translation;
}

//------------------------------------------------------------
inline Mat4f
createRotationMatrix(Vec3 const & rotation) {
    Mat4f rotX = createIdentityMatrix(); // cleanup : make code inline
    setRotationX(rotX, rotation.x);
    Mat4f rotY = createIdentityMatrix();
    setRotationY(rotY, rotation.y);
    Mat4f rotZ = createIdentityMatrix();
    setRotationZ(rotZ, rotation.z);
    return rotX * rotY * rotZ;
}

//------------------------------------------------------------
inline Mat4f
createScaleMatrix(Vec3 const & scale) {
    Mat4f scaleMat;
    scaleMat[0]  = scale.x;
    scaleMat[5]  = scale.y;
    scaleMat[10] = scale.z;
    scaleMat[15] = 1;
    return scaleMat;
}

//------------------------------------------------------------
inline Mat4f
createScreenSpaceTransform(float halfWidth, float halfHeight) {
    Mat4f screen = createIdentityMatrix();
    screen[0] =  halfWidth;
    screen[5] = -halfHeight;
    screen[12] = halfWidth - 0.5f;
    screen[13] = halfHeight - 0.5f;
    return screen;
}

//------------------------------------------------------------
inline void
transform(Vec4 & position, Mat4f & transformation) {
    position = transformation * position;
}

//------------------------------------------------------------
inline void 
setIdentity(Mat4f & matrix) {
    matrix[0]  = 1;  matrix[1]  = 0;  matrix[2]  = 0;  matrix[3]  = 0;
    matrix[4]  = 0;  matrix[5]  = 1;  matrix[6]  = 0;  matrix[7]  = 0;
    matrix[8]  = 0;  matrix[9]  = 0;  matrix[10] = 1;  matrix[11] = 0;
    matrix[12] = 0;  matrix[13] = 0;  matrix[14] = 0;  matrix[15] = 1;
}

//------------------------------------------------------------
inline void
setTranslation(Mat4f & matrix, Vec3 const & position) {
    matrix[12] = position.x;
    matrix[13] = position.y;
    matrix[14] = position.z;
}

//------------------------------------------------------------
inline void
setRotationX(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[5]  =  cos;
    matrix[6]  =  sin;
    matrix[9]  = -sin;
    matrix[10] =  cos;
}

//------------------------------------------------------------
inline void
setRotationY(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[0] =  cos;
    matrix[2] = -sin;
    matrix[8] =  sin;
    matrix[10] = cos;
}

//------------------------------------------------------------
inline void
setRotationZ(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[0] =  cos;
    matrix[1] =  sin;
    matrix[4] = -sin;
    matrix[5] =  cos;
}

//------------------------------------------------------------
inline void 
setScale(Mat4f & matrix, Vec3 const & scale) {
    matrix[0]  = scale.x;
    matrix[5]  = scale.y;
    matrix[10] = scale.z;
}

//------------------------------------------------------------
inline void
perspectiveDivide(Vec4 & vec) {
    vec.x /= vec.w;
    vec.y /= vec.w;
    vec.z /= vec.w;
    //vec.w /= vec.w; // don't include w because we need the info retained for perspective texture mapping
}

} /* namespace Maths */