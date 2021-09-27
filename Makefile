NAME = dig.exe

INC = -I include \
	-I lib \
	-I lib\SDL2-2.0.16\x86_64-w64-mingw32\include\SDL2 \
	-I lib\SDL2_ttf-2.0.15\x86_64-w64-mingw32\include\SDL2 \
	-I lib\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2

SRC = src\circle.cpp \
	src\entity.cpp \
	src\game.cpp \
	src\gameSetup.cpp \
	src\tileset.cpp \
	src\tile.cpp \
	src\main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	$(CXX) -o $(NAME) $^ \
	-l stdc++fs \
	-l mingw32 \
	-L lib\SDL2-2.0.16\x86_64-w64-mingw32\lib \
	-l SDL2main \
	-l SDL2 \
	-L lib\SDL2_ttf-2.0.15\x86_64-w64-mingw32\lib \
	-l SDL2_ttf \
	-L lib\SDL2_image-2.0.5\\x86_64-w64-mingw32\\lib \
	-l SDL2_image

%.o: %.cpp
	$(CXX) -g -std=c++17 $(INC) -c $< -o $@ 

re: fclean all

clean:
	del $(OBJ)

fclean: clean
	del dig.exe

.PHONY: all re clean fclean
