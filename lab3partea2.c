/**
 * Furmanek Carina
 * IR3 2024, subgrupa 3
 * Tema 3 (- partea 2

Programul implementeaza un shell simplu care poate executa comenzi introduse de utilizator
Utilizatorul este se autentifica cu credentiale din fisiercul credentials.txt
Shell-ul poate executa comenzi pana la la semnalul de intrerupere CTRL-C

 * Am tratat urmatoarele edge case-uri:
 -Esec fork/exec: Gestionarea erorilor pentru fork() si exec() cu mesaje de eroare si 
  iesirea din program
 -Inchiderea programului: Asigura terminarea ordonata a shell-ului si a tuturor proceselor copil 
  la iesirea utilizatorului din shell
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_USERNAME_LENGTH 256
#define MAX_PASSWORD_LENGTH 256

// implementarea functiei system (am numit my_system)
int my_system(char * const command) {
    pid_t pid = fork(); // creez un proces copil
    if (pid == -1) {
        // daca fork a esuat, afisez o eroare
        perror("Eroare fork");
        return -1;
    } else if (pid == 0) {
        // procesul copil executa comanda
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        // daca execl esueaza, afisez eroarea si termin executia
        perror("Eroare execl");
        exit(EXIT_FAILURE);
    } else {
        // procesul parinte asteapta sfarsitul executiei procesului copil
        int status;
        waitpid(pid, &status, 0);
        // returnez statusul procesului copil
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            // daca procesul copil nu s-a terminat normal, returnez -1
            return -1;
        }
    }
}


// functia login pt autentificare. stochez niste credentiale tip username si password intr un fisier text
void login(char * const username, char * const password) {
    FILE *file = fopen("credentials.txt", "r"); // deschid fisierul cu credentiale
    char file_username[MAX_USERNAME_LENGTH];
    char file_password[MAX_PASSWORD_LENGTH];

    if (file == NULL) {
        perror("Nu s-a putut deschide fisierul de credentiale");
        exit(EXIT_FAILURE);
    }

    // parcurg fisierul si caut username-ul si parola
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            printf("Autentificare reusita pentru '%s'.\n", username);
            fclose(file);
            return; 
        }
    }

    // in caz ca autentificarea nu a mers
    printf("Autentificare esuata pentru '%s'.\n", username);
    fclose(file);
    exit(EXIT_FAILURE); // ies di program
}

// functia shell
void shell() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("shell> "); // adizes prompt-ul la inceputul liniei in terminal 
        fflush(stdout); // golesc

        // citesc o comanda de la utilizator
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\nLa revedere!\n");
            break; // Iesim daca intalnim EOF - ca CTRL-D
        }

        // user-ul poate inchide "shell-ul" cu CTRL-C
        if (command[0] == 3) {
            printf("\nLa revedere!\n");
            break;
        }

        // elimin newline-ul de la finalul comenzii
        command[strcspn(command, "\n")] = 0;

        // executam comanda folosind functia system deifinat anterior
        int status = system(command);
        if (status == -1) {
            fprintf(stderr, "Eroare la executarea comenzii.\n");
        }
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];


    //cer credentialele user-ului inainte de deschiderea "shell-ului"
    printf("Nume utilizator: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Eroare la citirea numelui de utilizator.\n");
        exit(EXIT_FAILURE);
    }
    username[strcspn(username, "\n")] = 0; // elimin newline-ul

    printf("Parola: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Eroare la citirea parolei.\n");
        exit(EXIT_FAILURE);
    }
    password[strcspn(password, "\n")] = 0; //elimin newline-ul

    
    login(username, password); // autentific user-ul

   //deschid "shell-ul"
    shell(); 

    return 0; 
}


/*
ex output

carina@PCD:~$ gcc lab3partea2.c -o lab3partea2
carina@PCD:~$ ./lab3partea2
Nume utilizator: carina
Parola: ceva
Autentificare reusita pentru 'carina'.
shell> ls
a.out		 ex1tema2.c  ex3	  lab3ex1_4.c	 process_list.txt
app3		 ex2	     ex3t3	  lab3ex1_5	 Public
argparse	 ex2t1	     ex3tema2.c   lab3ex1_5.c	 snap
credentials.txt  ex2t221     lab3ex1_1	  lab3ex1_6	 task2ex1
Desktop		 ex2t3	     lab3ex1_1.c  lab3ex1_6.c	 task2ex1.c
Documents	 ex2t33      lab3ex1_2	  lab3partea2	 task2ex2
Downloads	 ex2te1      lab3ex1_2.c  lab3partea2.c  task2ex2.c
ex1lab1		 ex2tema2    lab3ex1_3	  Music		 tema1
ex1lab2		 ex2tema2.c  lab3ex1_3.c  PCD_teme	 Templates
ex1tema2	 ex2tema2.o  lab3ex1_4	  Pictures	 Videos
shell> ^C
carina@PCD:~$ 

*/