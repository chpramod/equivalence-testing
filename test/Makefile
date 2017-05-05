
TESTS = simple function math concrete_return uniform_test
TESTS += cfg_test cfg_search_test conditional table_test
TESTS += structure_test shift_cast

all: cil attach
cil:
	gcc -D_GNUCC -E -I../bin/../include -DCIL=1 $(PROG).c -o ./$(PROG).i
	../cil/bin/cilly.native --out ./$(PROG).cil.c --doCrestInstrument ./$(PROG).i
	
rest:
	gcc -D_GNUCC -E -I../bin/../include ./$(PROG).cil.c -o ./$(PROG).cil.i
	gcc -D_GNUCC -c -I../bin/../include -o ./$(PROG).o ./$(PROG).cil.i
	# gcc -D_GNUCC -o $(PROG) -I../bin/../include ./$(PROG).o -L../bin/../lib/ -lserver -lcrest -lstdc++
	gcc -D_GNUCC -o $(PROG) -I../include ./$(PROG).o -L../lib/ -lserver -lcrest -lstdc++

attach:
	gcc -I../include -c ./$(PROG).cil.c -o ./$(PROG).o
	gcc -I../include -o $(PROG) ./$(PROG).o -L../lib -lserver -lcrest -lstdc++

server:
	../bin/run_crest_server ./$(PROG) 10 -dfs $(PORT)

client:
	../bin/run_crest_client ./$(PROG) 10 -dfs $(PORT)

clean:
	rm -f idcount stmtcount funcount cfg cfg_branches cfg_func_map branches
	rm -f *.i *.cil.c *.o *~
	rm -f coverage input szd_execution yices_log
	rm -f $(TESTS)
