make:
	g++ -o server ./source/my-server.cpp -levent
run:
	./server
clean:
	rm server
