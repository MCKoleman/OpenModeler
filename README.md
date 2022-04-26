# OpenGL Modeler Project
This project is a simple OpenGL 3D modeling engine. 
It allows .obj and .mtl files to be opened, viewed, modified, and written back into files. 
The core libraries used are GLEW, GLFW, and GLM.

## Compilation
The project uses CMake to build. 
Running the CMake GUI application and selecting the project's root directory, ie. `<location>/OpenModeler/` 
as the source code location, and `<location>/OpenModeler/build` as the build location, 
and then running `configure` and `generate` allows the user to create visual studio project files for the project. 
After these files are generated, the program can be opened in visual studio by opening the `OpenModeler.sln` project file. 
To build the program in visual studio, right click the 'OpenModeler' project inside the 
solution hierarchy in Visual Studio and select `Set as startup project`. 
Finally, right click the 'OpenModeler' project, select properties, 
and in the 'Configuration Properties >> Linker >> Input' section, add `glew32s.lib` to the 'Additional Dependencies' field. 
Now the project can be recompiled by pressing F7 or selecting 'Build >> Build Solution' in Visual Studio.

## Running
The program can be launched on Windows by opening the OpenModeler.exe file in the `/bin/` folder. 
If the program was recompiled in visual studio, make sure that the executable file is in the `<location>/OpenModeler/bin/` folder. 
If this folder does not exist, create the folder and move the executable to that folder. 
The project structure requires that `config.txt` is in the root folder `/`, `OpenModeler.exe` is in the `/bin/` folder, 
3D models to be loaded are in the `/models/` folder, and vertex and fragment shader source codes are in the `/shaders/` folder. 
If the program does not run, ensure that the program files follow this exact structure.
The program can also be run by opening the visual studio project and launching the application in either Debug or Release mode.

## Operation
In `/config.txt`, choose which model to load and options on how to load it. 
The project comes with several 3D models, but new ones can be placed in the `/models/` folder and selected in `/config.txt` to be loaded.

### Options usage:
Which object should be loaded by the program. This should be a '.obj' file
`object = cube.obj`
Scale of the object in the program. This should be in range (0, 1]
`scale = 0.6`
Position of the object in the program. Marked as <x, y, z> coordinates
`position = 0.0 0.0 0.0`
Default color of meshes. Marked as <r, g, b> data
`dcolor = 0.8 0.8 0.8`
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
Without a fancy UI to assist you, the console is your best friend and you 
are strongly encouraged to view the console side-by-side with the program to see what tool is selected etc.

#### Tool selection
Press `[1]` to turn on mesh selection mode 

Press `[2]` to turn on vertex selection mode

Press `[3]` to turn on face selection mode

Press `[5]` to toggle wireframe on and off


Press `[Q]` to turn on selection mode

Press `[E]` to turn on scale mode

Press `[R]` to turn on rotate mode

Press `[T]` to turn on translate mode

Press `[Ctrl + E]` to turn on extrude mode


#### Camera controls
Hold `[Alt]` + Press `[WASDZX]` to move the camera forward/left/back/right/up/down

Hold `[Alt]` + Press `[Arrows Keys]` to rotate 

Hold `[Alt]` + Press `[Left Mouse Button]` to rotate camera with the mouse

Hold `[Alt]` + Press `[Right Mouse Button]` to move camera with the mouse


#### Selection functions
Press `[Del]` to delete all currently selected vertices (this may cause holes in the mesh, so be careful)

Press `[Left Mouse Button]` to select the mesh/vertex/face your mouse is currently over, depending on which selection mode you are in

##### When in translate mode:
Press `[WASDZX]` to move selection forward/left/back/right/up/down

##### When in scale mode:
Press `[WASDZX]` to scale selection
Holding shift while scaling will scale uniformly in all directions

##### When in rotate mode
Press `[WASDZX]` to rotate selection

#### Program functions

Press `[F]` to focus the camera on the current object

Press `[Ctrl + T]` to triangulate the mesh (this is irreversible)

Press `[Ctrl + R]` to render the current view to a file (this may take a while)

Press `[Ctrl + S]` to save the object to file

Press `[Esc]` to exit the program

### Links to libraries:
http://glew.sourceforge.net/

https://www.glfw.org/

https://github.com/g-truc/glm