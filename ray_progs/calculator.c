#include "raylib.h"
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
int matching_variable(int *variables, int digit);
int delete (char* symbol, int i);
int take_last_operation(char* symbol, char* mas_last_operation, int i, int* operation_count, int* variables);
int do_operation(int* num1, int* num2, char operation, char pre_last_operation, int *operation_count);
Vector2 mousePosition;

int main() {
    SetTargetFPS(100);
    int variables[50];
    char symbol[50], mas_last_operation[3] = {' ', ' ', '\0'};
    for (int z = 0; z<30 ; z++) {
        variables[z] = 0;
        symbol[z] = ' ';
    }
    InitWindow(395, 489, "калькулятор");
    
    int i = 0;
    int num1 = 0, num2 = 0, operations_count = 0, result = 0, i_max = 0, mode = 1, switcher_x_pos = 330;
    int switcher_r = 0, switcher_g = 255; 

    while (!WindowShouldClose())
    {
        mousePosition = GetMousePosition();
        BeginDrawing();
        DrawFPS(300,10);
        Color switcer_color = {switcher_r, switcher_g, 0, 255}; 
            ClearBackground(RAYWHITE);
            DrawRectangle(10, 200, 90, 65, BLACK); //строка 1 
            DrawRectangle(105, 200, 90, 65, BLACK);
            DrawRectangle(200, 200, 90, 65, BLACK);
            DrawRectangle(295, 200, 90, 65, BLACK);
            DrawRectangle(11, 201, 88, 63, WHITE);
            DrawRectangle(106, 201, 88, 63, WHITE);
            DrawRectangle(201, 201, 88, 63, WHITE);
            DrawRectangle(296, 201, 88, 63, WHITE);
            DrawText("1", 53, 220, 27, BLACK);
            DrawText("2", 145, 220, 27, BLACK);
            DrawText("3", 237, 220, 27, BLACK);
            DrawText("+", 333, 220, 27, BLACK);
            if ((mousePosition.x > 10) && (mousePosition.y > 200) && (mousePosition.x < 100) && (mousePosition.y < 265)) {
                DrawRectangle(11, 201, 88, 63, GRAY);
                DrawText("1", 53, 220, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '1';}
                }
            if ((mousePosition.x > 105) && (mousePosition.y > 200) && (mousePosition.x < 195) && (mousePosition.y < 265)) {
                DrawRectangle(106, 201, 88, 63, GRAY);
                DrawText("2", 145, 220, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '2';}}
            if ((mousePosition.x > 200) && (mousePosition.y > 200) && (mousePosition.x < 290) && (mousePosition.y < 265)) {
                DrawRectangle(201, 201, 88, 63, GRAY);
                DrawText("3", 237, 220, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '3';}}
            if ((mousePosition.x > 295) && (mousePosition.y > 200) && (mousePosition.x < 385) && (mousePosition.y < 265)) {
                DrawRectangle(296, 201, 88, 63, GRAY);
                DrawText("+", 333, 220, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    mas_last_operation[1] = mas_last_operation[0];
                    i++;
                    symbol[i] = '+';
                    i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                    if (mode) {
                        if (mas_last_operation[0] != ' ') {
                            if ((mas_last_operation[0] == mas_last_operation[1]) || (mas_last_operation[1] == ' ')) {
                                result = do_operation(&num1, &num2, symbol[i-1], mas_last_operation[0], &operations_count);
                            }
                        }
                        num1 = result;
                        num2 = 0;
                        if ((operations_count % 2) == 0) {
                           operations_count++;
                        }
                    }
                }
            }

            DrawRectangle(10, 270, 90, 65, BLACK); // строка 2
            DrawRectangle(105, 270, 90, 65, BLACK);
            DrawRectangle(200, 270, 90, 65, BLACK);
            DrawRectangle(295, 270, 90, 65, BLACK);
            DrawRectangle(11, 271, 88, 63, WHITE);
            DrawRectangle(106, 271, 88, 63, WHITE);
            DrawRectangle(201, 271, 88, 63, WHITE);
            DrawRectangle(296, 271, 88, 63, WHITE);
            DrawText("4", 49, 290, 27, BLACK);
            DrawText("5", 145, 290, 27, BLACK);
            DrawText("6", 237, 290, 27, BLACK);
            DrawText("-", 333, 290, 27, BLACK);
            if ((mousePosition.x > 10) && (mousePosition.y > 270) && (mousePosition.x < 100) && (mousePosition.y < 335)) {
                DrawRectangle(11, 271, 88, 63, GRAY);
                DrawText("4", 49, 290, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '4';}}
            if ((mousePosition.x > 105) && (mousePosition.y > 270) && (mousePosition.x < 195) && (mousePosition.y < 335)) {
                DrawRectangle(106, 271, 88, 63, GRAY);
                DrawText("5", 145, 290, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '5';}}
            if ((mousePosition.x > 200) && (mousePosition.y > 270) && (mousePosition.x < 290) && (mousePosition.y < 335)) {
                DrawRectangle(201, 271, 88, 63, GRAY);
                DrawText("6", 237, 290, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '6';}}
            if ((mousePosition.x > 295) && (mousePosition.y > 270) && (mousePosition.x < 385) && (mousePosition.y < 335)) {
                DrawRectangle(296, 271, 88, 63, GRAY);
                DrawText("-", 333, 290, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    mas_last_operation[1] = mas_last_operation[0];
                    i++;
                    symbol[i] = '-';
                    i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                    if (mode) {
                        if (mas_last_operation[0] != ' ') {
                            if ((mas_last_operation[0] == mas_last_operation[1]) || (mas_last_operation[1] == ' ')) {
                                result = do_operation(&num1, &num2, symbol[i-1], mas_last_operation[0], &operations_count);
                            }
                        }
                        num1 = result;
                        num2 = 0;
                        if ((operations_count % 2) == 0) {
                            operations_count++;
                        }
                    }
                }
            }

            DrawRectangle(10, 340, 90, 65, BLACK); // строка 3
            DrawRectangle(105, 340, 90, 65, BLACK);
            DrawRectangle(200, 340, 90, 65, BLACK);
            DrawRectangle(295, 340, 90, 65, BLACK);
            DrawRectangle(11, 341, 88, 63, WHITE);
            DrawRectangle(106, 341, 88, 63, WHITE);
            DrawRectangle(201, 341, 88, 63, WHITE);
            DrawRectangle(296, 341, 88, 63, WHITE);
            DrawText("7", 49, 360, 27, BLACK);
            DrawText("8", 145, 360, 27, BLACK);           
            DrawText("9", 237, 360, 27, BLACK);
            DrawText("*", 333, 360, 27, BLACK);
            if ((mousePosition.x > 10) && (mousePosition.y > 340) && (mousePosition.x < 100) && (mousePosition.y < 405)) {
                DrawRectangle(11, 341, 88, 63, GRAY);
                DrawText("7", 49, 360, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '7';};}
            if ((mousePosition.x > 105) && (mousePosition.y > 340) && (mousePosition.x < 195) && (mousePosition.y < 405)) {
                DrawRectangle(106, 341, 88, 63, GRAY);
                DrawText("8", 145, 360, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '8';}}
            if ((mousePosition.x > 200) && (mousePosition.y > 340) && (mousePosition.x < 290) && (mousePosition.y < 405)) {
                DrawRectangle(201, 341, 88, 63, GRAY);
                DrawText("9", 237, 360, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = '9';}}
            if ((mousePosition.x > 295) && (mousePosition.y > 340) && (mousePosition.x < 385) && (mousePosition.y < 405)) {
                DrawRectangle(296, 341, 88, 63, GRAY);
                DrawText("*", 333, 360, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    mas_last_operation[1] = mas_last_operation[0];
                    i++;
                    symbol[i] = '*';
                    i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                    if (mode) {
                        if (mas_last_operation[0] != ' ') {
                            if ((mas_last_operation[0] == mas_last_operation[1]) || (mas_last_operation[1] == ' ')) {
                                result = do_operation(&num1, &num2, symbol[i-1], mas_last_operation[0], &operations_count);
                            }
                        }
                        num1 = result;
                        num2 = 0;
                        if ((operations_count % 2) == 0) {
                            operations_count++;
                        }
                    }
                }
            }

            DrawRectangle(10, 410, 90, 65, BLACK); // строка 4 
            DrawRectangle(105, 410, 90, 65, BLACK);
            DrawRectangle(200, 410, 90, 65, BLACK);
            DrawRectangle(295, 410, 90, 65, BLACK);
            DrawRectangle(11, 411, 88, 63, WHITE);
            DrawRectangle(106, 411, 88, 63, WHITE);
            DrawRectangle(201, 411, 88, 63, WHITE);
            DrawRectangle(296, 411, 88, 63, WHITE);
            DrawText("del", 38, 430, 27, BLACK);
            DrawText("0", 145, 430, 27, BLACK);
            DrawText("/", 237, 430, 30, BLACK);
            DrawText("=", 333, 430, 27, BLACK);
            if ((mousePosition.x > 10) && (mousePosition.y > 410) && (mousePosition.x < 100) && (mousePosition.y < 475)) {
                DrawRectangle(11, 411, 88, 63, GRAY);
                DrawText("del", 38, 430, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                symbol[i] = ' ';
                i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                num1 = 0;
                num2 = 0;
                i_max = 0;
                operations_count = 0;
                result = 0;}}
            if ((mousePosition.x > 105) && (mousePosition.y > 410) && (mousePosition.x < 195) && (mousePosition.y < 475)) {
                DrawRectangle(106, 411, 88, 63, GRAY);
                DrawText("0", 145, 430, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if ((operations_count % 2) == 0) {
                        if (num1 != 0) {
                            i++;
                            symbol[i] = '0';
                        }
                    } else {
                        if (num2 != 0) {
                            i++;
                            symbol[i] = '0';
                        }
                    }                     
                } 
            }
            if ((mousePosition.x > 200) && (mousePosition.y > 410) && (mousePosition.x < 290) && (mousePosition.y < 475)) {
                DrawRectangle(201, 411, 88, 63, GRAY);
                DrawText("/", 237, 430, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    mas_last_operation[1] = mas_last_operation[0];
                    i++;
                    symbol[i] = '/';
                    i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                    if (mode) {
                        if (mas_last_operation[0] != ' ') {
                            if ((mas_last_operation[0] == mas_last_operation[1]) || (mas_last_operation[1] == ' ')) {
                                result = do_operation(&num1, &num2, symbol[i-1], mas_last_operation[0], &operations_count);
                            }
                        }
                        num1 = result;
                        num2 = 0;
                        if ((operations_count % 2) == 0) {
                            operations_count++;
                        }
                    }
                }
            }
            if ((mousePosition.x > 295) && (mousePosition.y > 410) && (mousePosition.x < 385) && (mousePosition.y < 475)) {
                DrawRectangle(296, 411, 88, 63, GRAY);
                DrawText("=", 333, 430, 27, BLACK);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                i++;
                
                symbol[i] = '=';
                i = take_last_operation(symbol, mas_last_operation, i, &operations_count, variables);
                num1 = result;
                num2 = 0;
                operations_count++;
                }
            }
            // переключатель
            if (mode) {
                DrawText("Mode:", 240, 161, 26, BLACK);
                DrawCircle(330, 175, 7, GRAY);
                DrawCircle(350, 175, 7, GRAY);
                DrawRectangle(330, 168, 20, 14, GRAY);
                DrawCircle(switcher_x_pos, 175, 11, BLACK);
                DrawCircle(switcher_x_pos, 175, 10, switcer_color);
                DrawText("normal", 280, 135, 20, BLACK);
                if ((mousePosition.x > 325) && (mousePosition.y > 160) && (mousePosition.x < 350) && (mousePosition.y < 186) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    mode = 0;
                }
                if (switcher_x_pos<350) {
                    switcher_x_pos++;
                }
                if (switcher_r>0) {
                    switcher_r-= 12;
                }
                if (switcher_g<255) {
                    switcher_g+= 12;
                }
            } else { 
                DrawText("Mode:", 240, 161, 26, BLACK);
                DrawCircle(350, 175, 7, GRAY);
                DrawCircle(330, 175, 7, GRAY);
                DrawRectangle(330, 168, 20, 14, GRAY);
                DrawCircle(switcher_x_pos, 175, 11, BLACK);
                DrawCircle(switcher_x_pos, 175, 10, switcer_color);
                DrawText("strange)", 280, 135, 20, BLACK);
                if ((mousePosition.x > 325) && (mousePosition.y > 160) && (mousePosition.x < 350) && (mousePosition.y < 186) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
                    mode = 1;
                }
                if (switcher_x_pos>330) {
                    switcher_x_pos--;
                }
                if ((switcher_g>13) ) {
                    switcher_g-= 12;
                }
                if ((switcher_r<243) ) {
                    switcher_r+= 12;
                }
            }

            // не дает написать 2 знака подряд    
            if (((symbol[i-1] == '=') || (symbol[i-1] == '+') || (symbol[i-1] == '-') || (symbol[i-1] == '*')||(symbol[i-1] == '/'))
             && ((symbol[i] == '=') || (symbol[i] == '+') || (symbol[i] == '-') || (symbol[i] == '*') || (symbol[i] == '/'))) {
                i--;
            }
            
            // создание переменных 
            if (isdigit(symbol[i])) {  
                variables[i] = abs(48 - (int)symbol[i]);
                if ((operations_count % 2) == 0) {
                    num1 = matching_variable(variables, i);
                } else {
                    num2 = matching_variable(variables, i);
                }   
            }
            
            //определение смещения знака операции
            int num1_copy = abs(num1), num2_copy = abs(num2), num1_count = 0, num2_count = 0;
            while (num1_copy > 0) {
                num1_copy /= 10;
                num1_count++;
            }
            while (num2_copy > 0) {
                num2_copy /= 10;
                num2_count++;
            }
            if (num1_count > num2_count) {
                i_max = num1_count;
            } else {
                i_max = num2_count;
            }
if (mas_last_operation[0] != ' ') {
    result = do_operation(&num1, &num2, symbol[i-1], mas_last_operation[0], &operations_count);
}
            DrawText(TextFormat("%d", num1), 10, 20, 21, DARKGRAY); //первое число
            DrawText(TextFormat("%d", num2), 10, 46, 21, DARKGRAY); //второе число
            if (i_max>0) {
                DrawText(TextFormat("%c", mas_last_operation[0]), 15 + (i_max * 12), 30, 30, DARKGRAY); //последняя операция
            }
            DrawText(TextFormat("=%d", result), 10, 100, 35, BLACK); // результат
        EndDrawing();

    }
    CloseWindow();
    return 0;
}

