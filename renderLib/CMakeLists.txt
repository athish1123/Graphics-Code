add_library(renderlib
  framebuffer.cpp
  framebuffer.h
  color.h
  vec3.h
  ray.h
)

target_include_directories(renderlib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(renderlib PUBLIC PNG::PNG)