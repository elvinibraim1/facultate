#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int posibleMoves; // numarul de copii (daca jocul nu s-a terminat cu victoria unui jucator)
	char board[3][3]; // tabla de joc
	int *free; // pozitiile libere (1->9); free % 3 - coloana; free / 3 - linia
	int depth; // adancimea nodului
	struct node *next[9]; // nodurile arborelui
	char TF; // 
	char toMove; // jucatorul care trebuie sa mute
} node;

node* init (node **tree, FILE *fin) {

	(*tree) = (node*) malloc (sizeof (node));
	(*tree)->posibleMoves = 0;
	(*tree)->free = (int*) malloc (9 * sizeof (int));
	(*tree)->depth = 0;

	char c;

	// citesc din fisier si setez pozitiile libere

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c = fgetc(fin);
			(*tree)->board[i][j] = c;
			fgetc(fin);

			if (c == '-') {
				*((*tree)->free + (*tree)->posibleMoves) = 3*i + j;
				(*tree)->posibleMoves ++;
			}
		}
	}

	return *tree;

}

int verifyEnd (node *tree) {

	// functia verifica daca unul dintre cei doi jucatori a castigat
	
	if (tree->board[0][0] == tree->board[1][1] && 
		tree->board[1][1] == tree->board[2][2] && 
		tree->board[1][1] != '-') {
		return 1; //diagonala principala
	}

	if (tree->board[1][1] == tree->board[0][2] && 
		tree->board[1][1] == tree->board[2][0] && 
		tree->board[1][1] != '-') {
		return 1; //diagonala secundara
	}

	for (int i = 0; i < 3; i++) {
		if (tree->board[i][0] == tree->board[i][1] && 
			tree->board[i][1] == tree->board[i][2] && 
			tree->board[i][1] != '-') {
			return 1; //linie
		}

		if (tree->board[0][i] == tree->board[1][i] && 
			tree->board[1][i] == tree->board[2][i] && 
			tree->board[1][i] != '-') {
			return 1; //coloana
		}
	}

	return 0; // la nodul dat nu a castigat niciunul dintre jucatori
}

char verifyEndC (node *tree) {

	if (tree->board[0][0] == tree->board[1][1] && 
		tree->board[1][1] == tree->board[2][2] && 
		tree->board[1][1] != '-') {
		return tree->board[1][1]; //diagonala principala
	}

	if (tree->board[1][1] == tree->board[0][2] && 
		tree->board[1][1] == tree->board[2][0] && 
		tree->board[1][1] != '-') {
		return tree->board[1][1]; //diagonala secundara
	}

	for (int i = 0; i < 3; i++) {
		if (tree->board[i][0] == tree->board[i][1] && 
			tree->board[i][1] == tree->board[i][2] && 
			tree->board[i][1] != '-') {
			return tree->board[i][1]; //linie
		}

		if (tree->board[0][i] == tree->board[1][i] && 
			tree->board[1][i] == tree->board[2][i] && 
			tree->board[1][i] != '-') {
			return tree->board[1][i]; //coloana
		}
	}
}

void playX (node *tree) {

	for (int i = 0; i < tree->posibleMoves; i++) {

		// pentru fiecare fiu

		tree->next[i] = (node*) malloc (sizeof (node)); // se aloca urmatorul nod
		tree->next[i]->posibleMoves = tree->posibleMoves - 1; // se decrementeaza miscarile posibile
		tree->next[i]->depth = tree->depth + 1; 

		if(tree->toMove == 'X')
			tree->next[i]->toMove = 'O';
		else tree->next[i]->toMove='X';

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				tree->next[i]->board[j][k] = tree->board[j][k]; 
			}
		}

		// se copiaza starea trecuta si se modfica ulterior una dintre pozitiile libere cu X sau O

		if (tree->posibleMoves % 2 == 0) {
			// daca avem numar par de pozitii libere, urmatorul care va muta este O si X in caz
			// contrar; pentru cazul in care X este jucatorul care a inceput jocul
			tree->next[i]->board[*(tree->free + i) / 3][*(tree->free + i) % 3] = 'O';
		} else {
			tree->next[i]->board[*(tree->free + i) / 3][*(tree->free + i) % 3] = 'X';
		}

		// se afla din nou pozitiile libere

		if (verifyEnd(tree->next[i]) == 0 && tree->next[i]->posibleMoves > 0) {

			tree->next[i]->free = (int*) malloc (tree->next[i]->posibleMoves * sizeof (int));
			tree->next[i]->posibleMoves = 0;

			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					if (tree->next[i]->board[k][j] == '-') {

						*(tree->next[i]->free + tree->next[i]->posibleMoves) = 3*k + j;
						tree->next[i]->posibleMoves ++;
				}
			}
		}

		if (verifyEnd(tree->next[i]) == 1)
			tree->next[i]->posibleMoves = 0;

			playX(tree->next[i]); // se apelaeaza recursiv pana cand nu mai exista miscari posibile
		}

	}

}

