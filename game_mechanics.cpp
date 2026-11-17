#include "game_mechanics.h"

bool addOrStackItemToBackpack(ListBackpack &BP, int idItem, string namaItem, string kategori, int rarity, int qty) {
    NodeBackpack* existing = findItemById(BP, idItem);
    if (existing != nullptr) {
        if (existing->info.jumlah + qty > 200) {
            existing->info.jumlah = 200;
            cout << "[INFO] " << namaItem << " mencapai batas maksimum stack (200/200)!\n";
        } else {
            existing->info.jumlah += qty;
        }
        return true;
    }

    if (isFullBackpack(BP)) {
        cout << "[GAGAL] Slot Backpack penuh! Tidak dapat menambah " << namaItem << ".\n";
        return false;
    }

    ItemBackpack baru = {idItem, namaItem, kategori, rarity, qty};
    NodeBackpack* P = allocateBackpack(baru);
    insertLastBackpack(BP, P);
    return true;
}

bool consumeItemFromBackpack(ListBackpack &BP, int idItem, int qty) {
    NodeBackpack* P = findItemById(BP, idItem);
    if (P == nullptr || P->info.jumlah < qty) {
        return false;
    }

    P->info.jumlah -= qty;
    if (P->info.jumlah == 0) {
        deleteNodeBackpack(BP, P);
    }
    return true;
}

void initGrowtopiaData(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, ListRecipe &LR) {
    player.growID = "FarmerIrvan";
    player.gems = 150;
    player.nextTanamId = 1;
    player.nextRecipeId = 1;

    createListBackpack(BP, 16);
    createFarmQueue(FQ, 6);
    createListRecipe(LR);

    // Pre-populate Seed Dasar Khas Growtopia ke Backpack (Doubly Linked List)
    addOrStackItemToBackpack(BP, 101, "Dirt Seed", "Seed", 1, 10);
    addOrStackItemToBackpack(BP, 102, "Rock Seed", "Seed", 2, 8);
    addOrStackItemToBackpack(BP, 103, "Lava Seed", "Seed", 3, 6);
    addOrStackItemToBackpack(BP, 104, "Cave Background Seed", "Seed", 2, 5);

    // Pre-populate Resep Splicing Growtopia ke Multi-Linked List
    // Resep 1: Dirt Seed (101) + Rock Seed (102) -> Grass Seed (105) / Grass Block (205)
    NodeRecipe* r1 = allocateRecipe(player.nextRecipeId++, 105, 205, "Grass Seed", "Grass Block", 3, 30);
    insertIngredientToRecipe(r1, allocateIngredient(101, "Dirt Seed"));
    insertIngredientToRecipe(r1, allocateIngredient(102, "Rock Seed"));
    insertLastRecipe(LR, r1);

    // Resep 2: Rock Seed (102) + Lava Seed (103) -> Obsidian Seed (106) / Obsidian Block (206)
    NodeRecipe* r2 = allocateRecipe(player.nextRecipeId++, 106, 206, "Obsidian Seed", "Obsidian Block", 5, 60);
    insertIngredientToRecipe(r2, allocateIngredient(102, "Rock Seed"));
    insertIngredientToRecipe(r2, allocateIngredient(103, "Lava Seed"));
    insertLastRecipe(LR, r2);

    // Resep 3: Dirt Seed (101) + Lava Seed (103) -> Wood Block Seed (107) / Wood Block (207)
    NodeRecipe* r3 = allocateRecipe(player.nextRecipeId++, 107, 207, "Wood Block Seed", "Wood Block", 4, 45);
    insertIngredientToRecipe(r3, allocateIngredient(101, "Dirt Seed"));
    insertIngredientToRecipe(r3, allocateIngredient(103, "Lava Seed"));
    insertLastRecipe(LR, r3);

    // Resep 4: Grass Seed (105) + Rock Seed (102) -> Brick Seed (108) / Brick Block (208)
    NodeRecipe* r4 = allocateRecipe(player.nextRecipeId++, 108, 208, "Brick Seed", "Brick Block", 5, 50);
    insertIngredientToRecipe(r4, allocateIngredient(105, "Grass Seed"));
    insertIngredientToRecipe(r4, allocateIngredient(102, "Rock Seed"));
    insertLastRecipe(LR, r4);

    // Resep 5: Dirt Seed (101) + Cave Background Seed (104) -> Door Seed (109) / Main Door (209)
    NodeRecipe* r5 = allocateRecipe(player.nextRecipeId++, 109, 209, "Door Seed", "Main Door", 3, 25);
    insertIngredientToRecipe(r5, allocateIngredient(101, "Dirt Seed"));
    insertIngredientToRecipe(r5, allocateIngredient(104, "Cave Background Seed"));
    insertLastRecipe(LR, r5);

    // Resep 6: Wood Block Seed (107) + Cave Background Seed (104) -> Sign Seed (110) / Wooden Sign (210)
    NodeRecipe* r6 = allocateRecipe(player.nextRecipeId++, 110, 210, "Sign Seed", "Wooden Sign", 6, 70);
    insertIngredientToRecipe(r6, allocateIngredient(107, "Wood Block Seed"));
    insertIngredientToRecipe(r6, allocateIngredient(104, "Cave Background Seed"));
    insertLastRecipe(LR, r6);
}

