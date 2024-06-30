#include <iostream>
#include <windows.h>
#include <conio.h>

#define max 100

using namespace std;

int pil, jmlRiwayat = 0, i, j, pilMenu, noMenu;
string managerName, managerPass, status;
char pilihan;

// Data menu makanan
string namaMakananArr[] = { "Nasi Goreng", "Mie Goreng", "Ayam Goreng", "Ayam Bakar", "Ayam Kecap", "Ayam Rica", "Ayam Geprek", "Ayam Penyet" };
int hargaMakananArr[] = { 15000, 12000, 20000, 25000, 25000, 25000, 20000, 20000 };
int stokMakananArr[] = { 1, 5, 3, 6, 6, 7, 10, 10 };

// struct
struct DataPesanan {
	string namaMakanan;
	int harga;
	int totalHargaPerMenu;
	int jumlahPesanan;
};

struct DataCustomer {
	string namaCustomer;
	int totalHarga;
	int jumlahMenuMakanan;

	DataPesanan dataPesanan[max];
	DataPesanan riwayatDataPesanan[max];
};

struct QUEUE {
	DataCustomer dataCustomer[max];
	DataCustomer riwayatDataCustomer[max];
	int head;
	int tail;
} antrian;


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

void masukAkun();
void halamanManager();
void searchNama();
void sortPengeluaranCustomer();