void playO (node *tree) {

	for (int i = 0; i < tree->posibleMoves; i++) {

		tree->next[i] = (node*) malloc (sizeof (node));
		tree->next[i]->posibleMoves = tree->posibleMoves - 1;
		tree->next[i]->depth = tree->depth + 1;

		if(tree->toMove == 'X')
			tree->next[i]->toMove = 'O';
		else tree->next[i]->toMove='X';

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				tree->next[i]->board[j][k] = tree->board[j][k];
			}
		}

		if (tree->posibleMoves % 2 == 0) {
			tree->next[i]->board[*(tree->free + i) / 3][*(tree->free + i) % 3] = 'X';
		} else {
			tree->next[i]->board[*(tree->free + i) / 3][*(tree->free + i) % 3] = 'O';
		}

		if (verifyEnd(tree->next[i]) == 0 && tree->next[i]->posibleMoves > 0) {

			tree->next[i]->free = (int*) malloc (tree->next[i]->posibleMoves * sizeof (int));
			tree->next[i]->posibleMoves = 0;

			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					if (tree->next[i]->board[k][j] == '-') {

						*(tree->next[i]->free + tree->next[i]->posibleMoves) = 3*k + j;
						tree->next[i]->posibleMoves ++;
				}
			}
		}

		if (verifyEnd(tree->next[i]) == 1)
			tree->next[i]->posibleMoves = 0;

			playO(tree->next[i]);
		}

	}

}

void printfisc1 (node* tree, FILE* fout) {

	// la afisare, apelul recursiv de face in interiorul for-ului de fii, doar in cazul in care
	// jocul nu s-a terminat (cu egal sau victorie)
	for (int i = 0; i < tree->posibleMoves; i ++) {

		for (int j = 0; j < 3;  j++) {
			fputc('\t', fout);
			for (int m = 0; m < tree->depth; m ++) {
					fputc('\t', fout);
				}
				for (int k = 0; k < 2; k++) {
					fputc(tree->next[i]->board[j][k], fout);
					fputc(' ', fout);
				}	fputc(tree->next[i]->board[j][2], fout);
			fputc('\n', fout);
		}

		fputc('\n', fout);

		if(verifyEnd(tree->next[i]) == 0 && tree->posibleMoves > 0) { 
			printfisc1(tree->next[i], fout);

		}

	}

}

void freeC1 (node* tree) {
	printf("%d\n",tree->posibleMoves);

	for (int i = 0; i < tree->posibleMoves; i++) {

		if(verifyEnd(tree->next[i]) == 0 && tree->posibleMoves >= 0) { 
		freeC1 (tree->next[i]);
	}

	}
}

void TF (node* tree, char player) {

	if (tree->posibleMoves == 0 && player != tree->TF) {
		if (verifyEnd (tree) == 1)
			tree->TF = 'T';
			else {
				tree->TF = 'F';
			}
	}

	if (tree->posibleMoves == 0 && tree->toMove == tree->TF)
		tree->TF = 'F';

	for (int i = 0; i < tree->posibleMoves; i++) {
		if(tree->next[i] != NULL)
			TF(tree->next[i], player);

	
			printf("%c %d %d %d\n", tree->toMove, tree->depth, i, verifyEnd(tree));
		
	}
}

void printfisc2 (node* tree, FILE* fout) {
	for (int i = 0; i < tree->posibleMoves; i ++) {
		fputc('\t', fout);
			for (int m = 0; m < tree->depth; m ++) {
					fputc('\t', fout);
				}

				fputc(tree->TF, fout);
				fputc('\n', fout);

		if(verifyEnd(tree->next[i]) == 0 && tree->posibleMoves > 0) { 
			printfisc2(tree->next[i], fout);

		}

	}

}

void main (int argc, char *argv[]) {

	FILE *fin = fopen(argv[2], "r");

	FILE *fout = fopen(argv[3], "w");

	if (strcmp(argv[1], "-c1") == 0) {
		//cerinta 1
		char toMove = fgetc(fin);

		fgetc(fin);

		node* gameTree = NULL;
		init(&gameTree, fin);

		// se scrie in fisier starea initiala

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				fputc(gameTree->board[i][j], fout);
				fputc(' ', fout);
			}
			fputc(gameTree->board[i][2], fout);
			fputc('\n', fout);
		}

		fputc('\n', fout);

		gameTree->toMove = toMove;

		// verific cu datele de intrare daca jucatorul X sau jucatorul O a inceput partida (de la 0)

		if (gameTree->posibleMoves % 2 == 0) {
			if (toMove == 'X') {
				playO(gameTree);
			} else {
				playX(gameTree);
			}	
		} else {
			if (toMove == 'X') {
				playX(gameTree);
			} else {
				playO(gameTree);
			}
		}

		printfisc1(gameTree, fout); // se scrie in fisier arborele de joc
		freeC1(gameTree);

		}

	if (strcmp(argv[1], "-c2") == 0) {

		char toMove = fgetc(fin);

		fgetc(fin);

		node* gameTree = NULL;
		init(&gameTree, fin);

		gameTree->toMove = toMove;

		if (gameTree->posibleMoves % 2 == 0) {
			if (toMove == 'X') {
				playO(gameTree);
			} else {
				playX(gameTree);
			}	
		} else {
			if (toMove == 'X') {
				playX(gameTree);
			} else {
				playO(gameTree);
			}
		}

		//TF(gameTree, toMove);

		//printfisc2(gameTree, fout);

	}

	if (strcmp(argv[1], "-c3") == 0) {
		
	}

	
}