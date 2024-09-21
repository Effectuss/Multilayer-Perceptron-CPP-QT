all: install

build:
	mkdir -p ../build
	cd ../build; cmake ../src; make

install: build
	-cp ../build/MultilayerPerceptron ~/MultilayerPerceptron
	-cp ../build/MultilayerPerceptron.app ~/MultilayerPerceptron.app

uninstall:
	rm -rf ~/MultilayerPerceptron
	rm -rf ~/MultilayerPerceptron.app

dist:
	cd ..; zip -r -9 dist.zip src

clean:
	rm -rf ../build
