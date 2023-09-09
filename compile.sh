rm stellar
 
sh clearlogs.sh

g++ src/main.cpp -o stellar -w  -ljsoncpp -lmenu -lncurses -lrt -fpermissive -g -lSDL2 -lSDL_image -lSDL2_ttf

#g++ src/main.cpp SFML-2.6.0/lib/libsfml-graphics.so.2.6 SFML-2.6.0/lib/libsfml-window.so.2.6 SFML-2.6.0/lib/libsfml-system.so.2.6 -o stellar -w -I SFML-2.6.0/include -ljsoncpp -lmenu -lncurses -ljpeg -lrt -fpermissive -g -lX11 -lXext -lXcursor -lXrandr -lfreetype



export LD_LIBRARY_PATH=SFML-2.6.0/lib:.

./stellar