### P20

**若将$y\leftarrow uniform(0,1) $改为$y\leftarrow x$，则上述算法估计的值是什么？**

更改后算法变为在直线$y=x$上从$(0,0)$到$(1,1)$的采样，$k$值为落入以原点为圆心半径为1的圆的样本个数，所以算法估计的值为
$$
\frac{4k}{n}=\frac{4}{\sqrt{2}}=2\sqrt{2}
$$

### P23

**在机器上用$4\int_0^1{\sqrt{1-x^2}}dx$估计$\pi$值，给出不同的n值及精度**

| n | 估计值 | 绝对误差 |
| ---- | ---- | ---- |
|1e+06|3.1396|0.00199265|
|1e+07|3.14211|0.000522146|
|1e+08|3.14176|0.000171786|
|1e+09|3.14162|2.99344e-05|

**设$a$、 $b$、 $c$和$d$是实数，且$a ≤ b$，$c ≤ d$， $f:[a, b] \rightarrow [c, d]$是一个连续函数，写一概率算法计算积分$\int_a^b{f(x) dx}$**

```c++
typedef double (*Function)(double);

double EvaluateIntFunction(
    Function Func, double A, double B, double C, double D, int NumSamples)
{
    int HitCount = 0;
    default_random_engine Generator;
    uniform_real_distribution<double> UniformX(A, B);

    double YMax = max(D, 0.0);
    double YMin = min(C, 0.0);

    uniform_real_distribution<double> UniformY(YMin, YMax);

    for (size_t I = 0; I < NumSamples; I++)
    {
        double X = UniformX(Generator);
        double Y = UniformY(Generator);

        if (Y > 0 && Y <= Func(X))
        {
            HitCount += 1;
        }
        else if (Y < 0 && Y >= Func(X))
        {
            HitCount -= 1;
        }
    }

    double Area = (B - A) * (YMax - YMin);

    return static_cast<double>(HitCount) /
           static_cast<double>(NumSamples) * Area;
}
```

选取三个连续函数$exp(x)$、$sqrt(x)$和$sin(x)$进行测试，测试结果如下。其中真实值直接由积分后函数计算得出。

| 函数 | n    | 估计值 | 真实值 |
| ---- | ---- | ------ | ------ |
|Exp|1e+06|17.3638|17.3673|
|Sqrt|1e+06|2.79884|2.79743|
|Sin|1e+06|1.53159|1.53029|
|Exp|1e+07|17.3634|17.3673|
|Sqrt|1e+07|2.79725|2.79743|
|Sin|1e+07|1.53091|1.53029|
|Exp|1e+08|17.3669|17.3673|
|Sqrt|1e+08|2.79719|2.79743|
|Sin|1e+08|1.53047|1.53029|
|Exp|1e+09|17.3678|17.3673|
|Sqrt|1e+09|2.79744|2.79743|
|Sin|1e+09|1.53029|1.53029|

### P24

**设$\epsilon$，$\delta$是$(0,1)$之间的常数，证明：若$I$是$\int_0^1{f(x)dx}$的正确值，$h$是由HitorMiss算法返回的值，则当$n \ge \frac{I(1-I)}{\epsilon^2 {\delta} }$，有$P(|h-I| \lt \epsilon)\ge 1 - {\delta} $**

$\because P(|h-I|\lt\epsilon)=1-P(|h-I|\ge\epsilon)\ge1-\delta$

$\therefore$问题等价于证明当$n \ge \frac{I(1-I)}{\epsilon^2 {\delta} }$时，有$P(|h-I|\ge \epsilon)\le \delta$

设随机变量$H$表示HitorMiss算法返回值，随机变量$X$表示HitorMiss中每次随机采样值，取值范围为$\{0，1\}$

两者满足$H=nX$，其中$E(X)=I$，$Var(X)=I(1-I)$，$Var(H)=\frac{Var(X)}{n}$

考虑切比雪夫不等式$P(|H-I|\ge \epsilon)\le \frac{Var(H)}{\epsilon^2}$，其中$\epsilon $为$(0,1)$之间的常数

当$n \ge \frac{I(1-I)}{\epsilon^2 {\delta} }$时，$Var(H)\le\epsilon^2\delta$，从而$P(|H-I|\ge \epsilon)\le \frac{Var(H)}{\epsilon^2}\le\delta$

### P36

运行算法10000次求K值期望，然后利用K值估计集合的势。由下表可知，n值越大，估计值越准确。原因是算法中使用的$k=\sqrt{n\pi/2}$当且仅当n趋近于无穷大时成立，当n越大该估计就越准确。

| n | 估计值 | 相对误差 |
| ---- | ---- | ---- |
|10|5.72958|0.427042|
|100|91.6732|0.0832675|
|1000|919.279|0.080721|
|10000|9788.67|0.0211334|
|100000|100337|0.00337006|

### P54

**分析dlogRH的工作原理，指出该算法相应的u和v**

### P67

