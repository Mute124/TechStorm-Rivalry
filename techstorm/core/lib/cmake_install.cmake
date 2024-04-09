# Install script for directory: C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/AudioDevice.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/AudioStream.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/AutomationEventList.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/BoundingBox.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Camera2D.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Camera3D.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Color.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Font.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Functions.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Gamepad.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Image.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Material.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Matrix.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Mesh.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Model.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/ModelAnimation.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Mouse.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Music.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Ray.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/RayCollision.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/RaylibException.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/raylib-cpp-utils.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/raylib-cpp.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/raylib.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/raymath.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Rectangle.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/RenderTexture.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Shader.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Sound.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Text.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Texture.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/TextureUnmanaged.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Touch.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Vector2.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Vector3.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Vector4.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/VrStereoConfig.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Wave.hpp"
    "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/Window.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/HP/source/repos/TechStorm-Rivalry/techstorm/core/lib/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
