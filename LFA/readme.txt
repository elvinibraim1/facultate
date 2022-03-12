Ibraim Elvin 331CC
	Varianta C - Obiecte 3D

Tema facuta in Ubuntu
Implementarea functioneaza doar pentru obiecte 3D simple, dar indiferent de
ordinea in care a fost definit obiectul.
Folosesc variabilele noVertexes si noFaces pentru a salva numarul de vertecsi,
respectiv numarul de fete al obiectului analizat. Acest lucru se face cand 
linia incepe cu "vertexes " sau "faces " (se incrementeaza variabilele corespunzatoare
de fiecare data cand gaseste un nou varf sau o noua fata).
Variabila boolTexture se foloseste pentru a afisa, la sfarsit, daca obiectul are sau nu
textura.
Sirurile de caractere obj si img stocheaza numele obiectului, respectiv numele texturii
(daca este cazul), ele vor fi afisate corespunzator cand se intalneste "}" (sfarsit de 
definire al unui obiect). Dupa afisare se reseteaza noVertexes, noFaces si boolTexture.

In aceasta implementare am folosit urmatoarele stari: NEXT, VERTEXES, FACES, TEXTURE, 
SET_NAME_TXT, SET_NAME_OBJ.

NEXT:
	Este folosit prima data intr-un obiect nou dupa ce a fost analizat si salvat
	numele. El analizeaza toate inceputurile de linie astfel: daca linia incepe
	cu "vertexes " se foloseste starea VERTEXES care numara varfurile obiectului;
	daca linia incepe cu "faces ", numara fetele obiectului folosind starea FACES;
	daca linia incepe cu "texture ", se seteaza variabila boolTexture la 1 pentru a
	putea afisa la sfarsit numele texturii folosite;
	daca linia incepe cu "img ", se salveaza numele texturii pentru afisare.
	daca linia incepe cu "}", atunci se afiseaza obiectul cu toate datele obtinute si
	incepe cu analizarea urmatorului obiect (daca este cazul

SET_NAME_TXT:
	Se foloseste de yytext pentru a stoca numele texturii curente.

SET_NAME_OBJ:
	Se foloseste de yytext pentru a stoca numele obiectului curent.