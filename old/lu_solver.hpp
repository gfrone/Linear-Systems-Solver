#ifndef LU_SOLVER_HPP
#define LU_SOLVER_HPP

#include <vector>

enum class LUStatus {
    Success,     // fatoração bem-sucedida
    Singular,    // matriz singular (det ≈ 0)
    Error        // Caso ocorrer um erro de verificação
};

// Estrutura que guarda os fatores e a permutação
struct LUDecomposition {
    std::vector<std::vector<double>> LU;  // L e U sobrepostos numa matriz só
    std::vector<int> perm;                // ordem das linhas (pivoteamento)
    int swaps = 0;                        // nº de trocas (útil para o sinal do determinante)
    LUStatus status = LUStatus::Singular;
};

// Fase 1 : decompõe A em L e U
LUDecomposition lu_decompose(std::vector<std::vector<double>> A,
                             double tol = 1e-9);

// Fase 2 (barata, chame quantas vezes quiser): resolve Ax = b
// usando os fatores guardados em decomp
bool lu_solve(const LUDecomposition& decomp,
              const std::vector<double>& b,
              std::vector<double>& x);

#endif // LU_SOLVER_HPP