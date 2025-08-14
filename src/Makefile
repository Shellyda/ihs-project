# Makefile to install CMake 3.25, Raylib into Ubuntu/Debian and link it into repository
# Uso: make all

CMAKE_VERSION = 3.25.0
CMAKE_TAR = cmake-$(CMAKE_VERSION).tar.gz
CMAKE_URL = https://github.com/Kitware/CMake/releases/download/v$(CMAKE_VERSION)/$(CMAKE_TAR)

.PHONY: all deps cmake raylib clean

all: deps cmake raylib linkRaylib

deps:
	sudo apt update
	sudo apt install -y git build-essential pkg-config \
		libx11-dev libxrandr-dev libxi-dev libxinerama-dev libxcursor-dev \
		libgl1-mesa-dev libglu1-mesa-dev libasound2-dev wget

cmake:
	wget $(CMAKE_URL)
	tar -zxvf $(CMAKE_TAR)
	cd cmake-$(CMAKE_VERSION) && ./bootstrap && make -j$$(nproc) && sudo make install
	rm -rf cmake-$(CMAKE_VERSION) $(CMAKE_TAR)

raylib:
	git clone https://github.com/raysan5/raylib.git
	cd raylib && mkdir build && cd build && cmake .. && make -j$$(nproc) && sudo make install

clean:
	rm -rf raylib
	rm -rf cmake-$(CMAKE_VERSION) $(CMAKE_TAR)

linkRaylib:
	g++ target/release/obj/*.o -o target/release/app $(pkg-config --libs raylib)