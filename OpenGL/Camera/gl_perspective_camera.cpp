#define _USE_MATH_DEFINES

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl_perspective_camera.h"

GLperspectiveCamera::GLperspectiveCamera(glm::vec3 cameraOrigin, glm::vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height, float near, float far)
{
    m_pos = cameraOrigin;
    m_focalLength = focalLength;
    m_planeWidth = imagePlaneWidth;
    m_width = width;
    m_height = height;
    m_far = far;
    m_near = near;

    m_W = -glm::normalize(cameraViewDir);
    m_U = glm::normalize(glm::cross(glm::vec3(0,1,0), m_W));
    m_V = glm::cross(m_W, m_U);

}

glm::mat4 GLperspectiveCamera::getProjectionMatrix()
{
    float aspect = m_width / (float)m_height;
    float planeHeight = m_planeWidth / aspect;
    float fov = 2.0f * atan((planeHeight / 2.0f) / static_cast<float>(m_focalLength));
    return glm::perspective(fov, aspect, m_near, m_far);
}

void GLperspectiveCamera::moveForward(float d)
{
    m_pos = m_pos + -m_W * d;
}

void GLperspectiveCamera::moveBackward(float d)
{
    m_pos = m_pos + m_W * d;
}

void GLperspectiveCamera::moveLeft(float d)
{
    m_pos = m_pos + -m_U * d;
}

void GLperspectiveCamera::moveRight(float d)
{
     m_pos = m_pos + m_U * d;
}
