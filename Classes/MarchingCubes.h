#include <raylib.h>
#include <vector>

class MarchingCubes {
public:
    MarchingCubes(int width, int height, int depth, float threshold)
        : width(width), height(height), depth(depth), threshold(threshold) {
        // Create the 3D grid
        grid.resize(width * height * depth);
    }

    void generateMesh() {
        // Generate the mesh
        for (int z = 0; z < depth - 1; z++) {
            for (int y = 0; y < height - 1; y++) {
                for (int x = 0; x < width - 1; x++) {
                    // Compute the index into the grid
                    int index = x + y * width + z * width * height;

                    // Retrieve the grid values
                    float val0 = grid[index];
                    float val1 = grid[index + 1];
                    float val2 = grid[index + width];
                    float val3 = grid[index + width + 1];
                    float val4 = grid[index + width * height];
                    float val5 = grid[index + width * height + 1];
                    float val6 = grid[index + width * height + width];
                    float val7 = grid[index + width * height + width + 1];

                    // Perform the Marching Cubes algorithm
                    int cubeIndex = 0;
                    if (val0 < threshold) cubeIndex |= 1;
                    if (val1 < threshold) cubeIndex |= 2;
                    if (val2 < threshold) cubeIndex |= 8;
                    if (val3 < threshold) cubeIndex |= 4;
                    if (val4 < threshold) cubeIndex |= 16;
                    if (val5 < threshold) cubeIndex |= 32;
                    if (val6 < threshold) cubeIndex |= 128;
                    if (val7 < threshold) cubeIndex |= 64;

                    // Generate the triangles for the current cube
                    for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
                        int edge0 = triTable[cubeIndex][i];
                        int edge1 = triTable[cubeIndex][i + 1];
                        int edge2 = triTable[cubeIndex][i + 2];

                        // Compute the interpolated positions and add them to the vertices list
                        vertices.push_back(interpolateVertex(x, y, z, edge0));
                        vertices.push_back(interpolateVertex(x, y, z, edge1));
                        vertices.push_back(interpolateVertex(x, y, z, edge2));
                    }
                }
            }
        }
    }

    void setGridValue(int x, int y, int z, float value) {
        // Set the value at the specified grid position
        int index = x + y * width + z * width * height;
        grid[index] = value;
    }

    void render() {
        // Render the generated mesh
        for (size_t i = 0; i < vertices.size(); i += 3) {
            DrawTriangle3D()(vertices[i], vertices[i + 1], vertices[i + 2], GREEN);
        }
    }

