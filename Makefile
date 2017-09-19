CPP     	= 	g++-5 -O3  -std=c++1z -fexceptions -D__GLIBCXX_TYPE_INT_N_0=__int128 -D__GLIBCXX_BITSIZE_INT_N_0=128
STRIPPER 	= 	./removecomments.pl
EMCC    	=       ~/Extern/emscripten3/emscripten/emcc -Wc++11-extensions -std=c++11
OPT             = 	 -s PRECISE_I64_MATH=1
SET     	= 	-O2 -s ALLOW_MEMORY_GROWTH=1 -s ASM_JS=0
LIBPATH 	= 
SYSLIBS 	= 	-lstdc++ -lboost_regex -lboost_thread -lboost_system -lboost_date_time -lrt  -lpthread -lm
PRGS		=	celld


all: le_build celld cell_test

cell_test: le_build/cell_test.o
	$(CPP) -fexceptions -D_BOOL  $^ -I$(INCPATH) -L$(LIBPATH) $(SYSLIBS) -o $@
le_build/cell_test.o: cell_test.cpp cw_complex.h spaces.h algebra.h math_helpers.h
	$(CPP) -fexceptions -D_BOOL -c $< -I$(INCPATH) -L$(LIBPATH)  -DHAVE_IOMANIP -DHAVE_IOSTREAM -DHAVE_LIMITS_H -o $@

celld: le_build/celld.o
	$(CPP) -fexceptions -D_BOOL  $^ -I$(INCPATH) -L$(LIBPATH) $(SYSLIBS) -o $@

clean:
	rm -rf le_build celld cell_test;\

le_build/celld.o: celld.cpp celld.h simple_httpd.h cw_complex.h spaces.h algebra.h math_helpers.h
	$(CPP) -fexceptions -D_BOOL -c $< -I$(INCPATH) -L$(LIBPATH)  -DHAVE_IOMANIP -DHAVE_IOSTREAM -DHAVE_LIMITS_H -o $@

le_build:
	mkdir ./le_build

cellc-opt.js: cellct.js
	closure-compiler --language_in=ECMASCRIPT5  --compilation_level ADVANCED_OPTIMIZATIONS --js $< --warning_level QUIET > $@ && cp ./$@ ./data/
cellc.js: main.js webglfoo.js cell-stripped.js LA_helpers.js
	cat $^ > $@ && cp ./$@ ./data/

cell.js: cell.sym cell.cpp cell.h
	$(EMCC) $(OPT) $<  -o $@ -s EXPORTED_FUNCTIONS=$(shell cat $^) $(SET)
cell-stripped.js: cell.js
	$(STRIPPER) $^ > $@
cell.sym: cell.cpp
symbols=\"[`awk '$$1 ~/EMCEXPORT/{sub(/\(.*/,"");printf "\x27_"$$3"\x27,"}' $<`]\";echo $$symbols > $@; echo "Functions to export: " $$symbols;


