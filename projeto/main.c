#include "globals.h"
#include "lex.h"

int main(int argc, char* argv[]){
	open_source_file(argc, argv);
	allocate_buffer();

	mainLex = get_next_lexem();
	while(mainLex.last != 1){
		mainLex = get_next_lexem();
	}	

	deallocate_buffer();
	close_source_file();
	return 0;
}