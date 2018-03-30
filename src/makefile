make: svgg.l new.y circuit.c
	flex svgg.l
	bison -d  new.y
	gcc -o ac_circuit_solver new.tab.c circuit.c lex.yy.c -lfl -lm