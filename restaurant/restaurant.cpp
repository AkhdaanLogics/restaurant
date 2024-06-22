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

struct Menu
{
	string namaCustomer; // Queue // Untuk menampilkan antrian atas nama ... dan untuk menyelesaikan pesanan pertama
	string namaMakanan; // Menambahkan menu makanan
	int harga; // Pointer // Mengubah harga makanan
	int totalHarga;
	int jumlahPesanan;
	int stok; // Pointer // Menambahkan stok makanan
}menu[max];

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
	Menu menu[max];
	RiwayatPesanan riwayat[max];
	int head;
	int tail;
}antrian;

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
		cout << "Pesanan atas nama " << antrian.menu[antrian.head].namaCustomer << " selesai" << endl;
		antrian.head++;
	}
	else
	{
		cout << "Antrian kosong!" << endl;
	}
}

void tampilPesanan()
{
	if (!isEmpty())
	{
		for (int i = antrian.head; i < antrian.tail; i++)
		{
			cout << "Pesanan ke - " << i + 1 << endl;
			cout << "Nama Customer : " << antrian.menu[i].namaCustomer << endl;
			cout << "Nama Makanan : " << antrian.menu[i].namaMakanan << endl;
			cout << "Jumlah : " << antrian.menu[i].jumlahPesanan << endl;
			cout << "Harga : " << antrian.menu[i].harga << endl;
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
	menu[0].namaMakanan = "Nasi Goreng";
	menu[0].harga = 15000;
	menu[0].stok = 1;

	menu[1].namaMakanan = "Mie Goreng";
	menu[1].harga = 12000;
	menu[1].stok = 2;

	menu[2].namaMakanan = "Ayam Goreng";
	menu[2].harga = 20000;
	menu[2].stok = 3;

	menu[3].namaMakanan = "Ayam Bakar";
	menu[3].harga = 25000;
	menu[3].stok = 4;

	menu[4].namaMakanan = "Ayam Geprek";
	menu[4].harga = 18000;
	menu[4].stok = 5;

	menu[5].namaMakanan = "Es Teh";
	menu[5].harga = 5000;
	menu[5].stok = 6;

	menu[6].namaMakanan = "Es Jeruk";
	menu[6].harga = 6000;
	menu[6].stok = 7;

	menu[7].namaMakanan = "Es Campur";
	menu[7].harga = 10000;
	menu[7].stok = 8;

	for (int i = 0; i < 8; i++)
	{
		cout << "Menu ke - " << i + 1 << endl;
		cout << "Nama Makanan : " << menu[i].namaMakanan << endl;
		cout << "Harga : " << menu[i].harga << endl;
		if (menu[i].stok == 0)
		{
			cout << "Stok : Habis" << endl;
		}
		else
		{
			cout << "Stok : " << menu[i].stok << endl;
		}
		cout << endl;
	}
}

int pilMenu;
int stokSisa;
int noMenu;

void enqueue()
{
	//if (!isFull()) 
	//{
	//	cout << "Masukkan nama customer : ";
	//	cin >> antrian.menu[antrian.tail].namaCustomer;
	//	antrian.riwayat[antrian.tail].riwayatNamaCustomer = antrian.menu[antrian.tail].namaCustomer;
	//	char pilihan;
	//	do 
	//	{
	//		tampilMenu();
	//		cout << "Masukkan nomor menu : ";
	//		cin >> pilMenu;
	//		pilMenu--;

	//		if (pilMenu >= 0 && pilMenu < 8) 
	//		{
	//			if (menu[pilMenu].stok == 0) 
	//			{
	//				cout << "Stok habis" << endl;
	//			}
	//			else 
	//			{
	//				cout << "Nama Makanan : " << menu[pilMenu].namaMakanan << endl;

	//				cout << "Jumlah pesanan : ";
	//				cin >> menu[pilMenu].jumlahPesanan;
	//				antrian.menu[antrian.tail].jumlahPesanan = menu[pilMenu].jumlahPesanan;
	//				antrian.riwayat[antrian.tail].riwayatJumlahPesanan = menu[pilMenu].jumlahPesanan;

	//				if (menu[pilMenu].jumlahPesanan > menu[pilMenu].stok)
	//				{
	//					cout << "Stok tidak mencukupi" << endl;
	//				}
	//				else 
	//				{
	//					menu[pilMenu].totalHarga = menu[pilMenu].harga * menu[pilMenu].jumlahPesanan;
	//					antrian.riwayat[antrian.tail].riwayatHarga = menu[pilMenu].harga;

	//					cout << "Total harga : " << menu[pilMenu].totalHarga << endl;
	//					cout << "Pesanan berhasil ditambahkan" << endl;

	//					antrian.menu[antrian.tail].namaMakanan = menu[pilMenu].namaMakanan;
	//					antrian.riwayat[antrian.tail].riwayatNamaMakanan = menu[pilMenu].namaMakanan;

	//					antrian.menu[antrian.tail].harga = menu[pilMenu].harga;
	//					antrian.riwayat[antrian.tail].riwayatHarga = menu[pilMenu].harga;

	//					// BUG : Stok tidak berkurang saat memasukkan menu yang sama
	//					antrian.menu[antrian.tail].stok = menu[pilMenu].stok - menu[pilMenu].jumlahPesanan;
	//					menu[pilMenu].stok -= menu[pilMenu].jumlahPesanan;

	//					antrian.tail++;
	//					cout << "Apakah ingin menambahkan pesanan lagi? (y/n) : ";
	//					cin >> pilihan;
	//				}
	//			}
	//		}
	//		else 
	//		{
	//			cout << "Menu tidak tersedia" << endl;
	//			pilihan = 'y';
	//		}
	//	} while (pilihan == 'y');

	//	cout << "Terimakasih sudah memesan" << endl;
	//	halamanKasir();
	//}
	//else 
	//{
	//	cout << "Antrian penuh, mohon menunggu beberapa saat!" << endl;
	//}

	// Perbaikan dari chat gpt
	if (!isFull())
	{
		cout << "Masukkan nama customer : ";
		cin >> antrian.menu[antrian.tail].namaCustomer;
		antrian.riwayat[antrian.tail].riwayatNamaCustomer = antrian.menu[antrian.tail].namaCustomer;
		char pilihan;
		do
		{
			tampilMenu();
			cout << "Masukkan nomor menu : ";
			cin >> pilMenu;
			pilMenu--;

			if (pilMenu >= 0 && pilMenu < 8)
			{
				if (menu[pilMenu].stok == 0)
				{
					cout << "Stok habis" << endl;
				}
				else
				{
					cout << "Nama Makanan : " << menu[pilMenu].namaMakanan << endl;

					cout << "Jumlah pesanan : ";
					cin >> menu[pilMenu].jumlahPesanan;
					antrian.menu[antrian.tail].jumlahPesanan = menu[pilMenu].jumlahPesanan;
					antrian.riwayat[antrian.tail].riwayatJumlahPesanan = menu[pilMenu].jumlahPesanan;

					if (menu[pilMenu].jumlahPesanan > menu[pilMenu].stok)
					{
						cout << "Stok tidak mencukupi" << endl;
					}
					else
					{
						// Simpan informasi pesanan di antrian
						antrian.menu[antrian.tail].namaMakanan = menu[pilMenu].namaMakanan;
						antrian.riwayat[antrian.tail].riwayatNamaMakanan = menu[pilMenu].namaMakanan;
						antrian.menu[antrian.tail].harga = menu[pilMenu].harga;
						antrian.riwayat[antrian.tail].riwayatHarga = menu[pilMenu].harga;

						// Hitung total harga pesanan
						menu[pilMenu].totalHarga = menu[pilMenu].harga * menu[pilMenu].jumlahPesanan;
						antrian.menu[antrian.tail].totalHarga = menu[pilMenu].totalHarga;
						antrian.riwayat[antrian.tail].riwayatTotalHarga = menu[pilMenu].totalHarga;

						// Kurangi stok di menu
						menu[pilMenu].stok -= menu[pilMenu].jumlahPesanan;
						antrian.menu[antrian.tail].stok = menu[pilMenu].stok;

						antrian.tail++;
						cout << "Pesanan berhasil ditambahkan" << endl;
						cout << "Apakah ingin menambahkan pesanan lagi? (y/n) : ";
						cin >> pilihan;
					}
				}
			}
			else
			{
				cout << "Menu tidak tersedia" << endl;
				pilihan = 'y';
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
	cout << "=== Halaman Kasir ===" << endl;
	cout << "[1] Tambah antrian" << endl;
	cout << "[2] Lihat antrian" << endl;
	cout << "[2] Pesanan selesai" << endl;
	cout << "[3] Keluar" << endl;
	cout << "Masukkan pilihan: ";
	cin >> pil;
	if (pil == 1)
	{
		enqueue();
	}
	else if (pil == 2)
	{
		tampilPesanan();
	}
	else if (pil == 3)
	{
		dequeue();
	}
	else if (pil == 4)
	{
		cout << "Anda keluar" << endl;
		exit(0);
	}
	else
	{
		cout << "Pilihan tidak tersedia" << endl;
	}
}

void tambahStok(Menu* menu, int posisi, int tambah)
{
	menu[posisi].stok += tambah;
	tampilMenu();
	cout << "Stok berhasil ditambahkan" << endl;
}

void halamanManager()
{
	do
	{
		cout << "=== Halaman Manager ===" << endl;
		cout << "[1] Lihat Menu" << endl;
		cout << "[2] Tambahkan Stok" << endl;
		cout << "[3] Lihat Stok" << endl;
		cout << "[4] Cari Riwayat Pemesanan" << endl;
		cout << "[5] Laporan Keuangan" << endl;
		cout << "[6] Keluar" << endl;
		cout << "Masukkan pilihan : ";
		cin >> pil;
		if (pil == 1)
		{
			tampilMenu();
		}
		else if (pil == 2)
		{
			cout << "Masukkan nomor menu : ";
			cin >> noMenu;
			noMenu--;
			cout << "Tambahkan stok : ";
			cin >> stokSisa;
			tambahStok(menu, noMenu, stokSisa);
		}
		else if (pil == 3)
		{
			for (int i = 0; i < 8; i++)
			{
				cout << "Menu ke - " << i + 1 << endl;
				cout << "Nama Makanan : " << menu[i].namaMakanan << endl;
				cout << "Stok : " << menu[i].stok << endl;
				cout << endl;
			}
		}
		else if (pil == 4)
		{
			//searchNama();
		}
		else if (pil == 5)
		{
			cout << "Laporan Keuangan" << endl;
		}
		else if (pil == 6)
		{
			cout << "Anda keluar" << endl;
			exit(0);
		}
		else
		{
			cout << "Pilihan tidak tersedia" << endl;
		}
	} while (pil != 6);
}

void searchNama()
{
	if (!isEmpty())
	{

	}
	else
	{
		cout << "Antrian kosong!" << endl;
	}
}

int main()
{
	do
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
	} while (pil != 3);
}