#pragma once

#include <GL/glew.h>

class Icosphere
{
public:
    explicit Icosphere(unsigned int subdivisions, float radius = 1.0f);
    ~Icosphere();

    Icosphere(const Icosphere&) = delete;
    Icosphere& operator=(const Icosphere&) = delete;

    void draw() const;

private:
    GLuint vertexArray_ = 0;
    GLuint vertexBuffer_ = 0;
    GLuint indexBuffer_ = 0;
    GLsizei indexCount_ = 0;
};
