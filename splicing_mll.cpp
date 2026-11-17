#include "splicing_mll.h"

void createListRecipe(ListRecipe &LR) {
    LR.first = nullptr;
}

NodeRecipe* allocateRecipe(int idRec, int idSeed, int idBlock, string namaSeed, string namaBlock, int rarity, int growTime) {
    NodeRecipe* P = new NodeRecipe;
    P->idRecipe = idRec;
    P->idHasilSeed = idSeed;
    P->idHasilBlock = idBlock;
    P->namaHasilSeed = namaSeed;
    P->namaHasilBlock = namaBlock;
    P->rarityHasil = rarity;
    P->growTime = growTime;
    P->firstIngredient = nullptr;
    P->next = nullptr;
    return P;
}

NodeIngredient* allocateIngredient(int idSeedBahan, string namaSeedBahan) {
    NodeIngredient* C = new NodeIngredient;
    C->idSeedBahan = idSeedBahan;
    C->namaSeedBahan = namaSeedBahan;
    C->next = nullptr;
    return C;
}

void insertLastRecipe(ListRecipe &LR, NodeRecipe* P) {
    if (LR.first == nullptr) {
        LR.first = P;
    } else {
        NodeRecipe* Q = LR.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertIngredientToRecipe(NodeRecipe* P, NodeIngredient* C) {
    if (P == nullptr || C == nullptr) return;
    if (P->firstIngredient == nullptr) {
        P->firstIngredient = C;
    } else {
        NodeIngredient* Q = P->firstIngredient;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
    }
}

NodeRecipe* findRecipeById(ListRecipe LR, int idRecipe) {
    NodeRecipe* P = LR.first;
    while (P != nullptr) {
        if (P->idRecipe == idRecipe) return P;
        P = P->next;
    }
    return nullptr;
}

NodeRecipe* findRecipeByTwoSeeds(ListRecipe LR, int idSeed1, int idSeed2) {
    if (idSeed1 == idSeed2) return nullptr;

    NodeRecipe* P = LR.first;
    while (P != nullptr) {
        bool match1 = false;
        bool match2 = false;
        int countBahan = 0;

        NodeIngredient* C = P->firstIngredient;
        while (C != nullptr) {
            if (C->idSeedBahan == idSeed1) match1 = true;
            if (C->idSeedBahan == idSeed2) match2 = true;
            countBahan++;
            C = C->next;
        }

        if (countBahan == 2 && match1 && match2) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

bool deleteRecipeById(ListRecipe &LR, int idRecipe) {
    if (LR.first == nullptr) return false;

    NodeRecipe* P = LR.first;
    NodeRecipe* prevP = nullptr;

    while (P != nullptr && P->idRecipe != idRecipe) {
        prevP = P;
        P = P->next;
    }

    if (P == nullptr) return false;

    // Dealokasi seluruh Child (Ingredient) milik Parent P terlebih dahulu
    NodeIngredient* C = P->firstIngredient;
    while (C != nullptr) {
        NodeIngredient* tempC = C;
        C = C->next;
        delete tempC;
    }

    if (prevP == nullptr) {
        LR.first = P->next;
    } else {
        prevP->next = P->next;
    }
    delete P;
    return true;
}

void printAllRecipes(ListRecipe LR) {
    cout << "\n==================== GROWTOPIA SPLICING RECIPE BOOK ====================\n";
    if (LR.first == nullptr) {
        cout << "[Belum ada resep splicing terdaftar]\n";
        return;
    }

    NodeRecipe* P = LR.first;
    while (P != nullptr) {
        cout << "[Resep #" << P->idRecipe << "] " << P->namaHasilSeed
             << " (Menghasilkan: " << P->namaHasilBlock << ")"
             << " | Rarity: " << P->rarityHasil
             << " | Grow Time: " << P->growTime << "s\n";
        cout << "   Kombinasi Bahan: ";

        NodeIngredient* C = P->firstIngredient;
        while (C != nullptr) {
            cout << C->namaSeedBahan << " [ID:" << C->idSeedBahan << "]";
            if (C->next != nullptr) cout << "  +  ";
            C = C->next;
        }
        cout << "\n------------------------------------------------------------------------\n";
        P = P->next;
    }
}
