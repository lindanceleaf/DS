#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    clock_t begin, end;
    double cost;
    //開始記錄
    begin = clock();
    /*待測試程式段*/
    printf("hello world!\n");
    //結束記錄
    end = clock();
    cost = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("constant CLOCKS_PER_SEC is: %ld, time cost is: %lf secs", CLOCKS_PER_SEC, cost);
}