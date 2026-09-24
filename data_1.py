import pandas as pd
import matplotlib.pyplot as plt

data = {
    "Hari": ["Senin", "Selasa", "Rabu", "Kamis", "Jumat"],
    "Penjualan": [120, 150, 130, 200, 170]
}

df = pd.DataFrame(data)

print("--- MENAMPILKAN TABEL DATA ---")
print(df)
print("\n")

plt.figure(figsize=(7, 4))
plt.plot(df["Hari"], df["Penjualan"], marker='o', color='blue', linewidth=2)

plt.title("Grafik Penjualan Harian")
plt.xlabel("Hari")
plt.ylabel("Jumlah Penjualan")
plt.grid(True)

plt.show()