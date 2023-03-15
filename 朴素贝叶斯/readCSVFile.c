#include "readCSVFile.h"

//����csv�ļ��е�������
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
//����csv�ļ��е����������Ե�һ�е�����Ϊ��׼��
int GetTotalColCount(FILE * fp)
{
	int i = 0;
	char *temp;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	if (fgets(strLine, MAX_LINE_SIZE, fp))
	{
		temp = strtok(strLine, ",");  //�����ַ��������ַ���,��֮ǰ���ַ���ʣ�µı�������̬������
		while (temp != NULL)
		{
			i++;
			temp = strtok(NULL, ",");                //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��������ֽ�
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
// ͨ��ָ������ݶ�̬�����ڴ�ռ�
int AssignSpaceForData(int inumdata) {
	giCsvData = NULL;
	giCsvData = (double*)malloc(sizeof(double)*inumdata);
	if (giCsvData == NULL)
		return 0;
	memset(giCsvData, 0, sizeof(double)*inumdata);
	return 1;
}


// ��csv�ļ��ж�ȡ����
int ReadCsvData(char* csvFilePath)
{
	int i, j;
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	// ���ļ�
	if (fopen_s(&fCsv, csvFilePath, "r") != 0)
	{
		printf("open file %s failed", csvFilePath);
		return -1;
	}
	else
	{
		// ȷ����̬����Ĵ�С��Ȼ�󿪱ٿռ�
		giNumRow = GetTotalLineCount(fCsv);
		giNumCol = GetTotalColCount(fCsv);
		//printf("%i��%i��\n", giNumRow, giNumCol);
		giNumData = giNumRow * giNumCol;
		AssignSpaceForData(giNumData);

		
		// ��ȡ����
		for (i = 0; i < giNumRow; i++)
		{
			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				ptr = strtok(strLine, ",");  //�����ַ��������ַ���,��֮ǰ���ַ���ʣ�µı�������̬������
				while (ptr != NULL)
				{ 
					giCsvData[i*giNumCol + j] = atof(ptr);     //���ַ�ת��Ϊdouble�������ݲ����浽��̬������
					j++;
					ptr = strtok(NULL, ",");                //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��������ֽ�
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
		// �ر��ļ�
		fclose(fCsv);
	}
	return 1;
}

//���������ٳ�ȡ������������Ч��
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
			//printf("��%i����: %d\n", t + 1, randarr[t]);
			t++;
		}
	}
}

//k�����ݼ�
void  k_folders(int* k)
{
	number = (int)(giNumRow / *k);
}

//������Լ��������
void calculate()
{
	classnumber = (int*)malloc(sizeof(int)*allclass); //���ÿ�����ĸ���
	memset(classnumber, 0, sizeof(int)*allclass);
	for (int m = 0; m < (number*(k - 1)); m++)     //�������Լ�������
	{
		int index = randarr[m];   //��m�е��к�
		double temp = giCsvData[index*giNumCol - 1];    //��m�е�class���
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
	count = (int*)malloc(sizeof(int)*allclass); //���ÿ�����ĸ���
	memset(count, 0, sizeof(int)*allclass);
	for (int m = 0; m < (number*(k - 1)); m++)     //�������Լ�������
	{
		int index = randarr[m];  
		double temp = giCsvData[index*giNumCol - 1];    //��m�е�class���
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
	//�������ֵ
	for (int i = 0; i < allclass; i++)   //ÿ��class
	{
		for (int k = 0; k < giNumCol - 1; k++)   //ÿһ���������
		{
			for (int j = 0; j < giNumRow; j++)     //ÿ��class����к�
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
	//���������
	for (int i = 0; i < allclass; i++)   //ÿ��class
	{
		for (int k = 0; k < giNumCol - 1; k++)   //ÿһ���������
		{
			for (int j = 0; j < giNumRow; j++)     //ÿ��class����к�
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
	rate = (double*)malloc(sizeof(double)*allclass); //���ÿ�������ռ����
	memset(rate, 0, sizeof(double)*allclass);
	for (int i = 0; i < allclass; i++)
	{
		rate[i] = (double)classnumber[i] / (number * (k - 1));
	}
	//�������Լ�,����������ĸ���
	double *probabilities = (double*)malloc(sizeof(double) * allclass * (giNumRow - number * (k - 1)));
	memset(probabilities, 1, sizeof(double) * allclass * (giNumRow - number * (k - 1)));
	for (int m = 0; m < (giNumRow - number * (k - 1)); m++)  //ÿ����������
	{
		int index = randarr[m + number * (k - 1)];
		for (int i = 0; i < allclass; i++)   //ÿ��class
		{
			probabilities[m*allclass + i] = rate[i];
			for (int n = 0; n < giNumCol - 1; n++)  //��������xn
			{
				double exponent = exp(-((giCsvData[(index - 1)*giNumCol + n] - vector[i][n * 2])*(giCsvData[(index - 1)*giNumCol + n] - vector[i][n * 2])) / (2 * vector[i][n * 2 + 1] * vector[i][n * 2 + 1]));
				probabilities[m*allclass + i] *= ((1 / (sqrt(2 * PI)* vector[i][n * 2 + 1]))*exponent);
			}
		}
	}
	//��������Ƿ���ȷ
	correct = 0;
	for (int m = 0; m < (giNumRow - number * (k - 1)); m++)
	{
		int index = randarr[m + number * (k - 1)];
		double maxpro = probabilities[allclass * m];  //Ĭ�ϵ�һ��classΪ������
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


//ÿ��ִ��ʱ����������λһ��(number��)��ʵ��k��
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
		printf("\n������ȷ��%f\n", right);
		mean += right;
	}
	mean = mean/(double)k;
	printf("\n\nƽ����ȷ��%f\n", mean);
}