int matching_variable(int *variables, int digit) {
    int result = 0, i = 1, mas_result[50] = {0}, res_count = 0;
    for (; i<=digit ; i++)
    {
        result += variables[i] * pow(10,i-1);
    }
    while (result != 0) {
        mas_result[i] = result % 10;
        result /= 10;  
        i++;   
    }
    
    for (int j = 0; i>0 ; i--) {
        result += mas_result[j] * pow(10,i-1);
        j++;
    } 
    int res_copy = result;
    while (res_copy > 0) { // добавляет нули в конце, если они нужны
        res_copy /= 10;
        res_count++;
    }
    if (res_count<digit) {
        result *= pow(10, digit-res_count);
    } //добавляет нули в конце, если они нужны
    return result; 
}

int delete (char *symbol, int i) {
    if (!isdigit(symbol[i])) {
            while (i != 0) {
                symbol[i] = ' ';
            i--;
        }
    }
    return i;
}

int take_last_operation(char* symbol, char* mas_last_operation, int i, int* operation_count, int *variables) {
    int temp = *operation_count;
    if (!isdigit(symbol[i]) && !isdigit(symbol[i-1])) {

    } else {
        temp++;
    }
    *operation_count = temp;
    if (symbol[i] != '=') {
    mas_last_operation[0] = symbol[i];
    }
    i = delete(symbol, i);
    for (int z = 0; z<40 ; z++) {
        variables[z] = 0;
    }
    return i;
}

int do_operation(int* num1,int* num2, char operation, char pre_last_operation, int *operation_count) {
    int result = 0;
    int var1 = *num1, var2 = *num2;
    if (pre_last_operation == '+') {
        result = var1 + var2;
    } else if (pre_last_operation == '-') {
        result = var1 - var2;
    } else if (pre_last_operation == '*') {
        if ((var2 == 0)) {
            var2 = 1;
        }
        result = var1 * var2;
    } else if (pre_last_operation == '/') {
        if (var2 == 0) {
            var2 = 1;
        }
        result = var1 / var2;
    }
    return result;
}