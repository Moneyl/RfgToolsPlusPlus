
cmake_minimum_required (VERSION 3.8)
project (TestApp VERSION 1.0.0
                  DESCRIPTION "TestApp"
                  LANGUAGES CXX)

# Get list of source files in project src folders recursively
# Places in SOURCES variable
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Add source to this project's executable.
add_executable (TestApp ${SOURCES})

# Add include directories
target_include_directories(TestApp SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/
    ${CMAKE_CURRENT_SOURCE_DIR}/../RfgTools++/
    ${CMAKE_CURRENT_SOURCE_DIR}/../RfgTools++/RfgTools++/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/zlib/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/BinaryTools/ # TODO: Hook this up as a static lib once it's got a CMakeLists.txt
)

# Add statically linked libs
target_link_libraries(TestApp PRIVATE Common)
target_link_libraries(TestApp PRIVATE RfgTools++)