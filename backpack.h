#ifndef BACKPACK_H
#define BACKPACK_H

#include <iostream>
#include <string>
using namespace std;

struct ItemBackpack {
    int idItem;
    string namaItem;
    string kategori; // "Seed" atau "Block"
    int rarity;
    int jumlah;
};

struct NodeBackpack {
    ItemBackpack info;
    NodeBackpack* prev;
    NodeBackpack* next;
};

struct ListBackpack {
    NodeBackpack* first;
    NodeBackpack* last;
    NodeBackpack* cursor;
    int maxSlot;
    int currentSlot;
};

// Operasi Primitif Doubly Linked List
void createListBackpack(ListBackpack &L, int maxSlot);
bool isEmptyBackpack(ListBackpack L);
bool isFullBackpack(ListBackpack L);
NodeBackpack* allocateBackpack(ItemBackpack data);
void deallocateBackpack(NodeBackpack* P);
void insertLastBackpack(ListBackpack &L, NodeBackpack* P);
void deleteNodeBackpack(ListBackpack &L, NodeBackpack* P);
NodeBackpack* findItemById(ListBackpack L, int idItem);
NodeBackpack* findItemByName(ListBackpack L, string namaItem);
void printBackpack(ListBackpack L);

#endif
