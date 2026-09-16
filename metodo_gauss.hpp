#ifndef METODO_GAUSS_HPP
#define METODO_GAUSS_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

enum class SolveStatus { UniqueSolution, NoSolution, InfiniteSolutions, Error};

SolveStatus solver(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x, double tol = 1e-9);
/*
    Sistema para resolver sistemas lineares Ax = b

    Argumento | Papel       | Entrada ou Saída
    
    A(Matriz)   Coeficientes   Entrada(mas modificada)
    B(Vetor)    Termos indep   Entrada(modificado)
    x           Solução        Saída
    tol         Tolerância     Opcional - detecção pivo
*/

#endif  // METODO_GAUSS_HPP
