#pragma once

/*
* DRAW_CLIPPABLE : called before 3d object drawing (but being drawn to FBO), and can be clipped by 3d objects.
* DRAW_AFTER3D : Called after 3d object drawing but before end of FBO drawing, Cannot be clipped by 3d objects.
* DRAW_POST : Called at post process time, aka any post process affects on the screen will also affect the draw command.
* DRAW_FINAL : called absolutely last in the frame.
*/
typedef enum EDrawType {
	DRAW_NULL,
	DRAW_CLIPPABLE,
	DRAW_AFTER3D,
	DRAW_POST,
	DRAW_FINAL,
};
