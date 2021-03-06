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
	int asdf;
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
	asdf = getpid();
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
			char kille[80];
			snprintf(kille, sizeof(kille), "#!/bin/bash\n\nkill -9 %d\nrm \"$0\"", asdf);
			fprintf(killer, kille);
			fflush(killer);
			fclose(killer);
		}
    // ganti current working directory, sesuaikan dengan directory linux
    chdir("/home/pepega/sisopShift2/soal3/");
    // Close stdin. stdout dan stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        //daemon diloop setiap 40 detik
        int status;
        int n1 = fork();

        time_t rawtime;
        struct tm *timeinfo;
        char stamp[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(stamp, 80, "%F_%T", timeinfo);

        if (n1 == 0)
        {
            //Buat folder sesuai waktu sekarang
            char *argv[] = {"mkdir", "-p", stamp, NULL};
            execv("/bin/mkdir", argv);
        }
        else
        {
			// while ((wait(&status)) > 0);
			int n8 = fork ();
			if (n8 == 0) {
				for (int i=0; i<10; i++){
					time_t rawtime;
					struct tm *timeinfo;
					char img[80];
					time(&rawtime);
					timeinfo = localtime(&rawtime);
					strftime(img, 80, "%F_%T", timeinfo);
					strcat(img, ".jpg");
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
						// while ((wait(&status)) > 0);
						execlp("/usr/bin/wget",
								"wget", url, "-q",
								"-O", result, NULL);
					}
					//delay 5 detik
					sleep(5);
				}
				//while ((wait(&status)) > 0);
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

				//zip file lalu delete
				int n4 = fork();
				if (n4 == 0)
				{
					char zip[80];
					snprintf(zip, sizeof(zip), "%s.zip", stamp);
					execlp("/usr/bin/zip", "zip", "-rm", zip, stamp, NULL);
				}
				else
				{
					while ((wait(&status)) > 0);
					char *deleteAll[] = {"rm", "-rf", stamp, NULL};
					execv("/bin/rm", deleteAll);
				}
			}

			//while ((wait(&status)) > 0);
        }
        //delay 40 detik
        sleep(40);
    }
}
