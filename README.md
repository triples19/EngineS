# EngineS

A toy game engine.

## Prerequisites
EngineS needs a recent compiler that supports most features of C++20. Currently known to work with:

* GCC 12+
* Clang 16+
* MSVC 19.36+

Also you need [LLVM](https://github.com/llvm/llvm-project) installed to build ReflCompiler. Other third-party libraries are included as git submodules.

## Current status

* **Graphics** - Basic 2D sprite rendering with basic Graphics API abstraction
* **Input** - Keyboard input
* **Assets** - A resource manager which can auto-reload resources at runtime
* **Reflection** - A reflection module with run-time type information
* **ReflCompiler** - A code generation tool for reflection with Clang-Tools libraries
* **Components** - Components-based engine structure
* **Memory** - Based on reference counting, automatically releasing unused objects every frame

## Roadmap

* [ ] **Containers** - Custom containers and data sturctures that fit better with the engine
* [ ] **Scripting** - Support Lua scripts with the help of reflection module
* [ ] **2D Graphics** - Better sprite support, full Grapics API abstraction
* [ ] **3D Graphics** - Basic 3D rendering
* [ ] **Graphics** - Support Vulkan
* [ ] **Input** - Support mouse and gamepad
* [ ] **Sound** - Support audio
* [ ] **Physics** - Support 2D Physics with maybe Box2D
* [ ] **Editor** 