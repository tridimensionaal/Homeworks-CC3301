#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
    char* name = argv[1];
    FILE *in = fopen(name,"r+");

    if(in==NULL){
        perror(name);
        exit(1);
    }
    char line[21];
    char b_line[21];
    memset(&b_line, ' ', 20);
    b_line[19] = '\n';
    b_line[20] = 0;

    int i = 0;
    int j = 0;

    for(;;){
        fseek(in, i*20, SEEK_SET);
        if(fread(line,1,20,in)==0){
            break;
        }

        line[19] = '\n';
        line[20] = 0;
        if (strcmp(line,b_line)){
            fseek(in, j*20, SEEK_SET);
            fwrite(line, 1, 20, in);
            j++;
        }
        i++;
    }
    while(i!=j){
        fseek(in, j*20,SEEK_SET);
        fwrite(b_line,1,20,in);
        j++;
    }
    j++;
}   

