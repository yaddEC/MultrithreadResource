#include <Log.h>

#include <Model.h>

#include <App.h>

#include <sstream>

using namespace Core::Maths;
using namespace Core::Debug;
using namespace std;
using namespace Resources;

void Model::Print() {
    Log log;
    log.Print("number of vertices = %i\n", vertices.size());
    log.Print("Position :\n");
    for (int i = 0; i < vertices.size(); i++)
        vertices.at(i).position.Print();
    log.Print("Normal :\n");
    for (int i = 0; i < vertices.size(); i++)
        vertices.at(i).normal.Print();
    log.Print("TextureUV :\n");
    for (int i = 0; i < vertices.size(); i++)
        vertices.at(i).textureUV.Print();

}

void Model::Load(const std::string& path) {

    Log log;
    log.Print("Opening %s ...\n", const_cast <char*> (path.c_str()));

    ifstream file(path);
    ASSERT(file.is_open(), "ERROR: Cannot open the file");

    log.Print("Opened\n");
    vector < unsigned int > indexVertex, indexNormal , indexUV;
    vector <Vec3> tempVertex,tempNormals;
    vector <Vec2> tempUV;
    GLint tempGLint;
    string lineHeader,prefix;
    stringstream ss;


    log.Print("Loading %s ... \n", const_cast <char*> (path.c_str()));
    while (getline(file, lineHeader))
    {
        ss.clear();
        ss.str(lineHeader);
        ss >> prefix;

        if (prefix == "v") 
        {
            Vec3 vertex;
            ss >> vertex.x;
            ss >> vertex.y;
            ss >> vertex.z;
            tempVertex.push_back(vertex);
        }
        else if (prefix == "vt")
        {
            Vec2 uv;
            ss >> uv.x;
            ss >> uv.y;
            tempUV.push_back(uv);
        }
        else if (prefix == "vn") 
        {
            Vec3 normal;
            ss >> normal.x;
            ss >> normal.y;
            ss >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (prefix == "f")
        {
            int counter = 0;
            while (ss >> tempGLint) 
            {
                if (counter == 0)
                    indexVertex.push_back(tempGLint);
                else if (counter == 1)
                    indexUV.push_back(tempGLint);
                else if (counter == 2)
                    indexNormal.push_back(tempGLint);

                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                if (counter > 2)
                    counter = 0;
            }
        }
    }

    vertices.resize(indexVertex.size(), Vertex());

    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].position = tempVertex[indexVertex[i] - 1];
        vertices[i].textureUV = tempUV[indexUV[i] - 1];
        vertices[i].normal = tempNormals[indexNormal[i] - 1];
    }
    log.Print("Loaded \n");

}