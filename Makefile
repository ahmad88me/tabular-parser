CC = g++
CFLAGS= -std=c++11


parser.out: parser.o main.o
	$(CC) $(CFLAGS) -o parser.out parser.o main.o

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


.PHONY: clean install lib libmac liblinux example

example:
	$(CC) $(CFLAGS) -o example.out parser.cpp example.cpp
	./example.out

lib:
	echo  "Detected OS: " $(DETECTEDOS)
	$(MAKE) $(LIBCMAKETARGET)

libmac:
	$(CC) $(CFLAGS)  -dynamiclib -flat_namespace  parser.cpp -o libtabularparser.so.1.0

liblinux:
	$(CC) $(CFLAGS) -fPIC -shared parser.cpp -o libtabularparser.so.1.0

install:
	mkdir -p  /usr/local/include/tabular_parser
	cp parser.h /usr/local/include/tabular_parser/
	$(MAKE) lib
	mv libtabularparser.so.1.0 /usr/local/lib/
	ln -fs /usr/local/lib/libtabularparser.so.1.0 /usr/local/lib/libtabularparser.so
	echo -e "tabular parser is installed"
	$(MAKE) clean

clean:
	$(RM) *.o
	$(RM) a.out
	$(RM) *.log






