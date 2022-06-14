#include <stdio.h>

#define NUMBER 100

#pragma warning (disable: 4996)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int currentSum, n, arr[NUMBER];

int IfAllMinus()
{
    int i;
    int min_neg = arr[0];
    for (i = 0; i < n; i++)
    {
        if (arr[i] < 0)
            min_neg = MAX(min_neg, arr[i]);
    }
    return min_neg;
}


int maxSum()
{
    int i, j;
    int end = 0;
    int ans = 0;
    currentSum = 0;

    for (i = 0; i < n; i++)
    {
        currentSum += arr[i];
        if (currentSum > ans)
        {
            ans = currentSum;
            end = i;
        }
        else if (currentSum < 0)
            currentSum = 0;
    }
    int endinx = end;
    int answer = ans;

    for (j = endinx; j >= 0; j--)
    {
        ans -= arr[j];
        printf("arr = %d\n", arr[j]);

        if (ans == 0)
            break;
    }

    if (answer == 0)
        return IfAllMinus();
    else
        return answer;
}


int main()
{
    printf("n = ");
    scanf("%d", &n);

    printf("arr = ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // system("cls");
    // visual studio에서는 돌아가는데 code에서는 안돼서 얘만 주석처리하면 됨

    maxSum();

    return 0;
}