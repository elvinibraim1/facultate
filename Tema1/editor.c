#include <stdio.h>
#include <stdlib.h>

typedef struct node { //nodul unui rand care reprezinta un caracater
	char c;
	struct node* left;
	struct node* right;
} node;

typedef struct doubleLinkedList {
	node* head;
	node* tail;
	int len;
} doubleLinkedList;

typedef struct nodeRow { //nodul unui text care reprezinta o lista de caractere, adica un rand
	struct doubleLinkedList* row;
	struct nodeRow* left;
	struct nodeRow* right;
} nodeRow;

typedef struct doubleLinkedListText {
	nodeRow* head;
	nodeRow* tail;
	int len;
} doubleLinkedListText;

void init (doubleLinkedList **list) {
	(*list) = (doubleLinkedList*) malloc (sizeof(doubleLinkedList));
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->len = 0;
}

void initText (doubleLinkedListText **list) {
	(*list) = (doubleLinkedListText*) malloc (sizeof(doubleLinkedListText));
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->len = 0;
}


void addTail (doubleLinkedList *list, char c) { //adaugarea unui caracter la sfarsit de rand

	node* tmp = (node*) malloc (sizeof (node));
	tmp->c = c;

	if(list->len == 0) {
		list->head = tmp;
		list->tail = tmp;
		tmp->left = NULL;
		tmp->right = NULL;
	} else {
		list->tail->right = tmp;
		list->tail->right->left = list->tail;
		list->tail = tmp;
		tmp->right = NULL;
	}

	list->len ++;

}

int addTailRow (doubleLinkedListText *list, doubleLinkedList *row) { //adaugare a unui rand la sfarsit
//este de tipul int pentru a verifica ulterior daca s-a adaugat sau nu

	if(row == NULL) {
		return -1;
	}

	nodeRow* tmp = (nodeRow*) malloc (sizeof (nodeRow));
	tmp->row = row;

	if(list->len == 0) {
		list->head = tmp;
		list->tail = tmp;
		tmp->left = NULL;
		tmp->right = NULL;
	} else {
		list->tail->right = tmp;
		list->tail->right->left = list->tail;
		list->tail = tmp;
		tmp->right = NULL;
	}

	list->len ++;

	return 1;

}

void removeRow(doubleLinkedListText *list, int n) { //stergere a unui rand

		int i;

		list->len--;

		nodeRow* tmp = list->head;

		for(i = 0; i < n - 1; i++) {
			tmp = tmp->right;
		}

		if(tmp->right->right == NULL)	{
			tmp->right= NULL;
			list->tail = tmp;
		} else {
			tmp->right = tmp->right->right;
			tmp->right->left = tmp;
		}

}

void freeRow(doubleLinkedList* list) { //eliberea memoriei dintr-o lista de caractere

	node* tmp = list->head;

	while(tmp != NULL) {
		node* next = tmp->right;
		free(tmp);
		tmp = next;
	}

	free(tmp);

	free(list);

}

void freeText(doubleLinkedListText* text) { //eliberea memoriei dintr-o lista de caractere
	
	nodeRow* tmp = text->head;

	while(tmp != NULL) {
		nodeRow* next = tmp->right;
		freeRow(tmp->row);
		free(tmp);
		tmp = next;
	}

	free(tmp);

	free(text);

}

void removeChar(doubleLinkedList *list, int n) { //remove pentru stergerea unui caracter

		int i;

		list->len--;

		node* tmp = list->head;

		for(i = 0; i < n - 1; i++) {
			tmp = tmp->right;
		}

		if(tmp->right->right == NULL)	{
			tmp->right= NULL;
			list->tail = tmp;
		} else {
			tmp->right = tmp->right->right;
			tmp->right->left = tmp;
		}

}

doubleLinkedList* getRow(FILE *fin) { //functie care returneaza o lista de caractere ce reprezinta un rand
//pentru a fi procesat (adaugat in text sau nu, in cazul comenzilor care modifica textul)
	
	doubleLinkedList* row = NULL;
	init(&row);

	char c = getc(fin);

	if(c == EOF)
		return NULL;

	while( c != '\n' && c != EOF) {
		addTail(row, c);
		c = getc(fin);
	}

	return row;

}

