#include "readCSVFile.h"

int main(void)
{
	ReadCsvData("sonar.all-data.csv");           //��ȡcsv����
	StdData();
	printf("������������");
	scanf("%i", &k);
	k_folders(&k);
	randnum();
	evaluate_algo();
	FreeCsvData();                   //�ͷŶ�̬����
	free(minmax);free(coef);free(randarr);
}