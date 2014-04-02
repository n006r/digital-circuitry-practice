#include <stdio.h>

//вынес функцию рисования графика, дабы не засорять этот файл
//#include "draw.c"


//команда для зачистки экрана. Для линукс надо будет заменить ее на clear кажется!!!!!
//а еще я не знаю почему оно работает. Я же не указал тип переменной! Хотя компилятор предупреждает об этом
//и также говорит что изменил тип на дефолтный
//lab3.c:8:1: warning: data definition has no type or storage class [enabled by default]
//я думаю если оно не сработает в следующий раз, стоит указать тип данных. Только какой?
cleanScreen = "cls";

//заменим
#define TRUE 1 
#define FALSE 0 

int binToDec (char *binAr, int rank)
{
	int sum=0; // n - количество бит, sum это наше десятичное число которое получится из двоичного
	//char ch[] = {'0','1','0','0','1','1','0','1'};//  это наше двоичное число. число символов рано n из предыдущей строки
 
	for (int i=0;i<=rank;i++) {//    пошли по строке бит
   		if (*(binAr+i)=='1') {  // если i-й бит в строке = 1 ,
   			sum+=pow(2,rank-i) ;// то прибавить к общей сумме 2 в степени i
   			//printf ("%c", ch[i]);
   		}
   	}
   	return sum;
}

int main()
{
	

	/********************************************
	*****           открываем файл           ****
	********************************************/

	char eprom [2048];

	FILE *fp;

	if ((fp = fopen ("eprom3.dat", "r")) == NULL){
		printf ("%s", "can't open file!");
		return 1;
		}
	else {
		char i;
		int count =0;
		while ((i = getc(fp)) != EOF) {
			eprom [count++] = i;
		}		
		fclose (fp);
		//putc ((char) sum, fp);
		}


		int notOE	= TRUE;
	int PGM	= FALSE;


	char PAB [11] = {'0', '0', '0', '0', '0', '0', '0','0', '0', '1', '1'}; 
	char PC [8] = {'0', '0', '0', '0', '0', '1', '0', '0'}; 
	/********************************************
	*****         Главный цикл               ****
	********************************************/
	for (int period = 0; TRUE; period++) {
	system (cleanScreen);

	//записываем в файл
	if (PGM & notOE) {
		printf("\n", "WRITE TO EPROM!!!");
		eprom[binToDec(&PAB, 10)] = binToDec (&PC, 7);
		if ((fp = fopen ("eprom3.dat", "w")) == NULL){
			printf ("%s", "can't open file!");
			return 1;
		}
		else {
			int count =0;
			for (int c=0; c<2048; c++) {
				putc (eprom [c], fp);
			}		
			fclose (fp);
		//putc ((char) sum, fp);
		}
	printf("\n", "everythink is good!!!");
	getchar();

	}

	printf("%s%i\n", "      notOE ", notOE);	
	printf("%s%i\n", "        PGM ", PGM);	
	//printf ("\n\n\n%s%c%c%c", "PA = ", PA [0], PA [1], PA [2]);
	//printf ("\n%s%i\n", "eprom 2 = ", eprom[2]);

	printf ("\n%s", "PA = "); for (int i = 0; i < 3; i++) printf ("%c", PAB[i]);
	printf ("\n%s", "PB = "); for (int i = 3; i < 11; i++) printf ("%c", PAB[i]);
	printf ("\n%s", "PC = "); for (int i = 0; i < 8; i++) printf ("%c", PC[i]);
	printf ("\n%c", eprom [1]);
		printf("%s%i\n", "bin to dec PC ", binToDec(&PC, 7));
		printf("%s%i\n", "bin to dec PAB ", binToDec(&PAB, 10));
	printf("\n%s\n", "for next period- enter \"-\"");
	
		char inpt [20];
		scanf ("%s", inpt);
		if ( inpt [0] == 'q') break;
			if ( inpt [0] == '-') ;
			if ( inpt [0] == 'o' & inpt [1] == 'e') notOE = !notOE;
			if ( inpt [0] == 'p' & inpt [1] == 'g' & inpt [2] == 'm') PGM = !PGM;
			if ( inpt [0] == 'P' & inpt [1] == 'A') {
				printf ("\n%s", "enter PA: ");
				scanf ("%s", PAB);
			}
			if ( inpt [0] == 'P' & inpt [1] == 'B') {
				printf ("\n%s", "enter PB: ");
				scanf ("%s", PAB+3);
			}
			if ( inpt [0] == 'P' & inpt [1] == 'C') {
				printf ("\n%s", "enter PC: ");
				scanf ("%s", PC);
			}
		
	}

	return 0;
}