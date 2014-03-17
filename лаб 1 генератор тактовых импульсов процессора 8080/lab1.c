#include <stdio.h>
//заменим
#define TRUE 1 
#define FALSE 0 

//осциллятор
int oscillator (int in1, int in2) {
	/*if (in1 & in2) return TRUE;
		else return FALSE;
	*/
	return in1 & in2;
}
//инвертор
int invertor (int in) {
	//if (in == TRUE) return FALSE;
	//else return TRUE;
	return !in;

}

//в функцию делителя частоты подаются указатели на все выходы. Сделано это потому, что возвращать можно только одно значение
void clock (int in, int *counter, int *toF1, int *toF2, int *toFi2, int *STSTBap, int *Fi2ap) {
	*counter += !in;
	printf("%i\n", *counter);
	if (*counter >= 4 & *counter < 6) *toF1 = FALSE;
	else *toF1 = TRUE;

	if (*counter >= 2 & *counter < 6) *toF2 = TRUE;
	else *toF2 = FALSE;

	if (*counter >= 2 & *counter < 6) *toFi2 = FALSE;
	else *toFi2 = TRUE;

	if (*counter == 7) *Fi2ap = TRUE;
	else *Fi2ap = FALSE;

	if (*counter == 3)	*STSTBap = TRUE;
	else *STSTBap = FALSE;

	if (*counter == 9) {
		*counter = 0;
	}
}

// функция рисующая диаграммы. Нужен массив хранящий предыдущие значения графика.
void drawGraph (int value, int period, int *graph) {
	//нужно чтобы переданное значение value заносилось в переданный массив в этой функции
	*(graph+period) = value;

	printf("\t");
	//вернуюю строчку делаем
	for (int i = 0;i<=period;i++){
	if (*(graph+i)) {
		if (*(graph+i-1))
			printf (           "%s", "__");
		else
			printf (           "%s", " _");}
	else
		printf (           	   "%s", "  ");
	}
	putchar ('\n');


	printf("\t\t");
	//делаем нижнюю строчку
	for (int i = 0;i<=(period);i++){
	if (*(graph+i)) {
		if (*(graph+i-1))
			printf (           "%s", "  ");
		else
			printf (           "%s", "| ");}
	else
		if (*(graph+i-1))
			printf (           "%s", "|_");
		else
			printf (           "%s", "__");

	}
	printf("\n");

}

int and (int in1, int in2) {
	return in1 & in2;
}

int notAnd (int in1, int in2) {
	return !(in1 & in2);				//ЗДЕСЬ СТОИТ УМЫШЛЕННАЯ ПОКА ОШИБКА ДЛЯ ТЕСТИРОВАНИЯ ПРОГРАММЫ
}

int notOr (int in1, int in2) {
	return !(in1 | in2);
}

int DCtrig (int d, int c, int *dcStat) {
	if (c) *dcStat= d;
	return *dcStat;
}

int main ()
{
	int XTAL1= TRUE;
	int XTAL2= TRUE;
	int SYNC = FALSE;
	int RESIN= TRUE;
	int RDYN = TRUE;

	int F1;
	int F2;
	int Fi2;



	
	
	printf("%i\n", oscillator (TRUE, FALSE));
	printf("%i\n", invertor (FALSE));
	//переменная для делителя частоты. В ней он будет хранить свой внутренний счет
	int counter= 0;
	//статус счетчика
	int status = FALSE;
	//выходы счетчика
	int toF1= FALSE;	//к выходу ф1
	int toF2;	//к выходу ф2
	int toFi2;	//к выходу фи2
	int STSTBap;//выход STSTB'
	int Fi2ap; //f2'
	int notSTSTB;
	int RESET;
	int READY;
	int dc1Stat; //сюда будет сохраняться состояние триггера
	int dc2Stat;

	/*
	printf("%i\n", clock(1, &counter, &status, &toF1, &toF2, &toFi2, &STSTBap, &Fi2ap));
	printf("%i\n", counter);
	putchar ('\a');
	getchar ();
	*/


	int F1graph [30];
	int F2graph [30];
	int Fi2graph[30];
	int STSTBapgraph [30];
	int notRESINgraph[30];
	int RDYNgraph[30];
	int RESETgraph[30];
	int READYgraph[30];
	

	//массив который хранит значения осциллятора
	int oscin [30];
	//создаем вывод

	printf("%s\n", "run");

	char exit = ' ';

	for (int period = 0; exit != 'q'; period++) {
	//period будет отсчитывать какой сейчас по счету период. Это нужно для постепенной отрисовки графика

		
		printf("%s\n\n\n\n\n\n\n\n\n");
		printf("%s\n", "           \t ------------------------------------------------");
		printf("%s", "       OSC ");	drawGraph(invertor (oscillator(XTAL1, XTAL2)), period, &oscin);
		printf("%s\n", "           ");
			clock (oscillator(XTAL1, XTAL2), &counter, &toF1, &toF2, &toFi2, &STSTBap, &Fi2ap);
			F1 = invertor (toF1);
		printf("%s"  , "        F1");	drawGraph(F1, period, &F1graph);

			F2 = invertor (toF2);
		printf("%s", "        F2");	drawGraph(F2, period, &F2graph);
			Fi2 = toFi2; 
		printf("%s", "       fi2"); drawGraph(Fi2, period, &Fi2graph);
		printf("%s", "   STSTB\'"); drawGraph(STSTBap, period, &STSTBapgraph);
			RESET = invertor (DCtrig (RESIN, Fi2ap, &dc1Stat));
			printf("%i\n", RESET);
			//notSTSTB = notOr (and (STSTBap, SYNC), FALSE);
		//printf("%s", "   notSTSTB"); 
		printf("%s", " NOT RESIN"); drawGraph(RESIN, period, &notRESINgraph);
		printf("%s", "      RDYN"); drawGraph(invertor (RDYN), period, &RDYNgraph);  //бог его знает зачем тут нужен инвертор. По идее его тут быть вообще не должно. Ну или строкой выше
		printf("%s", "     RESET"); drawGraph(RESET, period, &RESETgraph);
			READY = DCtrig (RDYN,  Fi2ap, &dc2Stat);
		printf("%s", "     READY");  drawGraph(READY, period, &READYgraph);
			
		//printf("\n%s\n", "if you want change sync-signal, just enter s-key");
		//printf("%s\n", "if you really want change RESIN signal, enter r-key");
		printf("%s\n", "Press ENTER to new period");
		exit = getchar ();
		if (exit == 's') SYNC = !SYNC;
		if (period == 2) RESIN = !RESIN;
		if (period == 2) RDYN = !RDYN;


		//каждый такт сменяется состояние xtal1 и xtal2
			XTAL1 = !XTAL1;
			XTAL2 = !XTAL2;

	}
	return 0;
}

