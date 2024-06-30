#include <iostream>
#include <windows.h>
#include <conio.h>

#define max 100

using namespace std;

int pil, jmlRiwayat = 0, i, pilMenu, stokSisa, noMenu, batas = 0;
string managerName, managerPass, status;
char pilihan;

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

struct queue
{
	DataPesanan data[max];
	RiwayatPesanan riwayat[max];
	int head;
	int tail;
}antrian;


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

void header() {
	cout << "=============================\n";
	cout << "          RESTAURANT         \n";
	cout << "=============================\n\n";
}

void masukAkun();
void searchNama();
void sortPengeluaranCustomer();
void halamanManager();


void loading() {
	header();
	cout << "Loading";
	for (i = 0; i < 5; i++) {
		cout << ".";
		Sleep(300);
	}
	system("cls");
}

void dequeue() // Queue
{
	if (!isEmpty())
	{
		system("cls");
		header();
		cout << "Pesanan teratas selesai" << endl;

		antrian.head++;
		if (antrian.head == antrian.tail)
		{
			antrian.head = antrian.tail = 0;
		}
		batas++;
		Sleep(1000);
		system("cls");
	}
	else
	{
		system("cls");
		header();
		cout << "Antrian kosong!" << endl;
		Sleep(1000);
		system("cls");
	}
}

void tampilAntrian()
{
	if (!isEmpty())
	{ // i sekarang 0
		system("cls");
		header();
		cout << "=== Antrian Pesanan ===\n" << endl;
		cout << "=========================================================================\n";
		cout << "| No\t| Nama Customer\t| Nama Makanan\t| Jumlah\t| Total Harga\t|\n";
		for (i = antrian.head; i < antrian.tail; i++) {
			cout << "| " << i - antrian.head + 1 << "\t| " << antrian.data[i].namaCustomer << "\t\t| " << antrian.data[i].namaMakanan << "\t| " << antrian.data[i].jumlahPesanan << "\t\t| " << antrian.data[i].totalHarga << "\t\t|\n";
		}
		cout << "=========================================================================\n";
		_getch();
		system("cls");
	}
	else
	{
		system("cls");
		header();
		cout << "Antrian kosong!" << endl;
		Sleep(1000);
		system("cls");
	}
}

void tampilMenu()
{
	system("cls");
	header();
	cout << "=== Menu yang tersedia ===" << endl;
	cout << "=========================================\n";
	cout << "| No\t| Nama Makanan\t| Harga\t| Stock |\n";
	for (i = 0; i < 8; i++) {
		cout << "| " << i + 1 << "\t| " << namaMakananArr[i] << "\t| " << hargaMakananArr[i] << "\t| " << stokMakananArr[i] << "\t|\n";
	}
	cout << "=========================================\n";
}

