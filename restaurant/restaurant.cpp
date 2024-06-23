#include <iostream>
#include<windows.h>
#define max 100
using namespace std;

int pil;
string managerName, managerPass;

// Data menu makanan
string namaMakananArr[] = { "Nasi Goreng", "Mie Goreng", "Ayam Goreng", "Ayam Bakar", "Ayam Kecap", "Ayam Rica", "Ayam Geprek", "Ayam Penyet" };
int hargaMakananArr[] = { 15000, 12000, 20000, 25000, 25000, 25000, 20000, 20000 };
int stokMakananArr[] = { 1, 5, 3, 6, 6, 7, 10, 10 };

struct DataPesanan
{
	string namaCustomer;
	string namaMakanan;
	int harga;
	int totalHarga;
	int jumlahPesanan;
	int stok;
}data[max];

struct RiwayatPesanan
{
	string riwayatNamaCustomer;
	string riwayatNamaMakanan;
	int riwayatJumlahPesanan;
	int riwayatHarga;
	int riwayatTotalHarga;
}riwayat[max];

int jmlRiwayat = 0;

struct queue
{
	DataPesanan data[max];
	RiwayatPesanan riwayat[max];
	int head;
	int tail;
}antrian;


void sortPengeluaranCustomer();
void searchNama();
void masukAkun();
void halamanAdmin();
void halamanKasir();
void halamanManager();
void tampilMenu();
void tampilPesanan();
void enqueue();
void dequeue();
bool isEmpty();
bool isFull();


