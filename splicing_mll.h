#ifndef SPLICING_MLL_H
#define SPLICING_MLL_H

#include <iostream>
#include <string>
using namespace std;

// Child Node: Komponen Seed Bahan Splicing
struct NodeIngredient {
    int idSeedBahan;
    string namaSeedBahan;
    NodeIngredient* next;
};

// Parent Node: Resep Hasil Splicing
struct NodeRecipe {
    int idRecipe;
    int idHasilSeed;
    int idHasilBlock;
    string namaHasilSeed;
    string namaHasilBlock;
    int rarityHasil;
    int growTime;
    NodeIngredient* firstIngredient;
    NodeRecipe* next;
};

struct ListRecipe {
    NodeRecipe* first;
};

// Operasi Primitif Multi-Linked List
void createListRecipe(ListRecipe &LR);
NodeRecipe* allocateRecipe(int idRec, int idSeed, int idBlock, string namaSeed, string namaBlock, int rarity, int growTime);
NodeIngredient* allocateIngredient(int idSeedBahan, string namaSeedBahan);
void insertLastRecipe(ListRecipe &LR, NodeRecipe* P);
void insertIngredientToRecipe(NodeRecipe* P, NodeIngredient* C);
NodeRecipe* findRecipeById(ListRecipe LR, int idRecipe);
NodeRecipe* findRecipeByTwoSeeds(ListRecipe LR, int idSeed1, int idSeed2);
bool deleteRecipeById(ListRecipe &LR, int idRecipe);
void printAllRecipes(ListRecipe LR);

#endif
