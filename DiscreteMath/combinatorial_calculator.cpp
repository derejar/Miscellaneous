#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <string>

enum class Option
{
    placementWithoutRepetitions = 1,
    placementWithRepetition,
    combinationWithoutRepetition,
    combinationWithRepetition,
    permutationWithoutRepetition,
    permutationWithRepetition
};

int64_t factorial(const int64_t& number)
{
    int64_t result = 1;
    for(int64_t i = 2; i <= number; ++i)
        result *= i;
    return result;
}

int64_t divideFactorials(const int64_t& numerator, const int64_t& denominator)
{
    int64_t result = 1;
    for(int64_t i = denominator + 1; i <= numerator; ++i)
        result *= i;
    return result;
}

std::vector<int64_t>& getNumbersToFactorial(const int64_t& number, std::vector<int64_t>& numbers)
{
    for(int64_t i = 2; i <= number; ++i)
        numbers.push_back(i);
    return numbers;
}

void dividing(std::vector<int64_t>& numerators, std::vector<int64_t>& denominators)
{
    for(std::size_t i = 0; i < numerators.size(); ++i)
    {
        for(int64_t j = static_cast<int64_t>(denominators.size()) - 1; j >= 0 && numerators[i] != 1; --j)
        {
            if(denominators[j] == 1)
                continue;
            if(numerators[i] % denominators[j] == 0)
            {
                numerators[i] /= denominators[j];
                denominators[j] = 1;
            }
        }
    }
}

template<typename... Args>
int64_t divide(const int64_t& numerator, Args... args)
{
    std::vector<int64_t> toFactorials{args...};
    std::vector<int64_t> denominators;
    for(const int64_t& number : toFactorials)
        getNumbersToFactorial(number, denominators);
    std::vector<int64_t> numerators;
    getNumbersToFactorial(numerator, numerators);
    dividing(numerators, denominators);
    int64_t result = 1;
    for(const int64_t& n : numerators)
        result *= n;
    for(const int64_t d : denominators)
        result /= d;
    return result;
}

int64_t placementWithoutRepetition(const int64_t& n, const int64_t& k)
{
    return divideFactorials(n, n - k);
}

int64_t placementWithRepetition(const int64_t& n, const int64_t& k)
{
    return std::pow(n, k);
}

int64_t combinationWithoutRepetition(const int64_t& n, const int64_t& k)
{
    return divide(n, k, n - k);
}

int64_t combinationWithRepetition(const int64_t& n, const int64_t& k)
{
    return divide(n + k - 1, k, n - 1);
}

int64_t permutationWithoutRepetition(const int64_t& n)
{
    return factorial(n);
}

int64_t permutationWithRepetition(const int64_t& n, const std::vector<int64_t>& ks)
{
    return divide(n, ks);
}

int32_t main()
{
    int32_t option;
    do
    {
        std::cout << "[1] Размещение без повторений.\n" <<
                "[2] Размещение с повторениями.\n" <<
                "[3] Сочетание без повторений.\n" <<
                "[4] Сочетание с повторениями.\n" <<
                "[5] Перестановка без повторений.\n" <<
                "[6] Перестановка с повторениями.\n" <<
                "[0] Выход.\n";
        std::cin >> option;
        int64_t n; int64_t k = 1; std::vector<int64_t> ks;
        if(option == 5)
        {
            std::cout << "Введите n: ";
            std::cin >> n;
        }
        else if(option == 6)
        {
            std::cout << "Введите n: ";
            std::cin >> n;
            ks.reserve(n);
            int64_t sum = 0;
            while(sum < n && k > 0)
            {
                std::cin >> k;
                if(k > 0)
                {
                    sum += k;
                    ks.push_back(k);
                }
            }
            if(sum != n && k > 0)
            {
                std::cout << "Сумма значений k должна равняться n. Попробуйте заново.\n";
                option = 10;
            }
        }
        else if(option > 0 && option < 5)
        {
            std::cout << "Введите n: ";
            std::cin >> n;
            std::cout << "Введите k: ";
            std::cin >> k;
        }

        // std::cout << std::string(25, '\n');
        switch(static_cast<Option>(option))
        {
            case Option::placementWithoutRepetitions :
                std::cout << "Размещение без повторений из " << n << " по " << k << " = " << placementWithoutRepetition(n, k) << "\n"; break;
            case Option::placementWithRepetition :
                std::cout << "Размещение с повторениями из " << n << " по " << k << " = " << placementWithRepetition(n, k) << "\n"; break;
            case Option::combinationWithoutRepetition :
                std::cout << "Сочетание без повторений из " << n << " по " << k << " = " << combinationWithoutRepetition(n, k) << "\n"; break;
            case Option::combinationWithRepetition :
                std::cout << "Сочетание с повторениями из " << n << " по " << k << " = " << combinationWithRepetition(n, k) << "\n"; break;
            case Option::permutationWithoutRepetition :
                std::cout << "Перестановка без повторений из " << n << " = " << permutationWithoutRepetition(n) << "\n"; break;
            case Option::permutationWithRepetition :
                std::cout << "Перестановка с повторениями из " << n  << " = " << permutationWithRepetition(n, ks) << "\n"; break;
        }
        // std::cout << "\n" << std::string(15, '-') << "\n\n";
    }while(option);
}
