#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void auto_mow(int signum);
char key = 'w', last_tap = 'w';
int px = 5, py = 5;

int main() {
    struct itimerval timer;
    struct termios old, new;
    char area[13][31];
    int memory[13][31][2];
    int spy, spx, count=0, minus_count, longest = 1, ox = 10,oy = 3, alarm_count = 0;
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

    last_tap = key;
    

    // Установка обработчика сигнала
    signal(SIGALRM, auto_mow);

    // Установка интервала и начального значения таймера
    timer.it_value.tv_sec = 1;       // Первый сигнал через 1 секунд
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;    // Повторяющиеся сигналы каждые 1 секунды
    timer.it_interval.tv_usec = 0;
    // Установка таймера
    
    
    
    tcgetattr(STDIN_FILENO, &old); // сохраняем текущие настройки терминала
    new = old;
    new.c_lflag &= ~(ICANON | ECHO); // отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &new); // применяем новые настройки
    key = getchar(); // читаем символ без нажатия Enter
    //tcsetattr(STDIN_FILENO, TCSANOW, &old); // восстанавливаем исходные настройки

if ((setitimer(ITIMER_REAL, &timer, NULL) == 0) && (getchar() != isalpha(key))) {
        
    };
    usleep(300000);
        
    spy = py;
    spx = px;   
    memory[py][px][1]=42;
    memory[py][px][2]=count;
    if (key == last_tap) {
        switch (last_tap)
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
    } else {
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
    alarm_count++;
    minus_count = count-longest;
    } while (key != 'e');
    printf("*****WASTED*****\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old); // восстанавливаем исходные настройки
    return 0;
}
void auto_mow(int signum) {
    key = last_tap;
}