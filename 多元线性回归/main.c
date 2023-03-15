#include "readcsv.h"

int main(void)
{
	ReadCsvData("winequality-white.csv");           //读取csv数据
	StdData();
	printf("请输入折数：");
	scanf("%i", &k);
	double l_rate; int n_epoch;
	printf("请输入学习率：");
	scanf("%f", &l_rate);
	printf("请输入更新次数：");
	scanf("%i", &n_epoch);
	k_folders(&k);
	randnum();
	evaluate_algo(l_rate,n_epoch);
	FreeCsvData();                   //释放动态数组
	free(minmax);free(randarr);free(coef);
}





