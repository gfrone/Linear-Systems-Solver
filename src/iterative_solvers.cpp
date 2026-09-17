#include "iterative_solvers.hpp"
#include <cmath>

LinearSolveResult jacobi_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol, int max_iter) {
    LinearSolveResult result;

    // TODO:
    // 1. Validar se A é quadrada e se as dimensões de A, b e x são compatíveis.
    // 2. Verificar se há elementos nulos na diagonal principal (A[i][i] == 0).
    // 3. (Opcional) Testar o critério das linhas para garantir convergência.
    // 4. Loop de iteração (até max_iter):
    //      - Calcular o próximo vetor x_novo usando o vetor x da iteração anterior:
    //        x_novo[i] = (b[i] - soma_{j != i}(A[i][j] * x[j])) / A[i][i]
    //      - Calcular a norma do erro relativo: ||x_novo - x|| / ||x_novo||
    //      - Atualizar x = x_novo.
    //      - Se erro < tol: status = Success, preencher result e retornar.
    // 5. Se atingir max_iter sem convergir: status = MaxIterationsReached.

    return result;
}

LinearSolveResult seidel_solve(const Matrix& A, const Vector& b, Vector& x,
                             double tol, int max_iter) {
    LinearSolveResult result;

    // TODO:
    // 1. Validar dimensões e zeros na diagonal principal.
    // 2. (Opcional) Testar o critério de Sassenfeld.
    // 3. Loop de iteração (até max_iter):
    //      - Atualizar cada componente de x usando os valores já calculados na iteração atual:
    //        x[i] = (b[i] - soma_{j < i}(A[i][j] * x[j]) - soma_{j > i}(A[i][j] * x_anterior[j])) / A[i][i]
    //      - Calcular a variação/erro em relação ao passo anterior.
    //      - Se erro < tol: status = Success, preencher result e retornar.
    // 4. Se atingir max_iter: status = MaxIterationsReached.

    return result;
}