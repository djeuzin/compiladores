/************************/
/*  Cross: C- Compiler  */
/*          __          */
/*      ___/  \___      */
/*     /__      __\     */
/*     \_/      \_/     */
/*      /________\      */
/*      \        /      */
/*       \______/       */
/*                      */
/************************/

#include "globals.h"
#include "lex.h"
#include "parser.h"
#include "utils.h"

int main(int argc, char* argv[]){
	open_source_file(argc, argv);
	allocate_buffer();

	if(lexOnly){
		while(mainLex.token != ENDFILE)
			get_next_lexem();
	}
	else{
		parse();
	}
	
	deallocate_buffer();
	close_source_file();

	return 0;
}