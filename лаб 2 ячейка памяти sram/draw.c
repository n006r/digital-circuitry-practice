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