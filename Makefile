all:
	g++ -I src/include -L src/lib -o main main.cpp common_function.cpp base_object.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
