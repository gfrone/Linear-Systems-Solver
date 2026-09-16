#ifndef ITERATIVE_SOLVERS_HPP
#define ITERATIVE_SOLVERS_HPP

#include "types.hpp"

// Armazena métricas da convergência do método iterativo
struct IterativeResult {
    SolveStatus status = SolveStatus::Error;
    int iterations = 0;       // Quantidade de iterações executadas
    double final_error = 0.0; // Valor final da métrica de erro/parada
};

/*
    Método de Gauss-Jacobi:
    - x: recebe a aproximação inicial (x0) e retorna a solução final calculada.
    - tol: tolerância do critério de parada (ex: erro relativo entre iterações).
    - max_iter: número máximo de iterações permitidas.
*/
IterativeResult jacobi_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol = 1e-6, int max_iter = 1000);

/*
    Método de Gauss-Seidel:
    - Similar ao Jacobi, porém usando os valores já atualizados dentro da mesma iteração.
    - x: chute inicial na entrada e vetor solução na saída.
*/
IterativeResult seidel_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol = 1e-6, int max_iter = 1000);

#endif // ITERATIVE_SOLVERS_HPP