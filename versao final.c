#include <stdio.h>    // printf(), scanf()
#include <stdlib.h>   // system()
#include <string.h>   // strcmp(), strcpy(), strcat()
#include <conio.h>    // getch(), getchar(), getche()
#include <locale.h>   // setlocale(LC_ALL, "Portuguese")

int main() {
char c;
char login[20];
char senha[20];
int a=10, b=10;
int i=0;
int verifica_senha=0;

setlocale(LC_ALL,"Portuguese");

while(verifica_senha==0){ // condição da variavel
	system("cls");
	system("color 07");
	printf("Sistema: SIGSaúde\n\nDigite seu nome de usuário: ");
    gets(login);
    printf("Digite sua senha: ");

    while((c=getch())!=13){
        senha[i]=c;
        i++;
        printf("*");
    }
    senha[i]='\0';
    i=0;
    system("cls");
    a=strcmp(senha,"123456789"); // Verifica a senha
    b=strcmp(login,"saude_2024"); // Verifica o login

    if(a==0 && b==0){
        printf("\n------------Seja bem vindo!------------");
        system("color 0a");
        verifica_senha=1;
        Beep(1500,200);

    }
    else{
        if(b!=0){
            printf("\nUsuário inválido! %s\n", login);
        }
        if(a!=0){
            printf("\nSenha incorreta: %s\n", senha);
        }
        system("color 0c");
        Beep(1200,200);
    }
    printf("\n");
    system("pause");
}

return 0;
}



