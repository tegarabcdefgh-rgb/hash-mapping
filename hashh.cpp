#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10; // Ukuran tabel hash

// Status slot dalam tabel
enum SlotState { EMPTY, OCCUPIED, DELETED };

// Struktur data mahasiswa
struct Mahasiswa {
    long long npm;
    string nama;
    string jurusan;
    SlotState state;
};

// Fungsi hash untuk menentukan indeks tabel
int hashFunction(long long key) {
    return (key % SIZE + SIZE) % SIZE;
}

// Inisialisasi tabel agar kosong
void initTable(Mahasiswa table[]) {
    for (int i = 0; i < SIZE; ++i) {
        table[i].state = EMPTY;
    }
}

// Fungsi untuk menambahkan data mahasiswa
bool insert(Mahasiswa table[], long long npm, string nama, string jurusan) {
    int idx = hashFunction(npm);
    int firstDeleted = -1;

    for (int step = 0; step < SIZE; ++step) {
        int i = (idx + step) % SIZE;

        if (table[i].state == OCCUPIED) {
            if (table[i].npm == npm) {
                table[i].nama = nama;
                table[i].jurusan = jurusan;
                return true;
            }
        } else if (table[i].state == DELETED) {
            if (firstDeleted == -1) firstDeleted = i;
        } else {
            if (firstDeleted != -1) i = firstDeleted;
            table[i].npm = npm;
            table[i].nama = nama;
            table[i].jurusan = jurusan;
            table[i].state = OCCUPIED;
            return true;
        }
    }

    if (firstDeleted != -1) {
        table[firstDeleted].npm = npm;
        table[firstDeleted].nama = nama;
        table[firstDeleted].jurusan = jurusan;
        table[firstDeleted].state = OCCUPIED;
        return true;
    }
    return false;
}

// Fungsi untuk mencari mahasiswa berdasarkan NPM
Mahasiswa* search(Mahasiswa table[], long long npm) {
    int idx = hashFunction(npm);

    for (int step = 0; step < SIZE; ++step) {
        int i = (idx + step) % SIZE;
        if (table[i].state == EMPTY)
            return nullptr;
        if (table[i].state == OCCUPIED && table[i].npm == npm)
            return &table[i];
    }
    return nullptr;
}

// Fungsi untuk menghapus data berdasarkan NPM
bool removeKey(Mahasiswa table[], long long npm) {
    Mahasiswa* mhs = search(table, npm);
    if (!mhs) return false;
    mhs->state = DELETED;
    return true;
}

// Menampilkan isi tabel hash
void display(Mahasiswa table[]) {
    cout << "\n=== Data Mahasiswa (Hash Map - Open Addressing) ===\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i << ": ";
        if (table[i].state == EMPTY)
            cout << "EMPTY\n";
        else if (table[i].state == DELETED)
            cout << "DELETED\n";
        else
            cout << "(" << table[i].npm << ", " << table[i].nama << ", " << table[i].jurusan << ")\n";
    }
}

int main() {
    Mahasiswa table[SIZE];
    initTable(table);

    // Menambahkan data mahasiswa kampus
    insert(table, 2415061010, "Jaya Pratama", "Informatika");
    insert(table, 2415061020, "Alfath Ariya", "Sistem Informasi");
    insert(table, 2415061030, "I Gede Dharma", "Teknik Komputer");
    insert(table, 2415061040, "Davi Tholiatul", "Informatika");
    insert(table, 2415061050, "Endy Yoga", "Data Science");

    display(table);

    // Mencari data mahasiswa berdasarkan NPM
    long long cariNPM;
    cout << "\nMasukkan NPM yang ingin dicari: ";
    cin >> cariNPM;

    Mahasiswa* hasil = search(table, cariNPM);
    if (hasil)
        cout << "Data ditemukan: " << hasil->nama << " - " << hasil->jurusan << endl;
    else
        cout << "Data dengan NPM tersebut tidak ditemukan.\n";

    // Menghapus data berdasarkan NPM
    long long hapusNPM;
    cout << "\nMasukkan NPM yang ingin dihapus: ";
    cin >> hapusNPM;

    if (removeKey(table, hapusNPM))
        cout << "Data berhasil dihapus.\n";
    else
        cout << "Data tidak ditemukan.\n";

    cout << "\nSetelah penghapusan:\n";
    display(table);

    return 0;
}
