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

int main(int argc, char* argv[]){
	open_source_file(argc, argv);
	allocate_buffer();

	parse();

	deallocate_buffer();
	close_source_file();

	return 0;
}