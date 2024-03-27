# CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Intro2Cmake C CXX)

# add_subdirectory 用于编译子目录。 在子目录中编写CMakeLists.txt,然后
# 在顶层CMakeLists.txt中将该子目录加入编译。 
# add_subdirectory(source_dir [binary_dir] [EXECLUDE_FROM_ALL] [SYSTEM])
add_subdirectory(util)
add_subdirectory(base)

add_executable(app main.cpp)
target_link_libraries(app base util)
target_include_directories(app 
                        PRIVATE ${PROJECT_SOURCE_DIR}/base)


# add_custom_target 用于添加一个target,执行某些命令
#  add_custom_target(Name [ALL] [command1 [args1...]]
#                       [COMMAND command2 [args2...]]
#                       [DEPENDS depend depend depend...]
#                       [WORKING_DIRECTORY dir]
#                       [JOB_POOL job_pool]
#                       [JOB_SERVER_AWARE <boo>]
#                       [VERBATIM] [USES_TERMINAL]
#                       [COMMAND_EXPAND_LISTS]
#                       [SOURCES src1 [src2...]])

