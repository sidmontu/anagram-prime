all : main

main : main.cc
	@export LD_LIBRARY_PATH=/usr/local/lib
	@g++ -O3 main.cc -L/usr/local/lib -lpapi -oanagram_checker
