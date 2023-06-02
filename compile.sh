rm stellar
 
sh clearlogs.sh

g++ src/main.cpp -o stellar -w -ljsoncpp -lmenu -lncurses -ljpeg -fpermissive -g
