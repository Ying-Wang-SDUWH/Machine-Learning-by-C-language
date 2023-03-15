#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok
#include <math.h> // for sqrt
#include <time.h> 



#define MAX_LINE_SIZE 1024   //fgets函数读取的最大字节数
#define PI 3.14159


double* giCsvData;           //动态分配数据内存的指针
int allclass;          //总类别数
int giNumData;            //读取的数据字节数
int giNumRow;             //每行的字节数
int giNumCol;             // 每列的字节数
int k;
int number;
int* randarr;   //打乱的行序
int correct;

double sum_error;
double right;  //正确率
double mean; 
int* classnumber;  //类别计数
int *count;
double* rate;
int **classeach;
double** vector;   //每个class、每一维输入均值方差


int GetTotalLineCount(FILE* fp);              //计算csv文件中的总行数
int GetTotalColCount(FILE * fp);              //计算csv文件中的总列数（以第一行的列数为基准）
int AssignSpaceForData(int inumdata);         //通过指针*giCsvData给数据动态分配内存空间
int ReadCsvData(char* csvFilePath);           //读取Csv中数据（本例默认数据类型为int）
void  k_folders(int* k);
void randnum();
void calculate();
void testdata();
void movearray();                //数组移位，实现k折
void  evaluate_algo();
