#include <iostream>
#include "Serializer.hpp"

int main() {
    // 1. On cree notre objet Data avec des informations
    Data originalData;
    originalData.id = 42;
    originalData.name = "Theodore Vicente";

    // On recupere son adresse memoire (le pointeur)
    Data* originalPtr = &originalData;

    std::cout << "===== 1. ETAT ORIGINAL =====" << std::endl;
    std::cout << "Adresse memoire : " << originalPtr << std::endl;
    std::cout << "ID              : " << originalPtr->id << std::endl;
    std::cout << "Nom             : " << originalPtr->name << std::endl;

    // 2. SERIALISATION (Pointeur -> Entier)
    std::cout << "\n[..... Serialisation en cours .....]" << std::endl;
    uintptr_t raw = Serializer::serialize(originalPtr);
    
    // On affiche l'entier brut
    std::cout << "Valeur brute (uintptr_t) : " << raw << std::endl;

    // 3. DESERIALISATION (Entier -> Pointeur)
    std::cout << "\n[..... Deserialisation en cours .....]" << std::endl;
    Data* deserializedPtr = Serializer::deserialize(raw);

    std::cout << "\n===== 2. ETAT APRES DESERIALISATION =====" << std::endl;
    std::cout << "Adresse memoire : " << deserializedPtr << std::endl;
    std::cout << "ID              : " << deserializedPtr->id << std::endl;
    std::cout << "Nom             : " << deserializedPtr->name << std::endl;

    std::cout << "\n===== 3. VERDICT =====" << std::endl;
    if (originalPtr == deserializedPtr) {
        std::cout << "SUCCES : Les deux adresses memoires sont STRICTEMENT identiques !"
		<< std::endl;
        std::cout << "Original : " << originalPtr << " == Recupere : " << deserializedPtr
		<< std::endl;
    } else {
        std::cout << "ECHEC : Les adresses ne correspondent pas !" << std::endl;
    }

    return 0;
}