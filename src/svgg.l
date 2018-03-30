%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "circuit.h"
#include "new.tab.h"
%}
 
%%

"PS"|"FS"|"NS"|"US"|"MS"|"KS"|"MEGS"|"S"  {yylval.str = strdup(yytext);return SEC;}
"SINE" {return SINUS;}
"("   {return OPE;}	
")" {return CLO;}
"PF"|"FF"|"NF"|"UF"|"MF"|"KF"|"MEGF"|"F"  {yylval.str=strdup(yytext);return FAR;}
"PH"|"FH"|"NH"|"UH"|"MH"|"KH"|"MEGH"|"H"  {yylval.str=strdup(yytext);return HEN;}
"P"|"F"|"N"|"U"|"M"|"K"|"MEG" {yylval.str=strdup(yytext);return KINA;}
"Phz"|"Fhz"|"Nhz"|"Uhz"|"Mhz"|"Khz"|"MEGhz"|"hz"  {yylval.str=strdup(yytext);return FREQ;}
"0" {return ZER;}
"V"[A-Za-z\_0-9]* {yylval.str=strdup(yytext);return VEE;}
"I"[A-Za-z\_0-9]* {yylval.str=strdup(yytext);return CURR;}
[a-zA-Z][a-zA-Z\_0-9]*  {yylval.str=strdup(yytext);return NAME;}
(([0-9]+"."[0-9]+)|([0-9]+)) {yylval.bhalue=atof(strdup(yytext));return NUM;}
"\n" {return EOLI;}
" " {}

%%