void spliceAndPlantMechanic(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, ListRecipe LR, int idSeed1, int idSeed2) {
    if (idSeed1 == idSeed2) {
        cout << "[GAGAL] Splicing membutuhkan dua jenis Seed yang BERBEDA!\n";
        return;
    }

    if (isFullFarm(FQ)) {
        cout << "[GAGAL] Lahan Farm Plot penuh (" << FQ.count << "/" << FQ.maxPlot << ")! Panen pohon terlebih dahulu.\n";
        return;
    }

    NodeBackpack* slot1 = findItemById(BP, idSeed1);
    NodeBackpack* slot2 = findItemById(BP, idSeed2);

    if (slot1 == nullptr || slot2 == nullptr) {
        cout << "[GAGAL] Salah satu atau kedua ID Seed tidak ditemukan di Backpack!\n";
        return;
    }

    if (slot1->info.kategori != "Seed" || slot2->info.kategori != "Seed") {
        cout << "[GAGAL] Hanya item bertipe 'Seed' yang dapat di-splice!\n";
        return;
    }

    NodeRecipe* resep = findRecipeByTwoSeeds(LR, idSeed1, idSeed2);
    if (resep == nullptr) {
        cout << "[GAGAL] Tidak ada kombinasi Splicing antara "
             << slot1->info.namaItem << " + " << slot2->info.namaItem << "!\n";
        return;
    }

    // Konsumsi masing-masing 1 seed dari Backpack (DLL)
    string nama1 = slot1->info.namaItem;
    string nama2 = slot2->info.namaItem;
    consumeItemFromBackpack(BP, idSeed1, 1);
    consumeItemFromBackpack(BP, idSeed2, 1);

    // Masukkan bibit pohon ke dalam antrean lahan tanam (FarmQueue)
    PlantedTree pohonBaru;
    pohonBaru.idTanam = player.nextTanamId++;
    pohonBaru.idHasilSeed = resep->idHasilSeed;
    pohonBaru.idHasilBlock = resep->idHasilBlock;
    pohonBaru.namaPohon = resep->namaHasilSeed + " Tree";
    pohonBaru.namaHasilSeed = resep->namaHasilSeed;
    pohonBaru.namaHasilBlock = resep->namaHasilBlock;
    pohonBaru.rarity = resep->rarityHasil;
    pohonBaru.sisaWaktuTumbuh = resep->growTime;

    NodeTree* nodePohon = allocateTree(pohonBaru);
    enqueueTree(FQ, nodePohon);

    cout << "\n[SPLICING BERHASIL!] " << nama1 << " + " << nama2
         << " -> " << pohonBaru.namaPohon << " ditanam di Plot #" << FQ.count
         << " (Waktu tumbuh: " << pohonBaru.sisaWaktuTumbuh << " detik).\n";
}

