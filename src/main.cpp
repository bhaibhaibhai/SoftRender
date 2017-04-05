// std
#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// dependancies
#include "SDL.h"

// my
#include "Window.hpp"
#include "RenderContext.hpp"
#include "StarField.hpp"
#include "Input.hpp"
#include "Maths/Maths.hpp"
#include "Vertex.hpp"
#include "Camera.hpp"

//------------------------------------------------------------
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

//------------------------------------------------------------
std::vector<Mesh> 
loadDannyFile(std::string const & filePath) {
    std::vector<Mesh> meshes;

    std::ifstream file(filePath);

    auto stringToVec = [](std::string const & string) -> std::vector<std::string> {
        std::stringstream ss(string);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        return vstrings;
    };

    if(file.is_open()) {
        std::string line; 
        std::vector<std::string> splitLine;

        std::getline(file, line); // get the first line containing the mesh count

        splitLine = stringToVec(line); // will only contain two entries "meshCount: " + numberOfMeshes
        
        const int meshCount = std::stoi(splitLine[1]);

        int currentLineNumber = 1 + meshCount;

        struct MeshSize {
            int numVertices;
            int numIndices;
        };

        std::vector<MeshSize> meshSizes; 
        meshSizes.resize(meshCount);

        for(int currMesh = 0; currMesh < meshCount; currMesh++) {
            std::getline(file, line);
            splitLine = stringToVec(line);

            int numVertices = std::stoi(splitLine[1]);
            int numIndices  = std::stoi(splitLine[2]);

            meshSizes[currMesh].numVertices = numVertices;
            meshSizes[currMesh].numIndices = numIndices;
            
            std::cout << numVertices << " " << numIndices << std::endl;

        }
       
        std::cout << meshCount << std::endl;

       // int meshOneEndLine = currentLineNumber
       for(int i = 0; i < meshSizes.size(); i++) {
            Mesh mesh;
             

            int loopEnd = currentLineNumber + meshSizes[i].numVertices;

            // extract vertices
            for(int j = currentLineNumber; j < loopEnd; j++) {
                std::getline(file, line);
                splitLine = stringToVec(line);
                
                // extract position
                Maths::Vec3 position;
                position.x = std::stof(splitLine[0]);
                position.y = std::stof(splitLine[1]);
                position.z = std::stof(splitLine[2]);

                // extract texture coordinates
                Maths::Vec2 texcoord;
                texcoord.x = std::stof(splitLine[3]);
                texcoord.y = std::stof(splitLine[4]);

                // extract colours
                Maths::Vec3 colour;
                colour.x = std::stof(splitLine[5]);
                colour.y = std::stof(splitLine[6]);
                colour.z = std::stof(splitLine[7]);

                Vertex v(position, texcoord, colour);

                mesh.vertices.push_back(v);
            }

            currentLineNumber = loopEnd;
            loopEnd += meshSizes[i].numIndices;

            // extract indices
            for(int j = currentLineNumber; j < loopEnd; j++) {
                std::getline(file, line);
                splitLine = stringToVec(line);
                mesh.indices.push_back(std::stoi(splitLine[0]));
            }
            currentLineNumber = loopEnd;

            meshes.push_back(mesh);
          
       }

        return meshes;

    } else {
        std::cerr << "file was not opened" << std::endl;
        return meshes;
    }
}

//------------------------------------------------------------
int main(int argc, char* argv[]) {
    
    // using
    using clock = std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using FpMilliseconds  = duration<float, milliseconds::period>;
    //..

    // window spec
    bool vSync = false;
    bool fullScreen = false;
    int width = 900;
    int height = width / 16 * 10;
    float bufferScale = 2.0f; // size of the framebuffer compared to the screen width & height
    Window window("SoftRender", -1, -1, width, height, bufferScale, vSync, fullScreen);
    
    //..

    Maths::Mat4f mat4_rot = Maths::createRotationMatrix(Maths::Vec3(1.0f));
    std::cout << "mat4 rot: " << mat4_rot << std::endl;


    /// MATRIX 3 TESTS ////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Maths::Mat3<float> mat_default;
    
    Maths::Mat3<float> mat_rot = Maths::createMat3RotationMatrix<float>(Maths::Vec3(1.0f));

    Maths::Mat3<float> mat_identity =  Maths::createMat3IdentityMatrix<float>();

    Maths::Mat3<float> mat_times_test =  mat_identity * mat_rot;

    std::cout << "default: " << mat_default << std::endl;
    std::cout << "rot: " << mat_rot << std::endl;

    std::cout << "times: " << mat_identity * mat_identity << std::endl;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    Input input; // subject
    Camera camera(70.0f, 0.001f, 1000.0f, (float) width / (float) height); // observer
    input.attachObserver(camera);

    RenderContext & rContext = window.getRenderContext();
    StarField starField(rContext, 0.00001f, 0.1);

    Bitmap randomBitmap = createRandomBitmap(100, 100);

    //  tree loaded from danny file
    std::vector<Mesh> tree = loadDannyFile("../../res/head.danny");

    std::cout << "size: " << tree.size() << std::endl;
    
    // game loop vars
    auto frames = 0;
    auto begin = clock::now();
    auto second = clock::now();
    //..

    float x = 0.0f;
    float y =  0.0f;
    float z =  -3.0f;

    float movementSpeed = 0.0005f;

    // matricies
    Maths::Mat4f translation = Maths::createTranslationMatrix(Maths::Vec3(x, y, z)); 
    Maths::Mat4f rotation    = Maths::createRotationMatrix(Maths::Vec3(0.0f));
    Maths::Mat4f scale       = Maths::createScaleMatrix(Maths::Vec3(1));
    Maths::Mat4f proj        = Maths::createProjectionMatrix(Maths::toRadians(70.0f), 0.01f, 1000.0f, (float)width / (float)height);
    //..

    // incrementers
    float rot = 0.0f;
    //..

    while(true) {
        if(!input.update()) break;
        frames++;

        auto current = clock::now();
        float delta = FpMilliseconds(current - begin).count();
        begin = clock::now();

        // update
        starField.update(delta);
        rotation = Maths::createRotationMatrix(Maths::Vec3(0, rot, 0));
        rot += movementSpeed * delta;

        if(input.isLeftDown()) {
            x-= movementSpeed * delta;
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, y, z)); 
        } else if(input.isRightDown()) {
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, y, z)); 
            x+= movementSpeed  * delta;
        } else if(input.isUpDown()) {
            z += movementSpeed  * delta;
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, y, z)); 
        } else if(input.isDownDown()) {
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, y, z)); 
            z -= movementSpeed * delta;
        }

        Maths::Mat4f model = proj * translation * rotation * scale;
        //..
        

        // every second call this
        if(duration_cast<milliseconds>(current - second) > milliseconds(1000)) {
            std::cout << "FPS: " << frames << "\n";
            std::cout << delta << std::endl;
            frames = 0;
            second = current; 
        }

        // render
        window.clear();
        rContext.clearDepthBuffer();
        {
            //starField.render();
          //  rContext.drawMesh(pyramidNo, model, randomBitmap);
            //rContext.drawMesh(pyramid, model, randomBitmap);

        for(auto i = 0; i < tree.size(); i++) {
            rContext.drawIndexedMesh(tree[i].vertices, tree[i].indices, model, randomBitmap);
        }
            
            //rContext.drawMesh(cube, cubeIndices, model, randomBitmap);

        }
        window.swapBackBuffer();
    }
    return 0;
}