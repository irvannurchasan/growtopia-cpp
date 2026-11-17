#include <iostream>
#include "game_mechanics.h"

using namespace std;

void tampilkanHeaderStatus(PlayerState player, ListBackpack BP, FarmQueue FQ) {
    cout << "\n=======================================================================\n";
    cout << "  GROWTOPIA SIMULATOR | GrowID: " << player.growID
         << " | Gems: " << player.gems
         << " | Slot: " << BP.currentSlot << "/" << BP.maxSlot
         << " | Farm Plot: " << FQ.count << "/" << FQ.maxPlot << "\n";
    cout << "=======================================================================\n";
}

int main() {
    PlayerState player;
    ListBackpack backpack;
    FarmQueue farmPlot;
    ListRecipe recipeBook;

    initGrowtopiaData(player, backpack, farmPlot, recipeBook);

    int pilihan = -1;
    while (pilihan != 0) {
        tampilkanHeaderStatus(player, backpack, farmPlot);
        cout << "MENU UTAMA MEKANIK GROWTOPIA:\n";
        cout << "1. Lihat Isi Backpack (Doubly Linked List)\n";
        cout << "2. Geser Active Slot Backpack ke Kiri (Prev Cursor)\n";
        cout << "3. Geser Active Slot Backpack ke Kanan (Next Cursor)\n";
        cout << "4. Buang / Trash Item pada Active Slot Backpack\n";
        cout << "5. Lihat Semua Resep Splicing (Multi-Linked List)\n";
        cout << "6. Cari Resep Berdasarkan ID Seed (Splicing Guide)\n";
        cout << "7. Cek Rekomendasi Seed yang Siap Di-Splice dari Backpack\n";
        cout << "8. Splice & Tanam 2 Seed ke Farm Plot (MLL + DLL -> Queue)\n";
        cout << "9. Lihat Status Lahan Tanam / Farm Plot (Queue)\n";
        cout << "10. Majukan Waktu & Panen Pohon (Simulate Growth & Harvest)\n";
        cout << "11. Tambah Resep Splicing Custom ke Recipe Book (MLL)\n";
        cout << "0. Keluar Program\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1) {
            printBackpack(backpack);
        } else if (pilihan == 2) {
            moveBackpackCursor(backpack, -1);
            printBackpack(backpack);
        } else if (pilihan == 3) {
            moveBackpackCursor(backpack, 1);
            printBackpack(backpack);
        } else if (pilihan == 4) {
            trashCurrentCursorItem(backpack);
            printBackpack(backpack);
        } else if (pilihan == 5) {
            printAllRecipes(recipeBook);
        } else if (pilihan == 6) {
            int idSeed;
            cout << "Masukkan ID Seed yang ingin dicari resepnya: ";
            cin >> idSeed;
            searchRecipesBySeed(recipeBook, idSeed);
        } else if (pilihan == 7) {
            recommendAvailableSplices(backpack, recipeBook);
        } else if (pilihan == 8) {
            printBackpack(backpack);
            int id1, id2;
            cout << "Masukkan ID Seed Pertama : ";
            cin >> id1;
            cout << "Masukkan ID Seed Kedua   : ";
            cin >> id2;
            spliceAndPlantMechanic(player, backpack, farmPlot, recipeBook, id1, id2);
        } else if (pilihan == 9) {
            printFarmQueue(farmPlot);
        } else if (pilihan == 10) {
            int detik;
            cout << "Masukkan durasi waktu yang dilewati (detik): ";
            cin >> detik;
            advanceTimeAndHarvestMechanic(player, backpack, farmPlot, detik);
        } else if (pilihan == 11) {
            addCustomRecipeMechanic(player, recipeBook);
        } else if (pilihan == 0) {
            cout << "Menyimpan state terakhir dan keluar dari Growtopia Simulator...\n";
        } else {
            cout << "[ERROR] Pilihan menu tidak valid!\n";
        }
    }

    freeAllMemory(backpack, farmPlot, recipeBook);
    return 0;
}
