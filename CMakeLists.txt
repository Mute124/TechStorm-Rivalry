cmake_minimum_required(VERSION 3.25) # FetchContent is available in 3.11+
project(Minero)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()
# Registers build options that are exposed to cmake
include(CMakeOptions.txt)

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)


include(FetchContent)

# Include PhysX
FetchContent_Declare(
        PhysX
        GIT_REPOSITORY "https://github.com/NVIDIA-Omniverse/PhysX"
        GIT_TAG        105.1-physx-5.3.1
)
FetchContent_MakeAvailable(PhysX)



option(PHYSX_BUILD_TYPE "The build type of PhysX, i.e., one of {debug, checked, profile, release}" "checked")

include_directories(PhysX/include)

if(CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building snippet in debug configuration")
    add_compile_definitions(_DEBUG)
    link_directories("PhysX/bin/linux.clang/debug") # This is the path where PhysX libraries are installed
else()
    message("Building snippet in release configuration with PhysX ${PHYSX_BUILD_TYPE} configuration")
    add_compile_definitions(NDEBUG)
    link_directories("PhysX/bin/linux.clang/${PHYSX_BUILD_TYPE}") # This is the path where PhysX libraries are installed
endif()

add_executable(Snippet
    main.cpp
)

target_link_libraries(Snippet
    PhysXExtensions_static_64
    PhysX_static_64
    PhysXPvdSDK_static_64
    PhysXCommon_static_64
    PhysXFoundation_static_64

    pthread
    dl
)

add_executable(${PROJECT_NAME} main.cpp)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)



# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

