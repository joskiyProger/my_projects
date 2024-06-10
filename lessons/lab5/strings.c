#include "strings.h"
#include <ctype.h>

int slen(char *str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    while(str[i] != '\0')
        i++;
    return i; 
}   

char *stok(char *str, char *sep) {
    static char *temp_str;
    static char *str_copy;
    static int i = 0;
    
    if (str != NULL) {
        if (temp_str != NULL){
            temp_str = realloc(temp_str, 0);
        } 
        str_copy = str;
        i = 0;
        while(str[i] != '\0') {
            int j = 0;
            while(j < slen(sep)) {
                if (str[i] == sep[j]) {
                    // printf("%d\n", slen(temp_str));
                    return temp_str;
                }
                j++;
            }
            
            temp_str = realloc(temp_str, i);
            // printf("!%s %d\t", temp_str, i);
            temp_str[i] = str[i];
            i++;
        }
    }
    else {
        if (i == slen(str_copy)) {
            return NULL;
        }
        int k = 0, len = slen(temp_str);
        for(int index = 0; index<len ; index++) {
            temp_str[index] = 0;
        }
        while(str_copy[i] != '\0') {
            int j = 0;
            while(j < slen(sep)) {
                if (i == slen(str_copy) - 1) {
                    temp_str = realloc(temp_str, k + 1);
                    temp_str[k] = str_copy[i];
                    i++;
                    return temp_str;
                }
                if (str_copy[i] == sep[j]) {
                    i++;
                    if (temp_str[0] != 0) 
                        return temp_str;
                }
                
                j++;
            }
            temp_str = realloc(temp_str, k + 1);
            temp_str[k] = str_copy[i];
            i++;
            k++; 
        }
    }
    return temp_str;    
}

int sspn(char *str, char *find) {
    int match_counter = 0;
    for(int i = 0; i<slen(str) ; i++) {
        for(int j = 0; j<slen(find) ; j++) {
            if (str[i] == find[j]) {
                match_counter++;
            }
        }
    }
    return match_counter;
}

int scmp(char *str, char *match) {
    if (slen(str) != slen(match)) {
        return -1;
    }
    for(int i = 0; i<slen(str) ; i++) {
        if (str[i] != match[i]) {
            return -1;
        }
    }
    return 0;
}

char *scpy(char *str) {
    static char *str_copy;
    if (str != NULL) {
        str_copy = str;
        return str_copy;
    }
    return NULL;
}

int check_URL(char * str) {
    int last_slash_index = 0;

    if (slen(str) > MAX_PATH) {
        return 0;
    }

    char * str_temp = stok(str, ":");
    printf("%s\n\n", str); 
    // char *smb_path = "smb:";
    // char *http_path = "http";
    // for (int i = 0; i<4 ; i++) {
    //     if (str[i] != smb_path[i] && str[i] != http_path[i]) {
    //         // printf()
    //         return 0;
    //     }
    // }
    // // if ((str[0] != 's'|| str[1] != 'm' || str[2] != 'b') || (str[0] != 'h' || str[1] != 't' || str[2] != 't' || str[3] != 's')) {
    // //     return 0;
    // // }

    // for (int i = 0; i < slen(str) ; i++) {
    //     if (str[i] == '/') {
    //         str[i] = '\\';
    //         last_slash_index = i;
    //     }
    // }

    // for (int i = last_slash_index; i<slen(str) ; i++) {
    //     if (str[i] == '.') {
    //         return 0;
    //     }
    // }

    // for(int i = 0; i + 2 < slen(str) ; i++) {
    //     if (isdigit(str[i]) && isdigit(str[i+1]) && isdigit(str[i+2])) { // '0' = 48
    //         if ((str[i] > 50 ) || (str[i] == 50 && str[i+1] > 53) || ((str[i] == 50 && str[i+1] == 53 && str[i+2] > 54))) {
    //             return 0;
    //         }
    //     }
    // }
    // // str = &str[4];
    // if (str[0] == 's') {
    //     int i = 0;
    //     for (i = 0; i < slen(str) - 4; i++) {
    //         str[i] = str[i + 4];
    //     }
    //     str[i] = '\0';
    // } else {
    //     int i = 0;
    //     for (i = 0; i < slen(str) - 5; i++) {
    //         str[i] = str[i + 5];
    //     }
    //     str[i] = '\0';
    // }
    // return 1;
}