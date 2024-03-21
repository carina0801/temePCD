
/**
 * Furmanek Carina
 * IR3 2024, subgrupa 3
 * Tema 3 -ex1.1
 * Programul exemplica folosirea functiei execv, si foloseste comanda ls -l din bash ca exemplu
 
 Am tratat urmatoarele edge case-uri:
 -cazul in care execv esueaza, afisez o eroare

 */

#include <stdio.h>
#include <unistd.h>

int main() {
   
    // primul argument este numele programului executat
    char *argv[] = {"/bin/ls", "-l", NULL}; // comanda ls -l

    // mesaj inainte de comanda
    printf("execut comanda 'ls -l' folosind execv.\n");

    // aici execut comanda '/bin/ls -l'
    // daca execv se executa cu succes, executia programului se va termina si va incepe execuția noului program
    execv("/bin/ls", argv);

    // cazul in care execv nu are succes
    perror("execv a esuat");
    return 0;
}


/* exemplu output

carina@PCD:~$ gcc lab3ex1_1.c -o lab3ex1_1
carina@PCD:~$ ./lab3ex1_1
execut comanda 'ls -l' folosind execv.
total 388
-rwxrwxr-x 1 carina carina 16304 Mar 12 19:39 a.out
-rwxrwxr-x 1 carina carina 16888 Mar 12 18:50 app3
drwxrwxr-x 5 carina carina  4096 Mar 11 18:00 argparse
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Desktop
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Documents
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Downloads
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
-rw-rw-r-- 1 carina carina   532 Mar 21 16:47 lab3ex1_1.c
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Music
drwxrwxr-x 2 carina carina  4096 Feb 29 19:47 PCD_teme
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Pictures
-rw-rw-r-- 1 carina carina  8313 Mar 13 17:16 process_list.txt
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Public
drwx------ 6 carina carina  4096 Mar 13 14:37 snap
-rwxrwxr-x 1 carina carina 16392 Mar 13 16:48 task2ex1
-rw-rw-r-- 1 carina carina  1705 Mar 13 16:48 task2ex1.c
-rwxrwxr-x 1 carina carina 16232 Mar 13 17:15 task2ex2
-rw-rw-r-- 1 carina carina   704 Mar 13 17:22 task2ex2.c
drwxrwxr-x 3 carina carina  4096 Mar 12 19:01 tema1
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Templates
drwxr-xr-x 2 carina carina  4096 Feb 29 16:37 Videos
carina@PCD:~$ 

*/