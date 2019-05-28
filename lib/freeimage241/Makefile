
# configure your options in Makefile.cfg

include Makefile.cfg



all: default

default: dist examples

dist: FreeImage
	cp Source/FreeImage/*.a Dist
	cp Source/FreeImage/*.so Dist

examples: FreeImage
	make -C Examples/Linux all

FreeImage:
	@if [ ! -f .nodos2unix ]; then \
	$(DOS2UNIX) Source/*.[ch]* Source/FreeImage/*.[ch]* \
	Source/LibJPEG/*.[ch]* Source/LibMNG/*.[ch]* Source/LibPNG/*.[ch]* \
	Source/LibTIFF/*.[ch]* Source/ZLib/*.[ch]* \
	Examples/Linux/*.[ch]* ; \
	touch .nodos2unix; \
	fi
	make -C Source/FreeImage all

refix:
	rm .nodos2unix

install:
	make -C Source/FreeImage install

clean:
	rm -f Dist/* u2dtmp* .nodos2unix
	make -C Source/FreeImage clean
	make -C Examples clean
