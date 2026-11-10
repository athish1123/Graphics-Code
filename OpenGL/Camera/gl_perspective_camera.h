#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "gl_camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class GLperspectiveCamera : public GLcamera {
    public:
        // PerspectiveCamera() : imageWidth(0), imageHeight(0) {};
        GLperspectiveCamera(glm::vec3 cameraOrigin, glm::vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height, float near = 0.1f, float far = 100.0f);

        // void generateRay(int width, int height, Ray& cRay) override;
        // void generateRay(int width, int height, Ray& cRay, double offsetX, double offsetY) override;

        glm::mat4 getViewMatrix() const { return glm::lookAt(m_pos, m_pos - m_W, m_V); }

        glm::mat4 getProjectionMatrix();

        void moveForward(float d);
        void moveBackward(float d);
        void moveLeft(float d);
        void moveRight(float d);

        private:
            
};
        

#endif