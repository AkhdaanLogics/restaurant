#include <iostream>
#define max 100
using namespace std;

int pil;
string managerName, managerPass;

struct Menu
{
	string namaCustomer;
	string namaMakanan;
	int harga;
	int jumlah;
}menu;

struct queue
{
	Menu menu[max];
	int head;
	int tail;
}antrian;

bool isEmpty()
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

bool isFull()
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

void dequeue()
{
	if (!isEmpty())
	{
		cout << "Pesanan atas nama " << antrian.menu[antrian.head].namaCustomer << " selesai" << endl;
		antrian.head++;
	}
}

void enqueue()
{
	if (!isFull())
	{
		Menu menu[5];
		menu[0].namaMakanan = "Nasi Goreng";
		menu[0].harga = 15000;
		menu[1].namaMakanan = "Mie Goreng";
		menu[1].harga = 12000;
		menu[2].namaMakanan = "Ayam Goreng";
		menu[2].harga = 10000;
		menu[3].namaMakanan = "Ayam Bakar";
		menu[3].harga = 15000;
		menu[4].namaMakanan = "Es Teh";
		menu[4].harga = 5000;

	x:

		int total = 0, banyak;


		cout << "=== Halaman Kasir ===" << endl;
		cout << "Menu Makanan" << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << "[" << i + 1 << "] " << menu[i].namaMakanan << " - Rp " << menu[i].harga << endl;
		}
		cout << "[6] Keluar" << endl;
		cout << "Masukkan banyaknya jenis pesanan :";
		cin >> banyak;
		for (int i = 0; i < banyak; i++)
		{
			cout << "Pesanan ke - " << i + 1 << endl;
			cout << "Masukkan nomor menu : ";
			cin >> pil;
			cout << "Jumlah makanan : ";
			cin >> antrian.menu[antrian.tail].jumlah;
			antrian.menu[antrian.tail].harga = menu[pil - 1].harga;
			antrian.tail++;

			for (int i = antrian.head; i <= antrian.tail; i++)
			{
				cout << "Pesanan ke - " << i + 1 << endl;
				total = total + (antrian.menu[i].harga * antrian.menu[i].jumlah);
				cout << antrian.menu[i].namaMakanan << " * " << antrian.menu[i].jumlah << " - Rp " << antrian.menu[i].harga << endl;
			}
			cout << "Total harga : Rp " << total << endl;
			goto x;
		

			//if (pil == 6)
			//{
			//	cout << "Keluar" << endl;
			//}
			//else if (pil >= 1 && pil <= 5)
			//{
			//	antrian.menu[antrian.tail].namaMakanan = menu[pil - 1].namaMakanan;
			//	antrian.menu[antrian.tail].harga = menu[pil - 1].harga;
			//	cout << "Masukkan jumlah : ";
			//	cin >> antrian.menu[antrian.tail].jumlah;
			//	total = antrian.menu[antrian.tail].harga * antrian.menu[antrian.tail].jumlah;
			//	cout << "Total harga : Rp " << total << endl;
			//	antrian.tail++;
			//	cout << "Pesanan atas nama " << antrian.menu[antrian.tail - 1].namaCustomer << " telah ditambahkan" << endl;
			//	cout << "Apakah anda ingin menambahkan pesanan lagi? (y/n): ";
			//	char pilihan;
			//	cin >> pilihan;
			//	if (pilihan == 'y' || pilihan == 'Y')
			//	{
			//		//Penambahan makanan
			//	}
			//	else
			//	{
			//		//halamanKasir();
			//	}
			//}
		}

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
	cout << "[2] Pesanan selesai" << endl;
	cout << "[3] Keluar" << endl;
	cout << "Masukkan pilihan: ";
	cin >> pil;
	if (pil == 1)
	{
		// Lakukan clearscreen disini
		cout << "Masukkan nama customer : ";
		cin >> antrian.menu[antrian.tail].namaCustomer;
		enqueue();
	}
	else if (pil == 2)
	{
		//dequeue();
	}
	else if (pil == 3)
	{
		cout << "Anda keluar" << endl;
		exit(0);
	}
	else
	{
		cout << "Pilihan tidak tersedia" << endl;
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