bool isEmpty() // Queue
{
	if (antrian.tail == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isFull() // Queue
{
	if (antrian.tail == max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void dequeue() // Queue
{
	if (!isEmpty())
	{
		system("cls");
		cout << "Pesanan teratas selesai" << endl;

		antrian.head++;
		if (antrian.head == antrian.tail)
		{
			antrian.head = antrian.tail = 0;
		}
		Sleep(1700);
		system("cls");
	}
	else
	{
		system("cls");
		cout << "Antrian kosong!" << endl;
		Sleep(1700);
		system("cls");
	}
}

void tampilAntrian()
{
	if (!isEmpty())
	{
		system("cls");
		cout << "=== Antrian Pesanan ===\n" << endl;
		for (int i = antrian.head; i < antrian.tail; i++)
		{
			cout << "Pesanan ke - " << i - antrian.head + 1 << endl;
			cout << "------------------------------" << endl;
			cout << "Nama Customer  : " << antrian.data[i].namaCustomer << endl;
			cout << "Nama Makanan   : " << antrian.data[i].namaMakanan << endl;
			cout << "Jumlah         : " << antrian.data[i].jumlahPesanan << endl;
			cout << "Total Harga    : " << antrian.data[i].totalHarga << endl;
			cout << "------------------------------" << endl;
			cout << endl;
		}
	}
	else
	{
		system("cls");
		cout << "Antrian kosong!" << endl;
		Sleep(1700);
		system("cls");
	}

}

void tampilMenu()
{
	cout << "===========================================" << endl;
	cout << "|        MENU MAKANAN YANG TERSEDIA       |" << endl;
	cout << "===========================================" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "-----------" << endl;
		cout << "Menu ke - " << i + 1 << endl;
		cout << "---------------------------" << endl;
		cout << "Nama Makanan : " << namaMakananArr[i] << endl;
		cout << "Harga        : " << hargaMakananArr[i] << endl;
		if (stokMakananArr[i] == 0)
		{
			cout << "Stok         : Habis" << endl;
			cout << "---------------------" << endl;
		}
		else
		{
			cout << "Stok         : " << stokMakananArr[i] << endl;
			cout << "---------------------------" << endl;
		}
		cout << endl;
	}
}

int pilMenu;
int stokSisa;
int noMenu;

void enqueue()
{
	if (!isFull())
	{
		cout << "\nMasukkan nama customer   : ";
		cin >> antrian.data[antrian.tail].namaCustomer;
		antrian.riwayat[antrian.tail].riwayatNamaCustomer = antrian.data[antrian.tail].namaCustomer; // Copy nama customer ke riwayat
		string tempNamaCustomer = antrian.data[antrian.tail].namaCustomer; // Simpan nama customer sementara

		char pilihan;
		do
		{
			bool stokHabis = false;
			do
			{
				tampilMenu();
				cout << "Masukkan nomor menu : ";
				cin >> noMenu;
				noMenu--; // Kurangi 1 karena array dimulai dari 0
				if (noMenu >= 0 && noMenu < 8)
				{
					if (stokMakananArr[noMenu] == 0)
					{
						cout << "Stok habis" << endl;
						cout << "Apakah ingin memilih menu lain? (y/n) : ";
						cin >> pilihan;
						if (pilihan == 'n')
						{
							stokHabis = true;
						}
					}
					else
					{
						stokHabis = true;
					}
				}
			} while (!stokHabis);
			cout << "---------------------------" << endl;
			cout << "Nama Makanan   : " << namaMakananArr[noMenu] << endl;
			cout << "Jumlah pesanan : ";
			cout << "---------------------------" << endl;
			cin >> antrian.data[antrian.tail].jumlahPesanan;
			antrian.riwayat[antrian.tail].riwayatJumlahPesanan = antrian.data[antrian.tail].jumlahPesanan; // Copy jumlah pesanan ke riwayat

			if (antrian.data[antrian.tail].jumlahPesanan > stokMakananArr[noMenu])
			{
				system("cls");
				cout << "Stok tidak mencukupi, silahkan pesan dengan jumlah yang lebih kecil" << endl;
				pilihan = 'y';
				Sleep(1700);
				system("cls");
			}
			else
			{
				antrian.data[antrian.tail].totalHarga = hargaMakananArr[noMenu] * antrian.data[antrian.tail].jumlahPesanan; // Hitung total harga
				antrian.riwayat[antrian.tail].riwayatHarga = hargaMakananArr[noMenu]; // Copy harga makanan ke riwayat
				cout << "Total harga     : " << antrian.data[antrian.tail].totalHarga << endl; // Tampilkan total harga
				cout << "Pesanan berhasil ditambahkan" << endl;

				// Copy data ke struktur antrian
				antrian.data[antrian.tail].namaCustomer = tempNamaCustomer; // Copy nama customer
				antrian.data[antrian.tail].namaMakanan = namaMakananArr[noMenu]; // Copy nama makanan
				antrian.data[antrian.tail].harga = hargaMakananArr[noMenu]; // Copy harga makanan
				stokSisa = stokMakananArr[noMenu] - antrian.data[antrian.tail].jumlahPesanan; // Hitung sisa stok
				antrian.data[antrian.tail].stok = stokSisa; // Copy sisa stok
				stokMakananArr[noMenu] -= antrian.data[antrian.tail].jumlahPesanan; // Kurangi stok

				// Copy data ke struktur riwayat
				antrian.riwayat[jmlRiwayat].riwayatNamaCustomer = tempNamaCustomer; // Copy nama customer ke riwayat
				antrian.riwayat[jmlRiwayat].riwayatNamaMakanan = namaMakananArr[noMenu]; // Copy nama makanan ke riwayat
				antrian.riwayat[jmlRiwayat].riwayatJumlahPesanan = antrian.data[antrian.tail].jumlahPesanan; // Copy jumlah pesanan ke riwayat
				antrian.riwayat[jmlRiwayat].riwayatHarga = hargaMakananArr[noMenu]; // Copy harga makanan ke riwayat
				antrian.riwayat[jmlRiwayat].riwayatTotalHarga = antrian.data[antrian.tail].totalHarga; // Copy total harga ke riwayat

				// Tambahkan index antrian
				antrian.tail++;
				jmlRiwayat++;

				cout << "Apakah ingin menambahkan pesanan lagi? (y/n) : ";
				cin >> pilihan;
				system("cls");
			}
		} while (pilihan == 'y');
	}
}

void halamanKasir()
{
	do
	{
		cout << "=============================" << endl;
		cout << "        Halaman Kasir        " << endl;
		cout << "=============================" << endl;
		cout << "[1] Tambah antrian" << endl;
		cout << "[2] Tampilkan antrian" << endl;
		cout << "[3] Selesaikan pesanan teratas" << endl;
		cout << "[4] Kembali" << endl;
		cout << "Masukkan pilihan: ";
		cin >> pil;
		if (pil == 1)
		{
			enqueue();
		}
		else if (pil == 2)
		{
			tampilAntrian();
		}
		else if (pil == 3)
		{
			dequeue();
		}
		else if (pil == 4)
		{
			system("cls");
			cout << "Anda keluar" << endl;
			masukAkun();
		}
		else
		{
			system("cls");
			cout << "Pilihan tidak tersedia" << endl;
			Sleep(1700);
			system("cls");
		}
	} while (pil != 4);
}

void tambahStok()
{
menu:
	tampilMenu();
	cout << "=== Ubah Stok ===" << endl;
	cout << "Masukkan nomor menu : ";
	cin >> noMenu;
	noMenu--; // Kurangi 1 karena array dimulai dari 0
	if (noMenu >= 0 && noMenu < 8)
	{
		cout << "---------------------" << endl;
		cout << "Nama Makanan  : " << namaMakananArr[noMenu] << endl;
		cout << "Stok sekarang : " << stokMakananArr[noMenu] << endl;
		cout << "Ubah stok     : ";
		int* stokBaru = &stokMakananArr[noMenu];
		cin >> *stokBaru;
		system("cls");
		cout << "Stok berhasil diubah!" << endl;
		Sleep(1700);
		system("cls");
	}
	else
	{
		system("cls");
		cout << "Menu tidak tersedia" << endl;
		Sleep(1700);
		system("cls");
		goto menu;
	}
}

void riwayatPesanCustomer()
{
	if (jmlRiwayat == 0)
	{
		system("cls");
		cout << "Riwayat kosong" << endl;
		Sleep(1700);
		system("cls");
	}
	else
	{
		system("cls");
		cout << "=== Riwayat Pesanan ===" << endl;
		for (int i = 0; i < jmlRiwayat; i++)
		{
			cout << "Nama Customer  : " << antrian.riwayat[i].riwayatNamaCustomer << endl;
			cout << "Nama Makanan   : " << antrian.riwayat[i].riwayatNamaMakanan << endl;
			cout << "Jumlah Pesanan : " << antrian.riwayat[i].riwayatJumlahPesanan << endl;
			cout << "Harga          : " << antrian.riwayat[i].riwayatHarga << endl;
			cout << "-------------------------------------     " << endl;
			cout << "Total Harga    : " << antrian.riwayat[i].riwayatTotalHarga << endl;
			cout << "-------------------------------------     " << endl;
			cout << endl;
		}
	}
}

void halamanManager()
{
	do
	{
		cout << "=============================" << endl;
		cout << "        Halaman Manager      " << endl;
		cout << "=============================" << endl;
		cout << "[1] Lihat Menu" << endl;
		cout << "[2] Ubah Stok" << endl;
		cout << "[3] Lihat Stok" << endl;
		cout << "[4] Tampilkan Riwayat Pemesanan" << endl;
		cout << "[5] Cari Riwayat Pemesanan" << endl;
		cout << "[6] Pengeluaran Customer" << endl;
		cout << "[7] Kembali" << endl;
		cout << "Masukkan pilihan : ";
		cin >> pil;
		if (pil == 1)
		{
			tampilMenu();
		}
		else if (pil == 2)
		{
			system("cls");
			tambahStok();
		}
		else if (pil == 3)
		{
			system("cls");
			cout << "=== Stok yang tersedia ===\n" << endl;
			for (int i = 0; i < 8; i++)
			{
				cout << "-----------" << endl;
				cout << "Menu ke - " << i + 1 << endl;
				cout << "---------------------------" << endl;
				cout << "Nama Makanan : " << namaMakananArr[i] << endl;
				cout << "Stok         : " << stokMakananArr[i] << endl;
				cout << "---------------------------" << endl;
				cout << endl;
			}
		}
		else if (pil == 4)
		{
			riwayatPesanCustomer();
		}
		else if (pil == 5)
		{
			searchNama();
		}
		else if (pil == 6)
		{
			sortPengeluaranCustomer();
		}
		else if (pil == 7)
		{
			system("cls");
			cout << "Kembali ke halaman login" << endl;
			Sleep(1700);
			system("cls");
			masukAkun();

		}
		else
		{
			system("cls");
			cout << "Pilihan tidak tersedia!" << endl;
			Sleep(1700);
			system("cls");
		}
	} while (pil != 8);
}

void sortPengeluaranCustomer()
{
	cout << "=== Urutkan Pengeluaran Customer ===" << endl;
	cout << "[1] Urutkan dari yang terbesar" << endl;
	cout << "[2] Urutkan dari yang terkecil" << endl;
	cout << "Masukkan pilihan : ";
	cin >> pil;
	if (pil == 1)
	{
		// Sorting dari yang terbesar
		if (pil == 1)
		{
			// Sorting dari yang terbesar menggunakan Bubble Sort
			for (int i = 0; i < jmlRiwayat - 1; i++)
			{
				for (int j = 0; j < jmlRiwayat - i - 1; j++)
				{
					if (antrian.riwayat[j].riwayatTotalHarga < antrian.riwayat[j + 1].riwayatTotalHarga)
					{
						// Tukar posisi
						RiwayatPesanan temp = antrian.riwayat[j];
						antrian.riwayat[j] = antrian.riwayat[j + 1];
						antrian.riwayat[j + 1] = temp;
					}
				}
			}
			system("cls");
			cout << "Pengeluaran customer dari yang terbesar : " << endl;
			for (int i = 0; i < jmlRiwayat; i++)
			{
				cout << "Nama Customer  : " << antrian.riwayat[i].riwayatNamaCustomer << endl;
				cout << "Nama Makanan   : " << antrian.riwayat[i].riwayatNamaMakanan << endl;
				cout << "Jumlah Pesanan : " << antrian.riwayat[i].riwayatJumlahPesanan << endl;
				cout << "Harga          : " << antrian.riwayat[i].riwayatHarga << endl;
				cout << "-------------------------------------     " << endl;
				cout << "Total Harga    : " << antrian.riwayat[i].riwayatTotalHarga << endl;
				cout << "-------------------------------------     " << endl;
				cout << endl;
			}
		}
	}

	// Sorting dari yang terkecil
	else if (pil == 2)
	{
		// Sorting dari yang terkecil menggunakan Bubble Sort
		for (int i = 0; i < jmlRiwayat - 1; i++)
		{
			for (int j = 0; j < jmlRiwayat - i - 1; j++)
			{
				if (antrian.riwayat[j].riwayatTotalHarga > antrian.riwayat[j + 1].riwayatTotalHarga)
				{
					// Tukar posisi
					RiwayatPesanan temp = antrian.riwayat[j];
					antrian.riwayat[j] = antrian.riwayat[j + 1];
					antrian.riwayat[j + 1] = temp;
				}
			}
		}
		system("cls");
		cout << "Pengeluaran customer dari yang terkecil : " << endl;
		for (int i = 0; i < jmlRiwayat; i++)
		{
			cout << "Nama Customer  : " << antrian.riwayat[i].riwayatNamaCustomer << endl;
			cout << "Nama Makanan   : " << antrian.riwayat[i].riwayatNamaMakanan << endl;
			cout << "Jumlah Pesanan : " << antrian.riwayat[i].riwayatJumlahPesanan << endl;
			cout << "Harga          : " << antrian.riwayat[i].riwayatHarga << endl;
			cout << "-------------------------------------     " << endl;
			cout << "Total Harga    : " << antrian.riwayat[i].riwayatTotalHarga << endl;
			cout << "-------------------------------------     " << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "Pilihan tidak tersedia" << endl;
	}
}

void searchNama()
{
	string cariNama; // Nama yang dicari
	int posisi[max]; // Menyimpan posisi data yang ditemukan
	int x = 0; // Menyimpan jumlah data yang ditemukan

	if (jmlRiwayat == 0)
	{
		system("cls");
		cout << "Riwayat kosong" << endl;
		Sleep(1700);
		system("cls");
	}
	else
	{
		cout << "Masukkan nama customer yang dicari : ";
		cin >> cariNama;
		for (int i = 0; i < jmlRiwayat; i++)
		{
			if (antrian.riwayat[i].riwayatNamaCustomer == cariNama)
			{
				// Simpan posisi data yang ditemukan
				posisi[x] = i;
				x++;
			}
		}
		cout << endl;

		if (x == 0)
		{
			system("cls");
			cout << "Sistem tidak menemukan customer dengan nama " << cariNama << endl;
			Sleep(2000);
			system("cls");
		}
		else
		{
			system("cls");
			cout << "Sistem menemukan customer dengan nama " << cariNama << endl;
			cout << "Berikut data pesanan yang telah dilakukan oleh \n" << cariNama << endl;
			for (int i = 0; i < x; i++)
			{
				cout << "Nama Customer  : " << antrian.riwayat[posisi[i]].riwayatNamaCustomer << endl;
				cout << "Nama Makanan   : " << antrian.riwayat[posisi[i]].riwayatNamaMakanan << endl;
				cout << "Jumlah Pesanan : " << antrian.riwayat[posisi[i]].riwayatJumlahPesanan << endl;
				cout << "Harga          : " << antrian.riwayat[posisi[i]].riwayatHarga << endl;
				cout << "-------------------------------------    " << endl;
				cout << "Total Harga    : " << antrian.riwayat[posisi[i]].riwayatTotalHarga << endl;
				cout << "-------------------------------------     " << endl;
				cout << endl;
			}
		}
	}
}

void masukAkun()
{
	cout << "=============================" << endl;
	cout << "|                           |" << endl;
	cout << "|       HALAMAN LOGIN       |" << endl;
	cout << "|                           |" << endl;
	cout << "=============================" << endl;
	cout << "[1] Login sebagai manager" << endl;
	cout << "[2] Login sebagai kasir" << endl;
	cout << "[3] Keluar" << endl;
	cout << "Masukkan pilihan: ";
	cin >> pil;
	if (pil == 1)
	{
		system("cls");
		cout << "=== Login as Manager ====" << endl;
		cout << "[*] Masukkan username : ";
		cin >> managerName;
		cout << "[*] Masukkan password : ";
		cin >> managerPass;
		if (managerName == "admin" && managerPass == "admin")
		{
			system("cls");
			int loading = 5;
			cout << "Loading";
			for (int i = 0; i < loading; ++i)
			{
				cout << ".";
				cout.flush();
				Sleep(200);
			}
			system("cls");
			cout << "Anda login sebagai manager\n" << endl;
			// Tambahkan animasi loading dengan cout Loading...
			// Tambahkan kode untuk menu manager
			halamanManager();
		}
		else
		{
			system("cls");
			int loading = 5;
			cout << "Loading";
			for (int i = 0; i < loading; ++i)
			{
				cout << ".";
				cout.flush();
				Sleep(200);
			}
			system("cls");
			cout << "Username atau password salah!" << endl;
			Sleep(1300);
			system("cls");
			// Tambahan kode untuk mengulang login
		}
	}
	else if (pil == 2)
	{
		system("cls");
		int loading = 5;
		cout << "Loading";
		for (int i = 0; i < loading; ++i)
		{
			cout << ".";
			cout.flush();
			Sleep(300);
		}
		system("cls");
		cout << "Anda login sebagai kasir\n" << endl;
		halamanKasir();
		// Tambahkan animasi loading dengan cout Loading...
		// Tambahkan kode untuk menu kasir
	}
	else if (pil == 3)
	{
		cout << "Anda keluar" << endl;
		// Tambahkan animasi loading dengan cout Keluar...
		exit(0);
	}
	else
	{
		system("cls");
		cout << "Pilihan tidak tersedia" << endl;
		Sleep(1700);
		system("cls");
	}
}

int main()
{
	while (true)
	{
		cout << "                             " << endl;
		cout << "  SELAMAT DATANG DI SISTEM   " << endl;
		masukAkun();
	}
}
