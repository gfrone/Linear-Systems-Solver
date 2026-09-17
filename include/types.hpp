#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

// Aliases para facilitar a leitura das matrizes e vetores
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Enum unificado para métodos diretos e iterativos
enum class SolveStatus {
    Success,              // Solução única encontrada / fatoração bem-sucedida
    Singular,             // Matriz singular (pivô nulo ou det ≈ 0)
    NoSolution,           // Sistema impossível
    InfiniteSolutions,    // Sistema possível indeterminado
    MaxIterationsReached, // Critério de iterações atingido sem convergência
    Error                 // Dimensões inválidas ou parâmetros inconsistentes
};



#endif // TYPES_HPP