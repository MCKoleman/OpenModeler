# OpenGL Warmup Project
This project is a simple OpenGL 3D model renderer. It allows .obj and .mtl files to be opened and viewed. The core libraries used are GLEW, GLFW, and GLM.

## Compilation
The project uses CMake to build. Running the CMake GUI application and selecting the project's root directory, ie. `<location>/OpenGLWarmup/` as the source code location, and `<location>/OpenGLWarmup/build` as the build location, and then running `configure` and `generate` allows the user to create visual studio project files for the project. After these files are generated, the program can be opened in visual studio by opening the `OpenGLWarmup.sln` project file. To build the program in visual studio, right click the 'OpenGLWarmup' project inside the solution hierarchy in visual studio and select `Set as startup project`. Finally, right click the 'OpenGLWarmup' project, select properties, and in the 'Configuration Properties >> Linker >> Input' section, add `glew32s.lib` to the 'Additional Dependencies' field. Now the project can be recompiled by pressing F7 or selecting 'Build >> Build Solution' in Visual Studio.

## Running
The program can be launched on Windows by opening the OpenGLWarmup.exe file in the `/bin/` folder. If the program was recompiled in visual studio, make sure that the executable file is in the `<location>/OpenGLWarmup/bin/` folder. If this folder does not exist, create the folder and move the executable to that folder. The project structure requires that `config.txt` is in the root folder `/`, `OpenGLWarmup.exe` is in the `/bin/` folder, 3D models to be loaded are in the `/models/` folder, and vertex and fragment shader source codes are in the `/src/` folder. If the program does not run, ensure that the program files follow this exact structure.
The program can also be run by opening the visual studio project and launching the application in either Debug or Release mode.

## Operation
In `/config.txt`, choose which model to load and options on how to load it. The project comes with several 3D models, but new ones can be placed in the `/models/` folder and selected in `/config.txt` to be loaded.

### Options usage:
Which object should be loaded by the program. Should be a '.obj' file
`object = cube.obj`
Scale of the object in the program. Should be in range (0, 1]
`scale = 0.6`
Position of the object in the program. Marked as <x, y, z> coordinates
`position = 0.0 0.0 0.0`
Default color of meshes. Marked as <r, g, b> data
`dcolor = 0.8 0.8 0.8`
Vertex model. [0] separate, [1] indexed. Indexed data structure may cause issues with complicated models with non-triangular faces
`vertexmodel = 0`
Should model be drawn in wireframe? [0] No, [1] Yes
`wireframe = 0`
Should the model information be printed in the console? [0] No, [1] Yes
`print = 0`
Should the model be rendered using Gouraud [0] or Phong [1] shading
`phong = 0`
#### Camera options
cameraStartPos = 0.0 0.0 1.0
Camera look at direction. This is what the camera looks at by default
`cameraStartLookAt = 0.0 0.0 0.0`
Camera up direction. (Only change this if you really know what you're doing)
`cameraStartUp = 0.0 1.0 0.0`
Camera field of view (FOV). Only used for the perspective camera
`cameraFov = 45.0`
Orthographic camera size. Only used for orthographic camera.
`cameraSize = 10.0 10.0`
Camera near clip plane. (Only change this if you know what you're doing)
`cameraNearClip = 0.1`
Camera far clip plane. (Only change this if you know what you're doing)
`cameraFarClip = 100.0`
Should the camera be in perspective? [1] Yes, [0] No
`perspective = 1`

### Program usage:
Press `[W]` to move mesh forward
Press `[S]` to move mesh back
Press `[D]` to move mesh right
Press `[A]` to move mesh left
Press `[Space]` to move mesh up
Press `[Shift]` to move mesh down

Press `[Ctrl + W]` to move camera forward
Press `[Ctrl + S]` to move camera back
Press `[Ctrl + D]` to move camera right
Press `[Ctrl + A]` to move camera left
Press `[Ctrl + Space]` to move camera up
Press `[Ctrl + Shift]` to move camera down

Press `[Q]` to scale mesh up
Press `[E]` to scale mesh down
Press `[Up Arrow]` to rotate mesh up
Press `[Down Arrow]` to rotate mesh down
Press `[Right Arrow]` to rotate mesh right
Press `[Left Arrow]` to rotate mesh left

Press `[Ctrl + Up Arrow]` to rotate camera up
Press `[Ctrl + Down Arrow]` to rotate camera down
Press `[Ctrl + Right Arrow]` to rotate camera right
Press `[Ctrl + Left Arrow]` to rotate camera left
Press `[F]` to focus camera on the mesh

Press `[Alt + Left Mouse Button]` to rotate camera with the mouse
Press `[Alt + Right Mouse Button]` to move camera with the mouse
Press `[Esc]` to exit the program

### Links to libraries:
http://glew.sourceforge.net/

https://www.glfw.org/

https://github.com/g-truc/glm