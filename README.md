# Tugas-Akhir Saharudin
Disain Kolam terpal ikan lele
![SAVE_20230614_205327](https://github.com/Saharudinsh/Tugas-Akhir/assets/83653696/192ccc33-b597-457e-9652-35d9f4e5a9ac)

![IMG_20230917_093833_1](https://github.com/Saharudinsh/Tugas-Akhir/assets/83653696/1416aa8a-b0af-4c51-9c32-f3b44634535b)


Deskripsi 

Kerangka kolam lele ini dibuat dengan menggabungkan pipa PVC berukuran ½ inci menjadi bentuk persegi. Bagian pipa tersebut dilengkapi dengan penyambung dan diplester untuk mencegah kebocoran saat kolam diisi air. Kolam lele ini dilengkapi dengan beberapa sensor, yaitu sensor kekeruhan, sensor ultrasonik, dan sensor aliran air, relay dan solenoid Valve. Sensor kekeruhan dipasang disisi dalam kolam, sementara sensor ultrasonik ditempatkan di atas permukaan air, sekitar 20 cm di atas kolam. Sensor aliran air dan solenoid Valve dipasang disisi luar kolam untuk mengukur volume air saat proses pengisian dan pengurasan, sedangkan relay di simpan di panel box.
Sistem pertukaran air dikendalikan menggunakan katup solenoid Valve. Relay menerima perintah dari program yang dijalankan oleh NodeMCU dan bertindak sebagai saklar untuk menghidupkan dan mematikan katup air sesuai dengan batasan ketinggian air dalam kolam, yakni batas maksimum dan minimum.
Inilah hasil akhir dari pengembangan sistem kontrol peralatan perangkat keras dan pemantauan kualitas air untuk kolam lele. Semua komponen ini dirancang untuk memastikan lingkungan yang optimal bagi ikan lele dan memudahkan pemantauan serta pengelolaan kolam.

Sistem control alat mejelaskan bahwa nilai kekeruhan air adalah 30 ntu, jika sensor mendeteksi lebih dari 30 ntu maka relay1 dalam kondisi normally open untuk membuka Valve1 sebagai pengurasan air sedangkan relay2 dalam kondisi normally close. Pada saat proses pengurasan sensor berfungsi untuk mengukur jarak air yang telah dikuras, dari pengurasan tersebut di berikan nilai batas bawah 40 cm untuk menutup Valve1 dan membuka Valve2 untuk mengisi air ke dalam kolam. Pada proses pengisian air sensor mengukur jarak air yang telah diberi nilai batas atas 20 cm bertujuan untuk menutup Valve2 supaya air yang masuk tidak melebihi kapasitas kolam. Siklus ini akan berulang kembali sampai sensor turbidity membaca nilai kekeruhan air 30 NTU.