void enqueue()
{
	if (!isFull())
	{
		system("cls");
		header();
		cout << "Masukkan nama customer : ";
		cin >> antrian.data[antrian.tail].namaCustomer;
		antrian.riwayat[antrian.tail].riwayatNamaCustomer = antrian.data[antrian.tail].namaCustomer; // Copy nama customer ke riwayat
		string tempNamaCustomer = antrian.data[antrian.tail].namaCustomer; // Simpan nama customer sementara

		do
		{
		perulanganMenu:
			tampilMenu();
			cout << "Masukkan nomor menu : ";
			cin >> noMenu;
			noMenu--; // Kurangi 1 karena array dimulai dari 0
			cout << "Nama Makanan   : " << namaMakananArr[noMenu] << endl;
			cout << "Jumlah pesanan : ";
			cin >> antrian.data[antrian.tail].jumlahPesanan;
			if (antrian.data[antrian.tail].jumlahPesanan == 0) {
				system("cls");
				header();
				cout << "Minimal pesanan 1\n";
				Sleep(1000);
				system("cls");
				goto perulanganMenu;
			}
			else {
				antrian.riwayat[antrian.tail].riwayatJumlahPesanan = antrian.data[antrian.tail].jumlahPesanan; // Copy jumlah pesanan ke riwayat

				if (antrian.data[antrian.tail].jumlahPesanan > stokMakananArr[noMenu])
				{
					system("cls");
					header();
					cout << "Stok telah habis atau tidak mencukupi, silahkan pesan dengan jumlah yang lebih kecil atau pesan menu lain" << endl;
					Sleep(1000);
					system("cls");
					pilihan = 'y';
				}
				else
				{
					antrian.data[antrian.tail].totalHarga = hargaMakananArr[noMenu] * antrian.data[antrian.tail].jumlahPesanan; 
					cout << "Total harga    : " << antrian.data[antrian.tail].totalHarga << endl; 
					cout << "Pesanan berhasil ditambahkan" << endl;

					// Copy data ke struktur antrian
					antrian.data[antrian.tail].namaCustomer = tempNamaCustomer; 
					antrian.data[antrian.tail].namaMakanan = namaMakananArr[noMenu]; 
					antrian.data[antrian.tail].harga = hargaMakananArr[noMenu]; 
					stokSisa = stokMakananArr[noMenu] - antrian.data[antrian.tail].jumlahPesanan; 
					antrian.data[antrian.tail].stok = stokSisa;
					stokMakananArr[noMenu] -= antrian.data[antrian.tail].jumlahPesanan; 

					// Copy data ke struktur riwayat
					antrian.riwayat[jmlRiwayat].riwayatNamaCustomer = tempNamaCustomer; 
					antrian.riwayat[jmlRiwayat].riwayatNamaMakanan = namaMakananArr[noMenu]; 
					antrian.riwayat[jmlRiwayat].riwayatJumlahPesanan = antrian.data[antrian.tail].jumlahPesanan;
					antrian.riwayat[jmlRiwayat].riwayatHarga = hargaMakananArr[noMenu]; 
					antrian.riwayat[jmlRiwayat].riwayatTotalHarga = antrian.data[antrian.tail].totalHarga;

					// Tambahkan index antrian
					antrian.tail++;
					jmlRiwayat++;

					cout << "Apakah ingin menambahkan pesanan lagi? (y/n) : ";
					cin >> pilihan;
					system("cls");
				}
			}
		} while (pilihan == 'y');
	}
	else
	{
		system("cls");
		header();
		cout << "Antrian penuh!" << endl;
		Sleep(1000);
		system("cls");
	}
}

void halamanKasir()
{
	do
	{
		header();
		cout << "=== Halaman Kasir ===" << endl;
		cout << "[1] Buat pesanan" << endl;
		cout << "[2] Tampilkan antrian" << endl;
		cout << "[3] Selesaikan pesanan teratas" << endl;
		cout << "[4] Kembali" << endl;
		cout << "Masukkan pilihan : ";
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
			header();
			cout << "Anda keluar dari halaman kasir" << endl;
			Sleep(1000);
			system("cls");
			masukAkun();
		}
		else
		{
			system("cls");
			header();
			cout << "Pilihan tidak tersedia!" << endl;
			Sleep(1000);
			system("cls");
		}
	} while (pil != 4);
}

void tambahStok()
{
	system("cls");
	header();
	tampilMenu();

	cout << "Masukkan nomor menu yang ingin dirubah stoknya : ";
	cin >> noMenu;
	noMenu--; 
	if (noMenu >= 0 && noMenu < 8)
	{
		cout << "Nama Makanan  : " << namaMakananArr[noMenu] << endl;
		cout << "Stok sekarang : " << stokMakananArr[noMenu] << endl;
		cout << "Ubah stok     : ";
		int* stokBaru = &stokMakananArr[noMenu];
		cin >> *stokBaru;
		system("cls");
		header();
		cout << "Stok berhasil diubah!" << endl;
		Sleep(1000);
		system("cls");
	}
	else
	{
		system("cls");
		header();
		cout << "Menu tidak tersedia" << endl;
		Sleep(1000);
		system("cls");
		tambahStok();
	}
}

