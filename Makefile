__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall



interp: obj/main.o obj/LibInterface.o obj/xmlinterp.o obj/klient.o obj/toolbox.o obj/xmlhandler.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/xmlinterp.o obj/klient.o obj/toolbox.o obj/xmlhandler.o -ldl -lxerces-c

obj/main.o: src/main.cpp  inc/AbstractInterp4Command.hh inc/AbstractScene.hh\
            inc/AbstractComChannel.hh inc/LibInterface.hh inc/xmlinterp.hh\
			inc/xmlhandler.hh inc/toolbox.hh inc/klient.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/klient.o: src/klient.cpp inc/klient.hh
	g++ -c ${CPPFLAGS} -o obj/klient.o src/klient.cpp

obj/toolbox.o: src/toolbox.cpp inc/toolbox.hh
	g++ -c ${CPPFLAGS} -o obj/toolbox.o src/toolbox.cpp

obj/xmlhandler.o: src/xmlhandler.cpp inc/xmlhandler.hh
	g++ -c ${CPPFLAGS} -o obj/xmlhandler.o src/xmlhandler.cpp


doc:
	cd dox; make

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
