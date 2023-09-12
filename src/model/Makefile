all: run

build:
	g++ -std=c++17 tmp_main.cc ./parser/parser.cc ./data/dataset.cc ./data/mapping.cc ./data/picture.cc -o app

run: build
	./app