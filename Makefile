OBJS	= ./src/system/planet/buildings/types/base.o ./src/system/planet/buildings/building.o ./src/system/planet/entities/human.o ./src/system/planet/planet.o ./src/system/team/laws/laws.o ./src/system/team/team.o ./src/system/system.o ./src/render/window.o ./src/other/size.o ./src/other/team.o ./src/main.o
SOURCE	= ./src/system/planet/buildings/types/base.cpp ./src/system/planet/buildings/building.cpp ./src/system/planet/entities/human.cpp ./src/system/planet/planet.cpp ./src/system/team/laws/laws.cpp ./src/system/team/team.cpp ./src/system/system.cpp ./src/render/window.cpp ./src/other/size.cpp ./src/other/team.cpp ./src/main.cpp
HEADER	= ./src/system/planet/buildings/types/base.h ./src/system/planet/buildings/building.h ./src/system/planet/entities/human.h ./src/system/planet/planet.h ./src/system/team/laws/laws.h ./src/system/team/team.h ./src/system/system.h ./src/system/utils/readJson.h ./src/render/tui.h ./src/render/ui/text.h ./src/render/ui/ui.h ./src/render/window.h ./src/other/size.h
OUT	= stellar
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

./src/system/planet/buildings/types/base.o: ./src/system/planet/buildings/types/base.cpp
	$(CC) $(FLAGS) ./src/system/planet/buildings/types/base.cpp 

./src/system/planet/buildings/building.o: ./src/system/planet/buildings/building.cpp
	$(CC) $(FLAGS) ./src/system/planet/buildings/building.cpp 

./src/system/planet/entities/human.o: ./src/system/planet/entities/human.cpp
	$(CC) $(FLAGS) ./src/system/planet/entities/human.cpp 

./src/system/planet/planet.o: ./src/system/planet/planet.cpp
	$(CC) $(FLAGS) ./src/system/planet/planet.cpp 

./src/system/team/laws/laws.o: ./src/system/team/laws/laws.cpp
	$(CC) $(FLAGS) ./src/system/team/laws/laws.cpp 

./src/system/team/team.o: ./src/system/team/team.cpp
	$(CC) $(FLAGS) ./src/system/team/team.cpp 

./src/system/system.o: ./src/system/system.cpp
	$(CC) $(FLAGS) ./src/system/system.cpp 

./src/render/window.o: ./src/render/window.cpp
	$(CC) $(FLAGS) ./src/render/window.cpp 

./src/other/size.o: ./src/other/size.cpp
	$(CC) $(FLAGS) ./src/other/size.cpp 

./src/other/team.o: ./src/other/team.cpp
	$(CC) $(FLAGS) ./src/other/team.cpp 

./src/main.o: ./src/main.cpp
	$(CC) $(FLAGS) ./src/main.cpp 


clean:
	rm -f $(OBJS) $(OUT)