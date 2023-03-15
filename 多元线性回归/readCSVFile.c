#include "readcsv.h"

//计算csv文件中的总行数
int GetTotalLineCount(FILE * fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	while (fgets(strLine, MAX_LINE_SIZE, fp))
		i++;
	fseek(fp, 0, SEEK_SET);
	return i;
}
//计算csv文件中的总列数（以第一行的列数为基准）
int GetTotalColCount(FILE * fp)
{
	int i = 0;
	char *temp;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	if (fgets(strLine, MAX_LINE_SIZE, fp))
	{
		temp = strtok(strLine, ",");  //返回字符数组中字符‘,’之前的字符，剩下的保留到静态数组中
		while (temp != NULL)
		{
			i++;
			temp = strtok(NULL, ",");                //将从文件中读取的当前行剩余字符数组，读取字符‘,’后面的字节
		}
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	return i;

}
// 通过指针给数据动态分配内存空间
int AssignSpaceForData(int inumdata) {
	giCsvData = NULL;
	giCsvData = (double*)malloc(sizeof(double)*inumdata);
	if (giCsvData == NULL)
		return 0;
	memset(giCsvData, 0, sizeof(double)*inumdata);
	return 1;
}

// 释放动态数据内存
void FreeCsvData() {
	free(giCsvData);
	giCsvData = NULL;
}

// 从csv文件中读取数据
int ReadCsvData(char* csvFilePath)
{
	int i, j;
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	// 已经有了数据，则先删除
	if (giCsvData != NULL)
		FreeCsvData();
	// 打开文件
	if (fopen_s(&fCsv, csvFilePath, "r") != 0)
	{
		printf("open file %s failed", csvFilePath);
		return -1;
	}
	else
	{
		// 确定动态数组的大小，然后开辟空间
		giNumRow = GetTotalLineCount(fCsv);
		giNumCol = GetTotalColCount(fCsv);
		giNumData = giNumRow * giNumCol;
		AssignSpaceForData(giNumData);

		// 读取数据
		for (i = 0; i < giNumRow; i++)
		{

			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				ptr = strtok(strLine, ",");  //返回字符数组中字符‘,’之前的字符，剩下的保留到静态数组中
				while (ptr != NULL)
				{
					giCsvData[i*giNumCol + j] = atof(ptr);     //将字符转换为float类型数据并保存到动态数组中
					j++;
					ptr = strtok(NULL, ",");                //将从文件中读取的当前行剩余字符数组，读取字符‘,’后面的字节
				}
			}
		}
		// 关闭文件
		fclose(fCsv);
	}
	return 1;
}

//求每列最大最小值，并标准化数据
void  StdData()
{
	int i, j;
	double *minmax= (double*)malloc(sizeof(double)*giNumCol*2);  //第一行作为初始最大值最小值
	memset(minmax, 0, sizeof(double)*giNumCol * 2);
	for (int c = 0; c < giNumCol; c++)
	{
		minmax[2*c] = giCsvData[c];
		minmax[2*c+1] = giCsvData[c];
	}
	for (int p = 0; p < giNumCol; p++)     //每一列
	{
		for (i = 0; i < giNumRow; i++)    //求最小值
		{
			if (giCsvData[i*giNumCol+p] < minmax[2*p])
				minmax[2*p] = giCsvData[i*giNumCol+p];
		}
		for (j = 0; j < giNumRow; j++)       //求最大值
		{
			if (giCsvData[j*giNumCol+p] > minmax[2 * p + 1])
				minmax[2 * p+1] = giCsvData[j*giNumCol+p];
		}
	}
	//标准化数据
	for (i = 0; i < giNumRow; i++)
	{
		for (j = 0; j < giNumCol; j++)
		{
			giCsvData[i*giNumCol + j] = ((giCsvData[i*giNumCol + j]) - minmax[2 * j]) / (minmax[2 * j+1] - minmax[2 * j]);
			//printf("第%i行第%i列：%f\n",i+1,j+1, giCsvData[i*giNumCol + j]);
		}
	}

}

//k分数据集
void  k_folders(int* k)
{
	number = (int)(giNumRow / *k);
	//printf("每折个数%i", number);
}

//打乱行序，再抽取，达成随机数的效果
void randnum()
{
	randarr = (int*)malloc(sizeof(int)*giNumRow);
	memset(randarr, 0, sizeof(int)*giNumRow);
	int RandNum;
	int j, flag = 0, t = 0;
	srand((unsigned)time(NULL));
	while (1)
	{
		flag = 0;
		if (t == giNumRow)
			break;
	
		RandNum = (rand() % (giNumRow)) + 1;
		for (j = 0; j < t; j++)
		{
			if (randarr[j] == RandNum)
				flag = 1;
		}
		if (flag != 1)
		{
			randarr[t] = RandNum;
			//printf("第%i个是: %d\n", t + 1, randarr[t]);
			t++;
		}
	}
}

//预测系数
void coefficients_sgd(double l_rate,int n_epoch)
{
	coef= (double*)malloc(sizeof(double)*giNumCol);
	memset(coef, 0, sizeof(double)*giNumCol);
	for (int i = 0; i < n_epoch; i++)   //循环次数 
	{
		for (int m=0; m < (number*(k-1)); m++)     //遍历测试集所有行
		{
			double yhat= coef[0];          
			int index = randarr[m];   //第m行的行号
			//计算内积
			for (int n = 0; n < giNumCol-1; n++)    
			{
				yhat += giCsvData[(index-1)*giNumCol + n]* coef[n+1];
			}
			//printf("第%i折第%i行输出：%f\n", j + 1,m+1, giCsvData[index*giNumCol-1]);
			double error=yhat - giCsvData[index*giNumCol-1];
			coef[0] -= l_rate * error;
			for (int n = 0; n < giNumCol - 1; n++)
			{
				coef[n + 1] -= l_rate * error*giCsvData[(index - 1)*giNumCol + n];
			}
		}
	}
	for (int i = 0; i < giNumCol; i++)
	{
		//printf("第%i个系数：%f\n", i + 1, coef[i]);
	}
	//预测数据集
	for (int m = (number*(k - 1)); m < giNumRow; m++)
	{
		int index = randarr[m];
		double yhat = coef[0];
		//预测值（内积）
		for (int n = 0; n < giNumCol - 1; n++)
		{
			yhat += giCsvData[(index - 1)*giNumCol + n] * coef[n + 1];
		}
		/*printf("第%i行预测值：%f\n", m+1, yhat);
		printf("第%i行实际值：%f\n\n", m+1, giCsvData[index*giNumCol - 1]);*/
		sum_error += (yhat-giCsvData[index*giNumCol - 1])*(yhat - giCsvData[index*giNumCol - 1]);
	}
	printf("单折误差%f\n", sum_error/(float)((giNumRow- number * (k - 1))));
}

//每次执行时，就往后移位一折(number个)，实现k折
void movearray()
{
	for (int i = 0; i < number; i++)
	{
		int lastitem = randarr[giNumRow - 1];
		for (int j = giNumRow - 1; j > 0; j--)
		{
			randarr[j] = randarr[j - 1];
		}
		randarr[0] = lastitem;
	}
}


void  evaluate_algo(double l_rate, int n_epoch)
{
	rmse = 0;
	for (int i = 0; i < k; i++)
	{
		movearray();   //数组移位，实现k折
		coefficients_sgd(0.001, 50);
		rmse += (sum_error / (float)((giNumRow - number * (k - 1))));
	}
	rmse = (rmse/ (double)k);
	printf("\n平均误差%f\n", rmse);
}