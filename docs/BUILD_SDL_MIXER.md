# Cài đặt SDL_mixer từ source code

Tài liệu này mô tả cách cài đặt SDL_mixer phiên bản 2.0.4

```console
sudo apt install libvorbisidec-dev -y
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer
git checkout release-2.0.4
./configure --enable-music-ogg-tremor
make
sudo make install
sudo ldconfig
```