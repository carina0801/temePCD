#/**
 * Furmanek Carina
 * IR3 2024, subgrupa 3
 * Tema 3 -ex1.5
 * Programul exemplica folosirea functiei execle, si foloseste comanda ls -l din bash ca exemplu
 
 Am tratat urmatoarele edge case-uri:
 -cazul in care execle esueaza, afisez o eroare

 */

#include <stdio.h>
#include <unistd.h>

int main() {

    // 'envp' este un cector de variabile de mediu transmis programului executat
    // in ex meu, nu am adaugat variabile de mediu suplimentare, si ccontine doar NULL (indic sfarsitul vectorului)
    char *envp[] = {NULL};

    printf("execut comanda 'ls -l' folosind execle.\n");

    // execut comanda folosind execle
    // argumentele sunt pasate individual după calea programului (/bin/ls)
    execle("/bin/ls", "ls", "-l", NULL, envp);

    perror("execle a esuat");
    return 0;
}

/*
ex output

carina@PCD:~$ gcc lab3ex1_5.c -o lab3ex1_5
carina@PCD:~$ ./lab3ex1_5
execut comanda 'ls -l' folosind execle.
total 468
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Desktop
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Documents
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Downloads
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Music
drwxrwxr-x 2 carina carina  4096 Feb 29 19:47 PCD_teme
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Pictures
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Public
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Templates
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Videos
-rwxrwxr-x 1 carina carina 16304 Mar 12 19:39 a.out
-rwxrwxr-x 1 carina carina 16888 Mar 12 18:50 app3
drwxrwxr-x 5 carina carina  4096 Mar 11 18:00 argparse
-rwxrwxr-x 1 carina carina 16304 Mar 11 17:01 ex1lab1
-rwxrwxr-x 1 carina carina 16312 Mar 11 17:02 ex1lab2
-rwxrwxr-x 1 carina carina 16520 Mar 12 19:15 ex1tema2
-rw-rw-r-- 1 carina carina  1812 Mar 14 20:23 ex1tema2.c
-rwxrwxr-x 1 carina carina 16344 Mar 13 13:56 ex2
-rwxrwxr-x 1 carina carina 16344 Mar 14 20:03 ex2t1
-rwxrwxr-x 1 carina carina 16512 Mar 14 20:23 ex2t221
-rwxrwxr-x 1 carina carina 16480 Mar 14 19:52 ex2t3
-rwxrwxr-x 1 carina carina 16344 Mar 14 20:36 ex2t33
-rwxrwxr-x 1 carina carina 16344 Mar 14 20:18 ex2te1
-rwxrwxr-x 1 carina carina 16304 Mar 12 19:59 ex2tema2
-rwxrwxrwx 1 carina carina  2443 Mar 13 13:56 ex2tema2.c
-rw-rw-r-- 1 carina carina  4080 Mar 13 13:56 ex2tema2.o
-rwxrwxr-x 1 carina carina 16584 Mar 13 14:03 ex3
-rwxrwxr-x 1 carina carina 16584 Mar 14 20:44 ex3t3
-rw-rw-r-- 1 carina carina  1841 Mar 13 14:03 ex3tema2.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 16:48 lab3ex1_1
-rw-rw-r-- 1 carina carina  2703 Mar 21 16:49 lab3ex1_1.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 16:51 lab3ex1_2
-rw-rw-r-- 1 carina carina  2680 Mar 21 16:52 lab3ex1_2.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 16:55 lab3ex1_3
-rw-rw-r-- 1 carina carina  2819 Mar 21 16:55 lab3ex1_3.c
-rwxrwxr-x 1 carina carina 16048 Mar 21 17:02 lab3ex1_4
-rw-rw-r-- 1 carina carina  3021 Mar 21 17:02 lab3ex1_4.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 17:04 lab3ex1_5
-rw-rw-r-- 1 carina carina   232 Mar 21 17:03 lab3ex1_5.c
-rw-rw-r-- 1 carina carina  8313 Mar 13 17:16 process_list.txt
drwx------ 6 carina carina  4096 Mar 13 14:37 snap
-rwxrwxr-x 1 carina carina 16392 Mar 13 16:48 task2ex1
-rw-rw-r-- 1 carina carina  1705 Mar 13 16:48 task2ex1.c
-rwxrwxr-x 1 carina carina 16232 Mar 13 17:15 task2ex2
-rw-rw-r-- 1 carina carina   704 Mar 13 17:22 task2ex2.c
drwxrwxr-x 3 carina carina  4096 Mar 12 19:01 tema1
carina@PCD:~$ 



*/