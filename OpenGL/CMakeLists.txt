include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
  Camera/gl_perspective_camera.cpp
  Camera/gl_perspective_camera.h
  Camera/gl_camera.h
)

target_include_directories(glfwExample PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Camera"
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

add_custom_command(TARGET glfwExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:glfwExample>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader/vertexShader_passthrough.glsl"
        "$<TARGET_FILE_DIR:glfwExample>/vertexShader_passthrough.glsl"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader/fragmentShader_passthrough.glsl"
        "$<TARGET_FILE_DIR:glfwExample>/fragmentShader_passthrough.glsl"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Shader/vertexShader_withMatrixTransformation.glsl"
        "$<TARGET_FILE_DIR:glfwExample>/vertexShader_withMatrixTransformation.glsl"
)

set_property(TARGET glfwExample PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:glfwExample>"
)
