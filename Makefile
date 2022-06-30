VERSION = 1.2
CC = g++
CFLAGS= -std=c++11
LIB = -pthread  
TLIB = $(LIB) -lgtest

COVCLEANFILES = gcov.css snow.png ruby.png *.gcov  *.gcda *.gcno index-sort-f.html index-sort-l.html index.html amber.png glass.png updown.png coverage.info emerald.png Users usr v1\

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
	$(CC) $(CFLAGS)  -dynamiclib -flat_namespace  parser.cpp -o libtabularparser.so.$(VERSION)

liblinux:
	$(CC) $(CFLAGS) -fPIC -shared parser.cpp -o libtabularparser.so.$(VERSION)

install:
	mkdir -p  /usr/local/include/tabular_parser
	cp parser.h /usr/local/include/tabular_parser/
	$(MAKE) lib
	mv libtabularparser.so.$(VERSION) /usr/local/lib/
	ln -fs /usr/local/lib/libtabularparser.so.$(VERSION) /usr/local/lib/libtabularparser.so
	echo -e "tabular parser is installed"
	$(MAKE) clean

test:
	$(CC) ${CFLAGS}  -c -fprofile-arcs -ftest-coverage -fPIC parser.cpp tests.cpp
	$(CC) -o testapp  -fprofile-arcs -ftest-coverage parser.o tests.o $(TLIB) 
	./testapp

covnoclean:
	$(CC) ${CFLAGS}  -c -fprofile-arcs -ftest-coverage -fPIC parser.cpp tests.cpp
	$(CC) -o covapp  -fprofile-arcs -ftest-coverage parser.o tests.o $(TLIB) 
	./covapp
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	# for mac
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
	-rm -Rf *.o
	-rm -Rf a.out
	-rm -Rf *.log
	-rm -Rf $(COVCLEANFILES)