void advanceTimeAndHarvestMechanic(PlayerState &player, ListBackpack &BP, FarmQueue &FQ, int detikLewat) {
    if (detikLewat <= 0) {
        cout << "[INFO] Masukkan durasi waktu positif (minimal 1 detik).\n";
        return;
    }

    if (isEmptyFarm(FQ)) {
        cout << "[INFO] Tidak ada pohon di Farm Plot untuk ditumbuhkan.\n";
        return;
    }

    // Kurangi sisa waktu tumbuh semua pohon di antrean
    NodeTree* curr = FQ.head;
    while (curr != nullptr) {
        curr->info.sisaWaktuTumbuh -= detikLewat;
        if (curr->info.sisaWaktuTumbuh < 0) {
            curr->info.sisaWaktuTumbuh = 0;
        }
        curr = curr->next;
    }

    cout << "\n[SIMULASI WAKTU] Waktu berlalu selama " << detikLewat << " detik...\n";

    // Panen berurutan dari depan antrean (FIFO) untuk pohon yang sudah matang
    int totalDipanen = 0;
    while (!isEmptyFarm(FQ) && FQ.head->info.sisaWaktuTumbuh <= 0) {
        NodeTree* siapPanen = nullptr;
        dequeueTree(FQ, siapPanen);

        if (siapPanen != nullptr) {
            int jumlahBlock = 3 + (siapPanen->info.rarity % 3); // 3-5 block per pohon
            int jumlahSeed = 2;                                // 2 seed baru agar bisa di-splice lagi
            int bonusGems = siapPanen->info.rarity * 15;

            addOrStackItemToBackpack(BP, siapPanen->info.idHasilBlock, siapPanen->info.namaHasilBlock, "Block", siapPanen->info.rarity, jumlahBlock);
            addOrStackItemToBackpack(BP, siapPanen->info.idHasilSeed, siapPanen->info.namaHasilSeed, "Seed", siapPanen->info.rarity, jumlahSeed);
            player.gems += bonusGems;

            cout << " -> [HARVEST!] " << siapPanen->info.namaPohon
                 << " dipanen! Mendapat: " << jumlahBlock << "x " << siapPanen->info.namaHasilBlock
                 << ", " << jumlahSeed << "x " << siapPanen->info.namaHasilSeed
                 << ", +" << bonusGems << " Gems!\n";

            delete siapPanen;
            totalDipanen++;
        }
    }

    if (totalDipanen == 0) {
        cout << " -> Belum ada pohon di urutan terdepan (Plot #1) yang siap dipanen.\n";
    }
}

void recommendAvailableSplices(ListBackpack BP, ListRecipe LR) {
    cout << "\n==================== REKOMENDASI SPLICING SAAT INI ====================\n";
    NodeRecipe* P = LR.first;
    int ditemukan = 0;

    while (P != nullptr) {
        bool semuaAda = true;
        NodeIngredient* C = P->firstIngredient;
        while (C != nullptr) {
            NodeBackpack* cek = findItemById(BP, C->idSeedBahan);
            if (cek == nullptr || cek->info.jumlah < 1) {
                semuaAda = false;
                break;
            }
            C = C->next;
        }

        if (semuaAda) {
            ditemukan++;
            cout << ditemukan << ". [SIAP SPLICE] " << P->namaHasilSeed
                 << " (Rarity " << P->rarityHasil << ") -> Gunakan: ";
            NodeIngredient* C2 = P->firstIngredient;
            while (C2 != nullptr) {
                cout << C2->namaSeedBahan << " [ID:" << C2->idSeedBahan << "]";
                if (C2->next != nullptr) cout << " + ";
                C2 = C2->next;
            }
            cout << "\n";
        }
        P = P->next;
    }

    if (ditemukan == 0) {
        cout << "[Tidak ada kombinasi seed yang mencukupi di Backpack saat ini]\n";
    }
    cout << "=======================================================================\n";
}

void searchRecipesBySeed(ListRecipe LR, int idSeed) {
    cout << "\n==================== HASIL PENCARIAN SPLICING (ID SEED: " << idSeed << ") ====================\n";
    NodeRecipe* P = LR.first;
    int ditemukan = 0;

    while (P != nullptr) {
        bool terlibat = false;
        NodeIngredient* C = P->firstIngredient;
        while (C != nullptr) {
            if (C->idSeedBahan == idSeed) {
                terlibat = true;
                break;
            }
            C = C->next;
        }

        if (terlibat) {
            ditemukan++;
            cout << ditemukan << ". Resep #" << P->idRecipe << " -> Menghasilkan: "
                 << P->namaHasilSeed << " (" << P->namaHasilBlock << ") | Bahan: ";
            NodeIngredient* C2 = P->firstIngredient;
            while (C2 != nullptr) {
                cout << C2->namaSeedBahan << " [ID:" << C2->idSeedBahan << "]";
                if (C2->next != nullptr) cout << " + ";
                C2 = C2->next;
            }
            cout << "\n";
        }
        P = P->next;
    }

    if (ditemukan == 0) {
        cout << "[Seed dengan ID " << idSeed << " belum terdaftar pada resep splicing mana pun]\n";
    }
    cout << "===================================================================================\n";
}

