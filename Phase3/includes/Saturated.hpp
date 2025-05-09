#pragma once

#include <cstdint>
#include <cmath>

// Valeur maximale du registre
constexpr int MAX_UPPER_LIMIT = 65535;

//// Retourne la valeur saturée d'un entier
constexpr uint16_t saturated(int n) {

	// Saturation de la valeur
    uint16_t value = std::min(std::max(n, 0), MAX_UPPER_LIMIT); 
	
	// Retourner la valeur saturée
	return value;

};