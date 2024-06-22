// Queue digunakan untuk kasir sebagai fitur antrian pesanan
// Linked list akan digunakan manager sebagai fitur penambahan menu, dan stok
// Linked list insertAwal untuk menambahkan menu di awal
// Linked list insertTengah untuk menambahkan menu di tengah
// Linked list insertAkhir untuk menambahkan menu di akhir

#include <iostream>
#define max 100
using namespace std;

int pil;
string managerName, managerPass;
bool isAdmin;

// Data menu
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
		cout << "Pesanan teratas selesai" << endl;

		antrian.head++;
		if (antrian.head == antrian.tail)
		{
			antrian.head = antrian.tail = 0;
		}
	}
	else
	{
		cout << "Antrian kosong!" << endl;
	}
}

void tampilAntrian()
{
	if (!isEmpty())
	{
		for (int i = antrian.head; i < antrian.tail; i++)
		{
			cout << "Pesanan ke - " << i + 1 << endl;
			cout << "Nama Customer : " << antrian.data[i].namaCustomer << endl;
			cout << "Nama Makanan : " << antrian.data[i].namaMakanan << endl;
			cout << "Jumlah : " << antrian.data[i].jumlahPesanan << endl;
			cout << "Total Harga : " << antrian.data[i].totalHarga << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "Antrian kosong!" << endl;
	}

}

void tampilMenu()
{
	for (int i = 0; i < 8; i++)
	{
		cout << "Menu ke - " << i + 1 << endl;
		cout << "Nama Makanan : " << namaMakananArr[i] << endl;
		cout << "Harga : " << hargaMakananArr[i] << endl;
		if (stokMakananArr[i] == 0)
		{
			cout << "Stok : Habis" << endl;
		}
		else
		{
			cout << "Stok : " << stokMakananArr[i] << endl;
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
		cout << "Masukkan nama customer : ";
		cin >> antrian.data[antrian.tail].namaCustomer;
		antrian.riwayat[antrian.tail].riwayatNamaCustomer = antrian.data[antrian.tail].namaCustomer;

		char pilihan;
		do
		{
			tampilMenu();
			cout << "Masukkan nomor menu : ";
			cin >> noMenu;
			noMenu--;
			if (noMenu >= 0 && noMenu < 8)
			{
				if (stokMakananArr[noMenu] == 0)
				{
					cout << "Stok habis" << endl;
				}
				else
				{
					cout << "Nama Makanan : " << namaMakananArr[noMenu] << endl;
					cout << "Jumlah pesanan : ";
					cin >> antrian.data[antrian.tail].jumlahPesanan;
					antrian.riwayat[antrian.tail].riwayatJumlahPesanan = antrian.data[antrian.tail].jumlahPesanan; // Copy jumlah pesanan ke riwayat

					if (antrian.data[antrian.tail].jumlahPesanan > stokMakananArr[noMenu])
					{
						cout << "Stok tidak mencukupi" << endl;
						enqueue();
					}
					else
					{
						antrian.data[antrian.tail].totalHarga = hargaMakananArr[noMenu] * antrian.data[antrian.tail].jumlahPesanan; // Hitung total harga
						antrian.riwayat[antrian.tail].riwayatHarga = hargaMakananArr[noMenu]; // Copy harga makanan ke riwayat
						cout << "Total harga : " << antrian.data[antrian.tail].totalHarga << endl; // Tampilkan total harga
						cout << "Pesanan berhasil ditambahkan" << endl;

						// Copy data ke struktur antrian
						antrian.data[antrian.tail].namaMakanan = namaMakananArr[noMenu]; // Copy nama makanan
						antrian.riwayat[antrian.tail].riwayatNamaMakanan = namaMakananArr[noMenu]; // Copy nama makanan ke riwayat
						antrian.data[antrian.tail].harga = hargaMakananArr[noMenu]; // Copy harga makanan
						antrian.riwayat[antrian.tail].riwayatHarga = hargaMakananArr[noMenu]; // Copy harga makanan ke riwayat
						stokSisa = stokMakananArr[noMenu] - antrian.data[antrian.tail].jumlahPesanan; // Hitung sisa stok
						antrian.data[antrian.tail].stok = stokSisa; // Copy sisa stok
						stokMakananArr[noMenu] -= antrian.data[antrian.tail].jumlahPesanan; // Kurangi stok

						antrian.tail++;

						cout << "Apakah ingin menambahkan pesanan lagi? (y/n) : ";
						cin >> pilihan;
					}
				}
			}
		} while (pilihan == 'y');

		cout << "Terimakasih sudah memesan" << endl;
		halamanKasir();
	}
	else
	{
		cout << "Antrian penuh, mohon menunggu beberapa saat!" << endl;
	}
}

void halamanKasir()
{
	do
	{
		cout << "=== Halaman Kasir ===" << endl;
		cout << "[1] Tambah antrian" << endl; // Done
		cout << "[2] Tampilkan antrian" << endl; // Done
		cout << "[3] Selesaikan pesanan teratas" << endl; // Done
		cout << "[4] Kembali" << endl; // Done
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
			cout << "Anda keluar" << endl;
			masukAkun();
		}
		else
		{
			cout << "Pilihan tidak tersedia" << endl;
		}
	} while (pil != 4);
}

void tambahStok()
{
	cout << "=== Ubah Stok ===" << endl;
	cout << "Masukkan nomor menu : ";
	cin >> noMenu;
	noMenu--;
	if (noMenu >= 0 && noMenu < 8)
	{
		cout << "Nama Makanan : " << namaMakananArr[noMenu] << endl;
		cout << "Stok sekarang : " << stokMakananArr[noMenu] << endl;
		cout << "Ubah stok : ";
		int* stokBaru = &stokMakananArr[noMenu];
		cin >> *stokBaru;
		/*	stokMakananArr[pilMenu] += *stokBaru;*/
		cout << "Stok berhasil ditambahkan" << endl;
	}
	else
	{
		cout << "Menu tidak tersedia" << endl;
	}
}

void halamanManager()
{
	do
	{
		cout << "=== Halaman Manager ===" << endl;
		cout << "[1] Lihat Menu" << endl; // Done
		cout << "[2] Ubah Stok" << endl; // Done
		cout << "[3] Lihat Stok" << endl; // Done
		cout << "[4] Cari Riwayat Pemesanan" << endl;
		cout << "[5] Laporan Keuangan" << endl;
		cout << "[6] Kembali" << endl;
		cout << "Masukkan pilihan : ";
		cin >> pil;
		if (pil == 1)
		{
			tampilMenu();
		}
		else if (pil == 2)
		{
			tambahStok();
		}
		else if (pil == 3)
		{
			for (int i = 0; i < 8; i++)
			{
				cout << "Menu ke - " << i + 1 << endl;
				cout << "Nama Makanan : " << namaMakananArr[i] << endl;
				cout << "Stok : " << stokMakananArr[i] << endl;
				cout << endl;
			}
		}
		else if (pil == 4)
		{
			searchNama();
		}
		else if (pil == 5)
		{
			cout << "Laporan Keuangan" << endl;
		}
		else if (pil == 6)
		{
			cout << "Anda keluar" << endl;
			masukAkun();
		}
		else
		{
			cout << "Pilihan tidak tersedia" << endl;
		}
	} while (pil != 6);
}

void searchNama()
{	
	string cariNama;
	int ketemu, posisi[max];
	int x = 0;
	int k = 0;

	if (riwayat == NULL)
	{
		cout << "Riwayat kosong" << endl;
	}
	else
	{
		cout << "Masukkan nama customer yang dicari : ";
		cin >> cariNama;
		while (antrian.riwayat[k].riwayatNamaCustomer == cariNama)
		{
			k++;
			posisi[x] = k;
			x++;
		}
		cout << endl;
		if (x == 0)
		{
			cout << "Sistem tidak menemukan customer dengan nama " << cariNama << endl;
		}
		else
		{
			cout << "Sistem menemukan customer dengan nama " << cariNama << endl;
			cout << cariNama << " telah memesan sebanyak " << x << " kali" << endl;
			cout << "Berikut data pesanan yang telah dilakukan oleh " << cariNama << endl;
			for (int i = 0; i < x; i++)
			{
				if (antrian.riwayat[i].riwayatNamaCustomer == cariNama)
				{
					cout << "Nama Customer : " << antrian.riwayat[posisi[i]].riwayatNamaCustomer << endl;
					cout << "Nama Makanan : " << antrian.riwayat[posisi[i]].riwayatNamaMakanan << endl;
					cout << "Jumlah Pesanan : " << antrian.riwayat[posisi[i]].riwayatJumlahPesanan << endl;
					cout << "Harga : " << antrian.riwayat[posisi[i]].riwayatHarga << endl;
					cout << "Total Harga : " << antrian.riwayat[posisi[i]].riwayatTotalHarga << endl;
					cout << endl;
				}
			}
		}
	}
}

void masukAkun()
{
	cout << "=== Halaman Login ===" << endl;
	cout << "[1] Login sebagai manager" << endl;
	cout << "[2] Login sebagai kasir" << endl;
	cout << "[3] Keluar" << endl;
	cout << "Masukkan pilihan: ";
	cin >> pil;
	if (pil == 1)
	{
		cout << "=== Login as Manager ====" << endl;
		cout << "[*] Masukkan username : ";
		cin >> managerName;
		cout << "[*] Masukkan password : ";
		cin >> managerPass;
		if (managerName == "admin" && managerPass == "admin")
		{
			cout << "Anda login sebagai manager" << endl;
			// Tambahkan animasi loading dengan cout Loading...
			// Tambahkan kode untuk menu manager
			halamanManager();
		}
		else
		{
			cout << "Username atau password salah" << endl;
			// Tambahan kode untuk mengulang login
		}
	}
	else if (pil == 2)
	{
		cout << "Anda login sebagai kasir" << endl;
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
		cout << "Pilihan tidak tersedia" << endl;
	}
}

int main()
{
	while (true)
	{
		masukAkun();
	}
}