/*

/**
 * Nume: Furmanek Carina
 * Grupa: IR3 2024, Subgrupa 3
 * Tema: 4 - Exercitiul 1, 2, 3
 * Descriere Program: Acest program ilustreaza folosirea  thread-urilor pentru operatii de citire si scriere in fisiere,
 * precum si afisarea fisierelor din directorul curent si afisarea permisiunilor acestora
 * 
 * Edge Cases:

 * - Erori la deschiderea fisierelor pentru citire sau scriere
 * - Erori la alocarea memoriei pentru buffer-ul de citire/scriere
 */


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// am definit struct-uri pentru stocarea informatiilor necesare thread-urilor de citire si scriere
typedef struct inFile {
    char *filePath;
    char *buffer;
    size_t size;
} inFile_t;

typedef struct outFile {
    char *filePath;
    char *buffer;
    size_t size;
} outFile_t;

// functia myRead - citeste date dintr-un fisier si le pune intr-un buffer.
size_t myRead(char *path, char **buffer, size_t size) {
    FILE *file = fopen(path, "rb");//deschid un fisier - rb (r si rb sunt "la fel", desi rb functioneaza si cu fisiere binary)
    if (!file) {
        perror("Eroare la deschiderea fisierului pentru citire");
        return 0;
    }

    *buffer = malloc(size);//aici aloc memorie buffer-ului de citire
    if (!*buffer) {
        perror("Eroare la alocarea memoriei pentru buffer");
        fclose(file);
        return 0;
    }

    size_t bytesRead = fread(*buffer, 1, size, file);
    fclose(file);
    return bytesRead;//returnez numarul de bytes cititi
}

// functia myWrite - scrie ce gaseste in buffer-ul definit mai sus intr-un fisier specificat (in cazul meu output.txt)
size_t myWrite(char *path, char *buffer, size_t size) {
    FILE *file = fopen(path, "wb");//deschid un fisier cu optinuea "wb" (din nou, w si wb sunt "la fel", desi cu wb fot scrie si in fisiere binare)
    if (!file) {
        perror("Eroare la deschiderea fisierului pentru scriere");
        return 0;
    }

    size_t bytesWritten = fwrite(buffer, 1, size, file);//identific cati bytes am scris in fisierul resspectiv
    fclose(file);
    return bytesWritten;//returnsez valoarea
}

//Functia pentru thread-ul care realizeaza operatia citirea din fisier
void *inThread(void *arg) {
    // convertesc rgumentul primit în tipul corect (inFile_t*)
    inFile_t *inFile = (inFile_t *)arg;

    // initializez buffer-ul cu NULL in cazul in care acesta contine date reziduale
    inFile->buffer = NULL;

    // apelez functia funcția myRead pentru a citi datele din fișierul specificat în struct-ul inFile(in czul acesta input.txt)
    // in bytesRead tin numarul de bytes cititi (myRead returneza numarul de bytes)
    size_t bytesRead = myRead(inFile->filePath, &inFile->buffer, inFile->size);

    // afisez in terminal un mesaj in care specific numarul de bytes cititi si fisierul din care au fost cititi
    printf("read thread: au fost cititi %zu bytes din fisierul '%s'.\n", bytesRead, inFile->filePath);

    // returnez numarul de bytes cititi (cast-uit in void pentru a respecta functia thread)
    return (void *)bytesRead;
}


//functia pentru thread-ul care realizeaza scrierea in fisier
//aceiasi structura ca si inThread mai sus
void *outThread(void *arg) {
    outFile_t *outFile = (outFile_t *)arg;
    size_t bytesWritten = myWrite(outFile->filePath, outFile->buffer, outFile->size);
    printf("write thread: au fost scrisi %zu bytes in fisierul '%s'.\n", bytesWritten, outFile->filePath);
    return (void *)bytesWritten;
}

