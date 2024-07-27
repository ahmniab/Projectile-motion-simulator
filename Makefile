CC = /C/raylib/w64devkit/bin/gcc.exe 
flags = -s -static -Os -std=c99 -Wall -I/C/raylib/raylib/src -I./objs/ -I./controles/ -Iexternal -DPLATFORM_DESKTOP -lraylib -lopengl32 -lgdi32 -lwinmm


main.o: main.c
	${CC} -c main.c -o binaries/main.o ${flags}


helper.o: helper.c helper.h
	${CC} -c helper.c -o binaries/helper.o ${flags}

ball.o: objs/ball.c objs/ball.h
	${CC} -c objs/ball.c -o binaries/ball.o  ${flags}

Mab.o: Mab/Mab.c Mab/Mab.h
	${CC} -c Mab/Mab.c  ${flags}



clean:
	rm -f binaries/*.o shell