start-server:
	mkdir -p executabels
	g++ src/main.cpp src/TCP_Server/server.cpp -o executabels/startServer