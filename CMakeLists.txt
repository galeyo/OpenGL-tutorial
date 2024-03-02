cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(OpenGL-tutorial)

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add all Header Files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Find glfw
find_package(glfw3)

# Include GLAD
set(GLAD_ROOT_DIR external/glad)
add_subdirectory(${GLAD_ROOT_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_ROOT_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${GLAD_ROOT_DIR}/src)


target_link_libraries(${PROJECT_NAME} glfw glad)
