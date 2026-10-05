add_library (cs4212-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
)
target_compile_definitions(cs4212-util PUBLIC HAS_GLM)
target_link_libraries(cs4212-util PRIVATE Boost::program_options)
target_link_libraries(cs4212-util PUBLIC glm::glm)

# add_executable(mainCode
#   mainCode.cpp
# )


# target_link_libraries(mainCode PRIVATE cs4212-util)
# target_link_libraries(mainCode PRIVATE renderLib)
# target_link_libraries(mainCode PRIVATE ${Boost_PROGRAM_OPTIONS_LIBRARIES})
# target_link_libraries(mainCode PRIVATE PNG::PNG)
# target_link_libraries(mainCode PRIVATE ZLIB::ZLIB)

# add_executable(sphereTest 
#   sphereTest.cpp
# )

# target_link_libraries(sphereTest PRIVATE cs4212-util)
# target_link_libraries(sphereTest PRIVATE renderLib)
# target_link_libraries(sphereTest PRIVATE ${Boost_PROGRAM_OPTIONS_LIBRARIES})
# target_link_libraries(sphereTest PRIVATE PNG::PNG)
# target_link_libraries(sphereTest PRIVATE ZLIB::ZLIB)

add_executable(lambertianShaderTest
  lambertianShaderTest.cpp
)

target_link_libraries(lambertianShaderTest PRIVATE cs4212-util)
target_link_libraries(lambertianShaderTest PRIVATE renderLib)
target_link_libraries(lambertianShaderTest PRIVATE ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(lambertianShaderTest PRIVATE PNG::PNG)
target_link_libraries(lambertianShaderTest PRIVATE ZLIB::ZLIB)