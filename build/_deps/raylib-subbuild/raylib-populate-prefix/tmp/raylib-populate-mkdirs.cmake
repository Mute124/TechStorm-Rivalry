# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-src"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-build"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/build/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
