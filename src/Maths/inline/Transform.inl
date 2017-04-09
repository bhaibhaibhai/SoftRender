namespace djc_math {

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
createMat3RotationMatrix(Vec3<T> const & rotation) {

    T xSin = std::sin(rotation.x);
    T xCos = std::cos(rotation.x);

    T ySin = std::sin(rotation.y);
    T yCos = std::cos(rotation.y);

    T zSin = std::sin(rotation.z);
    T zCos = std::cos(rotation.z);
    
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
createMat4TranslationMatrix(Vec3<T> const & vec) {
    return Mat4<T>(std::array<T, 16>{{
            1,     0,     0,    0,
            0,     1,     0,    0,
            0,     0,     1,    0,
        vec.x, vec.y, vec.z,    1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4RotationMatrix(Vec3<T> const & rotation) {
    T xSin = std::sin(rotation.x);
    T xCos = std::cos(rotation.x);

    T ySin = std::sin(rotation.y);
    T yCos = std::cos(rotation.y);

    T zSin = std::sin(rotation.z);
    T zCos = std::cos(rotation.z);

    // perf : change this to Mat3 then put into Mat4 on return

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
createMat4ScaleMatrix(Vec3<T> const & vec) {
     return Mat4<T>(std::array<T, 16>{{
        vec.x,     0,     0, 0,
            0, vec.y,     0, 0,
            0,     0, vec.z, 0,
            0,     0,     0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ModelMatrix(Vec3<T> const & position, Vec3<T> const & rotation, Vec3<T> const & scale) {
    Mat4<T> _translation = createMat4TranslationMatrix<T>(position);
    Mat4<T> _rotation    = createMat4RotationMatrix<T>(rotation);
    Mat4<T> _scale       = createMat4ScaleMatrix<T>(scale);

    return _translation * _rotation * _scale;
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ProjectionMatrix(T fov, T near, T far, T aspect) {
    T range = std::tan(fov / 2.0f) * near;
    T Sx    = (2 * near) / (range * aspect + range * aspect);
    T Sy    = near / range;
    T Sz    = -(far + near) / (far - near);
    T Pz    = -(2 * far * near) / (far - near);

    return Mat4<T>(std::array<T, 16>{{
        Sx, 0,  0,  0,
        0, Sy,  0,  0,
        0,  0, Sz, -1,
        0,  0, Pz,  0
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4<T>
createMat4ScreenSpaceTransform(T halfWidth, T halfHeight) {
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

//-------------------//
/*      Other        */
//-------------------//

//------------------------------------------------------------
template<typename T> inline Mat4<T>
rotate(T angle, Vec3<T> axis) {
    return createMat4RotationMatrix<T>(axis + angle);
}

} /* namespace djc_math */