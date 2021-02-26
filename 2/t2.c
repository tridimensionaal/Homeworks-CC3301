#include<stdlib.h>
void reducir(char* s){
    char* p = s;

    while(*s){
        if(*s == ' '){
            *p = *s;
            s++;
            p++;
            while(*s==' '){
                s++;
            }

        }
        else{
            *p = *s;
            s++;
            p++;
 
        }
    }
    *p = 0;

}
char *reduccion(char *s){
    int i = 0;
    char* p = s;

    while(*s){
        if(*s == ' '){
            i++;
            while(*s==' '){
                s++;
            }

        }
        else{
            s++;
            i++;
        }
    }
    s = p;

    char *ss = malloc(i*sizeof(char));
    p = ss;

    while(*s){
        if(*s == ' '){
            *ss = *s;
            s++;
            ss++;
            while(*s==' '){
                s++;
            }

        }
        else{
            *ss = *s;
            s++;
            ss++;
        }
    }
    *ss = 0;
    return p;
}


