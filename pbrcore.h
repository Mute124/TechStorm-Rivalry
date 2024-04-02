/***********************************************************************************
*
*   rPBR [core] - Physically Based Rendering 3D drawing functions for raylib
*
*   FEATURES:
*       - Phyiscally based rendering for any 3D model.
*       - Metalness/Roughness PBR workflow.
*       - Split-Sum Approximation for specular reflection calculations.
*       - Support for normal mapping, parallax mapping and emission mapping.
*       - Simple and easy-to-use implementation code.
*       - Multi-material scene supported.
*       - Point and directional lights supported.
*       - Internal shader values and locations points handled automatically.
*
*   NOTES:
*       Physically based rendering shaders paths are set up by default
*       Remember to call UnloadMaterialPBR and UnloadEnvironment to deallocate required memory and unload textures
*       Physically based rendering requires OpenGL 3.3 or ES2
*
*   DEPENDENCIES:
*       stb_image (Sean Barret) for images loading (JPEG, PNG, BMP, HDR)
*       GLAD for OpenGL extensions loading (3.3 Core profile)
*
*   LICENSE: zlib/libpng
*
*   rPBR is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 2017-2020 Victor Fisac
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
***********************************************************************************/

//----------------------------------------------------------------------------------
// Includesf
//----------------------------------------------------------------------------------
#include <math.h>                           // Required for: powf()
#include <raylib.h>
#include "raymath.h"    // Required for matrix, vectors and other math functions


#include "glad/glad.h"                  // Required for OpenGL API

