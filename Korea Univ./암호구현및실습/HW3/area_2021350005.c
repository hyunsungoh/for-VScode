// 두번째 문제는 입력 값의 넓이를 구하는 문제이고 O(n ln n)을 만족해야 합니다.

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int height[10];

int calculateArea(int left, int right)
{
    if (left == right)
        return height[left];
    int mid = (left + right) / 2;
    int area = MAX(calculateArea(left, mid), calculateArea(mid, right));
    int ls = mid - 1, rs = mid + 1;
    int h = MIN(height[ls + 1], height[rs]);
    area = MAX(area, h * 2);
    //int h = MIN(height[ls], height[rs]);
    //area = MAX(area, h * 2);
    while (left < ls || rs < right)
    {
        if (rs < right && (ls + 1 == left || height[ls] < height[rs+1]))
        {
            ++rs;
            h = MIN(h, height[rs]);
        }
        else
        {
            --ls;
            h = MIN(h, height[ls]);
        }
        area = MAX(area, h * (rs - ls));
    }
    return area;

}

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &height[i]);
    }

    printf("%d", calculateArea(0, n - 1));

    return 0;
}