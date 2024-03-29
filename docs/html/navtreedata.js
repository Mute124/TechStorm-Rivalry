/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "TechStorm-Rivalry", "index.html", [
    [ "Getting Started", "md_techstorm_2lib_2_r_e_a_d_m_e.html", null ],
    [ "rres design concerns", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html", [
      [ "1. File Structure Concerns", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md2", [
        [ "Input file processing or packaging only", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md3", null ],
        [ "Multi-chunk resources", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md4", null ],
        [ "Resource identifiers", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md5", null ],
        [ "Resource chunks padding", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md6", null ],
        [ "Filename memory alignment in <tt>CDIR</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md7", null ],
        [ "Compression/Encryption support", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md8", null ]
      ] ],
      [ "2. Data Types Concerns", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md9", [
        [ "Raw data resources", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md10", null ],
        [ "Externally linked files", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md11", null ],
        [ "External resource chunk data", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md12", null ],
        [ "External central directory resource", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md13", null ],
        [ "End-Of-File resource chunk", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md14", null ],
        [ "Code file resources", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md15", null ],
        [ "Zero-terminated <tt>TEXT</tt> resources", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md16", null ]
      ] ],
      [ "3. Implementation Concerns", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md17", [
        [ "Make rres file-format engine-agnostic", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md18", null ],
        [ "Compression/Encryption support", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md19", null ],
        [ "Expose rres structures directly to the user", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md20", null ]
      ] ],
      [ "4. Future Concerns / Improvements", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md21", [
        [ "Multi-chunk resources", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md22", null ],
        [ "Number of data properties", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2design_2_r_e_a_d_m_e.html#autotoc_md23", null ]
      ] ]
    ] ],
    [ "rres CMake Definitions", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2projects_2_c_make_2_r_e_a_d_m_e.html", [
      [ "Usage", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2projects_2_c_make_2_r_e_a_d_m_e.html#autotoc_md25", null ]
    ] ],
    [ "README", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html", [
      [ "Index", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md26", [
        [ "Design Goals", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md28", null ],
        [ "Usage Benefits", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md29", null ],
        [ "Design History", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md30", null ],
        [ "File Structure", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md31", null ],
        [ "File Header: <tt>rresFileHeader</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md32", null ],
        [ "Resource Chunk: <tt>rresResourceChunk</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md33", [
          [ "Resource Chunk Info: <tt>rresResourceChunkInfo</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md34", null ],
          [ "Resource Chunk Data: <tt>rresResourceChunkData</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md35", null ],
          [ "Resource Data Type: <tt>rresResourceDataType</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md36", null ],
          [ "Resource Chunk: Central Directory: <tt>rresCentralDir</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md37", null ]
        ] ],
        [ "Custom Engine Implementation", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md38", [
          [ "Base library: <tt>rres.h</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md39", null ],
          [ "Engine mapping library: <tt>rres-raylib.h</tt>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md40", null ],
          [ "Packaging tool: <a href=\"https://raylibtech.itch.io/rrespacker\" ><tt>rrespacker</tt></a>", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md41", null ]
        ] ],
        [ "Versions", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md42", null ],
        [ "License", "md_techstorm_2lib_2rres-1_82_80_2rres-1_82_80_2_r_e_a_d_m_e.html#autotoc_md43", null ]
      ] ]
    ] ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", "namespacemembers_dup" ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", "namespacemembers_eval" ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Related Symbols", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", "globals_vars" ],
        [ "Typedefs", "globals_type.html", "globals_type" ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", "globals_eval" ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_a_d_s_renvelope_8hpp.html",
"_e_f_x-_util_8h.html#a1cb7b134e89e68568a07eaae4c0c1ab3",
"_framework_8cpp.html#a1b0509366c2b0683ce7cf4a177094ad0",
"_load_o_a_l_8h.html#a7ceb66d27922321b03fe7399cbbb0253",
"al_8h.html#a462b184a52d71fc1a42d1e7118f78d47",
"channel_interface_8hpp.html#a4f08b1d9e49e990c1366ed7cce69acae",
"class_display.html#ac0deb8090688e525374663ccb140ac68",
"class_object_layer_pair_filter_impl.html#afd7e357870f8e60ff900decf5a02903b",
"class_tech_storm_1_1_application.html#a6119ca1c4e05e1039817bd5514c48dbb",
"class_tech_storm_1_1_game_object_material.html#aea6812e95cd8a2cc016423774af2445b",
"class_tech_storm_1_1_u_i_element.html#a78ecc468cffb6daa118d2ac2d9d3400a",
"class_tech_storm_1_1abstract.html#ad1187e842989f93c2b71f18007829580",
"class_tech_storm_rivalry_1_1_console_1_1_console_u_i.html#a0299650fa562ac148c2f4b4f850a44de",
"class_tech_storm_rivalry_1_1_main_menu_1_1_main_menu_background.html#a896244fee26e13f44903186bb0d8363b",
"class_tech_storm_rivalry_1_1_player_1_1_player_controller.html#a743553a735450bae9b7ca35aa7f1fba2",
"class_u_i_affliction_container.html#a8eeda89c1b3a8b24593c412ce73f3ab5",
"class_y_s_e_1_1_d_e_v_i_c_e_1_1interface_object.html#affdf8b63ba22cef1babae3a2c8838ed6",
"class_y_s_e_1_1_d_s_p_1_1_m_o_d_u_l_e_s_1_1granulator.html#ae0faa39dfcce0e64b3a6f1414a941970",
"class_y_s_e_1_1_d_s_p_1_1_m_o_d_u_l_e_s_1_1phaser.html#a57c94b665614122b3bf9d4206b4f13f9",
"class_y_s_e_1_1_d_s_p_1_1complex_one_zero.html#a1ac144400c0662cecac8c73897c721d9",
"class_y_s_e_1_1_d_s_p_1_1filter_base.html#a17eff66b7fcbfb1c2853bb4a31e7eea3",
"class_y_s_e_1_1_d_s_p_1_1ramp.html#aa3d3506a2af50ae5c151cd70c635ab88",
"class_y_s_e_1_1_m_o_t_i_f_1_1interface_object.html#a31ffdf21f434bc9bcfafd7d77495f78f",
"class_y_s_e_1_1_p_l_a_y_e_r_1_1interface_object.html#a81d90a0d70590026e447a74bac7f655f",
"class_y_s_e_1_1_s_y_n_t_h_1_1interface_object.html#a76ba2bc552f6e1373d6494cbb4bc7684",
"class_y_s_e_1_1system.html#a413e0b6ad0606e91978fa79847b8e938",
"classarray.html#a63e8132f3b5cad45f09e8afcd4f037d1",
"classtable.html#a6248c10022c6cd670f045cda74cb1cbe",
"core_2ecs_2_e_c_s_man_8h_source.html",
"core_2ui_2_e_u_i_types_8h.html",
"efx-creative_8h.html#a17f5778f98e0cf57a18dbacb905a3f1c",
"efx_8h.html#a6164526bac8e63f711f4aabe3f80c4ea",
"efx_8h.html#afcd72812259aba5a9b93505944007a8c",
"engine_2rendering_2_defered_renderer_8h.html#a4d88670e3f0c9cd1b1ded7bf0dc72a52ae6eec34f7e3859ce6cee28ecee25fd7a",
"enums_8hpp.html#a766033eb6f2401aab8c7236ca1c27eb3a74b1dd43c2d1ac5eb62a4afa1610a304",
"functions_rela.html",
"lz4_8c.html#a4ae1dab0fb4b072a66584546209e7d58",
"misc_8hpp.html",
"namespace_y_s_e.html#a833ec74e5b001da5afd4294b7d51247ba5ee5c603583a815f752ff42d8887b899",
"namespace_y_s_e_1_1_n_o_t_e.html#a766033eb6f2401aab8c7236ca1c27eb3a7d85876f57c4ae8a9f5ef8ffd920ea3a",
"ogg_8h.html#a7ba15c21247b46a4ef85b672495335d5",
"raygui_8h.html#a6aedaa95cd39d406c77c08cfe12b1d15a5dee998c4fc4a9efa4077a40a54e3bf5",
"raygui_8h.html#aea465d6cfa60332c80b866153fa55bb5",
"rlgl_8h.html#a49ad6901aff24dba9cd3081645dd3a2a",
"rlgl_8h.html#af0b65875cce7839b869464b01af30ee5",
"struct___e_a_x_e_x_c_l_u_s_i_o_n_p_r_o_p_e_r_t_i_e_s.html#ac2cb1ca331d9ce53c378a11e8b625dbd",
"struct_o_p_e_n_a_l_f_n_t_a_b_l_e.html#a6640e3ddf1ec20db2df00ea5b1866638",
"structdepth__counter__scope.html",
"structrres_resource_chunk_info.html#a589da83dbb03b79662481a043718271c",
"toml_8h.html#a1234ac91a810b3bd926ed6721ad1e44a",
"toml_8h.html#abec69dd25f1e4c1dfbdd288441864939"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';