#include <stdio.h>

//вынес функцию рисования графика, дабы не засорять этот файл
#include "draw.c"


//заменим
#define TRUE 1 
#define FALSE 0 

void sram (int *notCE, int *notWE, int *DI, int *notOE, int *DO, int *internalValue) {
	//сохранение входящего значени D0 в ячейке памяти
	if (!*notCE && !*notWE)*internalValue = *DI;
	//вывод сохраненного значения
	if (!*notCE && !*notOE) *DO = *internalValue;
}

int main ()
{
	int A	= TRUE;
	int notCE	= TRUE;
	int notOE= TRUE;
	int notWE= TRUE;
	int DI	= TRUE;
	int DO = TRUE;

	//переменная которая хранит занесенное внутрь состояние ячейки sram
	int internalValue;

	//Графы для рисования графиков
	int Agraph [30];
	int notCEgraph [30];
	int notOEgraph[30];
	int notWEgraph[30];
	int DIgraph[30];
	int DOgraph[30];

	char exit = ' ';


	int period = 0;




	/********************************************
	*****         Диаграмма записи           ****
	********************************************/
	for (; exit != 'q'; period++) {

	//вызываем функцию имитирующую ячейку
		sram (&notCE, &notWE, &DI, &notOE, &DO, &internalValue);

	//выводим строку А
	printf("%s", "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("%s%i", "     notCE is ", notCE);	drawGraph(notCE, period, &notCEgraph);
	printf("%s%i", "     notOE is ", notOE);	drawGraph(notOE, period, &notOEgraph);
	printf("%s%i", "     notWE is ", notWE);	drawGraph(notWE, period, &notWEgraph);
	printf("%s", "        DI");	drawGraph(DI, period, &DIgraph);
	printf("%s%i", "        DO is ", DO);	drawGraph(DO, period, &DOgraph);
	


	printf("%s\n", "Press ENTER to new period");
	printf("%s\n", "change notCE- print c,\nchange notOE- print o,\nchange notWE- print w,");

	//предупреждение о том что ячейка памяти стала чувствительна к входу DO
	if (!notCE && !notWE) printf("%s\n", "WRITING MODE ON!\n   change DI- print d");

	//предупреждение о том, что выход DI стал информационным
	if (!notCE && !notOE) printf("%s\n", "DO RETURN VALUE!");

	exit = getchar ();
	if (exit == 'c') notCE = !notCE;
	if (exit == 'w') notWE = !notWE;
	if (exit == 'o') notOE = !notOE;
	if (exit == 'd') DI = !DI;


	}



	


	/*/********************************************
	*****         Диаграмма чтения           ****
	********************************************
	for (exit = ' '; exit != 'q'; period++) {

		//вызываем функцию имитирующую ячейку
		sram (&notCE, &notWE, &DI, &notOE, &DO, &internalValue);


	//выводим строку А
	printf("%s", "         А");	drawGraph(A, period, &Agraph);
	printf("%s", "     notCE");	drawGraph(notCE, period, &notCEgraph);
	printf("%s", "     notOE");	drawGraph(notOE, period, &notOEgraph);
	printf("%s", "     notWE");	drawGraph(notWE, period, &notWEgraph);
	printf("%s", "        DI");	drawGraph(DI, period, &DIgraph);
	printf("%s", "        DO");	drawGraph(DO, period, &DOgraph);
	


	printf("%s\n", "Press ENTER to new period");
	exit = getchar ();
	}
	*/

	return 0;
}