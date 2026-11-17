#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include "backpack.h"
#include "farm_queue.h"
#include "splicing_mll.h"

struct PlayerState {
    string growID;
    int gems;
    int nextTanamId;
    int nextRecipeId;
};

// Inisialisasi Data Awal Growtopia
void initGrowtopiaData(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, ListRecipe &LR);

// Helper Manajemen Stackable Backpack
bool addOrStackItemToBackpack(ListBackpack &BP, int idItem, string namaItem, string kategori, int rarity, int qty);
bool consumeItemFromBackpack(ListBackpack &BP, int idItem, int qty);

// Subprogram Utama Mekanik Growtopia (Non-Primitif)
void spliceAndPlantMechanic(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, ListRecipe LR, int idSeed1, int idSeed2);
void advanceTimeAndHarvestMechanic(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, int detikLewat);
void recommendAvailableSplices(ListBackpack BP, ListRecipe LR);
void searchRecipesBySeed(ListRecipe LR, int idSeed);
void moveBackpackCursor(ListBackpack &BP, int arah); // -1 untuk Kiri (Prev), +1 untuk Kanan (Next)
void trashCurrentCursorItem(ListBackpack &BP);
void addCustomRecipeMechanic(PlayerState &player, ListRecipe &LR);

// Pembersihan Memori Sebelum Keluar Program
void freeAllMemory(ListBackpack &BP, FarmQueue &FQ, ListRecipe &LR);

#endif
