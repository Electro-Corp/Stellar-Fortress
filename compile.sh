rm stellar
#g++ -g $(find src -type f -iregex ".*\.cpp") -o stellar -fpermissive -ljsoncpp -Wwrite-strings
g++ src/main.cpp -o stellar -w -ljsoncpp -lmenu -lncurses -ljpeg -fpermissive
#make
# https ://invisible-island.net/xterm/ctlseqs/ctlseqs.html