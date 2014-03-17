#include <stdio.h>

//вынес функцию рисования графика, дабы не засорять этот файл
#include "draw.c"


//команда для зачистки экрана. Для линукс надо будет заменить ее на clear кажется!!!!!
//а еще я не знаю почему оно работает. Я же не указал тип переменной! Хотя компилятор предупреждает об этом
//и также говорит что изменил тип на дефолтный
//lab3.c:8:1: warning: data definition has no type or storage class [enabled by default]
//я думаю если оно не сработает в следующий раз, стоит указать тип данных. Только какой?
cleanScreen = "cls";

//заменим
#define TRUE 1 
#define FALSE 0 

/*самому бы не забыть.
	inputbus это массив который имитирует входную шину D0-3, верно обратное касательно outputbus.
	load это сигнал на разрешение записи в массив queue который имитирует непосредственно память.
	unload аналогично load, только работает на вывод
	loadNum и unloadNum служат для сохранения позиций очереди на ввод и вывод
*/
void fifo (int *inputBus, int load, int *outputBus, int unload, int *queue, int *loadNum, int *unloadNum){
	//данные две строки нужна чтобы зациклить очередь
	if (*loadNum >=15) *loadNum-=15;
	if (*unloadNum >=15) *unloadNum-=15;
	if (load) {
		/*вы можете спросить что это такое и как оно работает. Я отвечу что это магия ссылок. Чтобы понять этот
		фокус, а также что такое двумерные массивы на самом деле я советую вам почитать хорошую книжку по си
		Брайана Кернигана и Денниса Ритчи. Это создатели языка си, а это пожалуй одна из лучших книг по 
		программированию вообще.*/
		int loadN = *loadNum;
		*(queue+4*loadN+0)= *(inputBus+0);
		*(queue+4*loadN+1)= *(inputBus+1);
		*(queue+4*loadN+2)= *(inputBus+2);
		*(queue+4*loadN+3)= *(inputBus+3);
		*loadNum +=1;
		printf("%s\n", "CELL WAS LOADED");
	}
	if (unload) {
		int unloadN = *unloadNum;
		*(outputBus+0) = *(queue+4*unloadN+0);
		*(outputBus+1) = *(queue+4*unloadN+1);
		*(outputBus+2) = *(queue+4*unloadN+2);
		*(outputBus+3) = *(queue+4*unloadN+3);
		*unloadNum +=1;
		printf("%s\n", "CELL WAS UNLOADED");
	}
}


int main()
{
	int notRST	= TRUE;
	int LDCK	= FALSE;
	int Dbus [4]= {FALSE, FALSE, FALSE, FALSE};
	/*почему в массиве Dbus 4 элементов? Да потому что если сделать их три, то notEMPTY тоже меняет значение
	я абсолютно не понимаю причину этого. Можете конечно поэксперементировать, но не думаю что у вас что-то выйдет.*/
	int UNCK	= FALSE;
	int Qbus [4]= {FALSE, FALSE, FALSE, FALSE};
	//почему снова 4 элементов? Да на всякий случай! см. комментарий выше
	int notEMPTY= TRUE;
	int notFULL = TRUE;

	//массив, который указывает на расположение переменных с очередью
	int queue [16] [3];

	//две переменные, в которых будет храниться номер, на котором остановилась очередь вывода и ввода
	int loadNum = 0;
	int unloadNum = 0;
	


	int notRSTgraph	[30];
	int LDCKgraph	[30];
	int Dgraph  [4] [30];
	int UNCKgraph	[30];
	int Qgraph  [4] [30];
	int notEMPTYgraph[30];
	int notFULLgraph[30];



	



	/********************************************
	*****         рисование графиков         ****
	********************************************/
	
	for (int period = 0; TRUE; period++) {

	system (cleanScreen);

		//выполняется главная функция
		fifo (&Dbus, LDCK, &Qbus, UNCK, &queue, &loadNum, &unloadNum);


	printf("%s%i", "     notRST ", notRST);	drawGraph(notRST, period, &notRSTgraph);
	printf("%s%i", "       LDCK ", LDCK);	drawGraph(LDCK, period, &LDCKgraph);
	printf("%s%i", "         D0 ", Dbus[0]);	drawGraph(Dbus[0], period, &Dgraph[0]);
	printf("%s%i", "         D1 ", Dbus[1]);	drawGraph(Dbus[1], period, &Dgraph[1]);
	printf("%s%i", "         D2 ", Dbus[2]);	drawGraph(Dbus[2], period, &Dgraph[2]);
	printf("%s%i", "         D3 ", Dbus[3]);	drawGraph(Dbus[3], period, &Dgraph[3]);
	printf("%s%i", "       UNCK ", UNCK);	drawGraph(UNCK, period, &UNCKgraph);
	printf("%s%i", "         Q0 ", Qbus[0]);	drawGraph(Qbus[0], period, &Qgraph[0]);
	printf("%s%i", "         Q1 ", Qbus[1]);	drawGraph(Qbus[1], period, &Qgraph[1]);
	printf("%s%i", "         Q2 ", Qbus[2]);	drawGraph(Qbus[2], period, &Qgraph[2]);
	printf("%s%i", "         Q3 ", Qbus[3]);	drawGraph(Qbus[3], period, &Qgraph[3]);
	printf("%s%i", "   notEMPTY ", notEMPTY);	drawGraph(notEMPTY, period, &notEMPTYgraph);
	printf("%s%i", "    notFULL ", notFULL);	drawGraph(notFULL, period, &notFULLgraph);
	//если хочется посмотреть состояние счетчиков, то раскомметируйте строчку ниже.
	//printf("%s%i%s%i\n", "loadNum = ", loadNum, "unloadNum = ", unloadNum);
	printf("\n%s\n", "for next period- enter \"-\"");
	

		char inpt [10];
		scanf ("%s", inpt);
		if ( inpt [0] == 'q') break;

		for (int c = 0; inpt[c] != '\0'; c++) {
			if ( inpt [c] == '-') ;
			if ( inpt [c] == '0') Dbus[0] = !Dbus[0];
			if ( inpt [c] == '1') Dbus[1] = !Dbus[1];
			if ( inpt [c] == '2') Dbus[2] = !Dbus[2];
			if ( inpt [c] == '3') Dbus[3] = !Dbus[3];
			if ( inpt [c] == 'l') LDCK = !LDCK;
			if ( inpt [c] == 'u') UNCK = !UNCK;
			if ( inpt [c] == 'r') {
					notRST = !notRST;
					loadNum = 1;
					unloadNum = 0;
					notEMPTY = FALSE;
					notFULL = TRUE;
			}
		}
	}

	return 0;
}