#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok
#include <math.h> // for sqrt
#include <time.h> 



#define MAX_LINE_SIZE 1024   //fgets������ȡ������ֽ���


double* giCsvData;           //��̬���������ڴ��ָ��
double* minmax;
int giNumData;            //��ȡ�������ֽ���
int giNumRow;             //ÿ�е��ֽ���
int giNumCol;             // ÿ�е��ֽ���
int k, number;
int* randarr;   //���ҵ�����
double *coef;  //ϵ������
double sum_error;
double rmse; //���������


int GetTotalLineCount(FILE* fp);              //����csv�ļ��е�������
int GetTotalColCount(FILE * fp);              //����csv�ļ��е����������Ե�һ�е�����Ϊ��׼��
int AssignSpaceForData(int inumdata);         //ͨ��ָ��*giCsvData�����ݶ�̬�����ڴ�ռ�
void FreeCsvData();                           //�ͷŶ�̬�����ڴ�
int ReadCsvData(char* csvFilePath);       
void  StdData();
void  k_folders(int* k);
void randnum();
void coefficients_sgd(double l_rate, int n_epoch);
void  evaluate_algo(double l_rate, int n_epoch);
void movearray();
