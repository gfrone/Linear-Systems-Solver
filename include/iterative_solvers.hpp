#ifndef ITERATIVE_SOLVERS_HPP
#define ITERATIVE_SOLVERS_HPP

#include "types.hpp"
#include <vector>
#include <string>
#include <cmath>

// Dados de cada iteração
struct IterationData {
    int it;
    std::vector<double> x_k;
    double error; // x^(k) - x^(k-1) with k -> inf
};

struct LinearSolveResult {
    std::string method_name;
    SolveStatus status;
    std::vector<double> x_k;
    int iteration_used = 0;
    std::vector<IterationData> history;
    double final_error = 0.0;

    bool is_success() const {
        return status == SolveStatus::Success;
    }

    std::string get_status_message() const {
        switch (status) {
            case SolveStatus::Success: return "Solucao convergida com sucesso";
            case SolveStatus::MaxIterationsReached: return "Aviso: Numero maximo de iteracoes atingido";
            case SolveStatus::Error: return "Ocorreu um erro durante o processo";
            case SolveStatus::InfiniteSolutions: return "Infinitas soluções";
            case SolveStatus::NoSolution: return "Sem solução no domínio dos reais";
            case SolveStatus::Singular: return "Matriz singular";
            default: return "Erro Fatal: Ocorrencia nao mapeada";
        }
    }
};

/*
    Método de Gauss-Jacobi:
    - x: recebe a aproximação inicial (x0) e retorna a solução final calculada.
    - tol: tolerância do critério de parada (ex: erro relativo entre iterações).
    - max_iter: número máximo de iterações permitidas.
*/

LinearSolveResult jacobi_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol = 1e-6, int max_iter = 1000);

/*
    Método de Gauss-Seidel:
    - Similar ao Jacobi, porém usando os valores já atualizados dentro da mesma iteração.
    - x: chute inicial na entrada e vetor solução na saída.
*/
LinearSolveResult seidel_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol = 1e-6, int max_iter = 1000);

#endif // ITERATIVE_SOLVERS_HPP