device_cheker:
	mkdir -p build
	g++ -std=c++17 -Isrc src/device_checker.cpp -o build/test $(shell sdl2-config --cflags --libs)

clean:
	rm -rf ./build