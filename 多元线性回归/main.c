#include "readcsv.h"

int main(void)
{
	ReadCsvData("winequality-white.csv");           //��ȡcsv����
	StdData();
	printf("������������");
	scanf("%i", &k);
	double l_rate; int n_epoch;
	printf("������ѧϰ�ʣ�");
	scanf("%f", &l_rate);
	printf("��������´�����");
	scanf("%i", &n_epoch);
	k_folders(&k);
	randnum();
	evaluate_algo(l_rate,n_epoch);
	FreeCsvData();                   //�ͷŶ�̬����
	free(minmax);free(randarr);free(coef);
}