//functia thread-ului care proceseaza informatii despre fisiere
void *fileThread(void *arg) {
    struct dirent *entry = (struct dirent *)arg;//struct care contine info despre fisierle din director
    char filePath[PATH_MAX];


    snprintf(filePath, PATH_MAX, "./%s", entry->d_name); // construiesc calea completa a fisierelor
    struct stat fileStat; // variabila in care stochez statisticile fisierului

    if (stat(filePath, &fileStat) < 0) { // aici obtin informatii despre fiser
        perror("stat");
        free(entry);
        return NULL;
    }

    // afisez numele si dimensiunea fisierului
    printf("Fisier: %s, Marime: %ld bytes\n", filePath, fileStat.st_size);
    // Pafisez permisiunile fisierului

    printf("Permisiuni: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    
    free(entry); // eliberz memoria pt struct-l dirent
    return NULL;
}


int main() {
    // dspecific fisierul de intrare si iesire
    char *inputFilePath = "input.txt";
    char *outputFilePath = "output.txt";
    size_t bufferSize = 1024; // specific dimensiunea buffer-ului

    // initializez struct-urile inFile_t si outFile_t 
    inFile_t inFileData = {inputFilePath, NULL, bufferSize};
    outFile_t outFileData = {outputFilePath, NULL, bufferSize};

    //identificatori pt thread-urile de citire și scriere
    pthread_t inThreadId, outThreadId;

    // creez si pornesc thread-ul pt citite din fisierul de intrare
    if (pthread_create(&inThreadId, NULL, inThread, &inFileData) != 0) {
        perror("nu am putut crea thread-ul pt citire");
        return 1; // in caz de eroare, programul se termina cu codul 1
    }

    // astept sa se termine thread ul de citire 
    pthread_join(inThreadId, NULL);


    // folosesc acelasi buffer pt scriere
    outFileData.buffer = inFileData.buffer;

    // creez si pornesc thread-ul de scriere in output file 
    if (pthread_create(&outThreadId, NULL, outThread, &outFileData) != 0) {
        perror("nu am putut crea thread-ul pt scriere");
        free(inFileData.buffer); // eliberez memoria din buffer
        return 2; // in caz de eroare, programul se termina cu codul 2
    }

    // astept finalizarea thread-ului de scriere
    pthread_join(outThreadId, NULL);

    // eliberez buffer-ul dupa ce s a terminat scrierea
    if (inFileData.buffer != NULL) {
        free(inFileData.buffer);
    }

    // unde afisez fisierele din si permisiunile lor 
    DIR *dir = opendir("."); // deschid directorul curent
    if (!dir) {
        perror("nu am putut deschide directorul");
        return 3; // eroare - cod 3
    }

     struct dirent *entry; 
    // iterez prin toate intrarile din director
    while ((entry = readdir(dir)) != NULL) {
        // doar fisierele normale sunt luate(
        if (entry->d_type == DT_REG) {
            struct dirent *entryCopy = malloc(sizeof(struct dirent));
            if (!entryCopy) {
                perror("nu am putut aloca memorue pt directorul entry");
                continue; 
            }
            memcpy(entryCopy, entry, sizeof(struct dirent)); // copiez datele intrarii pt a fi folosite in thread

            pthread_t fileThreadId;
            if (pthread_create(&fileThreadId, NULL, fileThread, entryCopy) != 0) {
                perror("nu am putut crea thread-ul pt informatii despre fisiere");
                free(entryCopy);
                continue; 
            }

            // Aastept s se termine thread ul cu info desrpre fisiere
            pthread_join(fileThreadId, NULL);
        }
    }

    closedir(dir); // inchid directorul deschis inainte

    return 0; 
}




/*

carina@PCD:~$ gcc -o tema4 tema4.c -pthread
carina@PCD:~$ ./tema4
read thread: au fost cititi 41 bytes din fisierul 'input.txt'.
write thread: au fost scrisi 1024 bytes in fisierul 'output.txt'.
Fisier: ./ex2, Marime: 16344 bytes
Permisiuni: -rwxrwxr-x
Fisier: ./.bash_history, Marime: 612 bytes
Permisiuni: -rw-------
Fisier: ./a.out, Marime: 16304 bytes
Permisiuni: -rwxrwxr-x
Fisier: ./output.txt, Marime: 1024 bytes
Permisiuni: -rw-rw-r--
Fisier: ./lab3ex1_5.c, Marime: 3425 bytes
Permisiuni: -rw-rw-r--
Fisier: ./task2ex2.c, Marime: 704 bytes
Permisiuni: -rw-rw-r--
Fisier: ./lab3ex1_4.c, Marime: 3274 bytes
Permisiuni: -rw-rw-r--
Fisier: ./ex2t3, Marime: 16480 bytes
Permisiuni: -rwxrwxr-x
Fisier: ./lab3ex1_2.c, Marime: 2934 bytes
Permisiuni: -rw-rw-r--
Fisier: ./ex2te1, Marime: 16344 bytes
Permisiuni: -rwxrwxr-x
Fisier: ./lab3ex1_4, Marime: 16048 bytes
Permisiuni: -rwxrwxr-x
Fisier: ./credentials.txt, Marime: 12 bytes
Permisiuni: -rw-rw-r--
Fisier: ./tema4, Marime: 16856 bytes


carina@PCD:~$ cat output.txt
buna ziua, eu sunt carina. imi pare bine


*/