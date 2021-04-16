# soal-shift-sisop-modul-2-IT01-2021
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
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
```
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
sourcecode
```





