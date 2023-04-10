UNAME = $(shell uname -s)
ifeq ($(findstring NT,$(UNAME)),NT)
	INC = -I../libraries/glfw-3.3.8.bin.WIN64/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.8.bin.WIN64/lib-mingw-w64
	LNK = -l glfw3 -l gdi32 -l opengl32
	OPT = 
else ifeq ($(findstring Darwin,$(UNAME)),Darwin)
	INC = -I../libraries/glfw-3.3.8.bin.MACOS/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.8.bin.MACOS/lib-universal
	LNK = -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit
	OPT = -arch arm64 -arch x86_64 -std=c++20 -Wno-deprecated -fsized-deallocation
else ifeq ($(findstring Linux,$(UNAME)),Linux)
	INC = -I../libraries/glad/include
	LIB = 
	LNK = -lglfw -lrt -lm -ldl -lGL
	OPT =
endif

bin/engine: obj/main.o obj/graphics.o obj/window.o obj/game.o obj/shader.o obj/mesh.o obj/texture.o obj/filereader.o obj/entity.o obj/model.o obj/scene.o obj/matrix.o obj/vector2.o obj/vector3.o obj/vertex.o | bin
	@echo Building engine...
	@g++ -g obj/*.o -o $@ $(LIB) $(LNK) $(OPT)

obj/main.o: src/main.cpp | obj
	@echo Compiling main.cpp...
	@g++ -g -c src/main.cpp -o $@ $(INC) $(OPT)

obj/graphics.o: src/graphics.cpp src/graphics.h | obj
	@echo Compiling graphics.cpp...
	@g++ -g -c src/graphics.cpp -o $@ $(INC) $(OPT)

obj/window.o: src/window.cpp | obj
	@echo Compiling window.cpp...
	@g++ -g -c src/window.cpp -o $@ $(INC) $(OPT)

obj/game.o: src/game.cpp | obj
	@echo Compiling game.cpp...
	@g++ -g -c src/game.cpp -o $@ $(INC) $(OPT)

obj/shader.o: src/shader.cpp | obj
	@echo Compiling shader.cpp...
	@g++ -g -c src/shader.cpp -o $@ $(INC) $(OPT)

obj/mesh.o: src/mesh.cpp | obj
	@echo Compiling mesh.cpp...
	@g++ -g -c src/mesh.cpp -o $@ $(INC) $(OPT)

obj/texture.o: src/texture.cpp | obj
	@echo Compiling texture.cpp...
	@g++ -g -c src/texture.cpp -o $@ $(INC) $(OPT)

obj/filereader.o: src/filereader.cpp | obj
	@echo Compiling filereader.cpp...
	@g++ -g -c src/filereader.cpp -o $@ $(INC) $(OPT)

obj/entity.o: src/entity.cpp | obj
	@echo Compiling entity.cpp...
	@g++ -g -c src/entity.cpp -o $@ $(INC) $(OPT)

obj/model.o: src/model.cpp | obj
	@echo Compiling model.cpp...
	@g++ -g -c src/model.cpp -o $@ $(INC) $(OPT)

obj/scene.o: src/scene.cpp | obj
	@echo Compiling scene.cpp...
	@g++ -g -c src/scene.cpp -o $@ $(INC) $(OPT)

obj/matrix.o: src/math/matrix.cpp | obj
	@echo Compiling matrix.cpp...
	@g++ -g -c src/math/matrix.cpp -o $@ $(INC) $(OPT)

obj/vector2.o: src/math/vector2.cpp | obj
	@echo Compiling vector2.cpp...
	@g++ -g -c src/math/vector2.cpp -o $@ $(INC) $(OPT)

obj/vector3.o: src/math/vector3.cpp | obj
	@echo Compiling vector3.cpp...
	@g++ -g -c src/math/vector3.cpp -o $@ $(INC) $(OPT)

obj/vertex.o: src/math/vertex.cpp | obj
	@echo Compiling vertex.cpp...
	@g++ -g -c src/math/vertex.cpp -o $@ $(INC) $(OPT)

bin:
	@echo Creating bin...
	@mkdir -p bin

obj:
	@echo Creating obj...
	@mkdir -p obj

run: bin/engine
	@echo Running engine...
	@bin/engine

clean:
	@echo Cleaning up...
	@rm -rf obj
	@rm -rf bin
