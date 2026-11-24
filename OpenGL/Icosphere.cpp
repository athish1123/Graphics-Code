#include "Icosphere.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include "glm/glm.hpp"

namespace
{
struct Face
{
    GLuint a;
    GLuint b;
    GLuint c;
};

std::uint64_t edgeKey(GLuint a, GLuint b)
{
    const GLuint low = a < b ? a : b;
    const GLuint high = a < b ? b : a;
    return (static_cast<std::uint64_t>(low) << 32) | high;
}
}

Icosphere::Icosphere(unsigned int subdivisions, float radius)
{
    constexpr unsigned int maxSubdivisions = 6;
    if (subdivisions > maxSubdivisions) {
        throw std::invalid_argument("Icosphere subdivisions must not exceed 6");
    }
    if (!std::isfinite(radius) || radius <= 0.0f) {
        throw std::invalid_argument("Icosphere radius must be finite and positive");
    }

    const float goldenRatio = (1.0f + std::sqrt(5.0f)) * 0.5f;
    std::vector<glm::vec3> positions{
        {-1.0f, goldenRatio, 0.0f}, {1.0f, goldenRatio, 0.0f},
        {-1.0f, -goldenRatio, 0.0f}, {1.0f, -goldenRatio, 0.0f},
        {0.0f, -1.0f, goldenRatio}, {0.0f, 1.0f, goldenRatio},
        {0.0f, -1.0f, -goldenRatio}, {0.0f, 1.0f, -goldenRatio},
        {goldenRatio, 0.0f, -1.0f}, {goldenRatio, 0.0f, 1.0f},
        {-goldenRatio, 0.0f, -1.0f}, {-goldenRatio, 0.0f, 1.0f}
    };

    std::vector<Face> faces{
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    for (glm::vec3& position : positions) {
        position = glm::normalize(position);
    }

    for (unsigned int level = 0; level < subdivisions; ++level) {
        std::unordered_map<std::uint64_t, GLuint> midpointCache;
        std::vector<Face> refinedFaces;
        refinedFaces.reserve(faces.size() * 4);

        const auto midpoint = [&positions, &midpointCache](GLuint a, GLuint b) {
            const std::uint64_t key = edgeKey(a, b);
            const auto found = midpointCache.find(key);
            if (found != midpointCache.end()) {
                return found->second;
            }

            const GLuint index = static_cast<GLuint>(positions.size());
            positions.push_back(glm::normalize((positions[a] + positions[b]) * 0.5f));
            midpointCache.emplace(key, index);
            return index;
        };

        for (const Face& face : faces) {
            const GLuint ab = midpoint(face.a, face.b);
            const GLuint bc = midpoint(face.b, face.c);
            const GLuint ca = midpoint(face.c, face.a);
            refinedFaces.push_back({face.a, ab, ca});
            refinedFaces.push_back({face.b, bc, ab});
            refinedFaces.push_back({face.c, ca, bc});
            refinedFaces.push_back({ab, bc, ca});
        }
        faces = std::move(refinedFaces);
    }

    std::vector<GLfloat> vertexData;
    vertexData.reserve(positions.size() * 6);
    for (const glm::vec3& normal : positions) {
        const glm::vec3 position = normal * radius;
        vertexData.insert(vertexData.end(), {
            position.x, position.y, position.z,
            normal.x, normal.y, normal.z
        });
    }

    std::vector<GLuint> indices;
    indices.reserve(faces.size() * 3);
    for (const Face& face : faces) {
        indices.insert(indices.end(), {face.a, face.b, face.c});
    }
    indexCount_ = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &vertexArray_);
    glGenBuffers(1, &vertexBuffer_);
    glGenBuffers(1, &indexBuffer_);

    glBindVertexArray(vertexArray_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexData.size() * sizeof(GLfloat)),
        vertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)),
        indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
        reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glBindVertexArray(0);
}

Icosphere::~Icosphere()
{
    glDeleteBuffers(1, &indexBuffer_);
    glDeleteBuffers(1, &vertexBuffer_);
    glDeleteVertexArrays(1, &vertexArray_);
}

void Icosphere::draw() const
{
    glBindVertexArray(vertexArray_);
    glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
