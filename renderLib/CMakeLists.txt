add_library(renderLib
  framebuffer.cpp
  framebuffer.h
  color.h
  vec3.h
  ray.h
  Camera/camera.cpp
  Camera/camera.h
  Camera/perspective_camera.cpp
  Camera/perspective_camera.h
  Shape/sphere.cpp
  Shape/sphere.h
  Shape/hittable.h
  Shape/triangle.h
  Shape/triangle.cpp
  Shape/hittable_list.h
  Shader/shader.h
  Shader/lambertian_shader.h
  Light/point_light.h
)

target_include_directories(renderLib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(renderLib PUBLIC PNG::PNG)