/*
 * Furmanek Carina
 * IR3 2024, subgrupa 3
 * Tema 4 - ex 4
 acest program creaza o structura de directoare/fisiere specificata in tema.
 */


#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // creez directorul d1 cu permisiunile 500 (dr-x------)
    mkdir("d1", 0500);

    // Creez directorul d2 in d1 cu permisiunile 400 (d------r--)
    mkdir("d1/d2", 0400);

    // creez directorul d3 in d1 cu permisiunile 630 (drw-r--wx-)
    mkdir("d1/d3", 0630);

    // creez fisierul f1 in d2 cu permisiunile 007 (------rwx)
    int fd1 = open("d1/d2/f1", O_CREAT, 0007);
    close(fd1);

    // creez fisierul f4 in d3 cu permisiunile 504 (r-xr-----)
    int fd2 = open("d1/d3/f4", O_CREAT, 0504);
    close(fd2);

    // creez fisierul f2 cu permisiunile 400 (------r--)
    int fd3 = open("f2", O_CREAT, 0400);
    close(fd3);

    // creez fisierul f3 cu permisiunile 002 (-------wx)
    int fd4 = open("f3", O_CREAT, 0002);
    close(fd4);

    // creez un hard link f5 la f1 in d2
    link("d1/d2/f1", "d1/f5");

    // creez un soft link (symlink) f4 la f1
    symlink("d1/d2/f1", "f4");

    printf("structura de fisiere si directoare a fost creata\n");

    return 0;
}

/*
cu comanda tree

.
├── d1
│   ├── d2
│   │   └── f1
│   ├── d3
│   │   └── f4
│   └── f5 -> d2/f1 (hard link)
├── f2
├── f3
└── f4 -> d1/d2/f1 (soft link)

2 directories, 5 files

carina@PCD:~$ gcc tema4ex4.c -o tema4ex4
carina@PCD:~$ ./tema4ex4
Structura de fisiere si directoare a fost creata.





*/
