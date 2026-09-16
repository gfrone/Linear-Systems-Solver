#include "direct_solvers.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// ==========================================
// Método: Eliminação de Gauss
// ==========================================
SolveStatus gauss_solve(Matrix A, Vector b, Vector& x, double tol) {
    // Verificações
    if(tol <= 0.0 || b.size() != x.size() || A.size() == 0) return SolveStatus::Error;
    // Caso não for quadrada
    if(A.size() != A[0].size()) return SolveStatus::Error; 

    int n = A.size();

    // Fase 1: eliminação (foward elimination)
    for(int k = 0; k < n; k++) {
        int p = k;

        for(int i = k + 1; i < n; i++) {
            if (fabs(A[i][k]) > fabs(A[p][k])) p = i;
        }

        if(fabs(A[p][k]) < tol) continue; // Coluna zerada
        
        // Troca de linhas - sobe linha com maior valor(p) 
        swap(A[k], A[p]);
        swap(b[k], b[p]);

        const double* linhaK = A[k].data();
        for(int i = k+1; i < n; i++) {
            double factor = A[i][k] / linhaK[k];
            double* linhaI = A[i].data();
            for(int j = k; j < n; j++) {
                linhaI[j] -= factor * linhaK[j];
            }
        }
    }

    // Etapa 2: Verificação
    for (int i = 0; i < n; ++i) {
        bool linhaNula = true;
        for (int j = 0; j < n; ++j)
            if (fabs(A[i][j]) > tol) { linhaNula = false; break; }

        if (linhaNula) {
            return (fabs(b[i]) > tol)
                ? SolveStatus::NoSolution
                : SolveStatus::InfiniteSolutions;
        }
    }

    // Etapa 3: solução Ax = b
    double final = b[n-1] / A[n - 1][n - 1];
    x[n-1] = final;
    
    for(int i = n - 2; i >= 0; i--) {
        double valor = b[i];
        for(int j = i + 1; j < n; j++) {
            valor -= A[i][j] * x[j];
        }
        x[i] = valor / A[i][i];
    }

    return SolveStatus::Success;
}

// ==========================================
// Método: Fatoração LU
// ==========================================
LUDecomposition lu_decompose(Matrix A, double tol) {
    LUDecomposition decomp;
    if(A.empty() || A.size() != A[0].size()){
        decomp.status = SolveStatus::Error;
        return decomp;
    }
    // por enquanto tratamos somente matrizes quadradas

    int n = A.size();
    decomp.perm.resize(n); // reinicializamos o vetor para o tamanho necessário
    for(int i = 0; i < n; i++) decomp.perm[i] = i;

    decomp.LU = A; // Matriz LU recebe iniciamente a matriz A
    
    for(int k = 0; k < n; k++) {
        int p = k;
        
        for(int i = k + 1; i < n; i++) {
            if(abs(decomp.LU[i][k]) > abs(decomp.LU[p][k])) p = i;
        }

        /* Logica para encontrar o maior p para o pivo entre as linhas. Caso ocorrer mudança
            Colocar no resultado de permutação. PA = LU */
        if(p != k) {
            swap(decomp.LU[k], decomp.LU[p]);
            swap(decomp.perm[k], decomp.perm[p]);
            decomp.swaps++;
        }

        // Checa singularidade DEPOIS do pivotamento - significa que elemento na diagonal é zero
        if(abs(decomp.LU[k][k]) < tol) {
            decomp.status = SolveStatus::Singular;
            return decomp;
        }

        // Guarda o fator e realiza a mesma etapa da eliminação de gauss no resante da linha
        for(int i = k + 1; i< n; i++) {
            double fator = decomp.LU[i][k] / decomp.LU[k][k];
            decomp.LU[i][k] = fator;
            for(int j = k + 1; j < n; j++) {
                decomp.LU[i][j] -= decomp.LU[k][j] * fator;
            }
        }
    }

    decomp.status = SolveStatus::Success;
    return decomp;
}

bool lu_solve(const LUDecomposition& decomp, const Vector& b, Vector& x) {
    if(b.empty() || x.empty()) return false;
    // Se retornar singular, então significa que não há solução única.
    if(decomp.status != SolveStatus::Success) return false;
    int n = decomp.LU.size();

    /* Como realizamos, possivelmente, a permutação, temos: PA = LU
        Dessa forma, o sistema é equivalente a LUx = Pb, então vou reconstruir a matriz
        original, pois guardamos os índices permutação na struct
    */
    Vector b_perm(n);
    for(int i = 0; i < n; i++) {
        // troca de indices para o novo vetor de b, agora na ordem correta.
        b_perm[i] = b[decomp.perm[i]];
    }

    // Resolução de: Ly = b_perm por substituição direta
    Vector y(n);
    for(int i = 0; i < n; i++) {
        double soma = 0.0;
        for(int j = 0; j < i; j++) {
            soma += decomp.LU[i][j] * y[j];
        }
        y[i] = b_perm[i] - soma;
    }

    // Passo 5: substituição reversa -> resolve Ux = y
    x.resize(n);
    for(int i = n - 1; i >= 0; i--) {
        double soma = 0.0;
        for(int j = i + 1; j < n; j++) {
            soma += decomp.LU[i][j] * x[j];
        }
        x[i] = (y[i] - soma) / decomp.LU[i][i];
    }

    return true;
}