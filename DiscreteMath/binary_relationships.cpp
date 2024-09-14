#include <iostream>
using namespace std;

bool isReflective(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
        if(matrix[i][i] != 1)
            return false;
    return true;
}

bool isAntiReflective(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
        if(matrix[i][i] != 0)
            return false;
    return true;
}

bool isSymmetric(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
        {
            if(matrix[i][j] != matrix[j][i] && j != i)
                return false;
        }
    return true;
}

bool isAntiSymmetric(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(matrix[i][j] == matrix[j][i] && matrix[i][j] == 0 && j != i)
                return true;
        }
    }
    return false;
}

bool isASymmetric(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
        if(matrix[i][i] != 0)
            return false;
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(matrix[i][j] == matrix[j][i] && matrix[i][j] == 0 && j != i)
                return true;
        }
    }
    return false;
}

bool isTransitive(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(i == j || !matrix[i][j])
                continue;
            for(int k = 0; k < 5; ++k)
            {
                if(k == i || k == j || matrix[j][k] == 0)
                    continue;
                else if(matrix[i][k] == 0)
                    return false;
            }
        }
    }
    return true;
}

bool isConnectivity(int (&matrix)[5][5])
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
            if(j != i && matrix[i][j] == matrix[j][i])
                return false;
    }
    return true;
}

int main()
{
    int matrix[5][5];
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            cin >> matrix[i][j];
    int count = 0;
    cout << "\n";
    if(isReflective(matrix))
        cout << ++count << ". Матрица отношений рефлексивна.\n";
    if(isAntiReflective(matrix))
        cout << ++count << ". Матрица отношений антирефлексивна.\n";
    if(isSymmetric(matrix))
        cout << ++count << ". Матрица отношений симметрична.\n";
    if(isASymmetric(matrix))
        cout << ++count << ". Матрица отношений асимметрична.\n";
    if(isAntiSymmetric(matrix))
        cout << ++count << ". Матрица отношений антисимметрична.\n";
    if(isTransitive(matrix))
        cout << ++count << ". Матрица отношений транзитивна.\n";
    if(isConnectivity(matrix))
        cout << ++count << ". Матрица отношений связная.\n";
    if(count == 0)
        cout << "Свойств не найдено!\n";
}