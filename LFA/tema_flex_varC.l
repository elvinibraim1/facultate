%{ 
// Ibraim Elvin 331CC
	
#include <stdio.h>
#include <stdlib.h>

int noVertexes = 0;
int noFaces = 0;
int boolTexture = 0;
char *obj;
char *img;

%}

%s NEXT
%s VERTEXES
%s FACES
%s TEXTURE
%s SET_NAME_TXT
%s SET_NAME_OBJ

digit [0-9]
natural {digit}+
real {natural}\.{natural}
letter [A-Za-z]+

objectName {letter}{digit}*
textureName {letter}{digit}*\.{letter}

face {digit}{1}" "{digit}{1}" "{digit}{1}";"

vertex1 [(]{1}{real}{1}" "{real}{1}" "{real}{1}[)]{1}
vertex2 [(]{1}{real}{1}" "{real}{1}" "{real}{1}" "{real}{1}[)]{1}

txt [(]{1}{real}{1}" "{real}{1}[)]{1}

%%

<INITIAL>[\n] {
	// clear endlines
}


<INITIAL>"Object " {
	BEGIN(SET_NAME_OBJ);
}


<SET_NAME_OBJ>{objectName} {
	// save the number of current object
	obj = (char*) malloc (strlen(yytext) * sizeof(char));
	strcpy(obj, yytext);
	BEGIN(NEXT);
}


<NEXT>[\n] {
	// clear endlines
}


<NEXT>"{" {
	// start object analysys
	BEGIN(NEXT);
}


<NEXT>"vertexes " {
	// Start vertexes analysys
	BEGIN(VERTEXES);
}


<VERTEXES>{vertex1} {
	noVertexes ++;
}


<VERTEXES>{vertex2} {
	noVertexes ++;
}


<VERTEXES>" " {
	// clear spaces
}


<VERTEXES>[\n] {
	// end of vertexes
	BEGIN(NEXT);
}


<NEXT>"faces " {
	// Start faces analysys
	BEGIN(FACES);
}


<FACES>{face} {
	noFaces ++;
}


<FACES>" " {
	// clear spaces
}


<FACES>[\n] {
	// end of faces
	BEGIN(NEXT);
}


<NEXT>"texture " {
	boolTexture = 1;
	BEGIN(TEXTURE);
}


<TEXTURE>{txt} {
	// texture coordinates not used in output
}


<TEXTURE>" " {
	// clear spaces
}


<TEXTURE>[\n] {
	BEGIN(NEXT);
}


<NEXT>"img " {
	BEGIN(SET_NAME_TXT);
}


<SET_NAME_TXT>{textureName} {
	img = (char*) malloc(strlen(yytext) * sizeof(char));
	strcpy(img, yytext);
	BEGIN(NEXT);
}


<NEXT>"}" {
	printf("Object %s: varfuri: %d, fete: %d, ",obj, noVertexes, noFaces);

	if(boolTexture == 0)
		printf("fara textura\n");
		else
		printf("imagine textura %s\n", img);

	// reset values
	if (obj != NULL)
		free(obj);
	noVertexes = 0;
	noFaces = 0;
	boolTexture = 0;

	BEGIN(INITIAL);
}


%%


int yywrap(){return(1);}


void main(int argc, char **argv) {
	
	yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("!!!eroare!!!"); exit(1);
    }

	yylex();

}