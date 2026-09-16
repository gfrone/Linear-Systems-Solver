#include "lu_solver.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

LUDecomposition lu_decompose(std::vector<std::vector<double>> A, double tol = 1e-9) {
    LUDecomposition decomp;
    if(A.empty() || A.size() != A[0].size()){
        decomp.status = LUStatus::Error;
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
            if(std::abs(decomp.LU[i][k]) > std::abs(decomp.LU[p][k])) p = i;
        }

        /* Logica para encontrar o maior p para o pivo entre as linhas. Caso ocorrer mudança
            Colocar no resultado de permutação. PA = LU */
        if(p != k) {
            std::swap(decomp.LU[k], decomp.LU[p]);
            std::swap(decomp.perm[k], decomp.perm[p]);
            decomp.swaps++;
        }

        // Checa singularidade DEPOIS do pivotamento - significa que elemento na diagonal é zero
        if(std::abs(decomp.LU[k][k]) < tol) {
            decomp.status = LUStatus::Singular;
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

}

bool lu_solve(const LUDecomposition& decomp,const std::vector<double>& b, std::vector<double>& x) {
    if(b.empty() || x.empty()) return false;
    // Se retornar singular, então significa que não há solução única.
    if(decomp.status == LUStatus::Singular) return false;
    int n = decomp.LU.size();

    /* Como realizamos, possivelmente, a permutação, temos: PA = LU
        Dessa forma, o sistema é equivalente a LUx = Pb, então vou reconstruir a matriz
        original, pois guardamos os índices permutação na struct
    */
    std::vector<double> b_perm(n);
    for(int i = 0; i < n; i++) {
        // troca de indices para o novo vetor de b, agora na ordem correta.
        b_perm[i] = b[decomp.perm[i]];
    }

    // Resolução de: Ly = b_perm por substituição direta
    std::vector<double> y(n);
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
