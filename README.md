# QuadtreeDemo
C++ SFML Quadtree implementation demo

## Description
You can read a detailed explanation of what quadtrees are on [Wikipedia](https://en.wikipedia.org/wiki/Quadtree).

This repository is just a live demo of what quadtrees could look like.  

## Usage
### Dependencies
You need the [SFML Library](https://github.com/SFML/SFML) in order to compile and run this code.

### Build
```sh
$> mkdir -p build && cd build && cmake .. && make
# or
$> ./setup.sh
```

### Run
* **Click** somewhere in the window to generate particles.
* Press **S** to slow down time by 50%.
* Press **F** to freeze time.
* Press **G** to toggle gravity on/off.
* Press **H** to hide/show the quadtree.
* Press **V** to toggle VSync on/off. (Default: ON)
* Press **Space** to remove every particles.
* Press **ESC, DEL or Q** to exit the program.

## Contribute
Feel free to contribute, make suggestions and report bugs! :)
