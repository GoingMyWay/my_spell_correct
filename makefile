main:
	g++ -g -o ./bin/main  ./src/*.cpp  -I./include/ -lpthread
clean:
	rm -rf ./bin/main
rebuild:
	rm -rf ./bin/main
	g++ -g -o ./bin/main  ./src/*.cpp  -I./include/ -lpthread

