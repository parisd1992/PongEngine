# PongEngine
An implementation of Pong using a physics and OpenGL rendering engine written from scratch in C++.

[Development still in progress]

Game is programmed to run at 60 FPS.

### Physics Engine features:
(See World.hpp + screenshots below for examples)

- Physics entities travel in a straight line based on a trajectory and velocity
- Entities collide and change direction based on weight
- Velocity increases with each collision
- Option for entities to provide a callback to be called when there is a collision (useful for updating score)
- Implementation of continuous collision detection to avoid entities missing each other as their velocity increases

### OpenGL Rendering Engine features:
(see Graphics.hpp and Renderer.hpp)

- Entities to be drawn are added to a queue as Drawables which are read by the render engine (potential to support multiple threads).
- Render engine reads the queue on each render call.
- Render engine renders entities via a single drawElements call to the GPU using OpenGL.
- Uses trivial implementation of vertex and fragment shaders in GLSL.

# Contents
**[Project Goals](#project-goals)**<br>
**[Building and Running](#building-and-running)**<br>
**[Screenshots](#screenshots)**<br>
**[Improvements](#improvements)**<br>
**[Next Steps](#next-steps)**<br>

# Project Goals

- Practice C++.
- Create a simple physics engine and OpenGL graphics engine from scratch.
- Implement a pong game.

The aim of this project is to practice C++11, OpenGL and game development.

# Building and Running

Built and run on a Mac running macOS 10.13.2 (C++11).

To build and run you can either:

a. Checkout and import into XCode.

b. [Mac only] Checkout and run CMake in the folder containing the CMakeLists.txt file to create a Makefile.
Then navigate to the Makefile and run Make to create an executable.

Requires OpenGL 3.2, GLFW 3.3, GLEW 2.1.0, GLM 0.9.8.5 to be installed on your computer.

You will need to change Renderer::initShaders() in Renderer.cpp  to point to your local location of the checked out shader files.
This will be fixed soon.

# Screenshots

### Balls with different speeds and weight bouncing against walls

![Alt text](screenshots/PongGL_BallsBouncing.gif?raw=true "Balls bouncing against walls")

### Balls picking up speed as they collide

![Alt text](screenshots/PongGL_BallsPickingUpSpeed.gif?raw=true "Balls picking up speed")

# Improvements

The game is still in development.  This section will be updated shortly.

# Next Steps

- Create controllable paddles
- Add controller logic
- Add a score
- Create a winning and losing game state
- TBD: Let players choose number of balls
- TBD: Add a particle system when entities collide




