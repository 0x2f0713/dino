# Dino
This project is under development. Tested on Ubuntu 20.04

### Dependencies

Install dependencies:
Cmake version 3.14 or higher is required. Please check Cmake version and install required version via Kitware APT Repository or Cmake source code.
```
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
sudo apt-get install cmake
```

### How to build
```
# Set source folder is current folder and build folder is "build" folder
cmake -S . -B build
cd build
make
```

### Run game

```
~/dino/build$ ./dino
```
