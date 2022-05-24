
#include <Model.h>


using namespace Core::Maths;
using namespace Core::Debug;
using namespace std;
using namespace Resources;

#define GLEW_STATIC



void VertexAttributes::Load(vector <Vertex> vertices, vector <uint32_t> indexes, Buffer vbo, Buffer ebo) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo.buffer);
    glGenBuffers(1, &ebo.buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo.buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indexes.size(), indexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
   

}

VertexAttributes::VertexAttributes() {}

VertexAttributes::~VertexAttributes() {
    glDeleteVertexArrays(1, &vao);
}

void VertexAttributes::bind() {
    glBindVertexArray(vao);
}

void VertexAttributes::unbind() {
    glBindVertexArray(0);
}

Buffer::Buffer(const void* data, unsigned int size) {
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Buffer::Buffer() {}

Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer);
}

void Buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void Buffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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
    indexes.resize(indexVertex.size());

    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].position = tempVertex[indexVertex[i] - 1];
        vertices[i].textureUV = tempUV[indexUV[i] - 1];
        vertices[i].normal = tempNormals[indexNormal[i] - 1];
        indexes[i] = i;
    }
    log.Print("Loaded \n");

    vao.Load(vertices,indexes,vbo,ebo);

}