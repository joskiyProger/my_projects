#include <stdio.h>
void mat_out(int matrix[4][4], int count)
{
    for (int j = 1; j <= count; j++)
    {
        for (int i = 1; i <= count; i++)
        {
            printf("%d ", matrix[i][j]); 
        }
        printf("\n");
    } 
}
int main()
{
    int count;
    scanf("%d", &count);
    int matrix[count + 1][count + 1];
    for (int j = 1; j <= count; j++)
    {
        for (int i = 1; i <= count; i++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
   if (count == 3){   
    printf("\n");
   // mat_out(matrix, count);

    printf("%d\n", (matrix[1][1]*matrix[2][2]*matrix[3][3])+(matrix[2][1]*matrix[3][2]*matrix[1][3])+(matrix[1][2]*matrix[2][3]*matrix[3][1])
    -((matrix[1][3]*matrix[2][2]*matrix[3][1])+(matrix[2][3]*matrix[3][2]*matrix[1][1])+(matrix[2][1]*matrix[1][2]*matrix[3][3])));

    } else if (count == 2) {
        printf("\n");
        mat_out(matrix, count);
        printf("%d\n", (matrix[1][1]*matrix[2][2])-(matrix[2][1]*matrix[1][2]));
    }
   return 0;
}