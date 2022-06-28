main: test.o tinyxml2.o tinyxml2.h
	g++ -g $^ -o $@

test: error_test.o tinyxml2.o tinyxml2.h
	g++ -g $^ -o $@

%.o: %.cpp tinyxml2.h
	g++ -g -c $< -o $@

clean:
	rm test.o main destination.xml