private:
    struct Vector3 {
        float x, y, z;
    };

    // Compute the interpolated vertex position
    Vector3 interpolateVertex(int x, int y, int z, int edge) {
        Vector3 p0 = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
        Vector3 p1 = { static_cast<float>(x + edgeToVertexOffset[edge][0]),
                       static_cast<float>(y + edgeToVertexOffset[edge][1]),
                       static_cast<float>(z + edgeToVertexOffset[edge][2]) };

        float val0 = grid[x + y * width + z * width * height];
        float val1 = grid[x + edgeToVertexOffset[edge][0] +
                           (y + edgeToVertexOffset[edge][1]) * width +
                           (z + edgeToVertexOffset[edge][2]) * width * height];

        float mu = (threshold - val0) / (val1 - val0);

        Vector3 p;
        p.x = p0.x + mu * (p1.x - p0.x);
        p.y = p0.y + mu * (p1.y - p0.y);
        p.z = p0.z + mu * (p1.z - p0.z);

        return p;
    }

    std::vector<float> grid;
    std::vector<Vector3> vertices;
    int width, height, depth;
    float threshold;

    static constexpr int edgeToVertexOffset[12][3] = {
        { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 },
        { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 0, 1, 1 },
        { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 0, 0 }
    };

    static constexpr int triTable[256][16] = {
        // Triangulation table - generated from Paul Bourke's implementation
        // (http://paulbourke.net/geometry/polygonise/)

        { -1 },
        { 0, 8, 3, -1 },
        { 0, 1, 9, -1 },
        { 1, 8, 3, 9, 8, 1, -1 },
        { 1, 2, 10, -1 },
        { 0, 8, 3, 1, 2, 10, -1 },
        { 9, 2, 10, 0, 2, 9, -1 },
        { 2, 8, 3, 2, 10, 8, 10, 9, 8, -1 },
        { 3, 11, 2, -1 },
        { 0, 11, 2, 8, 11, 0, -1 },
        { 1, 9, 0, 2, 3, 11, -1 },
        { 1, 11, 2, 1, 9, 11, 9, 8, 11, -1 },
        { 3, 10, 1, 11, 10, 3, -1 },
        { 0, 10, 1, 0, 8, 10, 8, 11, 10, -1 },
        { 3, 9, 0, 3, 11, 9, 11, 10, 9, -1 },
        { 9, 8, 10, 10, 8, 11, -1 },
        { 4, 7, 8, -1 },
        { 4, 3, 0, 7, 3, 4, -1 },
        { 0, 1, 9, 8, 4, 7, -1 },
        { 4, 1, 9, 4, 7, 1, 7, 3, 1, -1 },
        { 1, 2, 10, 8, 4, 7, -1 },
        { 3, 4, 7, 3, 0, 4, 1, 2, 10, -1 },
        { 9, 2, 10, 9, 0, 2, 8, 4, 7, -1 },
        { 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1 },
        { 8, 4, 7, 3, 11, 2, -1 },
        { 11, 4, 7, 11, 2, 4, 2, 0, 4, -1 },
        { 9, 0, 1, 8, 4, 7, 2, 3, 11, -1 },
        { 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1 },
        { 3, 10, 1, 3, 11, 10, 7, 8, 4, -1 },
        { 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1 },
        { 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1 },
        { 4, 7, 11, 4, 11, 9, 9, 11, 10, -1 },
        { 9, 5, 4, -1 },
        { 9, 5, 4, 0, 8, 3, -1 },
        { 0, 5, 4, 1, 5, 0, -1 },
        { 8, 5, 4, 8, 3, 5, 3, 1, 5, -1 },
        { 1, 2, 10, 9, 5, 4, -1 },
        { 3, 0, 8, 1, 2, 10, 4, 9, 5, -1 },
        { 5, 2, 10, 5, 4, 2, 4, 0, 2, -1 },
        { 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1 },
        { 9, 5, 4, 2, 3, 11, -1 },
        { 0, 11, 2, 0, 8, 11, 4, 9, 5, -1 },
        { 0, 5, 4, 0, 1, 5, 2, 3, 11, -1 },
        { 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1 },
        { 10, 3, 11, 10, 1, 3, 9, 5, 4, -1 },
        { 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1 },
        { 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1 },
        { 5, 4, 8, 5, 8, 10, 10, 8, 11, -1 },
        { 9, 7, 8, 5, 7, 9, -1 },
        { 9, 3, 0, 9, 5, 3, 5, 7, 3, -1 },
        { 0, 7, 8, 0, 1, 7, 1, 5, 7, -1 },
        { 1, 5, 3, 3, 5, 7, -1 },
        { 9, 7, 8, 9, 5, 7, 10, 1, 2, -1 },
        { 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1 },
        { 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1 },
        { 2, 10, 5, 2, 5, 3, 3, 5, 7, -1 },
        { 7, 9, 5, 7, 8, 9, 3, 11, 2, -1 },
        { 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1 },
        { 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1 },
        { 11, 2, 1, 11, 1, 7, 7, 1, 5, -1 },
        { 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1 },
        { 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, -1 },
        { 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, -1 },
        { 11, 10, 5, 7, 11, 5, -1 },
        { 10, 6, 5, -1 },
        { 0, 8, 3, 5, 10, 6, -1 },
        { 9, 0, 1, 5, 10, 6, -1 },
        { 1, 8, 3, 1, 9, 8, 5, 10, 6, -1 },
        { 1, 6, 5, 2, 6, 1, -1 },
        { 1, 6, 5, 1, 2, 6, 3, 0, 8, -1 },
        { 9, 6, 5, 9, 0, 6, 0, 2, 6, -1 },
        { 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1 },
        { 2, 3, 11, 10, 6, 5, -1 },
        { 11, 0, 8, 11, 2, 0, 10, 6, 5, -1 },
        { 0, 1, 9, 2, 3, 11, 5, 10, 6, -1 },
        { 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1 },
        { 6, 3, 11, 6, 5, 3, 5, 1, 3, -1 },
        { 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1 },
        { 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1 },
        { 6, 5, 9, 6, 9, 11, 11, 9, 8, -1 },
        { 5, 10, 6, 4, 7, 8, -1 },
        { 4, 3, 0, 4, 7, 3, 6, 5, 10, -1 },
        { 1, 9, 0, 5, 10, 6, 8, 4, 7, -1 },
        { 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1 },
        { 6, 1, 2, 6, 5, 1, 4, 7, 8, -1 },
        { 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1 },
        { 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1 },
        { 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, -1 },
        { 3, 11, 2, 7, 8, 4, 10, 6, 5, -1 },
        { 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1 },
        { 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1 },
        { 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, -1 },
        { 5, 10, 6, 4, 7, 3, 4, 3, 2, 3, 7, 11, -1 },
        { 7, 8, 4, 2, 5, 10, 2, 3, 5, 3, 4, 5, -1 },
        { 5, 10, 6, 9, 4, 7, 9, 7, 3, 9, 3, 0, -1 },
        { 6, 5, 9, 6, 9, 11, 11, 9, 4, -1 },
        { 7, 8, 4, 5, 11, 6, -1 },
        { 3, 0, 4, 3, 4, 7, 5, 11, 6, -1 },
        { 6, 5, 11, 6, 3, 5, 3, 1, 5, -1 },
        { 0, 1, 9, 4, 7, 8, 11, 6, 5, -1 },
        { 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, -1 },
        { 8, 4, 7, 3, 11, 2, 5, 9, 6, -1 },
        { 5, 9, 6, 2, 3, 11, 0, 1, 8, 4, 7, 8, -1 },
        { 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1 },
        { 9, 6, 5, 0, 5, 3, 0, 3, 2, 3, 5, 11, -1 },
        { 11, 2, 6, 11, 6, 3, 3, 6, 5, -1 },
        { 8, 4, 7, 3, 6, 5, 3, 5, 1, 5, 6, 2, -1 },
        { 0, 4, 7, 1, 0, 7, 1, 7, 6, 1, 6, 10, -1 },
        { 10, 1, 6, 10, 6, 5, 5, 6, 7, -1 },
        { 3, 0, 4, 3, 4, 7, 1, 10, 6, 1, 6, 5, -1 },
        { 6, 1, 10, 7, 6, 10, 7, 10, 4, 4, 10, 8, -1 },
        { 1, 4, 9, 1, 2, 4, 2, 7, 4, -1 },
        { 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 7, 4, -1 },
        { 0, 2, 4, 4, 2, 7, -1 },
        { 8, 3, 4, 4, 3, 2, 4, 2, 7, -1 },
        { 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1 },
        { 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, -1 },
        { 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, -1 },
        { 1, 10, 2, 8, 7, 4, -1 },
        { 4, 9, 1, 4, 1, 7, 7, 1, 3, -1 },
        { 4, 9, 1, 4, 1, 7, 0, 8, 1, -1 },
        { 4, 0, 3, 7, 4, 3, -1 },
        { 4, 8, 7, -1 },
        { 9, 10, 8, 10, 11, 8, -1 },
        { 3, 0, 9, 3, 9, 11, 11, 9, 10, -1 },
        { 0, 1, 10, 0, 10, 8, 8, 10, 11, -1 },
        { 3, 1, 10, 11, 3, 10, -1 },
        { 1, 2, 11, 1, 11, 9, 9, 11, 8, -1 },
        { 3, 0, 9, 3, 9, 11, 1, 2, 9, -1 },
        { 0, 2, 11, 8, 0, 11, -1 },
        { 3, 2, 11, -1 },
        { 2, 3, 8, 2, 8, 10, 10, 8, 9, -1 },
        { 9, 10, 2, 0, 9, 2, -1 },
        { 2, 3, 8, 2, 8, 10, 0, 1, 8, -1 },
        { 1, 10, 2, -1 },
        { 1, 3, 8, 9, 1, 8, -1 },
        { 0, 9, 1, -1 },
        { 0, 3, 8, -1 },
        {}  // Termination of the table
    };

    std::vector<Vector3> vertexList(12);  // Vertex list used for interpolation
    std::vector<Vector3> normalList(12);  // Normal list used for surface normals

