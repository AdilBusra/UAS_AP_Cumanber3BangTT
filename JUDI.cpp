#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class PapanLotreDigital {
    private:
        static const int jumlah_baris = 4;
        static const int jumlah_kolom = 5;
        static const int jumlah_bom = 2;
        char papan[jumlah_baris][jumlah_kolom];
        bool sudahDibuka[jumlah_baris][jumlah_kolom];
        int isiKotak[jumlah_baris][jumlah_kolom];
        int aman_terbuka;

    public:
        PapanLotreDigital() {
            aman_terbuka = 0;
            for (int i = 0; i < jumlah_baris; ++i) {
                for (int j = 0; j < jumlah_kolom; ++j) {
                    papan[i][j] = '*';
                    sudahDibuka[i][j] = false;
                    isiKotak[i][j] = 0;
                }
            }
            tempatkanBomSecaraAcak();
        }

        void tempatkanBomSecaraAcak() {
            srand((unsigned)time(0));
            int bomTerpasang = 0;
            while (bomTerpasang < jumlah_bom) {
                int baris = rand() % jumlah_baris;
                int kolom = rand() % jumlah_kolom;
                if (isiKotak[baris][kolom] == 0) {
                    isiKotak[baris][kolom] = 1;
                    bomTerpasang++;
                }
            }
        }

        void tampilkanPapan() {
            cout << "   ";
            for (int k = 0; k < jumlah_kolom; ++k) cout << k + 1 << " ";
            cout << endl;
            for (int i = 0; i < jumlah_baris; ++i) {
                cout << i + 1 << "  ";
                for (int j = 0; j < jumlah_kolom; ++j) {
                    cout << papan[i][j] << " ";
                }
                cout << endl;
            }
        }

        bool prosesTebakan(int baris, int kolom) {
            if (baris < 0 || baris >= jumlah_baris || kolom < 0 || kolom >= jumlah_kolom) {
                cout << "Posisi di luar jangkauan!\n";
                return false;
            }
            if (sudahDibuka[baris][kolom]) {
                cout << "Kotak sudah pernah dibuka!\n";
                return false;
            }
            sudahDibuka[baris][kolom] = true;

            if (isiKotak[baris][kolom] == 1) {
                papan[baris][kolom] = 'X';
                tampilkanPapan();
                cout << "Kamu menemukan BOM! Permainan berakhir.\n";
                return true;
            } else {
                papan[baris][kolom] = 'O';
                aman_terbuka++;
                cout << "Kotak Aman\n";
                return false;
            }
        }

        bool if_menang() {
            return (aman_terbuka == jumlah_baris * jumlah_kolom - jumlah_bom);
        }
};

int main() {
    PapanLotreDigital papan;
    int baris, kolom;
    bool selesai = false;

    cout << "LOTRE GOSOK DIGITAL\n";
    cout << "Tebak kotak yang aman. Jika menemukan bom, kamu kalah.\n";
    cout << "Jika semua kotak aman terbuka, kamu menang!\n\n";

    while (!selesai) {
        papan.tampilkanPapan();
        cout << "Masukkan baris dan kolom (contoh: 2 3): ";
        cin >> baris >> kolom;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Masukkan angka.\n";
            continue;
        }

        baris -= 1;
        kolom -= 1;

        bool kena_bom = papan.prosesTebakan(baris, kolom);
        if (kena_bom) {
            selesai = true;
            break;
        }
        if (papan.if_menang()) {
            papan.tampilkanPapan();
            cout << "Selamat! Kamu membuka semua kotak aman!\n";
            selesai = true;
        }
    }
    cout << "Permainan selesai.\n";
    return 0;
}
