rm stellar
 
sh clearlogs.sh

g++ src/main.cpp -o stellar -w -LSFML-2.6.0/lib -I SFML-2.6.0/include -ljsoncpp -lmenu -lncurses -ljpeg -lrt -fpermissive -g -lsfml-graphics -lsfml-window -lsfml-system -lX11 -lXext -lXcursor -lXrandr -lfreetype

export LD_LIBRARY_PATH=SFML-2.6.0/lib:.

./stellar