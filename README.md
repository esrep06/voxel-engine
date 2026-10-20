
# Voxel Engine

A C++20 voxel engine using OpenGL 3.3, GLFW, GLEW, and GLM.

## Dependencies

Dependencies are managed using Git submodules:

- GLFW
- GLEW (official upstream repository)
- GLM
- cpp-utilz

## Building

### 1. Clone the repository

```bash
git clone --recursive https://github.com/esrep06/voxel-engine.git
cd voxel-engine
```

### 2. Generate GLEW source files

The official GLEW Git repository requires its source files to be generated before building.

Make sure GNU Make and GLEW's required generation tools are installed.

```bash
cd include/glew
make extensions
cd ../..
```

### 3. Configure and build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

### 4. Run

From the repository root:

```bash
./build/VoxelEngine
```

Run from the project root
