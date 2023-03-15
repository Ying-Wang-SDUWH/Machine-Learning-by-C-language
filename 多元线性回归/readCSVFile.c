#include "readcsv.h"

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

// �ͷŶ�̬�����ڴ�
void FreeCsvData() {
	free(giCsvData);
	giCsvData = NULL;
}

// ��csv�ļ��ж�ȡ����
int ReadCsvData(char* csvFilePath)
{
	int i, j;
	FILE* fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	// �Ѿ��������ݣ�����ɾ��
	if (giCsvData != NULL)
		FreeCsvData();
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
					giCsvData[i*giNumCol + j] = atof(ptr);     //���ַ�ת��Ϊfloat�������ݲ����浽��̬������
					j++;
					ptr = strtok(NULL, ",");                //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��������ֽ�
				}
			}
		}
		// �ر��ļ�
		fclose(fCsv);
	}
	return 1;
}

//��ÿ�������Сֵ������׼������
void  StdData()
{
	int i, j;
	double *minmax= (double*)malloc(sizeof(double)*giNumCol*2);  //��һ����Ϊ��ʼ���ֵ��Сֵ
	memset(minmax, 0, sizeof(double)*giNumCol * 2);
	for (int c = 0; c < giNumCol; c++)
	{
		minmax[2*c] = giCsvData[c];
		minmax[2*c+1] = giCsvData[c];
	}
	for (int p = 0; p < giNumCol; p++)     //ÿһ��
	{
		for (i = 0; i < giNumRow; i++)    //����Сֵ
		{
			if (giCsvData[i*giNumCol+p] < minmax[2*p])
				minmax[2*p] = giCsvData[i*giNumCol+p];
		}
		for (j = 0; j < giNumRow; j++)       //�����ֵ
		{
			if (giCsvData[j*giNumCol+p] > minmax[2 * p + 1])
				minmax[2 * p+1] = giCsvData[j*giNumCol+p];
		}
	}
	//��׼������
	for (i = 0; i < giNumRow; i++)
	{
		for (j = 0; j < giNumCol; j++)
		{
			giCsvData[i*giNumCol + j] = ((giCsvData[i*giNumCol + j]) - minmax[2 * j]) / (minmax[2 * j+1] - minmax[2 * j]);
			//printf("��%i�е�%i�У�%f\n",i+1,j+1, giCsvData[i*giNumCol + j]);
		}
	}

}

//k�����ݼ�
void  k_folders(int* k)
{
	number = (int)(giNumRow / *k);
	//printf("ÿ�۸���%i", number);
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

//Ԥ��ϵ��
void coefficients_sgd(double l_rate,int n_epoch)
{
	coef= (double*)malloc(sizeof(double)*giNumCol);
	memset(coef, 0, sizeof(double)*giNumCol);
	for (int i = 0; i < n_epoch; i++)   //ѭ������ 
	{
		for (int m=0; m < (number*(k-1)); m++)     //�������Լ�������
		{
			double yhat= coef[0];          
			int index = randarr[m];   //��m�е��к�
			//�����ڻ�
			for (int n = 0; n < giNumCol-1; n++)    
			{
				yhat += giCsvData[(index-1)*giNumCol + n]* coef[n+1];
			}
			//printf("��%i�۵�%i�������%f\n", j + 1,m+1, giCsvData[index*giNumCol-1]);
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
		//printf("��%i��ϵ����%f\n", i + 1, coef[i]);
	}
	//Ԥ�����ݼ�
	for (int m = (number*(k - 1)); m < giNumRow; m++)
	{
		int index = randarr[m];
		double yhat = coef[0];
		//Ԥ��ֵ���ڻ���
		for (int n = 0; n < giNumCol - 1; n++)
		{
			yhat += giCsvData[(index - 1)*giNumCol + n] * coef[n + 1];
		}
		/*printf("��%i��Ԥ��ֵ��%f\n", m+1, yhat);
		printf("��%i��ʵ��ֵ��%f\n\n", m+1, giCsvData[index*giNumCol - 1]);*/
		sum_error += (yhat-giCsvData[index*giNumCol - 1])*(yhat - giCsvData[index*giNumCol - 1]);
	}
	printf("�������%f\n", sum_error/(float)((giNumRow- number * (k - 1))));
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


void  evaluate_algo(double l_rate, int n_epoch)
{
	rmse = 0;
	for (int i = 0; i < k; i++)
	{
		movearray();   //������λ��ʵ��k��
		coefficients_sgd(0.001, 50);
		rmse += (sum_error / (float)((giNumRow - number * (k - 1))));
	}
	rmse = (rmse/ (double)k);
	printf("\nƽ�����%f\n", rmse);
}