void moveBackpackCursor(ListBackpack &BP, int arah) {
    if (isEmptyBackpack(BP) || BP.cursor == nullptr) {
        cout << "[INFO] Backpack kosong, tidak ada slot yang dapat dipilih.\n";
        return;
    }

    if (arah < 0) {
        if (BP.cursor->prev != nullptr) {
            BP.cursor = BP.cursor->prev;
            cout << "[CURSOR PREV] Slot aktif berpindah ke: " << BP.cursor->info.namaItem
                 << " (Qty: " << BP.cursor->info.jumlah << ")\n";
        } else {
            cout << "[INFO] Cursor sudah berada di slot paling awal (kiri).\n";
        }
    } else {
        if (BP.cursor->next != nullptr) {
            BP.cursor = BP.cursor->next;
            cout << "[CURSOR NEXT] Slot aktif berpindah ke: " << BP.cursor->info.namaItem
                 << " (Qty: " << BP.cursor->info.jumlah << ")\n";
        } else {
            cout << "[INFO] Cursor sudah berada di slot paling akhir (kanan).\n";
        }
    }
}

void trashCurrentCursorItem(ListBackpack &BP) {
    if (isEmptyBackpack(BP) || BP.cursor == nullptr) {
        cout << "[INFO] Tidak ada item di slot aktif untuk dibuang.\n";
        return;
    }

    string namaDihapus = BP.cursor->info.namaItem;
    deleteNodeBackpack(BP, BP.cursor);
    cout << "[TRASH] Seluruh stack '" << namaDihapus << "' berhasil dibuang dari Backpack.\n";
}

void addCustomRecipeMechanic(PlayerState &player, ListRecipe &LR) {
    int idSeed1, idSeed2, idHasilSeed, idHasilBlock, rarity, growTime;
    string namaSeed1, namaSeed2, namaHasilSeed, namaHasilBlock;

    cout << "\n--- Tambah Resep Splicing Growtopia Baru ---\n";
    cout << "ID Seed Bahan 1   : "; cin >> idSeed1;
    cin.ignore();
    cout << "Nama Seed Bahan 1 : "; getline(cin, namaSeed1);

    cout << "ID Seed Bahan 2   : "; cin >> idSeed2;
    cin.ignore();
    cout << "Nama Seed Bahan 2 : "; getline(cin, namaSeed2);

    if (idSeed1 == idSeed2) {
        cout << "[GAGAL] Kedua ID Seed bahan harus berbeda!\n";
        return;
    }

    if (findRecipeByTwoSeeds(LR, idSeed1, idSeed2) != nullptr) {
        cout << "[GAGAL] Kombinasi kedua seed tersebut sudah memiliki resep!\n";
        return;
    }

    cout << "ID Seed Hasil     : "; cin >> idHasilSeed;
    cin.ignore();
    cout << "Nama Seed Hasil   : "; getline(cin, namaHasilSeed);

    cout << "ID Block Hasil    : "; cin >> idHasilBlock;
    cin.ignore();
    cout << "Nama Block Hasil  : "; getline(cin, namaHasilBlock);

    cout << "Rarity Item       : "; cin >> rarity;
    cout << "Grow Time (detik) : "; cin >> growTime;

    NodeRecipe* rBaru = allocateRecipe(player.nextRecipeId++, idHasilSeed, idHasilBlock, namaHasilSeed, namaHasilBlock, rarity, growTime);
    insertIngredientToRecipe(rBaru, allocateIngredient(idSeed1, namaSeed1));
    insertIngredientToRecipe(rBaru, allocateIngredient(idSeed2, namaSeed2));
    insertLastRecipe(LR, rBaru);

    cout << "[BERHASIL] Resep splicing untuk " << namaHasilSeed << " berhasil ditambahkan!\n";
}

void freeAllMemory(ListBackpack &BP, FarmQueue &FQ, ListRecipe &LR) {
    while (!isEmptyBackpack(BP)) {
        deleteNodeBackpack(BP, BP.first);
    }

    while (!isEmptyFarm(FQ)) {
        NodeTree* temp = nullptr;
        dequeueTree(FQ, temp);
        delete temp;
    }

    while (LR.first != nullptr) {
        deleteRecipeById(LR, LR.first->idRecipe);
    }
}
