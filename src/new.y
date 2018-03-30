%{
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "circuit.h"
extern FILE * yyout;
%}
%union
{
	char * str;
	double bhalue;
}


 
%token <str> NAME VEE CURR KINA FAR HEN FREQ SEC
%token <bhalue> NUM
%token EOLI CLO OPE SINUS ZER



%type <bhalue> addze unit
%type <str> var



%%
list:elem EOLI {printcircuit();}
| elem {printcircuit();}
| elem EOLI list
;

elem: 
|Resis
|Capac
|induc
|Voltag
// |Current
;

addze: ZER {$$ = 0;}
| NUM {$$ = $1 ;}
;

unit: {$$ = 1;}
| KINA {$$ = unitfn($1); }
;

var: NAME {$$ = $1;}
| ZER {$$ = "0";}
| VEE {$$ = $1; }
| CURR {$$ = $1; }
| KINA {$$ = $1;}
| FREQ {$$ = $1;}
| HEN {$$ = $1;}
| SEC {$$ = $1;}
| SINUS {$$ = "SINE";}
;






Resis: var var var addze unit  {add_elem($1,0,$2,$3,$4*$5,-1,-1,-1,-1,-1);}
;


Capac: var var var addze FAR {add_elem($1,1,$2,$3,unitfn($5)*$4,-1,-1,-1,-1,-1);}
;



induc: var var var addze HEN {add_elem($1,2,$2,$3,unitfn($5)*$4,-1,-1,-1,-1,-1);}
;


Voltag: var var var SINUS OPE addze addze addze FREQ addze SEC addze CLO  {add_elem($1,3,$2,$3,-1,$6,$7,$8*unitfn($9),$10*unitfn($11),$12);}
| var var var SINUS OPE addze addze addze FREQ addze SEC CLO {add_elem($1,3,$2,$3,-1,$6,$7,$8*unitfn($9),$10*unitfn($11),0);}
;

// Current:
//  CURR var var SINUS OPE addze addze addze FREQ addze SEC addze CLO  {add_elem($1,4,$2,$3,-1,$6,$7,$8*unitfn($9),$10*unitfn($11),$12);}
// | CURR var var SINUS OPE addze addze addze FREQ addze SEC CLO {add_elem($1,4,$2,$3,-1,$6,$7,$8*unitfn($9),$10*unitfn($11),0);} 
// ;

%%

main(int argc, char **argv)
{

	extern FILE * yyin;
	yyin = fopen(argv[1],"r");
	yyout = fopen(argv[2],"w");
	setfile(yyout);
	yyparse();
}
yyerror(char *s)
{
	fprintf(stderr, "Syntax Error\n");
}







