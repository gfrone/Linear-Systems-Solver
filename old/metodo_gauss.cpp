#include "metodo_gauss.hpp"

using namespace std;

SolveStatus solver(std::vector<std::vector<double>>& A,
    std::vector<double>& b, std::vector<double>& x, double tol = 1e-9) {
    
    // Verificações
    if(tol >= 0.0 || b.size() != (x).size() || A.size() == 0) return SolveStatus::Error;
    // Caso não for quadrada
    if(sizeof(A) != sizeof(A[0])) return SolveStatus::Error; 

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
            if (std::fabs(A[i][j]) > tol) { linhaNula = false; break; }

        if (linhaNula) {
            return (std::fabs(b[i]) > tol)
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
    }

    return SolveStatus::UniqueSolution;
}

