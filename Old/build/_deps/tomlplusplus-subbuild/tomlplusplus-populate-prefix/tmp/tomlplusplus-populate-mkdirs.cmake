# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-src"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-build"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/tmp"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/src/tomlplusplus-populate-stamp"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/src"
  "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/src/tomlplusplus-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/src/tomlplusplus-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/HP/Documents/GitHub/Minero-Game/build/_deps/tomlplusplus-subbuild/tomlplusplus-populate-prefix/src/tomlplusplus-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
