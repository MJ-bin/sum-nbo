#Makefile
all: sum-nbo example-bin

sum-nbo: sum-nbo.cpp
	g++ sum-nbo.cpp -o sum-nbo

example-bin:
	# Octal for default shell(/bin/sh) for makefile
	printf '\000\000\003\350' > thousand.bin &&\
	printf '\000\000\001\364' > five-hundred.bin &&\
	printf '\000\000\000\310' > two-hundred.bin

clean:
	rm ./sum-nbo
	rm ./*.bin