void printOut (FILE *fout, doubleLinkedList *row) { //scrie in fisierul .out un rand
	
	node* tmp = row->head;
	
	while(tmp->right != NULL) {
			fputc(tmp->c, fout);
			tmp = tmp->right;
		}	
		fputc(tmp->c, fout);
		fputc('\n', fout);

}

void printText (FILE *fout, doubleLinkedListText *text) { //scrie in fisierul .out tot textul
	
	nodeRow* tmp = text->head;

	while(tmp->right != NULL) {
		printOut(fout, tmp->row);
		tmp = tmp->right;
	}

	printOut(fout, tmp->row);

}

nodeRow* gotoRow (doubleLinkedListText* text, int row) { //returneaza un rand in functie de indicele dat

	int i;
	nodeRow* tmp = text->head;
	for(i = 1; i <= row; i++) {
		tmp = tmp->right;
	}

	return tmp;

}

void main() {
	int i;

	doubleLinkedListText* text = NULL;
	initText(&text);

	doubleLinkedListText* savedText = NULL;
	initText(&savedText);

	FILE *fin;

	fin = fopen("editor.in", "r");

	FILE *fout;

	fout = fopen("editor.out", "w");

	int x = addTailRow(text, getRow(fin)); //se adauga in text primul rand, presupun ca nu v-a fi niciodata o comanda

	int line = 1; //linia la care se afla cursorul
	int character = text->head->row->len; // caracterul la care se afla cursorul
	
	while(x > 0) {

		doubleLinkedList *row = getRow(fin);		

		if(row->len == 3 && row->head->c == ':' && row->head->right->c == ':' && row->tail->c == 'i') {
			freeRow(row);
			row = getRow(fin);
		} else {
			x = addTailRow(text, row);
			//freeRow(row);
			line = text->len;
			character = text->tail->row->len;
			continue;
		}
		
		back:	
			switch(row->head->c) {
				case 's': 
					freeRow(row);
					row = getRow(fin);
					savedText = text;
					goto back;

				case 'q': 
					printText(fout,savedText);
					freeRow(row);
					freeText(savedText);
					break;

				case 'g':
					x = 2;
					if(row->head->right->c == 'l') { //gl line
						line = row->tail->c - 48;
						character = 1;
					} else { // gc 
						if(row->len > 4) { // cazul gc charcater line
							character = row->tail->left->left->c - 48;
							line = row->tail->c - 48;
						} else { //cazul gc character; linia curenta
							character = row->tail->c - 48;
						}

					}
					freeRow(row);
					row = getRow(fin);
					goto back;
				

				case 'd':
				 	x = 2;
					if(row->len == 1) { // doar comanda d are lungimea 1
						removeChar(gotoRow(text, line -1)->row, character - 1);
						freeRow(row);
						row = getRow(fin);
						goto back;
					}

					if(row->len == 3) { // doar comanda d [chars] are lungimea 3
						for(i = 0; i < ((int) row->tail->c) - 48; i++) {
							removeChar(gotoRow(text, line -1)->row, character - 1);
					}
						freeRow(row);
						row = getRow(fin);
						goto back;
					}

					if(row->head->right->c == 'l') { //dl
						if(row->len > 3) { // dl line
							line = row->tail->c - 48;
							removeRow(text, line - 1);
						} else { // dl; linia curenta
							removeRow(text, line - 1);
						}
					}
					freeRow(row);
					row = getRow(fin);
					goto back;

				case ':' :
					x = 1;
					freeRow(row);
					continue;
					break;

				case 'b' :
					x = 2;
					removeChar(gotoRow(text, line -1)->row, character - 1);
					freeRow(row);
					row = getRow(fin);
					goto back;

				case 'u' :
					if(x == 1) // ultima operatie a fost adaugarea unei linii
						removeRow(text, line - 1);
					freeRow(row);
					row = getRow(fin);
					goto back;

				case 'r' :
					freeRow(row);
					row = getRow(fin);
					goto back;

				}
				
				break;
		}		


	fclose(fin);
	fclose(fout);
	
}