# Fractal Explorer

## About
A very generic, OpenGL fragment-shader driven program that maps pixel positions in **R**<sup>2</sup> to
texture positions in **R**<sup>2</sup> using a user-defined function, f: **R**<sup>2</sup> → **R**<sup>2</sup>. 
It then colours the window pixel using the colour at the resulting texture position.
Features ability to pan camera, zoom (manual or continuous), change maximum iterations
(for iterative functions), and save screenshots at resolutions 4X the window size.

## Controls
* `[SHIFT+]W` - Move up [slowly]
* `[SHIFT+]A` - Move left [slowly]
* `[SHIFT+]S` - Move down [slowly]
* `[SHIFT+]D` - Move right [slowly]
* `[SHIFT+]SCROLL-WHEEL` - Zoom in/out [slowly]
* `F` - Toggle fullscreen
* `-` - Decrease detail (decrease gpu usage)
* `=` - Increase detail (increase gpu usage)
* `Z` - Autozoom slowly in on the center of the screen
* `H` - Return back to default zoom and screen position
* `P` - Save the current screen to 'awesome.bmp' in 4X its current screen size/resolution. **Will overwrite file if exists**
* `ESC` - Exit

## Using other fractals
To change which fractal(s) are generated, you can edit the function `f` in frag_double.glsl. 
There are some commented example functions already there, as well as some common mathematical functions.
Furthermore, you can change which image is used to create the colour scale by passing its file path as a command-line argument. 
Note, if you pass it a file path, the image must be a .png or a .bmp (.jpeg not supported.)

## Notes
* If you zoom in far enough, you will eventually hit the precision limit of the computer and everything will start to look blocky.
When using the autozoom feature, it will reset back to default height (same position) when it reaches this point 
to continue the zoom in a continuous loop. 
* Since the print always saves to the same location, **if you want to permanently store a picture *be sure to rename or move it***.

## Bugs
* The SHIFT controls on Windows are prone to not picking up inputs for some reason (a bug not present in the Linux builds.)
Will spend some time looking into source.


## Example
![Mandelbrot ](images/example_result.png)
