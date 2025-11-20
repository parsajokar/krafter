# Krafter

Krafter is a **Minecraft-style voxel sandbox game** built from scratch in **C++17** and **OpenGL 4.5**.

---

## ✨ Features

- **Modern OpenGL 4.5 renderer**  
  Uses _Direct State Access_ (DSA) functionalities.

- **Configurable settings**  
  Window size, FOV, render distance, vsync, debug overlays, etc.

---

## 🛠️ Tech Stack

- **Language:** C++17
- **Graphics:** OpenGL 4.5
- **Libraries:**
  - GLFW — windowing & input
  - GLAD — loading OpenGL functions

---

## 📦 Building Krafter

### Requirements

- C++17 compiler
- CMake 3.20+
- OpenGL 4.5 capable GPU

### Clone the repository

```bash
git clone --recursive https://github.com/parsajokar/krafter.git
cd krafter
mkdir build
cd build
cmake ..
cd ..
cmake --build build/
./<THE EXECUTABLE>
```
