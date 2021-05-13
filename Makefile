exec: 
	g++ main.cpp -o exec -pthread -std=c++11

clean:
	del exec.exe

clean-linux:
	rm exec