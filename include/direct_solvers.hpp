#ifndef DIRECT_SOLVERS_HPP
#define DIRECT_SOLVERS_HPP

#include "types.hpp"
#include <vector>

// Estrutura que guarda os fatores L, U e as permutações de linha
struct LUDecomposition {
    Matrix LU;             // Matriz contendo L e U sobrepostos
    std::vector<int> perm; // Índices das linhas permutadas
    int swaps = 0;         // Número de trocas efetuadas
    SolveStatus status = SolveStatus::Singular;
};

// Eliminação de Gauss com pivoteamento parcial
SolveStatus gauss_solve(Matrix A, Vector b, Vector& x, double tol = 1e-9);

// Fase 1 da Fatoração LU: decompõe A em P*A = L*U
LUDecomposition lu_decompose(Matrix A, double tol = 1e-9);

// Fase 2 da Fatoração LU: resolve L*y = P*b e U*x = y
bool lu_solve(const LUDecomposition& decomp, const Vector& b, Vector& x);

#endif // DIRECT_SOLVERS_HPP