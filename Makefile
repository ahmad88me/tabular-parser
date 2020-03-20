CC = g++
CFLAGS= -std=c++11
LIB = -pthread  
TLIB = $(LIB) -lgtest


parser.out: parser.o main.o
	$(CC) $(CFLAGS) -o parser.out parser.o main.o

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBCMAKETARGET := liblinux
	DETECTEDOS := Linux
endif

ifeq  ($(UNAME_S),Darwin)
	DETECTEDOS := MacOS
	LIBCMAKETARGET := libmac
endif


.PHONY: clean install lib libmac liblinux example cov covnoclean codecov

example:
	$(CC) $(CFLAGS) -o example.out parser.cpp example.cpp
	./example.out

lib:
	echo  "Detected OS: " $(DETECTEDOS)
	$(MAKE) $(LIBCMAKETARGET)

libmac:
	$(CC) $(CFLAGS)  -dynamiclib -flat_namespace  parser.cpp -o libtabularparser.so.1.1

liblinux:
	$(CC) $(CFLAGS) -fPIC -shared parser.cpp -o libtabularparser.so.1.1

install:
	mkdir -p  /usr/local/include/tabular_parser
	cp parser.h /usr/local/include/tabular_parser/
	$(MAKE) lib
	mv libtabularparser.so.1.1 /usr/local/lib/
	ln -fs /usr/local/lib/libtabularparser.so.1.1 /usr/local/lib/libtabularparser.so
	echo -e "tabular parser is installed"
	$(MAKE) clean

covnoclean:
	$(CC) ${CFLAGS}  -c -fprofile-arcs -ftest-coverage -fPIC parser.cpp tests.cpp
	$(CC) -o covapp  -fprofile-arcs -ftest-coverage parser.o tests.o $(TLIB) 
	./covapp
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	lcov --remove coverage.info '/Applications/*' --output-file coverage.info
	lcov --list coverage.info

cov:
	$(MAKE) covnoclean
	$(MAKE) clean

codecov:
	$(MAKE) covnoclean
	curl -s https://codecov.io/bash > codecovpush.sh
	chmod +x codecovpush.sh
	./codecovpush.sh
	rm codecovpush.sh
	$(MAKE) clean

clean:
	$(RM) *.o
	$(RM) a.out
	$(RM) *.log






