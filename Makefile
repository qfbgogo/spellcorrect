project: src/*.cpp include/*.h
	g++ src/*.cpp -o bin/server.exe -std=c++11 -I ./include -llog4cpp -lpthread
clean:
	rm bin/server.exe
