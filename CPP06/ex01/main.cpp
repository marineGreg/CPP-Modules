#include <iostream>
#include "Serializer.hpp"

int main() {
    // 1. On crée notre objet Data avec des informations
    Data originalData;
    originalData.id = 42;
    originalData.name = "Theodore Vicente";

    // On récupère son adresse mémoire (le pointeur)
    Data* originalPtr = &originalData;

    std::cout << "==========================================" << std::endl;
    std::cout << "--- 1. ÉTAT ORIGINAL ---" << std::endl;
    std::cout << "Adresse mémoire : " << originalPtr << std::endl;
    std::cout << "ID              : " << originalPtr->id << std::endl;
    std::cout << "Nom             : " << originalPtr->name << std::endl;
    std::cout << "==========================================" << std::endl << std::endl;

    // 2. SÉRIALISATION (Pointeur -> Entier)
    std::cout << "[... Sérialisation en cours ...]" << std::endl;
    uintptr_t raw = Serializer::serialize(originalPtr);
    
    // On affiche l'entier brut (tu verras, c'est un très grand nombre !)
    std::cout << "Valeur brute (uintptr_t) : " << raw << std::endl << std::endl;

    // 3. DÉSÉRIALISATION (Entier -> Pointeur)
    std::cout << "[... Désérialisation en cours ...]" << std::endl;
    Data* deserializedPtr = Serializer::deserialize(raw);

    std::cout << "==========================================" << std::endl;
    std::cout << "--- 2. ÉTAT APRÈS DÉSÉRIALISATION ---" << std::endl;
    std::cout << "Adresse mémoire : " << deserializedPtr << std::endl;
    std::cout << "ID              : " << deserializedPtr->id << std::endl;
    std::cout << "Nom             : " << deserializedPtr->name << std::endl;
    std::cout << "==========================================" << std::endl << std::endl;

    std::cout << "--- 3. VERDICT ---" << std::endl;
    if (originalPtr == deserializedPtr) {
        std::cout << "SUCCÈS : Les deux adresses mémoires sont STRICTEMENT identiques !" << std::endl;
        std::cout << "   Original : " << originalPtr << " == Récupéré : " << deserializedPtr << std::endl;
    } else {
        std::cout << "ÉCHEC : Les adresses ne correspondent pas !" << std::endl;
    }

    return 0;
}