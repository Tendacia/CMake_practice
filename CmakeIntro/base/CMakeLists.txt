# base/CMakeLists.txt

add_library(base SHARED base.cpp)
target_include_directories(base 
                        PUBLIC ${PROJECT_SOURCE_DIR}/util)