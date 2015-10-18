/*
	Problem5 "Files"
	Protas Nikolay, 456gr.
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv)
{
	if (argc != 3){
		printf("Wrong args! Syntax →	[program name] [file1] [file2]\n");
		exit(0);
	}
	
	FILE* in = fopen(argv[1],"r");
	if (in==NULL){printf("File \"%s\" does not exist!\nExecution is stopped!\n",argv[1]);
	exit(0);
	}
	
	FILE* out = fopen(argv[2],"w+");
	if (out==NULL){printf("Impossible to create/open file \"%s\"\nExecution is stopped!\n",argv[2]);
	exit(0);
	}
		
	char a = (fgetc(in));
	while (a != EOF){
		fputc(toupper(a),out);
		a = (fgetc(in));
	}
	
	printf("FINISHED!\n");
	fclose(in); fclose(out);
	return 0;
	}
