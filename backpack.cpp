#include "backpack.h"

void createListBackpack(ListBackpack &L, int maxSlot) {
    L.first = nullptr;
    L.last = nullptr;
    L.cursor = nullptr;
    L.maxSlot = maxSlot;
    L.currentSlot = 0;
}

bool isEmptyBackpack(ListBackpack L) {
    return (L.first == nullptr && L.last == nullptr);
}

bool isFullBackpack(ListBackpack L) {
    return (L.currentSlot >= L.maxSlot);
}

NodeBackpack* allocateBackpack(ItemBackpack data) {
    NodeBackpack* P = new NodeBackpack;
    P->info = data;
    P->prev = nullptr;
    P->next = nullptr;
    return P;
}

void deallocateBackpack(NodeBackpack* P) {
    delete P;
}

void insertLastBackpack(ListBackpack &L, NodeBackpack* P) {
    if (isEmptyBackpack(L)) {
        L.first = P;
        L.last = P;
        L.cursor = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
    L.currentSlot++;
}

void deleteNodeBackpack(ListBackpack &L, NodeBackpack* P) {
    if (P == nullptr || isEmptyBackpack(L)) return;

    // Pindahkan cursor jika menunjuk node yang akan dihapus
    if (L.cursor == P) {
        if (P->next != nullptr) {
            L.cursor = P->next;
        } else {
            L.cursor = P->prev;
        }
    }

    if (P == L.first && P == L.last) {
        L.first = nullptr;
        L.last = nullptr;
        L.cursor = nullptr;
    } else if (P == L.first) {
        L.first = P->next;
        L.first->prev = nullptr;
    } else if (P == L.last) {
        L.last = P->prev;
        L.last->next = nullptr;
    } else {
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }

    deallocateBackpack(P);
    L.currentSlot--;
}

NodeBackpack* findItemById(ListBackpack L, int idItem) {
    NodeBackpack* P = L.first;
    while (P != nullptr) {
        if (P->info.idItem == idItem) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

NodeBackpack* findItemByName(ListBackpack L, string namaItem) {
    NodeBackpack* P = L.first;
    while (P != nullptr) {
        if (P->info.namaItem == namaItem) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void printBackpack(ListBackpack L) {
    cout << "\n==================== GROWTOPIA BACKPACK ("
         << L.currentSlot << "/" << L.maxSlot << " Slot) ====================\n";
    if (isEmptyBackpack(L)) {
        cout << "[Backpack kosong]\n";
        return;
    }

    NodeBackpack* P = L.first;
    int idx = 1;
    while (P != nullptr) {
        string marker = (P == L.cursor) ? " <-- [ACTIVE SLOT]" : "";
        cout << idx << ". [ID: " << P->info.idItem << "] "
             << P->info.namaItem << " (" << P->info.kategori << ")"
             << " | Rarity: " << P->info.rarity
             << " | Qty: " << P->info.jumlah << "/200"
             << marker << "\n";
        P = P->next;
        idx++;
    }
    cout << "=======================================================================\n";
}
