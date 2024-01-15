# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-src"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-build"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/tmp"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/src/physx-populate-stamp"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/src"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/src/physx-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/src/physx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/physx-subbuild/physx-populate-prefix/src/physx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
