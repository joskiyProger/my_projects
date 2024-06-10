#include <stdio.h>

int main() {
    int rows = 14, cols = 11;
    int matrix[rows][cols]; 
    int string_start = 0, string_stop = cols, counter = 1;
    int string_go_back = 0;
    int rows_start = 1, rows_stop = rows-1;

    for (int i = 0; i<rows ; i++) {
        if (string_go_back == 1) {
            for (int j = string_stop-1 ; j>=string_start ; j--){
                matrix[i][j] = counter;
                counter++;
            }
            for (int z = rows_stop-1 ; z>=rows_start ; z--) {
                matrix[z][string_start] = counter;
                counter++;
                i = z-1;
            }
            rows_stop--;
            rows_start++;
            string_start++;
            string_stop--;
            string_go_back = 0;
        } else {
            for (int j = string_start ; j<string_stop ; j++) {
                matrix[i][j] = counter;
                counter++;
            }
            for (int z = rows_start ; z<rows_stop ; z++) {
                matrix[z][string_stop-1] = counter;
                counter++;
                i = z;
            }
            string_go_back = 1;
        }
        if (counter > rows*cols) { break; }
    }
    printf("\n");
    for (int i = 0; i<rows ; i++) {
        for (int j = 0; j<cols ; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}