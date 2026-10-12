find_package(OpenMP REQUIRED)

add_library(renderLib
  vec3.cpp
  color.cpp
  framebuffer.cpp
  framebuffer.h
  Light/light.cpp
  color.h
  vec3.h
  ray.h
  Camera/camera.cpp
  Camera/camera.h
  Camera/perspective_camera.cpp
  Camera/perspective_camera.h
  Shape/sphere.cpp
  Shape/sphere.h
  Shape/shape.cpp
  Shape/scene.cpp
  Shape/shape.h
  Shape/triangle.h
  Shape/triangle.cpp
  Shape/scene.h
  Shader/shader.cpp
  Shader/lambertian_shader.cpp
  Shader/blinnphong_shader.cpp
  Shader/normal_shader.cpp
  Shader/shader.h
  Shader/lambertian_shader.h
  Light/light.h
  Shader/blinnphong_shader.h
  Shader/normal_shader.h
)

target_include_directories(renderLib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(renderLib PUBLIC PNG::PNG)

if(OpenMP_CXX_FOUND)
  target_link_libraries(renderLib PUBLIC OpenMP::OpenMP_CXX)
endif()