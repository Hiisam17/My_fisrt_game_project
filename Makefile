all:
	g++ -I src/include -L src/lib -o main main.cpp base_object.cpp common_function.cpp game_map.cpp player_object.cpp game_over.cpp threats.cpp check_attack.cpp Slash_skill.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer