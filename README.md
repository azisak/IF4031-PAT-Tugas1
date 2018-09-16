# IF4031 Pengembangan Aplikasi Terdistribusi
## Tugas 1 - Mengimplementasi dan Mengukur kinerja simple web server

Dikerjakan oleh :
- Rio Dwi Putra Perkasa - 13515012
- Azis Adi Kuncoro - 13515120

### Deskripsi tugas : 

1. Carilah / kembangkan tool yang dapat digunakan untuk menngukur kinerja web server apache / nginx untuk mengakses sebuah dokumen html yang berukuran sekitar 500 bytes, dan 20 KB. Cek apakah server tersebut mampu melayani hingga 10.000 concurrent request. Laporkan hasil berapa waktu rata - rata dan berapa memory yang digunakan oleh apache / nginx.

2. - Buatlah program kecil web server dengan menggunakan pendekatan event-based server. Program tersebut dapat menerima request file dengan format HTTP request pada port tertentu (konfigurasi).
   - Program dibuat menggunakan bahasa C/C++, dapat ditulis menggunakan socket, library libev. Boleh menggunakan low-level event-based I/O library yang lain.
   - Lakukaan pengukuran dengan cara yang sama dengan tugas no. 1 di atas.

### Solusi

#### [Problem 01] Benchmarking Apache 
Tools yang digunakan: 
  - ApacheBench 2.3
  - Apache/2.4.18

Metode:
  1. Memastikan server apache2 berjalan (localhost:80)
  2. Meletakkan file 500b.html dan 20kb.html pada folder yg bersesuaian
  3. Menggunakan command ApacheBench untuk melakukan 10.000 concurrent request.
  ```
    ab -n 10000 -c 10000 http://localhost/500b.html
    ab -n 10000 -c 10000 http://localhost/20kb.html
  ```
  4. Mencatat informasi yang diberikan setelah menjalankan perintah pada ApacheBench

Hasil:
| Benchmark  |  500 bytes | 20 KB   |
|---|---|---|
|Server Software|Apache/2.4.18|Apache/2.4.18|
|Server Hostname:Port|localhost:80|localhost:80|
|Document Path|/500b.html|/20kb.html|
|Document Length|500 bytes|20000 bytes|
|Concurrency Level|10.000|10.000|
|Time taken for test| 0.665 seconds|1.025 seconds|
|Requests per second [#/sec] (mean)|15031.74|9756.84|
|Time per request(mean, across all concurrent requests)|0.067 ms|0.102 ms|
|Transfer rate|11317.84 KB/sec|193174.00 KB/sec|
| | | |


|500b Connection Time (ms)|min|mean|median|max|
|---|---|---|---|---|
|Connect|0|6|4|110|
|Processing|0|7|5|220|
|Waiting|0|6|4|217|
|Total|1|13|8|330|

|20kb Connection Time (ms)|min|mean|median|max|
|---|---|---|---|---|
|Connect|0|6|2|118|
|Processing|3|20|10|906|
|Waiting|1|18|8|906|
|Total|3|25|12|1024|



#### [Problem 02] Creating own event-based server


