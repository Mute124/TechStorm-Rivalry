#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef RGUIAPI_H
#define RGUIAPI_H
#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#if defined(__TINYC__)
#define __declspec(x) __attribute__((x))
#endif
#define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
#elif defined(USE_LIBTYPE_SHARED)
#define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
#endif
#endif

#include "raylib.h"
#include "rguilayout.h"
#include "rgui/src/raygui.h"

// Standard C libraries
#include <stdlib.h>                         // Required for: calloc(), free()
#include <stdarg.h>                         // Required for: va_list, va_start(), vfprintf(), va_end()
#include <string.h>                         // Required for: strcpy(), strcat(), strlen()
#include <stdio.h>                          // Required for: FILE, fopen(), fclose()...
#include <ctype.h>                          // Required for: toupper(), tolower()

#if (!defined(_DEBUG) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)))
bool __stdcall FreeConsole(void);       // Close console from code (kernel32.lib)
#endif
#define ANCHOR_RADIUS               20      // Default anchor radius
#define MIN_CONTROL_SIZE            10      // Minimum control size
#define SCALE_BOX_CORNER_SIZE       12      // Scale box bottom-right corner square size

#define MOVEMENT_FRAME_SPEED         2      // Controls movement speed in pixels per frame

#define MAX_UNDO_LEVELS             64      // Undo levels supported for the ring buffer
#define UNDO_SNAPSHOT_FRAMERATE     90      // Frames to take a new layout snapshot (if changes done), @60 fps = 1.5sec

#define MAX_ICONS_AVAILABLE        220      // Max raygui icons displayed on icon selector

#define MAX_ELEMENTS_SELECTION      64      // Max elements selected

// Reset layout to default values
static void ResetLayout(GuiLayout* layout)
{
	// Set anchor points to default values
	for (int i = 0; i < MAX_ANCHOR_POINTS; i++)
	{
		layout->anchors[i].id = i;
		layout->anchors[i].x = 0;
		layout->anchors[i].y = 0;
		layout->anchors[i].enabled = false;
		layout->anchors[i].hidding = false;
		memset(layout->anchors[i].name, 0, MAX_ANCHOR_NAME_LENGTH);

		if (i == 0) strcpy(static_cast<char*>(static_cast<void*>(layout->anchors[i].name)), "refPoint");
		else strcpy(static_cast<char*>(static_cast<void*>(layout->anchors[layout->anchorCount].name)), TextFormat("anchor%02i", i));
	}

	// Initialize layout controls data
	for (int i = 0; i < MAX_GUI_CONTROLS; i++)
	{
		layout->controls[i].id = 0;
		layout->controls[i].type = 0;
		layout->controls[i].rec = Rectangle{ 0, 0, 0, 0 };
		memset(layout->controls[i].text, 0, MAX_CONTROL_TEXT_LENGTH);
		memset(layout->controls[i].name, 0, MAX_CONTROL_NAME_LENGTH);
		layout->controls[i].ap = &layout->anchors[0];  // By default, set parent anchor
	}

	layout->refWindow = Rectangle{ 0, 40, -1, -1 };
	layout->anchorCount = 0;
	layout->controlCount = 0;
}

