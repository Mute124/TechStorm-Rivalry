



#include <math.h>
#include <raylib.h>

/*
// Noise functions stolen from
// https://gist.github.com/nowl/828013
*/

static int SEED = 500;

static int hash[] = { 208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
					185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
					9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
					70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
					203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
					164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
					228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
					232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
					193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
					101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
					135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
					114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219 };

int noise2(int x, int y)
{
	int tmp = hash[(y + SEED) % 256];
	return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
	return x + s * (y - x);
}

float smooth_inter(float x, float y, float s)
{
	return lin_inter(x, y, s * s * (3 - 2 * s));
}

float noise2d(float x, float y)
{
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int);
	int t = noise2(x_int + 1, y_int);
	int u = noise2(x_int, y_int + 1);
	int v = noise2(x_int + 1, y_int + 1);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
	float xa = x * freq;
	float ya = y * freq;
	float amp = 1.0;
	float fin = 0;
	float div = 0.0;

	int i;
	for (i = 0; i < depth; i++)
	{
		div += 256 * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
	}

	return fin / div;
}

int main(void)
{
	const int screenWidth = 600;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "3D Perlin noise");

	// Camera setup
	Camera camera = { 0 };
	camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
	camera.position = Vector3{ 30.0f, 30.0f, 30.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	int freq = 1;
	int depth = 1;
	float scale = 1.0f;
	bool update = true;
	bool isCube = true;
	bool info = false;
	bool switchCamera = false;
	bool isFP = true;
	float map[100][100];

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// Update
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		if (IsKeyPressed(KEY_UP)) { freq++; update = true; }
		if (IsKeyPressed(KEY_DOWN)) { freq--; update = true; }
		if (IsKeyPressed(KEY_LEFT)) { depth++; update = true; }
		if (IsKeyPressed(KEY_RIGHT)) { depth--; update = true; }
		if (IsKeyPressed(KEY_N)) { scale += 0.1; update = true; }
		if (IsKeyPressed(KEY_M)) { scale -= 0.1; update = true; }
		if (IsKeyPressed(KEY_E)) { isCube = !isCube; }
		if (IsKeyPressed(KEY_Q)) { switchCamera = true; }
		if (IsKeyPressed(KEY_I)) { info = !info; }

		if (update)
		{
			for (int x = 0; x < 100; x++)
			{
				for (int y = 0; y < 100; y++)
				{
					map[x][y] = perlin2d(x * scale, y * scale, freq / 10.0f, depth) * 10;
				}
			}
			update = false;
		}

		if (switchCamera)
		{
			if (isFP)
			{
				UpdateCamera(&camera, CAMERA_ORBITAL);
				isFP = false;
			}
			else
			{
				UpdateCamera(&camera, CAMERA_FIRST_PERSON);
				isFP = true;
			}
			camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
			camera.position = Vector3{ 30.0f, 30.0f, 30.0f };
			switchCamera = false;
		}
		camera.position.y = 30.0f;

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);
		if (!isCube)
		{
			for (int x = 0; x < 100; x++)
			{
				for (int y = 0; y < 100; y++)
				{
					DrawSphere(Vector3{ (float)(x - 50) / 2.0f, map[x][y], (float)(y - 25) / 2.0f }, 0.05f, RED);
				}
			}
		}
		else
		{
			for (int x = 0; x < 100; x++)
			{
				for (int y = 0; y < 100; y++)
				{
					DrawCube(Vector3{ (float)(x - 50) / 2.0f, map[x][y], (float)(y - 25) / 2.0f },
						0.5f,
						map[x][y],
						0.5f,

						Color{ (map[x][y] / 10) * 255, (map[x][y] / 10) * 255, (map[x][y] / 10) * 255, 255 });
				}
			}
		}
		DrawGrid(25, 5.0f);
		EndMode3D();

		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 100; y++)
			{
				DrawPixel(screenWidth - 100 + x, y, (Color) { 255, 255, 255, (map[x][y] / 10) * 255 });
			}
		}

		// Draw Info
		if (info)
		{
			DrawRectangle(10, 10, 200, 130, (Color) { 130, 130, 130, 240 });
			DrawText(TextFormat("Freq: %0.1f", freq / 10.0f), 20, 20, 15, WHITE);
			DrawText(TextFormat("Depth: %d", depth), 20, 40, 15, WHITE);
			DrawText(TextFormat("Scale: %0.1f", scale), 20, 60, 15, WHITE);
			DrawText(TextFormat("Cam Pos: %0.1f, %0.1f, %0.1f", camera.position.x, camera.position.y, camera.position.z), 20, 80, 15, WHITE);
			DrawFPS(20, 100);
		}
		EndDrawing();
	}
}
