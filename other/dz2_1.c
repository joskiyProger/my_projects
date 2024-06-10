#include <stdio.h>

int main()
{
    printf("Lower letter: ");

    int count, width;
    scanf("%d", &count);
    int symbols = 65;
    width = count*2 - 1;
    int s;
    for (int j=0; j<count ; j++) {
        for (int i=0; i<count*2 ; i++) {
            if ((width - count-i == j) || ((count+j == i) && (!(width - count-i == j-1)))){          
                printf("%c", symbols);
            } else if ((width - count-i < j) && (count+j > i)) {
                if ((count+j == i+1)) {
                    continue;
                }
                s++;
                if (i>count-1) {s=s-2;}
                printf("%c", symbols+s);
            } else {
                printf(" ");
            } 
        }
        printf("\n");
        s=0;
    }
    return 0;
}