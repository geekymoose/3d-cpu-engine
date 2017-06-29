file(GLOB srcFiles *.cpp)
add_executable(3d-soft-engine ${srcFiles})
add_custom_target(runengine 3d-soft-engine)
