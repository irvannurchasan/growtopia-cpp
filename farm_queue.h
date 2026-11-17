#ifndef FARM_QUEUE_H
#define FARM_QUEUE_H

#include <iostream>
#include <string>
using namespace std;

struct PlantedTree {
    int idTanam;
    int idHasilSeed;
    int idHasilBlock;
    string namaPohon;
    string namaHasilSeed;
    string namaHasilBlock;
    int rarity;
    int sisaWaktuTumbuh; // dalam detik
};

struct NodeTree {
    PlantedTree info;
    NodeTree* next;
};

struct FarmQueue {
    NodeTree* head;
    NodeTree* tail;
    int count;
    int maxPlot;
};

// Operasi Primitif Queue
void createFarmQueue(FarmQueue &Q, int maxPlot);
bool isEmptyFarm(FarmQueue Q);
bool isFullFarm(FarmQueue Q);
NodeTree* allocateTree(PlantedTree data);
void enqueueTree(FarmQueue &Q, NodeTree* P);
void dequeueTree(FarmQueue &Q, NodeTree* &P);
void printFarmQueue(FarmQueue Q);

#endif
