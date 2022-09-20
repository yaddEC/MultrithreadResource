## MULTITHREAD - RESOURCE MANAGER

The goal of this project is to parallel the loading of resources by avoiding blocks and data strokes.
You will have to understand the memory alignment and synchronize your operations to obtain the best result.
It is written in C/C++.


## AUTHORS
LUANDA Osvaldo Bento - (o.luanda@student.isartdigital.com)
DECHAUX Yan        -   (y.dechaux@student.isartdigital.com)


## FEATURES
- ProccessThreadResource :a function that creates a thread that does not form part of the main thread.
First this fuction allows us to load 3D models in parallel with window management.
Second, it is faster because our code is split into fuctions that manage opengl and other tasks.
	
	 
	


<img src="">


## SCENE



## CAMERA - CONTROLS
- A - D : Left/right
- W - S : Forward/Backward
- R - F : Change the FOV(Field of view)
- Mouse Left Button : Move the camera up or down


## SCENE - CONTROLS
- ESCAPE     : Quit the apllication


<img src="">

## BIBLIOGRAPHIE
- https://www.realtimerendering.com
- https://en.wikipedia.org/wiki/Graphics_pipeline
- https://learnopengl.com
- https://github.com/nothings/stb
- http://www.cplusplus.com/reference/thread/thread
- http://www.cplusplus.com/reference/mutex/
