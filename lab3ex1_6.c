/**
 * Furmanek Carina
 * IR3 2024, subgrupa 3
 * Tema 3 -ex1.6
 * Programul exemplica folosirea functiei execlp, si foloseste comanda ls -l din bash ca exemplu
 
 Am tratat urmatoarele edge case-uri:
 -cazul in care execlp esueaza, afisez o eroare

 */


#include <stdio.h>
#include <unistd.h>

int main() {

    printf("Executam comanda 'ls -l' folosind execlp.\n");

    // execut comanda folosind execlp
    // primul argument este numele programului pe care il execut, la execlp nu trebuie specificata toata calea (din nou dir specificate de PATH)
    // NULL este sfarsitul listei de argumente
    execlp("ls", "ls", "-l", NULL);
    perror("execlp a esuat");

    return 0;
}


/*
ex output


carina@PCD:~$ gcc lab3ex1_6.c -o lab3ex1_6
carina@PCD:~$ ./lab3ex1_6
Executam comanda 'ls -l' folosind execlp.
total 488
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
-rw-rw-r-- 1 carina carina  2703 Mar 21 16:49 lab3ex1_1.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 16:51 lab3ex1_2
-rw-rw-r-- 1 carina carina  2680 Mar 21 16:52 lab3ex1_2.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 16:55 lab3ex1_3
-rw-rw-r-- 1 carina carina  2819 Mar 21 16:55 lab3ex1_3.c
-rwxrwxr-x 1 carina carina 16048 Mar 21 17:02 lab3ex1_4
-rw-rw-r-- 1 carina carina  3021 Mar 21 17:02 lab3ex1_4.c
-rwxrwxr-x 1 carina carina 16104 Mar 21 17:04 lab3ex1_5
-rw-rw-r-- 1 carina carina  3169 Mar 21 17:07 lab3ex1_5.c
-rwxrwxr-x 1 carina carina 16048 Mar 21 17:12 lab3ex1_6
-rw-rw-r-- 1 carina carina   427 Mar 21 17:12 lab3ex1_6.c
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