#include <string.h>  
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    char c;
    char login[20];
    char senha[20];
    int a=10, b=10;
    int i=0;
    int verifica_senha=0;
    
    while(verifica_senha==0){
        printf("\nSistema de login\n\nLogin: ");
        gets(login);
        printf("\nSenha: ");
        
        while((c=getch())!=13){
            senha[i]=c;
            i++;
            printf("*");
        }
        senha[i]='\0';
        i=0;
        system("cls");
        a=strcmp(senha,"nunes"); // Verifica a senha
        b=strcmp(login,"kevin"); // Verifica o login
        
        if(a==0 && b==0){ 
            printf("ACESSO PERMITIDO");
            system("color 0a");
            verifica_senha=1; 
            Beep(1500,200);
            
        }
        else{
            if(b!=0){
                printf("LOGIN INCORRETO: %s\n", login);
            }
            if(a!=0){
                printf("SENHA INCORRETA: %s\n", senha);
            }
            system("color 0c"); 
            Beep(1200,200);
        }
        printf("\n");
    }
    system("pause");
    
    return 0;
}

