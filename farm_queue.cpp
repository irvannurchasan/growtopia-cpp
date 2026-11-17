#include "farm_queue.h"

void createFarmQueue(FarmQueue &Q, int maxPlot) {
    Q.head = nullptr;
    Q.tail = nullptr;
    Q.count = 0;
    Q.maxPlot = maxPlot;
}

bool isEmptyFarm(FarmQueue Q) {
    return (Q.head == nullptr && Q.tail == nullptr);
}

bool isFullFarm(FarmQueue Q) {
    return (Q.count >= Q.maxPlot);
}

NodeTree* allocateTree(PlantedTree data) {
    NodeTree* P = new NodeTree;
    P->info = data;
    P->next = nullptr;
    return P;
}

void enqueueTree(FarmQueue &Q, NodeTree* P) {
    if (isFullFarm(Q)) return;

    if (isEmptyFarm(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
    Q.count++;
}

void dequeueTree(FarmQueue &Q, NodeTree* &P) {
    if (isEmptyFarm(Q)) {
        P = nullptr;
        return;
    }

    P = Q.head;
    if (Q.head == Q.tail) {
        Q.head = nullptr;
        Q.tail = nullptr;
    } else {
        Q.head = Q.head->next;
    }
    P->next = nullptr;
    Q.count--;
}

void printFarmQueue(FarmQueue Q) {
    cout << "\n==================== FARM PLOT QUEUE ("
         << Q.count << "/" << Q.maxPlot << " Plot) ====================\n";
    if (isEmptyFarm(Q)) {
        cout << "[Belum ada pohon yang ditanam di World ini]\n";
        return;
    }

    NodeTree* P = Q.head;
    int urutan = 1;
    while (P != nullptr) {
        string status = (P->info.sisaWaktuTumbuh <= 0)
                        ? "SIAP PANEN (READY!)"
                        : (to_string(P->info.sisaWaktuTumbuh) + " detik lagi");
        cout << "Plot #" << urutan << " [ID Tanam: " << P->info.idTanam << "] "
             << P->info.namaPohon
             << " | Rarity: " << P->info.rarity
             << " | Status: " << status << "\n";
        P = P->next;
        urutan++;
    }
    cout << "=====================================================================\n";
}