void header() {
	cout << "=============================\n";
	cout << "          RESTAURANT         \n";
	cout << "=============================\n\n";
}

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
	if (!isEmpty()) {
		system("cls");
		header();
		for (i = antrian.head; i < antrian.tail; i++) {
			cout << "Pesanan atas nama : " << antrian.dataCustomer[i].namaCustomer << endl;
			cout << "=========================================================\n";
			cout << "| No\t| Nama Makanan\t| Jumlah\t| Total Harga\t|\n";
			for (j = 0; j < antrian.dataCustomer[i].jumlahMenuMakanan; j++) {
				cout << "| " << j + 1 << "\t| " << antrian.dataCustomer[i].dataPesanan[j].namaMakanan << "\t| " << antrian.dataCustomer[i].dataPesanan[j].jumlahPesanan << "\t\t| " << antrian.dataCustomer[i].dataPesanan[j].totalHargaPerMenu << "\t\t|\n";
			}
			cout << "=========================================================\n";
			cout << "Total Harga : " << antrian.dataCustomer[i].totalHarga << endl << endl;
		}
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
	if (!isFull()) {
		DataPesanan dataPesanan;
		DataPesanan riwayatDataPesanan;
		antrian.dataCustomer[antrian.tail].jumlahMenuMakanan = 0;
		antrian.dataCustomer[antrian.tail].totalHarga = 0;
		header();
		cout << "Masukkan nama customer : ";
		cin >> antrian.dataCustomer[antrian.tail].namaCustomer;

	perulangan:
		do {
			if (antrian.dataCustomer[antrian.tail].jumlahMenuMakanan < max) {
			pilihMenu:
				tampilMenu();
				cout << "Masukkan nomor menu : ";
				cin >> noMenu;
				if (noMenu >= 1 && noMenu < 9) {
					noMenu--;
					cout << "Nama Makanan        : " << namaMakananArr[noMenu] << endl;
					cout << "Jumlah pesanan      : ";
					cin >> dataPesanan.jumlahPesanan;
					if (dataPesanan.jumlahPesanan == 0) {
						cout << "Minimal pesanan 1\n";
						Sleep(1000);
						system("cls");
						goto perulangan;
					}
					else if (dataPesanan.jumlahPesanan > stokMakananArr[noMenu]) {
						cout << "Stok tidak mencukupi, silakan pesan dengan jumlah yang lebih kecil atau pesan menu lain\n";
						Sleep(1000);
						system("cls");
						goto perulangan;
					}
					else {
						stokMakananArr[noMenu] -= dataPesanan.jumlahPesanan;
						dataPesanan.namaMakanan = namaMakananArr[noMenu];
						dataPesanan.harga = hargaMakananArr[noMenu];
						dataPesanan.totalHargaPerMenu = dataPesanan.harga * dataPesanan.jumlahPesanan;

						antrian.dataCustomer[antrian.tail].dataPesanan[antrian.dataCustomer[antrian.tail].jumlahMenuMakanan] = dataPesanan;
						antrian.dataCustomer[antrian.tail].jumlahMenuMakanan++;
						antrian.dataCustomer[antrian.tail].totalHarga += dataPesanan.totalHargaPerMenu;

						riwayatDataPesanan.jumlahPesanan = dataPesanan.jumlahPesanan;
						riwayatDataPesanan.namaMakanan = dataPesanan.namaMakanan;
						riwayatDataPesanan.harga = dataPesanan.harga;
						riwayatDataPesanan.totalHargaPerMenu = dataPesanan.totalHargaPerMenu;

						antrian.riwayatDataCustomer[antrian.tail].riwayatDataPesanan[antrian.riwayatDataCustomer[antrian.tail].jumlahMenuMakanan] = riwayatDataPesanan;
						antrian.riwayatDataCustomer[antrian.tail].jumlahMenuMakanan++;
						antrian.riwayatDataCustomer[antrian.tail].namaCustomer = antrian.dataCustomer[antrian.tail].namaCustomer;
						antrian.riwayatDataCustomer[antrian.tail].totalHarga = antrian.dataCustomer[antrian.tail].totalHarga;
					}
				}
				else {
					system("cls");
					header();
					cout << "Menu makanan tidak tersedia, silahkan pilih yang lain!\n";
					Sleep(1000);
					system("cls");
					goto pilihMenu;
				}

			}
			else {
				system("cls");
				header();
				cout << "Batas maks pesanan\n";
				Sleep(1000);
				system("cls");
			}
			cout << "Apakah ingin tambah pesanan (y/n) : ";
			cin >> pilihan;
			system("cls");
		} while (pilihan == 'y');

		header();
		cout << "BERIKUT ADALAH DAFTAR PESANAN\n" << endl;
		cout << "Pesanan atas nama : " << antrian.dataCustomer[antrian.tail].namaCustomer << endl;
		cout << "=========================================================\n";
		cout << "| No\t| Nama Makanan\t| Jumlah\t| Total Harga\t|\n";
		for (j = 0; j < antrian.dataCustomer[antrian.tail].jumlahMenuMakanan; j++) {
			cout << "| " << j + 1 << "\t| " << antrian.dataCustomer[antrian.tail].dataPesanan[j].namaMakanan << "\t| " << antrian.dataCustomer[antrian.tail].dataPesanan[j].jumlahPesanan << "\t\t| " << antrian.dataCustomer[antrian.tail].dataPesanan[j].totalHargaPerMenu << "\t\t|\n";
		}
		cout << "=========================================================\n";
		cout << "Total Harga : " << antrian.dataCustomer[antrian.tail].totalHarga << endl;
		jmlRiwayat++;
		antrian.tail++;
		_getch();
		system("cls");
	}
	else {
		system("cls");
		header();
		cout << "Antrian kosong!\n";
		Sleep(1000);
		system("cls");;
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
		system("cls");
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
	noMenu--; // Kurangi 1 karena array dimulai dari 0
	if (noMenu >= 0 && noMenu < 8)
	{
		cout << "Nama Makanan  : " << namaMakananArr[noMenu] << endl;
		cout << "Stok sekarang : " << stokMakananArr[noMenu] << endl;
		cout << "Ubah stok     : ";
		int* stokBaru = &stokMakananArr[noMenu];
		cin >> *stokBaru;
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
		for (i = 0; i < jmlRiwayat; i++) {
			if (i < antrian.head) {
				status = "Pesanan selesai";
			}
			else {
				status = "Dalam antrian\t";
			}
			cout << "Pesanan atas nama : " << antrian.riwayatDataCustomer[i].namaCustomer << endl;
			cout << "=========================================================================\n";
			cout << "| No\t| Nama Makanan\t| Jumlah| Total Harga\t| Status\t\t|\n";
			for (int j = 0; j < antrian.riwayatDataCustomer[i].jumlahMenuMakanan; j++) {
				cout << "| " << j + 1 << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].namaMakanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].jumlahPesanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].totalHargaPerMenu << "\t\t| " << status << "\t|\n";
			}
			cout << "=========================================================================\n";
			cout << "Total Harga : " << antrian.riwayatDataCustomer[i].totalHarga << endl << endl;
		}
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
		cout << "[4] Pengeluaran Customer" << endl;
		cout << "[5] Tampilkan riwayat pesanan" << endl;
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
	// Sorting dari yang terbesar
	if (pil == 1)
	{
		// Sorting dari yang terbesar menggunakan Bubble Sort
		for (i = 0; i < jmlRiwayat - 1; i++) {
			for (j = 0; j < jmlRiwayat - i - 1; j++) {
				if (antrian.riwayatDataCustomer[j].totalHarga < antrian.riwayatDataCustomer[j + 1].totalHarga) {
					DataCustomer temp = antrian.riwayatDataCustomer[j];
					antrian.riwayatDataCustomer[j] = antrian.riwayatDataCustomer[j + 1];
					antrian.riwayatDataCustomer[j + 1] = temp;
				}
			}
		}


		if (jmlRiwayat == 0) {
			cout << "Belum ada riwayat.\n\n";
		}
		else {
			for (i = 0; i < jmlRiwayat; i++) {
				cout << "Nama customer : " << antrian.riwayatDataCustomer[i].namaCustomer << endl;
				cout << "=========================================================\n";
				cout << "| No\t| Nama Makanan\t| Jumlah\t| Total Harga\t|\n";
				for (j = 0; j < antrian.riwayatDataCustomer[i].jumlahMenuMakanan; j++) {
					cout << "| " << j + 1 << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].namaMakanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].jumlahPesanan << "\t\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].totalHargaPerMenu << "\t\t|\n";
				}
				cout << "=========================================================\n";;
				cout << "Total Harga : " << antrian.riwayatDataCustomer[i].totalHarga << endl << endl;
			}
			_getch();
			system("cls");
		}
	}

	// Sorting dari yang terkecil
	else if (pil == 2)
	{
		// Sorting dari yang terkecil menggunakan Bubble Sort
		for (i = 0; i < jmlRiwayat - 1; i++) {
			for (j = 0; j < jmlRiwayat - i - 1; j++) {
				if (antrian.riwayatDataCustomer[j].totalHarga > antrian.riwayatDataCustomer[j + 1].totalHarga) {
					DataCustomer temp = antrian.riwayatDataCustomer[j];
					antrian.riwayatDataCustomer[j] = antrian.riwayatDataCustomer[j + 1];
					antrian.riwayatDataCustomer[j + 1] = temp;
				}
			}
		}


		if (jmlRiwayat == 0) {
			cout << "Belum ada riwayat.\n\n";
		}
		else {
			for (i = 0; i < jmlRiwayat; i++) {
				cout << "Nama customer : " << antrian.riwayatDataCustomer[i].namaCustomer << endl;
				cout << "=========================================================\n";
				cout << "| No\t| Nama Makanan\t| Jumlah\t| Total Harga\t|\n";
				for (j = 0; j < antrian.riwayatDataCustomer[i].jumlahMenuMakanan; j++) {
					cout << "| " << j + 1 << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].namaMakanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].jumlahPesanan << "\t\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].totalHargaPerMenu << "\t\t|\n";
				}
				cout << "=========================================================\n";
				cout << "Total Harga : " << antrian.riwayatDataCustomer[i].totalHarga << endl << endl;
			}
			_getch();
			system("cls");
		}
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

		for (int i = 0; i < jmlRiwayat; i++)
		{
			if (antrian.riwayatDataCustomer[i].namaCustomer == cariNama)
			{
				if (i < antrian.head) {
					status = "Pesanan selesai";
				}
				else {
					status = "Dalam antrian\t";
				}
				cout << "Pesanan atas nama : " << antrian.riwayatDataCustomer[i].namaCustomer << endl;
				cout << "=========================================================================\n";
				cout << "| No\t| Nama Makanan\t| Jumlah| Total Harga\t| Status\t\t|\n";
				for (int j = 0; j < antrian.riwayatDataCustomer[i].jumlahMenuMakanan; j++) {
					cout << "| " << j + 1 << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].namaMakanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].jumlahPesanan << "\t| " << antrian.riwayatDataCustomer[i].riwayatDataPesanan[j].totalHargaPerMenu << "\t\t| " << status << "\t|\n";
				}
				cout << "=========================================================================\n";
				cout << "Total Harga : " << antrian.riwayatDataCustomer[i].totalHarga << endl;
				cout << "=========================================================================\n\n";
				ditemukan = true;
			}
		}

		if (!ditemukan) {
			cout << "=========================================================================\n";
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
	cout << "Masukkan pilihan : ";
	cin >> pil;
	system("cls");
	if (pil == 1)
	{
		system("cls");
		//loading();
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