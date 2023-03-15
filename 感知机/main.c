#include "readCSVFile.h"

int main(void)
{
	ReadCsvData("sonar.all-data.csv");           //读取csv数据
	StdData();
	printf("请输入折数：");
	scanf("%i", &k);
	k_folders(&k);
	randnum();
	evaluate_algo();
	FreeCsvData();                   //释放动态数组
	free(minmax);free(coef);free(randarr);
}