// Load layout from text file
// NOTE: If NULL provided, an empty layout is initialized
static GuiLayout* LoadLayout(const char* fileName)
{
	GuiLayout* layout = (GuiLayout*)RL_CALLOC(1, sizeof(GuiLayout));

	ResetLayout(layout);    // Init some default values

	if (fileName != NULL)   // Try loading text layout file
	{
		FILE* rglFile = fopen(fileName, "rt");

		if (rglFile != NULL)
		{
			char buffer[256] = { 0 };
			char anchorName[MAX_ANCHOR_NAME_LENGTH] = { 0 };

			fgets(buffer, 256, rglFile);

			while (!feof(rglFile))
			{
				switch (buffer[0])
				{
				case 'r':
				{
					sscanf(buffer, "r %f %f %f %f", &layout->refWindow.x, &layout->refWindow.y, &layout->refWindow.width, &layout->refWindow.height);

					// NOTE: Reference window defines anchor[0]
					layout->anchors[0].id = 0;
					layout->anchors[0].ap = NULL;
					layout->anchors[0].x = layout->refWindow.x;
					layout->anchors[0].y = layout->refWindow.y;
					layout->anchors[0].enabled = true;

					strcpy(static_cast<char*>(static_cast<void*>(layout->anchors[0].name)), "refPoint");

					layout->anchorCount++;
				} break;
				case 'a':
				{
					int enabled = 0;
					sscanf(buffer, "a %d %s %d %d %d",
						&layout->anchors[layout->anchorCount].id,
						anchorName,
						&layout->anchors[layout->anchorCount].x,
						&layout->anchors[layout->anchorCount].y,
						&enabled);

					if (layout->anchors[layout->anchorCount].id > 0)
					{
						layout->anchors[layout->anchorCount].enabled = (enabled ? true : false);

						strcpy(static_cast<char*>(static_cast<void*>(layout->anchors[layout->anchorCount].name)), anchorName);

						layout->anchorCount++;
					}
				} break;
				case 'c':
				{
					int anchorId = 0;
					sscanf(buffer, "c %d %d %s %f %f %f %f %d %[^\n]s",
						&layout->controls[layout->controlCount].id,
						&layout->controls[layout->controlCount].type,
						layout->controls[layout->controlCount].name,
						&layout->controls[layout->controlCount].rec.x,
						&layout->controls[layout->controlCount].rec.y,
						&layout->controls[layout->controlCount].rec.width,
						&layout->controls[layout->controlCount].rec.height,
						&anchorId,
						layout->controls[layout->controlCount].text);

					layout->controls[layout->controlCount].ap = &layout->anchors[anchorId];

					// NOTE: refWindow offset (anchor[0]) must be added to controls with no anchor
					if (anchorId == 0)
					{
						layout->controls[layout->controlCount].rec.x += layout->refWindow.x;
						layout->controls[layout->controlCount].rec.y += layout->refWindow.y;
					}

					layout->controlCount++;
				} break;
				default: break;
				}

				fgets(buffer, 256, rglFile);
			}

			fclose(rglFile);

			// NOTE: refWindow offset (anchor[0]) must be added to all anchors
			for (int i = 1; i < layout->anchorCount; i++)
			{
				layout->anchors[i].x += layout->refWindow.x;
				layout->anchors[i].y += layout->refWindow.y;
			}
		}
	}
	else
	{
		// Define reference anchor
		layout->anchors[0].x = 0;
		layout->anchors[0].y = 40;
		layout->anchors[0].enabled = true;
		layout->refWindow.x = 0;
		layout->refWindow.y = 40;
		layout->anchorCount = 1;
	}

	return layout;
}

// Unload layout
static void UnloadLayout(GuiLayout* layout)
{
	RL_FREE(layout);
}

// Check if a rectangle is contained within another
static bool IsRecContainedInRec(Rectangle container, Rectangle rec)
{
	bool result = false;

	if ((rec.x >= container.x) && (rec.y >= container.y) &&
		((rec.x + rec.width) <= (container.x + container.width)) &&
		((rec.y + rec.height) <= (container.y + container.height))) result = true;

	return result;
}

// Check if fileName is valid for the platform/OS
static bool IsFileNameValid(const char* fileName)
{
	bool valid = true;

	if ((fileName != NULL) && (fileName[0] != '\0'))
	{
		int length = strlen(fileName);
		bool allPeriods = true;

		for (int i = 0; i < length; i++)
		{
			// Check invalid characters
			if ((fileName[i] == '<') ||
				(fileName[i] == '>') ||
				(fileName[i] == ':') ||
				(fileName[i] == '\"') ||
				(fileName[i] == '/') ||
				(fileName[i] == '\\') ||
				(fileName[i] == '|') ||
				(fileName[i] == '?') ||
				(fileName[i] == '*')) {
				valid = false; break;
			}

			// Check non-glyph characters
			if ((unsigned char)fileName[i] < 32) { valid = false; break; }

			// TODO: Check trailing periods/spaces?

			// Check if filename is not all periods
			if (fileName[i] != '.') allPeriods = false;
		}

		if (allPeriods) valid = false;

		/*
				if (valid)
				{
					// Check invalid DOS names
					if (length >= 3)
					{
						if (((fileName[0] == 'C') && (fileName[1] == 'O') && (fileName[2] == 'N')) ||   // CON
							((fileName[0] == 'P') && (fileName[1] == 'R') && (fileName[2] == 'N')) ||   // PRN
							((fileName[0] == 'A') && (fileName[1] == 'U') && (fileName[2] == 'X')) ||   // AUX
							((fileName[0] == 'N') && (fileName[1] == 'U') && (fileName[2] == 'L'))) valid = false; // NUL
					}

					if (length >= 4)
					{
						if (((fileName[0] == 'C') && (fileName[1] == 'O') && (fileName[2] == 'M') && ((fileName[3] >= '0') && (fileName[3] <= '9'))) ||  // COM0-9
							((fileName[0] == 'L') && (fileName[1] == 'P') && (fileName[2] == 'T') && ((fileName[3] >= '0') && (fileName[3] <= '9')))) valid = false; // LPT0-9
					}
				}
		*/
	}

	return valid;
}
#endif
