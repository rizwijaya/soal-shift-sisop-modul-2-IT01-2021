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

#include <dirent.h>

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
              DIR *directory;
              struct dirent *en;
              char namafile[100];
              directory = opendir("FOTO");
              if (directory) {
                  while ((en = readdir(directory)) != NULL) {    //Loop semua file yang terdapat di petshop
                      int ext = strlen(en->d_name)-4;
                      if(strstr(&en->d_name[ext], ".jpg")){   //filter format file jpg
                          //Dapatkan nama file
                          int n10 = fork();
                          
                          sprintf(namafile, "%s", en->d_name);
                          char result [80];
                          sprintf(result, "FOTO/%s", namafile);

                          if (n10 == 0){
                            char * movefoto[] = {
                              "mv", "-v", 
                              result,
                              "Pyoto",
                              NULL
                            };
                            execv("/bin/mv", movefoto);

                          }
                        while ((wait(NULL)) != n10);
                      }
                      
                  }
                  closedir(directory);
              }
              
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
                  "FOTO",
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
