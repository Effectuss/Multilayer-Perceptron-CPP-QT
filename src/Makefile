all: install

build:
	mkdir -p ../build
	cd ../build; cmake ../src; make

install: build
	-cp -r ../build/MultilayerPerceptron ~/MultilayerPerceptron
	-cp -r ../build/MultilayerPerceptron.app ~/MultilayerPerceptron.app

uninstall:
	rm -rf ~/MultilayerPerceptron
	rm -rf ~/MultilayerPerceptron.app

dist:
	cd ..; zip -r -9 dist.zip src

clean:
	rm -rf ../build
