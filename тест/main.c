#include <stdio.h>
int main () {
	FILE *fp;

	srand(time(NULL));

	char output [2048];

	int n = 7;
	int sum=0; // n - количество бит, sum это наше десятичное число которое получится из двоичного
	char ch[] = {'0','1','0','0','1','1','0','1'};//  это наше двоичное число. число символов рано n из предыдущей строки
	printf ("%s", "hi!");
 
	for (int i=0;i<=n;i++) {//    пошли по строке бит
   		if (ch[i]=='1') {  // если i-й бит в строке = 1 ,
   			sum+=pow(2,7-i) ;// то прибавить к общей сумме 2 в степени i
   			//printf ("%c", ch[i]);
   		}
   	}
	
	if ((fp = fopen ("eprom4.dat", "w")) == NULL){
		printf ("%s", "can't open file!");
		return 1;
		}
	else {
		for (int i=0, j=0; i< 2048; i++){
			putc ( 0, fp);
			if (j >=255) j=0;
		}
			
		}
	fclose (fp);

}