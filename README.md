# IMAT3606-Engine
_Game engine independently coded for university coursework_

This project is a reflection of my coding standards and skills during the middle of my final year of studies, under the context of making a base of a 3D game engine.

It demonstrates an implementation of a component based architecture and a data driven design. It also shows a proficiency with OpenGL and the SFML libraries.

Build information
-----------
The program was compiled with the Visual Studio 2013 (v120) toolset. To test the builds, ensure to run the executable in the same folder as the 'resources' folder, found in the 'GameEngine' folder. It is **highly** recommended to use the release builds, as the loading times can take a considerably longer time in debug.

Test information
-----------
The controls for the program are as follows:

`W, A, S, D` - Movement of the current camera

`Space` - Toggle camera

`Esc` - Regain mouse control, if pressed again in this state it will close the program

`Mouse Buttons` - Dependant on XML file chosen.

In regards to testing there are two XML files present in the 'resources': the CollisionTestArena.xml and the NightDeadForest.xml.

* The CollisionTestArena provides a simple landscape in which by pressing the left and right mouse buttons, the two objects in the scene will attempt to collide.

* The NightDeadForest has a longer loading time, although it will render a very basic forest like environment. It demonstrates both 2D text UI and a 3D UI-like object in the form of a sword. The sword can be spun using the left and right mouse buttons.

To switch between the two, either change the code in main.cpp (Change the `myCurrentScene` variable to point at either `myScene` or `myColScene`) or switch the names of the .xml files.

If there are any issues feel free to email me directly at: hussainpatel@hotmail.co.uk
