#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok
#include <math.h> // for sqrt
#include <time.h> 



#define MAX_LINE_SIZE 1024   //fgets������ȡ������ֽ���
#define PI 3.14159


double* giCsvData;           //��̬���������ڴ��ָ��
int allclass;          //�������
int giNumData;            //��ȡ�������ֽ���
int giNumRow;             //ÿ�е��ֽ���
int giNumCol;             // ÿ�е��ֽ���
int k;
int number;
int* randarr;   //���ҵ�����
int correct;

double sum_error;
double right;  //��ȷ��
double mean; 
int* classnumber;  //������
int *count;
double* rate;
int **classeach;
double** vector;   //ÿ��class��ÿһά�����ֵ����


int GetTotalLineCount(FILE* fp);              //����csv�ļ��е�������
int GetTotalColCount(FILE * fp);              //����csv�ļ��е����������Ե�һ�е�����Ϊ��׼��
int AssignSpaceForData(int inumdata);         //ͨ��ָ��*giCsvData�����ݶ�̬�����ڴ�ռ�
int ReadCsvData(char* csvFilePath);           //��ȡCsv�����ݣ�����Ĭ����������Ϊint��
void  k_folders(int* k);
void randnum();
void calculate();
void testdata();
void movearray();                //������λ��ʵ��k��
void  evaluate_algo();
