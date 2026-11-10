#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class GLcamera{
    public:
        
        // virtual void generateRay(int width, int height, Ray& cRay) = 0;
        // virtual void generateRay(int width, int height, Ray& cRay, double offsetX, double offsetY) = 0;
    
    protected:
        glm::vec3 m_pos, m_U, m_V, m_W;
        double m_focalLength, m_planeWidth;
        int m_width, m_height;
        float m_far, m_near;
        double leftBound, rightBound, topBound, bottomBound;
};



#endif