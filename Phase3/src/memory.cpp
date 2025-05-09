#include "Memory.hpp" // Inclusion de l'en-tête de la classe Memory

//// Surcharge de l'opérateur [] pour accéder à la mémoire
uint16_t& Memory::operator[](uint16_t address) {
    
    // Retourne une référence vers une valeur 16 bits à l'adresse donnée
    // Interprète deux octets consécutifs comme une seule valeur uint16_t (little endian)
    return *reinterpret_cast<uint16_t*>(&MEM[address]);
}


//// Méthode pop : retire un élément de la pile
uint16_t Memory::pop() {

    // Avancer le pointeur de pile de 2 octets (car on lit un uint16_t)
    _SP += 2;

    // Lire la valeur à cette adresse à l'aide de l'opérateur []
    uint16_t value = operator[](_SP);

    // Retourner la valeur retirée de la pile
    return value;
}


//// Méthode push : empile une valeur sur la pile
void Memory::push(uint16_t value) {

    // Écrire la valeur à l'adresse actuelle du pointeur de pile
    operator[](_SP) = value;

    // Décrémenter le pointeur de pile de 2 octets après l'écriture
    _SP -= 2;
}
