# The-Female-Gaze
The Female Gaze (TFG) is a new take on smart mirrors, meant to inspire introspection, discussion, and discovery. 

## How to Run: 
SSH into the mirror and then from the root directory run:
```
export DISPLAY=:0 // Do this once only. 
cd build; make; cd ..; ./build/the_feamle_gaze;
```

## Installation
TODO: This is still a work in progress so nothing to install yet!

### For Development
From the root directory of the repo. 
```
mkdir build
cd build
cmake ..
```

### Dependencies

```
sudo apt-get install libsfml-dev
sudo apt install g++
```