public:
    MarchingCubes(int width, int height, int length, float threshold)
        : width_(width), height_(height), length_(length), threshold_(threshold)
    {
        // Calculate the number of cells in the grid
        int numCells = (width_ - 1) * (height_ - 1) * (length_ - 1);

        // Resize the grid and surface vectors
        grid_.resize(numCells);
        surface_.reserve(numCells * 5);  // A rough estimation of the maximum number of vertices

        // Initialize the vertex and normal lists
        for (int i = 0; i < 12; ++i)
        {
            vertexList()[i] = Vector3();
            normalList()[i] = Vector3();
        }
    }

    void GenerateSurface(const float* data)
    {
        // Clear the surface vertices and normals
        surface_.clear();

        // Iterate over each cell in the grid
        for (int z = 0; z < length_ - 1; ++z)
        {
            for (int y = 0; y < height_ - 1; ++y)
            {
                for (int x = 0; x < width_ - 1; ++x)
                {
                    // Retrieve the scalar values at the corners of the cell
                    float values[8] = {
                        data[Index(x, y, z)],
                        data[Index(x + 1, y, z)],
                        data[Index(x + 1, y, z + 1)],
                        data[Index(x, y, z + 1)],
                        data[Index(x, y + 1, z)],
                        data[Index(x + 1, y + 1, z)],
                        data[Index(x + 1, y + 1, z + 1)],
                        data[Index(x, y + 1, z + 1)]
                    };

                    // Determine the index into the edge table based on the scalar values
                    int index = 0;
                    if (values[0] < threshold_) index |= 1;
                    if (values[1] < threshold_) index |= 2;
                    if (values[2] < threshold_) index |= 4;
                    if (values[3] < threshold_) index |= 8;
                    if (values[4] < threshold_) index |= 16;
                    if (values[5] < threshold_) index |= 32;
                    if (values[6] < threshold_) index |= 64;
                    if (values[7] < threshold_) index |= 128;

                    // Use the edge table to determine the triangulation for this cell
                    int edgeFlags = edgeTable[index];
                    if (edgeFlags == 0) continue;  // No triangles for this cell

                    // Interpolate the vertices and normals along the edges
                    if (edgeFlags & 1)
                        vertexList[0] = VertexInterpolate(x, y, z, values[0], values[1]);
                    if (edgeFlags & 2)
                        vertexList[1] = VertexInterpolate(x + 1, y, z, values[1], values[2]);
                    if (edgeFlags & 4)
                        vertexList[2] = VertexInterpolate(x + 1, y, z + 1, values[2], values[3]);
                    if (edgeFlags & 8)
                        vertexList[3] = VertexInterpolate(x, y, z + 1, values[3], values[0]);
                    if (edgeFlags & 16)
                        vertexList[4] = VertexInterpolate(x, y + 1, z, values[4], values[5]);
                    if (edgeFlags & 32)
                        vertexList[5] = VertexInterpolate(x + 1, y + 1, z, values[5], values[6]);
                    if (edgeFlags & 64)
                        vertexList[6] = VertexInterpolate(x + 1, y + 1, z + 1, values[6], values[7]);
                    if (edgeFlags & 128)
                        vertexList[7] = VertexInterpolate(x, y + 1, z + 1, values[7], values[4]);
                    if (edgeFlags & 256)
                        vertexList[8] = VertexInterpolate(x, y, z, values[0], values[4]);
                    if (edgeFlags & 512)
                        vertexList[9] = VertexInterpolate(x + 1, y, z, values[1], values[5]);
                    if (edgeFlags & 1024)
                        vertexList[10] = VertexInterpolate(x + 1, y, z + 1, values[2], values[6]);
                    if (edgeFlags & 2048)
                        vertexList[11] = VertexInterpolate(x, y, z + 1, values[3], values[7]);

                    // Create triangles from the vertices
                    for (int i = 0; triTable[index][i] != -1; i += 3)
                    {
                        int index1 = triTable[index][i];
                        int index2 = triTable[index][i + 1];
                        int index3 = triTable[index][i + 2];

                        // Calculate the surface normal using the cross product
                        Vector3 v1 = vertexList[index2] - vertexList[index1];
                        Vector3 v2 = vertexList[index3] - vertexList[index1];
                        Vector3 normal = Vector3::CrossProduct(v1, v2);

                        // Add the vertices and normals to the surface
                        surface_.push_back(vertexList[index1]);
                        surface_.push_back(normal);
                        surface_.push_back(vertexList[index2]);
                        surface_.push_back(normal);
                        surface_.push_back(vertexList[index3]);
                        surface_.push_back(normal);
                    }
                }
            }
        }
    }

    const std::vector<float>& GetSurface() const { return surface_; }