void riwayatPesanCustomer()
{
	if (jmlRiwayat == 0)
	{
		system("cls");
		header();
		cout << "Riwayat kosong!" << endl;
		Sleep(1000);
		system("cls");
		halamanManager();
	}
	else
	{
		system("cls");
		header();
		cout << "=== Riwayat Pesanan ===" << endl;
		cout << "=================================================================================================\n";
		cout << "| Nama\t\t| Nama Makanan\t\t| Jumlah| Harga\t| Total Harga\t| Status\t\t|\n";
		for (i = 0; i < jmlRiwayat; i++) {
			if (i < batas) {
				status = "Pesanan selesai";
			}
			else {
				status = "Dalam antrian\t";
			}
			cout << "| " << antrian.riwayat[i].riwayatNamaCustomer << "\t\t| " << antrian.riwayat[i].riwayatNamaMakanan << "\t\t| " << antrian.riwayat[i].riwayatJumlahPesanan << "\t| " << antrian.riwayat[i].riwayatHarga << "\t| " << antrian.riwayat[i].riwayatTotalHarga << "\t\t| " << status << "\t|\n";
		}
		cout << "=================================================================================================\n";
		_getch();
		system("cls");
		halamanManager();
	}
}

void halamanManager()
{
	do
	{
		header();
		cout << "=== Halaman Manager ===" << endl;
		cout << "[1] Lihat Menu & stock" << endl;
		cout << "[2] Ubah Stok" << endl;
		cout << "[3] Cari Riwayat Pemesanan" << endl;
		cout << "[4] Urutkan Pengeluaran Customer" << endl;
		cout << "[5] Tampilkan Riwayat Pesanan" << endl;
		cout << "[6] Kembali" << endl;
		cout << "Masukkan pilihan : ";
		cin >> pil;
		system("cls");
		if (pil == 1)
		{
			tampilMenu();
			_getch();
			system("cls");
		}
		else if (pil == 2)
		{
			tambahStok();
		}
		else if (pil == 3)
		{
			searchNama();
		}
		else if (pil == 4)
		{
			sortPengeluaranCustomer();
		}
		else if (pil == 5) {
			riwayatPesanCustomer();
		}
		else if (pil == 6)
		{
			system("cls");
			header();
			cout << "Kembali ke halaman login" << endl;
			Sleep(1000);
			system("cls");
			masukAkun();
		}
		else if (pil == 6) {
			masukAkun();
		}
		else
		{
			system("cls");
			header();
			cout << "Pilihan tidak tersedia!" << endl;
			Sleep(1000);
			system("cls");
		}
	} while (pil != 5);
}

void sortPengeluaranCustomer()
{
	system("cls");
	header();
	cout << "=== Urutkan Pengeluaran Customer ===" << endl;
	cout << "[1] Urutkan dari yang terbesar" << endl;
	cout << "[2] Urutkan dari yang terkecil" << endl;
	cout << "Masukkan pilihan : ";
	cin >> pil;
	system("cls");
	if (pil == 1)
	{
		// Sorting dari yang terbesar
		if (pil == 1)
		{
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
			cout << "=================================================================================\n";
			cout << "| No\t| Nama Customer\t| Nama Makanan\t| Jumlah| Harga\t\t| Total Harga\t|\n";
			for (i = 0; i < jmlRiwayat; i++) {
				cout << "| " << i + 1 << "\t| " << antrian.riwayat[i].riwayatNamaCustomer << "\t\t| " << antrian.riwayat[i].riwayatNamaMakanan << "\t| " << antrian.riwayat[i].riwayatJumlahPesanan << "\t| " << antrian.riwayat[i].riwayatHarga << "\t\t| " << antrian.riwayat[i].riwayatTotalHarga << "\t\t|\n";
			}
			cout << "=================================================================================\n";
			_getch();
			system("cls");
		}
	}

	// Sorting dari yang terkecil
	else if (pil == 2)
	{
		for (int i = 0; i < jmlRiwayat - 1; i++)
		{
			for (int j = 0; j < jmlRiwayat - i - 1; j++)
			{
				if (antrian.riwayat[j].riwayatTotalHarga > antrian.riwayat[j + 1].riwayatTotalHarga)
				{
					RiwayatPesanan temp = antrian.riwayat[j];
					antrian.riwayat[j] = antrian.riwayat[j + 1];
					antrian.riwayat[j + 1] = temp;
				}
			}
		}
		system("cls");
		cout << "Pengeluaran customer dari yang terkecil : " << endl;
		cout << "=================================================================================\n";
		cout << "| No\t| Nama Customer\t| Nama Makanan\t| Jumlah| Harga\t\t| Total Harga\t|\n";
		for (i = 0; i < jmlRiwayat; i++) {
			cout << "| " << i + 1 << "\t| " << antrian.riwayat[i].riwayatNamaCustomer << "\t\t| " << antrian.riwayat[i].riwayatNamaMakanan << "\t| " << antrian.riwayat[i].riwayatJumlahPesanan << "\t| " << antrian.riwayat[i].riwayatHarga << "\t\t| " << antrian.riwayat[i].riwayatTotalHarga << "\t\t|\n";
		}
		cout << "=================================================================================\n";
		_getch();
		system("cls");
	}
	else
	{
		system("cls");
		header();
		cout << "Pilihan tidak tersedia" << endl;
		Sleep(1000);
		system("cls");
	}
}

