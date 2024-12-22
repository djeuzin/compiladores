/************************/
/*  Cross: C- Compiler  */
/*          __          */
/*      ___/  \___      */
/*     /__      __\     */
/*     \_/      \_/     */
/*      /________\      */
/*      \        /      */
/*       \______/       */
/************************/

#include "globals.h"
#include "lex.h"

int main(int argc, char* argv[]){
	open_source_file(argc, argv);
	allocate_buffer();

	get_next_lexem();
	while(mainLex.token != OMTM){
		get_next_lexem();
	}	

	deallocate_buffer();
	close_source_file();
	return 0;
}