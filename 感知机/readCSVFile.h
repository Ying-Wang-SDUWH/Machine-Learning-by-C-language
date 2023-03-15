#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok
#include <math.h> // for sqrt
#include <time.h> 
#include <windows.h>



#define MAX_LINE_SIZE 1024   //fgets函数读取的最大字节数


double* giCsvData;           //动态分配数据内存的指针
double* minmax;
int giNumData;            //读取的数据字节数
int giNumRow;             //每行的字节数
int giNumCol;             // 每列的字节数
int k;
int number;
int* randarr;   //打乱的行序
double *coef;  //系数向量
double sum_error;
double rmse; //均方根误差
double correct;


int GetTotalLineCount(FILE* fp);              //计算csv文件中的总行数
int GetTotalColCount(FILE * fp);              //计算csv文件中的总列数（以第一行的列数为基准）
int AssignSpaceForData(int inumdata);         //通过指针*giCsvData给数据动态分配内存空间
void FreeCsvData();                           //释放动态数据内存
int ReadCsvData(char* csvFilePath);           //读取Csv中数据（本例默认数据类型为int）
void  StdData();
void  k_folders(int* k);
void randnum();
void coefficients_sgd(double l_rate, int n_epoch);
void  evaluate_algo();

