#include "readCSVFile.h"

int main(void)
{
	ReadCsvData("iris.csv");           //��ȡcsv����
	randnum();
	printf("������������");
	scanf("%i", &k);
	k_folders(&k);
	calculate();
	evaluate_algo();
	free(giCsvData);                  //�ͷŶ�̬����
	free(randarr, classnumber,count,rate);
	for (int i = 0; i < allclass; i++)   //�ͷŶ�ά����
	{
		free(classeach[i]);
		free(vector[i]);
	}
	free(classeach);
	free(vector);
}