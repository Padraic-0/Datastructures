#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    char characters[13] = {'Q','W','E','R','Y','U','P','G','H','J','Z','X','V'};
    for(int i = 0; i < 13; i++){
        
        for(int j = 0; j < 13; j++){
            printf("RU");
            printf("%c",characters[i]);
            printf("%c",characters[j]);
            printf("E\n");
        }
    }
    
    
    return 0;
}