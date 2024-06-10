#include "strings.h"
 
int main(){
    char *str = "smb://92.18.1.1/test+http://mysrv.com/Windows/+http://192.500.1.1/test+ftp://my.ru/m/n/k.txt";
    // printf("%s\n", scpy(str));
    // printf("%d\n", scmp(str, "smb://92.18.1.1/test+http://mysrv.com/Windows/+http://192.500.1.1/test+ftp://my.ru/m/n/k.txt"));
    // printf("%d\n", sspn(str, " c"));
    printf("delim: +\n");
    printf("paths: %s\n", str);
    printf("new paths: ");
    char *part = stok(str, "+");
    int first_plus = 0;
    while(part != NULL) {
        if (check_URL(part)) {
            if (first_plus) {
                printf("+%s", part);
            } 
            else {
                printf("%s", part);
                first_plus = 1;
            }
        }
        // printf("%s\n", part);
        part = stok(NULL, "+");
    }
    printf("\n");
}