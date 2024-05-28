CPP = g++
BISON = bison
FLEX = flex
TGT = runme
SCAN = pic.l
PARSE = pic.y

OBJ = scan.o parse.tab.o
CFLAGS = -g
HEADERS = pic.hh

$(TGT): $(OBJ)
	$(CPP) --std=c++0x  $(OBJ) -o $(TGT) -ly 

scan.o: scan.c $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c $<

parse.tab.o:parse.tab.c $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c  $<

%.o: %.cc $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c $<

scan.c : $(SCAN) parse.tab.h
	$(FLEX) -l --yylineno -o scan.c $(SCAN)

parse.tab.c parse.tab.h : $(PARSE)
	$(BISON) -b parse -dv  $(PARSE)

clean :
	rm -f *.o *.output
	rm -f $(TGT) 
	rm -rf parse.tab.c parse.tab.h scan.c 