void searchNama()
{
	bool ditemukan = false;
	string cariNama; // Nama yang dicari
	int posisi[max]; // Menyimpan posisi data yang ditemukan
	int x = 0; // Menyimpan jumlah data yang ditemukan

	if (jmlRiwayat == 0)
	{
		system("cls");
		header();
		cout << "Riwayat kosong" << endl;
		Sleep(1000);
		system("cls");
	}
	else
	{
		system("cls");
		header();
		cout << "Masukkan nama customer yang dicari : ";
		cin >> cariNama;

		cout << "=========================================================================\n";
		cout << "| Nama Customer\t| Nama Makanan\t| Jumlah Pesanan| Harga\t| Total Harga\t|\n";
		for (int i = 0; i < jmlRiwayat; i++)
		{
			if (antrian.riwayat[i].riwayatNamaCustomer == cariNama)
			{
				cout << "| " << antrian.riwayat[i].riwayatNamaCustomer << "\t\t| " << antrian.riwayat[i].riwayatNamaMakanan << "\t| " << antrian.riwayat[i].riwayatJumlahPesanan << "\t\t| " << antrian.riwayat[i].riwayatHarga << "\t| " << antrian.riwayat[i].riwayatTotalHarga << "\t\t|\n";
				ditemukan = true;
			}
		}
		cout << "=========================================================================\n";
		if (ditemukan = false) {
			cout << "Sistem tidak menemukan customer dengan nama " << cariNama << endl;
		}
		_getch();
		system("cls");
		halamanManager();
	}
}

void masukAkun()
{
	system("cls");
	header();
	cout << "=== Halaman Login ===" << endl;
	cout << "[1] Login sebagai manager" << endl;
	cout << "[2] Login sebagai kasir" << endl;
	cout << "[3] Keluar" << endl;
	cout << "Masukkan pilihan: ";
	cin >> pil;
	system("cls");
	if (pil == 1)
	{
		system("cls");
		loading();
		header();
		cout << "=== Login as Manager ====" << endl;
		cout << "[*] Masukkan username : ";
		cin >> managerName;
		cout << "[*] Masukkan password : ";
		cin >> managerPass;
		if (managerName == "admin" && managerPass == "admin")
		{
			system("cls");
			halamanManager();
		}
		else
		{
			system("cls");
			header();
			cout << "Username atau password salah!" << endl;
			Sleep(1000);
			system("cls");
			masukAkun();
		}
	}

	else if (pil == 2)
	{
		loading();
		halamanKasir();
	}
	else if (pil == 3)
	{
		cout << "Anda keluar!" << endl;
		Sleep(1000);
		exit(0);
	}
	else
	{
		system("cls");
		header();
		cout << "Pilihan tidak tersedia" << endl;
		Sleep(1000);
		system("cls");
		masukAkun();
	}
}

int main()
{
	while (true)
	{
		masukAkun();
	}
}