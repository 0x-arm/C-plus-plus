#include "Memory.hpp" // Inclusion de l'en-tête de la classe Memory
#include <stdexcept>

constexpr int MAX_STACK = 16; // Taille de la pile

//// Surcharge de l'opérateur [] pour accéder à la mémoire
uint16_t& Memory::operator[](uint16_t address) {

    // Vérifier si l'adresse dépasse les limites de la mémoire
    if (address >= SIZE) {

        // Quitter le programme
        std::exit(1);
    }

    // Conversion de l'adresse donnée en un pointeur vers uint16_t pour accéder aux deux octets à cette position.
    uint16_t* ptr = (uint16_t*)&MEM[address];

    // Retourne le pointeur déréférencé
    return *ptr;
}

//// Méthode pop : retire un élément de la pile
uint16_t Memory::pop() {

    // Vérifier si la pile est vide
    if (SP < 2) {

        // Quitter le programme
        std::exit(1); 
    }

    // Décrémenter le pointeur de pile de 2 octets après l'écriture
    SP -= 2;

    // Lire la valeur à cette adresse à l'aide de l'opérateur []
    uint16_t value = operator[](SP);

    // Retourner la valeur retirée de la pile
    return value;
}


//// Méthode push : empile une valeur sur la pile
void Memory::push(uint16_t value) {

    /// Vérifier si la pile déborde (au-delà de l’adresse 15)
    if (SP + 1 >= MAX_STACK) {

        // Quitter le programme
        std::exit(1);
    }

    // Écrire la valeur à l'adresse actuelle du pointeur de pile
    operator[](SP) = value;

    // Avancer le pointeur de pile de 2 octets (car on lit un uint16_t)
    SP += 2;
}
