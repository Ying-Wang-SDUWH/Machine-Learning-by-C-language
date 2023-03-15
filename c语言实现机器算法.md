# 机器学习c语言复现

> 注：所有算法均对任意数据集通用

## 1、simple linear regression（20'）

<table>
    <tr>
         <td><center>1、算法输入</center></td>
         <td ><center>训练集与测试集的分割比例</center></td>
    </tr>
    <tr>
         <td><center>2、算法输出</center></td>
         <td ><center>输出参数b0、b1和RMSE均方根误差，模型为 y=b0+b1*x</center></td>
    </tr>
    <tr>
        <td><center>3、算法评估</center> </td>
        <td ><center>RMSE均方根误差</center></td>
    </tr>
    <tr>
        <td><center>4、测试结果</center> </td>
        <td ><center>用瑞典保险数据集“insurance.csv"测试，训练模型的RMSE约为31，比基准成绩72好得多</center></td>
    </tr>
</table>
<img align="left" src="./pictures/simple.png"  width="550rpx">














## 2、multivariate linear regression（25'）

<table>
    <tr>
         <td><center>1、算法输入</center></td>
         <td ><center>总折数k、学习率、更新次数</center></td>
    </tr>
    <tr>
         <td><center>2、算法输出</center></td>
         <td ><center>单折误差、平均误差</center></td>
    </tr>
    <tr>
        <td><center>3、算法评估</center> </td>
        <td ><center>平均RMSE</center></td>
    </tr>
    <tr>
        <td><center>4、测试结果</center> </td>
        <td ><center>用“winequality-white.csv"测试，预测白酒质量，平均RMSE远低于基线值0.148</center></td>
    </tr>
</table>

<table>
    <tr>
        <td ><center><img src="./pictures/multiple2.png"  width="600rpx"></center></td>
        <td ><center><img src="./pictures/multiple1.png"  width="600rpx"> </center></td>
    </tr>
</table>



## 3、perceptron（25'）

* **预处理：在excel中把class类别（样本最后一列）替换为0/1**

<table>
    <tr>
         <td><center>1、算法输入</center></td>
         <td ><center>总折数k</center></td>
    </tr>
    <tr>
         <td><center>2、算法输出</center></td>
         <td ><center>单折正确率、平均正确率</center></td>
    </tr>
    <tr>
        <td><center>3、算法评估</center> </td>
        <td ><center>平均正确率</center></td>
    </tr>
    <tr>
        <td><center>4、测试结果</center> </td>
        <td ><center>用“sonar.all-data.csv"测试，进行矿山和岩石二分类，平均正确率约73%，远高于基线值50%</center></td>
    </tr>
</table>

<table>
    <tr>
        <td ><center><img src="./pictures/perceptron1.png"  width="600rpx"></center></td>
        <td ><center><img src="./pictures/perceptron2.png"  width="600rpx"> </center></td>
    </tr>
</table>



## 4、naive bayes（30'）

* **预处理：在excel中把class类别（样本最后一列）替换为0、1、2……**

<table>
    <tr>
         <td><center>1、算法输入</center></td>
         <td ><center>总折数k</center></td>
    </tr>
    <tr>
         <td><center>2、算法输出</center></td>
         <td ><center>单折正确率、平均正确率</center></td>
    </tr>
    <tr>
        <td><center>3、算法评估</center> </td>
        <td ><center>平均正确率</center></td>
    </tr>
    <tr>
        <td><center>4、测试结果</center> </td>
        <td ><center>用“iris.csv"测试，进行多分类; 平均正确率约96%，远高于基线值26%</center></td>
    </tr>
</table>



<table>
    <tr>
        <td ><center><img src="./pictures/b1.png"  width="600rpx"></center></td>
        <td ><center><img src="./pictures/b2.png"  width="600rpx"> </center></td>
    </tr>
</table>
