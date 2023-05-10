all:
	g++ main.cpp -o main
	@echo "1 = blank Map, 2 = random Map: ";\
	read FILE; \
	./main $$FILE

clean:
	rm *.o all

	
	
