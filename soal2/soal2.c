#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

pid_t child2;

void createfolder(char kategori[]) { //buat folder dengan nama kategori
    char folder[100];

    sprintf(folder, "petshop/%s", kategori);
    child2 = fork();
    if (child2 == 0){
        char *argv[] = {"mkdir", "-p", folder, NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(NULL) != child2);
}

void createfile(char kategori[]) { //buat file keterangan di folder kategori
    char file[100];

    sprintf(file, "petshop/%s/keterangan.txt", kategori);
    child2 = fork();
    if (child2 == 0) {
        char *argv[] = {"touch", file, NULL};
        execv("/bin/touch", argv);
    }
    while(wait(NULL) != child2);
}

void isifile(char nama[], char umur[], char kategori[]) {
        FILE *fp;
        char lokasi[100];

        sprintf(lokasi, "petshop/%s/keterangan.txt", kategori);
        fp = fopen(lokasi, "r+");

        fprintf(fp, "nama : %s\n", nama);
        fprintf(fp, "umur : %s tahun\n\n", umur);

        fclose(fp);
}

void movefile(char kategori[], char namafile[], char nama[]) { //Fungsi pindah nama hewan ke folder kategori
    char asal[100];
    char ke[100];
    char sebelum[100];
    char sesudah[100];

    sprintf(asal, "petshop/%s", namafile);
    sprintf(ke, "petshop/%s/", kategori);
    
    child2 = fork();
    if (child2 == 0) {
        char *argv[] = {"mv", asal, ke, NULL};
        execv("/bin/mv", argv);
    }
    while(wait(NULL) != child2);

    sprintf(sebelum, "petshop/%s/%s", kategori, namafile);
    sprintf(sesudah, "petshop/%s/%s", kategori, nama);
    
    child2 = fork();
    if (child2 == 0) {
        char *argv[] = {"mv", sebelum, sesudah, NULL};
        execv("/bin/mv", argv);
    }
    while(wait(NULL) != child2);
}

int main()
{
    DIR *directory;
    struct dirent *en;

    char kategori[100];
    char nama[100];
    char umur[100];
    char namafile[100];

    child2 = fork();
    if (child2 == 0){
        char *unzip[] = {"unzip", "pets.zip", "-d",
                        "petshop", NULL};
        execv("/usr/bin/unzip", unzip);
    }
    while(wait(NULL) != child2);
    
    sleep(5);
    directory = opendir("petshop");
    if (directory) {
        while ((en = readdir(directory)) != NULL) {    //Loop semua file yang terdapat di petshop
            
            int baris = 1;
            int ext = strlen(en->d_name)-4;
            if(strstr(&en->d_name[ext], ".jpg")){   //filter format file jpg

                sprintf(namafile, "%s", en->d_name); //Dapatkan nama file

                char *token = strtok(en->d_name, ";");
                while (token != NULL) { //Pisahkan nama file dengan deliminter
                    if (baris == 1) {  //deliminter pertama maka simpan ke kategori
                        sprintf(kategori, "%s", token);
                    }else if (baris == 2) {  //deliminter kedua maka simpan ke nama
                        sprintf(nama, "%s", token);
                    }else if (baris == 3) {  //deliminter ketiga maka simpan ke umur
                        sprintf(umur, "%s", token);
                        strtok(umur, "_");
                        strtok(umur, "j");
                        if (umur[strlen(umur) - 1] == '.') {
                            umur[strlen(umur) - 1] = '\0';
                        }
                    }
                    token = strtok(NULL, ";");
                    baris++;
                }
            }
            createfolder(kategori);
            createfile(kategori);
            movefile(kategori, namafile, nama);
            isifile(nama, umur, kategori);
        }
        closedir(directory);
    }
}