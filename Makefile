SRCS=src/main.c src/errorMsg.c src/gridMap.c
RAYLIB= lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
INCLUDE= -Iinclude -Isrc
NAME=c0ll3ctNd3f3nd

all:
	gcc $(SRCS) $(INCLUDE) $(RAYLIB) -o $(NAME)

re:
	clean
	all

clean:
	rm $(NAME)
