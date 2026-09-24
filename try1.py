def tampilkan_menu():
    print("\n--- MENU UTAMA ---")
    print("1. Lihat Daftar Tugas")
    print("2. Tambah Tugas Baru")
    print("3. Keluar")

def jalankan_aplikasi():
    daftar_tugas = []
    
    while True:
        tampilkan_menu()
        pilihan = input("Pilih menu (1/2/3): ")
        
        if pilihan == "1":
            print("\n--- DAFTAR TUGAS ANDA ---")
            if len(daftar_tugas) == 0:
                print("Belum ada tugas yang ditambahkan.")
            else:
                for i, tugas in enumerate(daftar_tugas, 1):
                    print(f"{i}. {tugas}")
                    
        elif pilihan == "2":
            tugas_baru = input("Masukkan nama tugas baru: ")
            daftar_tugas.append(tugas_baru)
            print(f"Tugas '{tugas_baru}' berhasil ditambahkan!")
            
        elif pilihan == "3":
            print("Terima kasih telah menggunakan aplikasi ini!")
            break
        else:
            print("Pilihan tidak valid, silakan coba lagi.")

if __name__ == "__main__":
    jalankan_aplikasi()