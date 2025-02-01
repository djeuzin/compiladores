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
#include "semantic.h"
#include "utils.h"

int main(int argc, char* argv[]){
	open_source_file(argc, argv);

	if(lexOnly){
		allocate_buffer();

		while(mainLex.token != ENDFILE)
			get_next_lexem();
			
		deallocate_buffer();
	}
	else{
		parse();
		semantic_analysis();
	}
	
	close_source_file();

	return 0;
}