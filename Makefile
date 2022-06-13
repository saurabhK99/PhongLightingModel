run: main.cpp SHADER/shader.cpp MESH/mesh.cpp WIN/window.cpp CAMERA/camera.cpp LIGHT/light.cpp TEXTURE/texture.cpp MATERIAL/material.cpp
	g++ main.cpp SHADER/shader.cpp MESH/mesh.cpp WIN/window.cpp CAMERA/camera.cpp LIGHT/light.cpp TEXTURE/texture.cpp MATERIAL/material.cpp -lGL -lGLEW -lglfw && ./a.out

clean: a.out
	rm a.out