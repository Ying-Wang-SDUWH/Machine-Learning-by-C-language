#include "readCSVFile.h"

int main(void)
{
	ReadCsvData("iris.csv");           //读取csv数据
	randnum();
	printf("请输入折数：");
	scanf("%i", &k);
	k_folders(&k);
	calculate();
	evaluate_algo();
	free(giCsvData);                  //释放动态数组
	free(randarr, classnumber,count,rate);
	for (int i = 0; i < allclass; i++)   //释放二维数组
	{
		free(classeach[i]);
		free(vector[i]);
	}
	free(classeach);
	free(vector);
}