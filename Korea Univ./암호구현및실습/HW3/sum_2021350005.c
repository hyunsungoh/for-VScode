// 첫번째 문제는 1부터 n까지 덧셈 문제인데 O(ln n)을 만족해야 함

#include <stdio.h>

// divide

int sum(int n)
{
    if(n <= 1)
        return n;
    else if(n % 2 == 0)
        return sum(n/2) * 2;
    else if(n % 2 == 1)
        return sum(n-1) + n;
}

/*
9, 11, 13번째 줄     =>  divide
10, 12, 14번째 줄     =>  conquer
8 ~ 15번째 줄          =>  combine
*/

