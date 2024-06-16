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

struct Menu
{
	string namaCustomer; // Queue // Untuk menampilkan antrian atas nama ... dan untuk menyelesaikan pesanan pertama
	string namaMakanan; // Linked List // Menambahkan menu makanan
	int harga; // Linked List // Menambahkan harga makanan
	int stok; // Linked List // Menambahkan stok makanan
	int jumlah; // Queue
}menu;

struct queue
{
	Menu menu[max];
	int head;
	int tail;
}antrian;

struct linkedList
{
	Menu menu;
	linkedList *next;
};

linkedList* head = NULL;
linkedList* tail = NULL;

void insertAwal()
{
	linkedList *newNode = NULL;
	newNode = new linkedList;
	cout << "==== Tambah Menu ====" << endl;
	cout << "Masukkan nama makanan : ";
	cin >> newNode -> menu.namaMakanan;
	cout << "Masukkan harga : ";
	cin >> newNode -> menu.harga;
	cout << "Masukkan stok : ";
	cin >> newNode -> menu.stok;
	cout << "Menu " << menu.namaMakanan << " berhasil ditambahkan" << endl;
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode -> next = head;
		head = newNode;
	}
}

void insertAkhir()
{
	linkedList* newNode = NULL;
	newNode = new linkedList;
	cout << "Masukkan nama makanan : ";
	cin >> newNode->menu.namaMakanan;
	cout << "Masukkan harga : ";
	cin >> newNode->menu.harga;
	cout << "Masukkan stok : ";
	cin >> newNode->menu.stok;
	cout << "Menu " << menu.namaMakanan << " berhasil ditambahkan" << endl;
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}

void tampilDataLinkedList()
{
	if (head == NULL)
	{
		cout << "Data kosong" << endl;
	}
	else
	{
		linkedList *bantu = head;
		while (bantu != NULL)
		{
			cout << "Nama Makanan : " << bantu->menu.namaMakanan << endl;
			cout << "Harga : " << bantu->menu.harga << endl;
			cout << "Stok : " << bantu->menu.stok << endl;
			bantu = bantu->next;
		}
	}
}

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
}

void enqueue() 
{
	int sizeArray = sizeof(antrian.menu) / sizeof(*antrian.menu);
	if (!isFull())
	{
		Menu menu[max];
		linkedList* bantu = head;
		cout << "=== Halaman Kasir ===" << endl;
		cout << "Menu Makanan" << endl;
		while (bantu != NULL)
		{
			int i = 0;
			cout << "[" << i + 1 << "] " << bantu->menu.namaMakanan << " - Rp " << bantu->menu.harga << endl;
			bantu = bantu->next;
		}
		cout << "Ketik 0 jika ingin mengakhiri" << endl;
		cout << "Masukkan pilihan : ";
		cin >> pil;
		if (pil <= sizeArray)
		{
			
		}
		else if (pil == 0)
		{
			cout << "Keluar" << endl;
		}
		else
		{
			cout << "Pilihan tidak tersedia" << endl;
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
		dequeue();
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

void halamanManager()
{
	cout << "=== Halaman Manager ===" << endl;
	cout << "[1] Tambahkan Menu Makanan" << endl;
	cout << "[2] Lihat Menu" << endl;
	cout << "[3] Tambahkan Stok" << endl;
	cout << "[4] Lihat Stok" << endl;
	cout << "[5] Keluar" << endl;
	cout << "Masukkan pilihan : ";
	cin >> pil;
	if (pil == 1)
	{
		insertAwal();
	}
	else if (pil == 2)
	{
		tampilDataLinkedList();
	}
	else if (pil == 3)
	{
		// Tambahkan kode untuk menambahkan stok
	}
	else if (pil == 4)
	{
		// Tambahkan kode untuk melihat stok
	}
	else if (pil == 5)
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