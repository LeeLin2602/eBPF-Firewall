CC = g++
CFLAGS = -Wall -g

all: alg

alg: alg.cpp
	$(CC) $(CFLAGS) alg.cpp -o alg

test: alg
	cat test.txt | python3 gen.py | ./alg

clean:
	rm -f alg

.PHONY: all test clean
