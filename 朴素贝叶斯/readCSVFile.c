#include "readCSVFile.h"

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


// 从csv文件中读取数据
int ReadCsvData(char* csvFilePath)
{
	int i, j;
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
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
		//printf("%i行%i列\n", giNumRow, giNumCol);
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
					giCsvData[i*giNumCol + j] = atof(ptr);     //将字符转换为double类型数据并保存到动态数组中
					j++;
					ptr = strtok(NULL, ",");                //将从文件中读取的当前行剩余字符数组，读取字符‘,’后面的字节
				}
			}
		}
		double all = giCsvData[giNumCol - 1];
		for (int i = 1; i < giNumRow-1; i++)
		{
			if (all < giCsvData[i*giNumCol + giNumCol - 1])
				all = giCsvData[i*giNumCol + giNumCol - 1];
		}
		all += 1;
		allclass = (int)all;
		// 关闭文件
		fclose(fCsv);
	}
	return 1;
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

//k分数据集
void  k_folders(int* k)
{
	number = (int)(giNumRow / *k);
}

//计算测试集相关数据
void calculate()
{
	classnumber = (int*)malloc(sizeof(int)*allclass); //存放每个类别的个数
	memset(classnumber, 0, sizeof(int)*allclass);
	for (int m = 0; m < (number*(k - 1)); m++)     //遍历测试集所有行
	{
		int index = randarr[m];   //第m行的行号
		double temp = giCsvData[index*giNumCol - 1];    //第m行的class类别
		for (int m = 0; m < allclass; m++)
		{
			if (temp == (double)m)
			{
				classnumber[m]++;
			}
		}
	}
	classeach = (int **)malloc(allclass * sizeof(int *));
	for (int i = 0; i < allclass; i++)
	{
		classeach[i] = (int *)malloc(giNumRow * sizeof(int));
		memset(classeach[i], 0, sizeof(int)*giNumRow);
	}
	count = (int*)malloc(sizeof(int)*allclass); //存放每个类别的个数
	memset(count, 0, sizeof(int)*allclass);
	for (int m = 0; m < (number*(k - 1)); m++)     //遍历测试集所有行
	{
		int index = randarr[m];  
		double temp = giCsvData[index*giNumCol - 1];    //第m行的class类别
		for (int m = 0; m < allclass; m++)
		{
			if (temp == (double)m)
			{
				int item = count[m];
				classeach[m][item] = index;
				count[m]++;
			}
		}
	}
	vector = (double **)malloc(allclass * sizeof(double *));
	for (int i = 0; i < allclass; i++)
	{
		vector[i] = (double *)malloc((giNumCol - 1) * 2 * sizeof(double));
		memset(vector[i], 0, sizeof(double)*(giNumCol - 1) * 2);
	}
	//求分量均值
	for (int i = 0; i < allclass; i++)   //每个class
	{
		for (int k = 0; k < giNumCol - 1; k++)   //每一个输入分量
		{
			for (int j = 0; j < giNumRow; j++)     //每个class里的行号
			{ 
				if (classeach[i][j] != (int)0)
				{
					int index = classeach[i][j];
					vector[i][2 * k] += giCsvData[(index - 1)*giNumCol + k];
				}
			}
			vector[i][2 * k] = vector[i][2 * k] / (double)classnumber[i];
		}
	}
	//求分量方差
	for (int i = 0; i < allclass; i++)   //每个class
	{
		for (int k = 0; k < giNumCol - 1; k++)   //每一个输入分量
		{
			for (int j = 0; j < giNumRow; j++)     //每个class里的行号
			{
				if (classeach[i][j] != (double)0)
				{
					int index = classeach[i][j];
					vector[i][2 * k+1] += (giCsvData[(index - 1)*giNumCol + k]- vector[i][2 * k])*(giCsvData[(index - 1)*giNumCol + k] - vector[i][2 * k]);
				}
			}
			vector[i][2 * k+1] = sqrt(vector[i][2 * k + 1] / (double)(classnumber[i]-1)) ;
		}
	}
}

void testdata()
{
	rate = (double*)malloc(sizeof(double)*allclass); //存放每个类别所占比例
	memset(rate, 0, sizeof(double)*allclass);
	for (int i = 0; i < allclass; i++)
	{
		rate[i] = (double)classnumber[i] / (number * (k - 1));
	}
	//遍历测试集,计算各个类别的概率
	double *probabilities = (double*)malloc(sizeof(double) * allclass * (giNumRow - number * (k - 1)));
	memset(probabilities, 1, sizeof(double) * allclass * (giNumRow - number * (k - 1)));
	for (int m = 0; m < (giNumRow - number * (k - 1)); m++)  //每个测试数据
	{
		int index = randarr[m + number * (k - 1)];
		for (int i = 0; i < allclass; i++)   //每个class
		{
			probabilities[m*allclass + i] = rate[i];
			for (int n = 0; n < giNumCol - 1; n++)  //遍历所有xn
			{
				double exponent = exp(-((giCsvData[(index - 1)*giNumCol + n] - vector[i][n * 2])*(giCsvData[(index - 1)*giNumCol + n] - vector[i][n * 2])) / (2 * vector[i][n * 2 + 1] * vector[i][n * 2 + 1]));
				probabilities[m*allclass + i] *= ((1 / (sqrt(2 * PI)* vector[i][n * 2 + 1]))*exponent);
			}
		}
	}
	//检验输出是否正确
	correct = 0;
	for (int m = 0; m < (giNumRow - number * (k - 1)); m++)
	{
		int index = randarr[m + number * (k - 1)];
		double maxpro = probabilities[allclass * m];  //默认第一个class为最大可能
		double predict = 0.0;
		for (int i = 1; i < allclass; i++)
		{
			if (maxpro < probabilities[allclass * m + i])
			{
				maxpro = probabilities[allclass * m + i];
				predict++;
			}
		}
		if (predict == giCsvData[index*giNumCol - 1])
		{
			correct++;
		}
	}
	right = (double)correct / (double)(giNumRow - number * (k - 1));
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


void  evaluate_algo()
{
	mean = 0.0;
	for (int i = 0; i < k; i++)
	{
		movearray();
		calculate();
		testdata();
		printf("\n单折正确率%f\n", right);
		mean += right;
	}
	mean = mean/(double)k;
	printf("\n\n平均正确率%f\n", mean);
}