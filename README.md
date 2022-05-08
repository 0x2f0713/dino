# Chess
This project is under development. Tested on Ubuntu 20.04

### Dependencies

##### Install SDL 2 development library
```
sudo apt-get install libsdl2-dev
```
##### Install SDL2 TTF
```
sudo apt-get install libsdl2-ttf-dev
```
##### Install image library (If install SDL2 Image from source)
```
sudo apt-get install libjpeg62-dev # For JPEG
sudo apt-get install libpng-dev    # For PNG
sudo apt install zlib1g-dev        # For PNG
sudo apt install libtiff-dev       # For TIFF

```
##### Install SDL 2 Image

###### Install from source
```
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.zip 
unzip SDL2_image-2.0.5.zip -d sdl_image
cd sdl_image
./configure
make
sudo make install
sudo ldconfig
```
###### Install from package manager

```
sudo apt install libsdl2-image-dev
sudo ldconfig
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
~/chess/build$ ./chess
```
