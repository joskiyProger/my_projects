#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    
    struct termios old, new;
    char area[13][31], key = 'w';
    int memory[13][31][2];
    int px = 5, py = 5, spy, spx, count=0, minus_count, longest = 1, ox = 10,oy = 3;
    char buffer[BUFSIZ];
    setbuf(stdin, buffer);
    do { 
    sprintf(area[0], "###press_w_a_s_d_to_control###");    
    sprintf(area[12], "##############################");
    for (int i = 1; i<12; i++) {
        sprintf(area[i], "#                            #");
    }

    fputs("\x1B[2J\x1B[H", stdout); 
    fflush(stdout);
    for (int i = 0; i<13 ; i++) {
        for (int j = 0; j<31 ; j++ ) {
            if ((memory[i][j][1] == 42) && (memory[i][j][2] > minus_count)) area[i][j] = '*';
        }
    }
    area[py][px] = '@';
    area[oy][ox] = 'O';
    for (int i = 0; i<13; i++) {
        printf("%s\n", area[i]);
    }
    
    tcgetattr(STDIN_FILENO, &old); // сохраняем текущие настройки терминала
    new = old;
    new.c_lflag &= ~(ICANON | ECHO); // отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &new); // применяем новые настройки
    key = getchar(); // читаем символ без нажатия Enter
    tcsetattr(STDIN_FILENO, TCSANOW, &old); // восстанавливаем исходные настройки
    
    spy = py;
    spx = px;   
    memory[py][px][1]=42;
    memory[py][px][2]=count;
    switch (key)
    {
    case 'w':
        py--;
        break;
    case 's':
        py++;
        break;
    case 'a':
        px--;
        break;
    case 'd':
        px++;
        break;
    }
    
    if (isgraph(area[py][px]) && (area[py][px]!='O')) {
        py = spy;
        px = spx;
        break;
    }
    if (area[py][px] == 'O') {
        area[py][px] = '@';
        longest++;
        ox = 1 + rand()%28;
        oy = 1 + rand()%11;
    }
    count++;
    minus_count = count-longest;
    } while (key != 'e');
    printf("*****WASTED*****\n");
    return 0;
}
