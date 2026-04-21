#include <stdio.h>

void encode(){
char c;
int first = 1;
while (scanf("%c",&c) ==1 && c !='\n'){
if (c == ' ') continue;

if (!first) printf(" ");
        printf("%X", (int)c);
        first = 0;

}


}
void decode() {
    unsigned int val;
    char c;
    int first = 1;
    
    while (scanf("%x%c", &val, &c) >= 1) {
        if (!first) printf(" ");
        printf("%c", (char)val);
        first = 0;
        
        if (c == '\n') break; 
        if (c != ' ') { 
            printf(" n/a"); 
            break;
        }
    }
}
int main(int argc, char *argv[]) {
   
    if (argc != 2) {
        printf("n/a\n");
        return 0;
    }

    
   if (argv[1][1] == '\0') {
        if (argv[1][0] == '0') {
            encode();
            printf("\n");
        } else if (argv[1][0] == '1') {
            decode();
            printf("\n");
        } else {
            printf("n/a\n");
        }
    } else {
        printf("n/a\n");
    }

    return 0;
}
