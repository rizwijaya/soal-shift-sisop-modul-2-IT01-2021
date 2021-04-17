# soal-shift-sisop-modul-2-IT01-2021
### Nama Anggota Kelompok:
1. Widya Inayatul Luthfiyah (05311940000010)
2. Muhammad Rizqi Wijaya (05311940000014)
3. Gavin Bagus Kanzie N (05311940000028)
---
## Soal Nomor 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi. 
### Penyelesaian :
- Nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg 
- Untuk musik, film, dan foto download di link yang disediakan 
- meng-extract zip setelah didownload
- Memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).
- Berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany. 
- Setelah itu pada waktu ulang tahunnya Stevany 09 April Pukul 22.22 WIB, semua folder di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).

Catatan :
- Cukup jalankan script 1x serta ubah time dan date 
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename() dan cron


```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main(int argc, char * argv[]) {
  pid_t process_id = 0;
  pid_t sid = 0;
  // buat child process
  process_id = fork();
  // indikasi fork() gagal
  if (process_id < 0) {
    printf("fork gagal!\n");
    // Return exit status
    exit(1);
  }
  // PARENT PROCESS. harus dibunuh.
  if (process_id > 0) {
    // return success exit status
    exit(0);
  }

  //unmask file mode
  umask(0);
  //set new session
  sid = setsid();
  if (sid < 0) {
    // return gagal
    exit(1);
  }

  // ganti current working directory
  chdir("/home/pepega/sisopShift2/soal1/");

  // close stdin. stdout dan stderr
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  // main loop
  while (1) {
    // tidur dulu
    sleep(1);
    int status;
    time_t rawtime;
    struct tm * timeinfo;
    char time_now[26];

    //dapatkan waktu sekarang
    time( & rawtime);
    timeinfo = localtime( & rawtime);
    strftime(time_now, 26, "%F_%H_%M_%S", timeinfo);

    // jika 6 jam sebelum hbd
    if (strcmp(time_now, "2021-04-09_16_22_00") == 0) {
      pid_t child_id;
      int status;

      child_id = fork();

      if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0) {
        // child
        char * argv[] = {
          "mkdir",
          "-p",
          "Musyik",
          "Fylm",
          "Pyoto",
          NULL
        };
        execv("/bin/mkdir", argv);

      } else {
        while ((wait( & status)) > 0);
        int n1 = fork();
        int n2 = fork();

        if (n1 > 0 && n2 > 0) {
          //Download foto dari google drive
          execlp("/usr/bin/wget", "wget", "--user-agent=\"Mozilla\"", "--no-check-certificate", "-b", "-q",
            "https://drive.google.com/u/0/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
            "-O Foto_for_Stevany.zip", NULL);;
        } else if (n1 == 0 && n2 > 0) {
          //Download Musik dari google drive
          execlp("/usr/bin/wget", "wget", "--user-agent=\"Mozilla\"", "--no-check-certificate", "-b", "-q",
            "https://drive.google.com/u/0/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
            "-O Musik_for_Stevany.zip", NULL);
        } else if (n1 > 0 && n2 == 0) {
          //Download Film dari google drive
          execlp("/usr/bin/wget", "wget", "--user-agent=\"Mozilla\"", "--no-check-certificate", "-b", "-q",
            "https://drive.google.com/u/0/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download",
            "-O Film_for_Stevany.zip", NULL);
        } else {
          sleep(12); // tunggu file selesai didownload. 12 detik biar aman untuk internet lemot
          int n3 = fork();
          int n4 = fork();
          if (n3 > 0 && n4 > 0) {
           // unzip
           execlp("/usr/bin/unzip", "unzip", "*.zip", NULL);
          }
          //pindah ke folder musyik, fylm, pyoto
          else if (n3 == 0 && n4 > 0) {
      sleep(5);
         char * delete[] = {
              "rm", "-rf",
              "Pyoto",
              "Fylm",
              "Musyik",
              NULL
            };
            execv("/bin/rm", delete);
             
          } 
          else if (n3 > 0 && n4 == 0) {
      sleep(7);
            char * movefilm[] = {
              "mv", "-v",
              "FILM",
              "Fylm",
              NULL
            };
            execv("/bin/mv", movefilm);
          } else {
            int n7 = fork();
            int n8 = fork();
            int status;

            if (n7 > 0 && n8 > 0) {
              sleep(7);
              char * movemusik[] = {
                "mv", "-v",
                "MUSIK",
                "Musyik",
                NULL
              };
              execv("/bin/mv", movemusik);

            } else if (n7 == 0 && n8 > 0) {
              sleep(7);
              char * movefoto[] = {
                "mv", "-v",
                "FOTO",
                "Pyoto",
                NULL
              };
              execv("/bin/mv", movefoto);
            } else if (n7 > 0 && n8 == 0) {
              // loop sampai HBD jam 22:22
              while (1) {
                time_t rawtime;
                struct tm * timeinfo;
                char time_now[26];

                //dapatkan waktu sekarang
                time( & rawtime);
                timeinfo = localtime( & rawtime);
                strftime(time_now, 26, "%F_%H_%M_%S", timeinfo);
                if (strcmp(time_now, "2021-04-09_22_22_00") == 0) break;
              }
              while ((wait( & status)) > 0);
              int n5 = fork();
              int n6 = fork();
              if (n5 > 0 && n6 > 0) {
                // zip semua
                char * zipAll[] = {
                  "zip",
                  "-r",
                  "Lopyu_Stevany.zip",
                  "Pyoto",
                  "Fylm",
                  "Musyik",
                  NULL
                };
                execv("/usr/bin/zip", zipAll);
              } else if (n5 == 0 && n6 > 0) {
                // tunggu zip selesai dulu baru hapus folder
                sleep(2);
                char * deleteAll[] = {
                  "rm",
                  "-rf",
                  "Pyoto",
                  "Fylm",
                  "Musyik",
                  NULL
                };
                execv("/bin/rm", deleteAll);
              } else if (n5 > 0 && n6 == 0) {
                // hapus .zip sisanya
                char * deleteAll2[] = {
                  "rm",
                  " Foto_for_Stevany.zip",
                  " Musik_for_Stevany.zip",
                  " Film_for_Stevany.zip",
                  NULL
                };
                execv("/bin/rm", deleteAll2);
              }

            }

          }

        }
      }
    }
  }
  return (0);
}
```
---
## Soal Nomor 2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.
### Penyelesaian :
- Mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Program harus bisa membedakan file dan folder dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
- Membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. (kucing : “/petshop/cat”)
- Setelah folder kategori berhasil dibuat, Memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
- Maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg”
- Di setiap folder buatlah sebuah file "keterangan.txt". Format dibuat sesuai contoh. 