private:
    int Index(int x, int y, int z) const
    {
        return x + y * width_ + z * width_ * height_;
    }

    Vector3 VertexInterpolate(int x, int y, int z, float value1, float value2) const
    {
        float t = (threshold_ - value1) / (value2 - value1);
        return Vector3(static_cast<float>(x) + t, static_cast<float>(y), static_cast<float>(z));
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Marching Cubes");

    Camera3D camera;
    camera.position = Vector3(10.0f, 10.0f, 10.0f);
    camera.target = Vector3(0.0f, 0.0f, 0.0f);
    camera.up = Vector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_ORBITAL);

    MarchingCubes marchingCubes(64, 64, 64, 0.5f);
    std::vector<float> data(64 * 64 * 64);

    // Generate some sample data
    for (int z = 0; z < 64; ++z)
    {
        for (int y = 0; y < 64; ++y)
        {
            for (int x = 0; x < 64; ++x)
            {
                float dx = static_cast<float>(x) - 32.0f;
                float dy = static_cast<float>(y) - 32.0f;
                float dz = static_cast<float>(z) - 32.0f;
                data[marchingCubes.Index(x, y, z)] = std::sqrt(dx * dx + dy * dy + dz * dz);
            }
        }
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);

        if (IsKeyPressed(KEY_SPACE))
        {
            marchingCubes.GenerateSurface(data.data());
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw the generated surface
        DrawMesh(DrawMeshPoly(marchingCubes.GetSurface(), WHITE));

        // Draw the grid lines
        for (int x = -32; x <= 32; ++x)
        {
            DrawLine3D(Vector3(static_cast<float>(x), -32.0f, 0.0f), Vector3(static_cast<float>(x), 32.0f, 0.0f), GRAY);
            DrawLine3D(Vector3(static_cast<float>(x), 0.0f, -32.0f), Vector3(static_cast<float>(x), 0.0f, 32.0f), GRAY);
        }

        for (int z = -32; z <= 32; ++z) 
        {
            DrawLine3D(Vector3(-32.0f, 0.0f, static_cast<float>(z)), Vector3(32.0f, 0.0f, static_cast<float>(z)), GRAY);
            DrawLine3D(Vector3(0.0f, -32.0f, static_cast<float>(z)), Vector3(0.0f, 32.0f, static_cast<float>(z)), GRAY);
        }

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