Catatan :
- Setiap data peliharaan disimpan sebagai nama foto dengan format [jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]. Jika terdapat lebih dari satu peliharaan, data dipisahkan menggunakan underscore(_).
- Tidak boleh menggunakan fungsi system(), mkdir(), dan rename().
- Menggunakan fork dan exec.

```
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
        fp = fopen(lokasi, "a+");

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
                createfolder(kategori);
                createfile(kategori);
                movefile(kategori, namafile, nama);
                isifile(nama, umur, kategori);
            }
        }
        closedir(directory);
    }
}
```
- Kendala yang ditemukan saat membuat program adalah masih belum mengetahui bagaimana cara memisahkan dua hewan yang terdapat pada satu foto, yang dipisahkan oleh tanda underscore (_).
---
## Soal Nomor 3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.
### Penyelesaian :
- Membuat sebuah program C yang setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].
- Setiap direktori yang dibuat diisi 10 gambar yang didownload dari https://picsum.photos/, dan setiap gambar akan didownload setiap 5 detik. 
- Setiap gambar yang didownload  diberi nama format timestamp [YYYY-mm-dd_HH:ii:ss] 
- Gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.
- Setelah direktori telah terisi program akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5.
- Setelah file dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.
- Membuat program “Killer” yang merupakan program bash.
- Program utama yang dibuat dijalankan di dalam dua mode. 
- Untuk mengaktifkan mode pertama = program harus dijalankan dengan argumen -z
- Untuk mengaktifkan mode kedua = program harus dijalankan dengan argumen -x
- Ketika dijalankan dalam mode pertama maka program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. 
- Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Catatan :
-	Tidak boleh menggunakan system()
-	Program utama merupakan SEBUAH PROGRAM C
-	Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat

```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <wait.h>

//untuk caesar cipher
char data[50], temp;
int key, count;

void caesarEncryption()
{
    for (count = 0; data[count] != '\0'; count++)
    {
        temp = data[count];
        if (temp >= 'a' && temp <= 'z')
        {
            temp = temp + key;
            if (temp > 'z')
            {
                temp = temp - 'z' + 'a' - 1;
            }
            data[count] = temp;
        }
        else if (temp >= 'A' && temp <= 'Z')
        {
            temp = temp + key;
            if (temp > 'Z')
            {
                temp = temp - 'Z' + 'A' - 1;
            }
            data[count] = temp;
        }
    }
}

int main(int argc, char *argv[])
{
    // untuk generate bash program
    if (argc < 2)
    {
        printf("missing argument\n");
        exit(-1);
    }
    if (strcmp(argv[1], "-z") == 0)
    {
        // pkill -9
        FILE *killer = NULL;
        umask(0);
        killer = fopen("killer.sh", "w+");
        // permission ganti dengan chmod
        chmod("killer.sh", 0777);
        // nama program sesuaikan dengan nama executable
        fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm \"$0\"");
        fflush(killer);
        fclose(killer);
    }
    else if (strcmp(argv[1], "-x") == 0)
    {
        // pkill
        FILE *killer = NULL;
        killer = fopen("killer.sh", "w+");
        // permission ganti dengan chmod
        chmod("killer.sh", 0777);
        // nama program sesuaikan dengan nama executable
        fprintf(killer, "#!/bin/bash\n\npkill soal3");
        fflush(killer);
        fclose(killer);
    }

    pid_t process_id = 0;
    pid_t sid = 0;
    // buat child process
    process_id = fork();
    // indikasi fork() gagal
    if (process_id < 0)
    {
        printf("fork failed!\n");
        // Return in exit status
        exit(1);
    }
    // PARENT PROCESS. harus dibunuh.
    if (process_id > 0)
    {
        // return success exit status
        exit(0);
    }
    //unmask file mode
    umask(0);
    //set new session
    sid = setsid();
    if (sid < 0)
    {
        // Return failure
        exit(1);
    }
    // ganti current working directory, sesuaikan dengan directory linux
    chdir("/home/kali/modul2/");
    // Close stdin. stdout dan stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        //daemon diloop setiap 40 detik
        int status;
        int n1 = fork();
        int n2 = fork();

        time_t rawtime;
        struct tm *timeinfo;
        char stamp[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(stamp, 80, "%F_%T", timeinfo);

        if (n1 > 0 && n2 > 0)
        {
            //Buat folder sesuai waktu sekarang
            char *argv[] = {"mkdir", "-p", stamp, NULL};
            execv("/bin/mkdir", argv);
        }
        else if (n1 == 0 && n2 > 0)
        {
            //daemon diloop 5 detik, download gambar
            pid_t process_id2 = 0;
            pid_t sid2 = 0;
            // buat child process
            process_id2 = fork();
            // indikasi fork() gagal
            if (process_id2 < 0)
            {
                printf("fork failed!\n");
                // Return exit status
                exit(1);
            }
            // PARENT PROCESS. harus dibunuh
            if (process_id2 > 0)
            {
                // return success exit status
                exit(0);
            }
            //unmask file mode
            umask(0);
            //set new session
            sid2 = setsid();
            if (sid2 < 0)
            {
                // Return failure
                exit(1);
            }
            // ganti current working directory
            chdir("/home/kali/modul2/");
            // Close stdin. stdout dan stderr
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            //counter jumlah file
            int count = 0;

            while (1)
            {
                //waktu sekarang untuk nama image
                time_t rawtime;
                struct tm *timeinfo;
                char img[80];
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(img, 80, "%F_%T", timeinfo);
                strcat(img, ".jpg");

                while ((wait(&status)) > 0)
                    ;
                int n3 = fork();

                //ukuran image
                unsigned long size = ((unsigned long)time(NULL) % 1000) + 50;
                //nama image
                char result[80];
                snprintf(result, sizeof(result), "%s/%s", stamp, img);
                //link download
                char url[80];
                snprintf(url, sizeof(url), "https://picsum.photos/%ld/%ld/\?random", size, size);

                if (n3 == 0)
                {
                    //Download gambar
                    while ((wait(&status)) > 0)
                        ;
                    execlp("/usr/bin/wget",
                           "wget", url, "-q",
                           "-O", result, NULL);
                }
                else
                {
                    if (count == 9)
                    {
                        //buat txt file
                        strcpy(data, "Download Success");
                        key = 5;
                        caesarEncryption();
                        char dir[80];
                        snprintf(dir, sizeof(dir), "%s/status.txt", stamp);
                        FILE *msg = NULL;
                        msg = fopen(dir, "w+");
                        fprintf(msg, "%s", data);
                        fflush(msg);
                        fclose(msg);
                    }
                }
                count++;
                if (count > 9)
                {
                    //zip file lalu delete
                    int n4 = fork();

                    if (n4 == 0)
                    {
                        char zip[80];
                        snprintf(zip, sizeof(zip), "%s.zip", stamp);
                        execlp("/usr/bin/zip", "zip", "-rm", zip, stamp, NULL);
                        break;
                    }
                    else
                    {
                        while ((wait(&status)) > 0)
                            ;
                        char *deleteAll[] = {"rm", "-rf", stamp, NULL};
                        execv("/bin/rm", deleteAll);
                        break;
                    }
                }
                //delay 5 detik
                sleep(1);
            }
        }
        //delay 40 detik
        sleep(8);
    }
}
```





