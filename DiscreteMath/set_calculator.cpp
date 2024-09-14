#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <list>

const int COUNT_OF_SETS = 3;

enum class InputMode
{
    AUTOMATICALLY = 1,
    AUTOMATICALLY_WITH_CONDITIONS,
    MANUALLY
};

enum class Action
{
    EXIT,
    CREATE_NEW_SET,
    PRINT_ALL_SETS,
    REMOVE_SET,
    UNION,
    INTERSECTION,
    DIFFERENCE,
    SYMMETRIC_DIFFERENCE,
    ADDITION
};

enum class Condition
{
    EVEN_NUMBERS = 1,
    ODD_NUMBERS,
    POSITIVE_NUMBERS,
    NEGATIVE_NUMBERS,
    DEVIDED_BY_N
};

int16_t menu()
{
    std::cout << "Выберите действие:\n" <<
                "[1] Создать новое множество.\n" <<
                "[2] Напечатать все множества.\n" <<
                "[3] Удалить множество.\n" <<
                "[4] Объединение множеств.\n" <<
                "[5] Пересечение множеств.\n" <<
                "[6] Разность множеств.\n" <<
                "[7] Симметрическая разность множеств.\n" <<
                "[8] Дополнение множества.\n" <<
                "[0] Выход.\n" <<
                "Выш выбор: ";
    int16_t action; std::cin >> action;
    if(action < 0 || action > 8)
    {
        std::cout << "\nВыбрано несуществующее действие! Попробуйте еще раз.\n\n";
        action = menu();
    }
    return action;
}

int16_t inputMenu()
{
    std::cout << "\nВыберите способ для заполнения множества:\n" <<
            "[1] Автоматически.\n" <<
            "[2] Автоматические с условиями.\n" <<
            "[3] Вручную.\n" <<
            "[0] Вернуться назад.\n";
    int16_t choice; std::cin >> choice;
    if(choice < 0 || choice > 3)
    {
        std::cout << "\nВыбран несуществующтий вариант заполнения множеств. Попробуйте еще раз.\n\n";
        choice = inputMenu();
    }
    return choice; 
}

std::set<int32_t> automaticallyInput()
{
    std::array<int32_t, 19> valuesTemplate;
    std::iota(valuesTemplate.begin(), valuesTemplate.end(), -9);
    std::random_shuffle(valuesTemplate.begin(), valuesTemplate.end());
    int32_t size = -1;
    while(size < 1 || size > 19)
    {
        std::cout << "Введите размер создаваемого множества (не более 19 элементов): ";
        std::cin >> size;
        if(size < 1 || size > 19)
            std::cout << "Указан неверный размер!\n";
    }
    std::set<int32_t> generatedSet;
    for(int i = 0; i < size; ++i)
        generatedSet.insert(valuesTemplate[i]);
    return generatedSet;
}

std::set<int32_t> createdWithCondition(bool(*condition)(int32_t number, int32_t n), int32_t n)
{
    std::array<int32_t, 19> valuesTemplate;
    std::iota(valuesTemplate.begin(), valuesTemplate.end(), -9);
    std::set<int32_t> generatedSet;
    for(int i = 0; i < valuesTemplate.size(); ++i)
        if(condition(valuesTemplate[i], n))
            generatedSet.insert(valuesTemplate[i]);
    return generatedSet;
}

std::set<int32_t> automaticallyInputWithConditions()
{
    int16_t condition = -1;
    while(condition < 1 || condition > 5)
    {
        std::cout << "Выберите условие добавления чисел во множество:\n" <<
                    "[1] Только четные числа.\n" <<
                    "[2] Только нечетные числа.\n" <<
                    "[3] Только положительные числа.\n" << 
                    "[4] Только отрицательные числа.\n" <<
                    "[5] Только числа кратные N.\n";
        std::cin >> condition;
    }
    switch(static_cast<Condition>(condition))
    {
        case Condition::EVEN_NUMBERS : 
            return createdWithCondition([](int32_t number, int32_t n) { return number % 2 == 0; }, 2);
        case Condition::ODD_NUMBERS :
            return createdWithCondition([](int32_t number, int32_t n) { return (number % 2 == 1 || number % 2 == -1); }, 2);
        case Condition::POSITIVE_NUMBERS :
            return createdWithCondition([](int32_t number, int32_t n) { return number >= 0; }, 0);
        case Condition::NEGATIVE_NUMBERS :
            return createdWithCondition([](int32_t number, int32_t n) { return number <= 0; }, 0);
        case Condition::DEVIDED_BY_N :
            std::cout << "N = ";
            int32_t n; std::cin >> n;
            while(n == 0)
            {
                std::cout << "Не существует чисел кратных нулю. Введите значение отличное от нуля.\n";
                std::cin >> n;
            }
            return createdWithCondition([](int32_t number, int32_t n) { return number % n == 0; }, n);
    }
}

std::set<int32_t> manuallyInput()
{
    int32_t count = -1;
    while(count < 1 || count > 19)
    {
        std::cout << "Введите размер создаваемого множества (не более 19 элементов): ";
        std::cin >> count;
    }
    std::cout << "Вводите числа неповторяющиеся числа из промежутка [-9; 9].\n";
    std::set<int32_t> generatedSet;
    for(int i = 0; i < count; ++i)
    {
        int32_t n; std::cin >> n;
        if(n < -9 || n > 9)
        {
            std::cout << "Вы ввели число " << n << " не лежащее в промежутке [-9; 9]. Введите другое число вместо него.\n";
            --i; continue;
        }
        if(generatedSet.find(n) != generatedSet.end())
        {
            std::cout << "Значение " << n << " уже присутствует в множестве, введите другое число вместо него.\n";
            --i; continue;
        }
        generatedSet.insert(n);
    }
    return generatedSet;
}

void printAllSets(const std::map<char, std::set<int32_t>>& group)
{
    std::cout << "\n";
    if(group.empty())
    {
        std::cout << "Список множеств пуст!\n\n";
        return;
    }
    for(auto it : group)
    {
        std::cout << it.first << ": ";
        for(auto i = it.second.begin(); i != it.second.end(); ++i)
            std::cout << *(i) << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void createNewSet(std::map<char, std::set<int32_t>>& group, const std::array<char, COUNT_OF_SETS * 2>& letters)
{
    if(group.size() == COUNT_OF_SETS)
    {
        std::cout << "Вы не можете создать больше " << COUNT_OF_SETS << " множеств.\n\n";
        return;
    }
    int16_t choice = inputMenu();
    switch(static_cast<InputMode>(choice))
    {
        case InputMode::AUTOMATICALLY : 
            group.insert(std::make_pair(letters[group.size()], automaticallyInput()));
            break;
        case InputMode::AUTOMATICALLY_WITH_CONDITIONS :
            group.insert(std::make_pair(letters[group.size()], automaticallyInputWithConditions()));
            break;
        case InputMode::MANUALLY : 
            group.insert(std::make_pair(letters[group.size()], manuallyInput()));
            break;
    }
}

void removeSet(std::map<char, std::set<int32_t>>& group, std::array<char, COUNT_OF_SETS * 2>& letters)
{
    if(group.empty())
    {
        std::cout << "Список множеств пуст!\n\n";
        return;
    }
    std::cout << "Выберите множество для удаления (Введите букву, обозначающую множество):";
    printAllSets(group);
    bool isFinded = false;
    char setToRemove;
    while(!isFinded)
    {
        std::cout << "Ваш выбор: ";
        std::cin >> setToRemove;
        isFinded = (group.find(setToRemove) != group.end());
        if(!isFinded)
            std::cout << "Множество не найдено!\n";
    }
    group.erase(group.find(setToRemove));
    letters[group.size()] = setToRemove;
    std::sort(letters.begin() + group.size(), letters.end());
}

void actionsWithSets(Action action, std::map<char, std::set<int32_t>>& group, std::array<char, COUNT_OF_SETS * 2>& letters)
{
    if( (action != Action::ADDITION && group.size() < 2) ||
        (action == Action::ADDITION && group.size() < 1) )
    {
        if(action == Action::ADDITION)
            std::cout << "\nДля выполнения операции дополнения создайте хотя бы одно множество!\n\n";
        else
            std::cout << "\nДля выполнения действий с множествами сначала создайте как минимум два множества.\n\n";
        return;
    }

    char firstSetName = '-';
    std::map<char, std::set<int32_t>>::iterator firstIterator;
    std::map<char, std::set<int32_t>>::iterator secondIterator;
    std::set<int32_t> first;
    std::set<int32_t> second;
    printAllSets(group);
    do
    {
        if(firstSetName != '-')
            std::cout << "Введено несуществующее множество!\n";
        std::cout << "Выберите множество: ";
        std::cin >> firstSetName;
    } while ((firstIterator = group.find(firstSetName)) == group.end());

    if(action != Action::ADDITION)
    {
        char secondSetName = '-';
        do
        {
            if(secondSetName != '-')
                std::cout << "Введено несуществующее множество!\n";
            std::cout << "Выберите второе множество: ";
            std::cin >> secondSetName;
        } while ((secondIterator = group.find(secondSetName)) == group.end());
        second = secondIterator->second;
    }
    
    first = firstIterator->second;
    std::set<int32_t> createdSet;
    switch (action)
    {
        case Action::UNION :
            std::merge(first.begin(), first.end(),
                       second.begin(), second.end(),
                       std::inserter(createdSet, createdSet.begin()));
        break;
        case Action::INTERSECTION :
            std::set_intersection(first.begin(), first.end(),
                                  second.begin(), second.end(),
                                  std::inserter(createdSet, createdSet.begin()));
        break;
        case Action::DIFFERENCE :
            std::set_difference(first.begin(), first.end(),
                                second.begin(), second.end(),
                                std::inserter(createdSet, createdSet.begin()));
        break;
        case Action::SYMMETRIC_DIFFERENCE :
            std::set_symmetric_difference(first.begin(), first.end(),
                                          second.begin(), second.end(),
                                          std::inserter(createdSet, createdSet.begin()));
        break;
        case Action::ADDITION :
            std::set<int32_t> nums;
            for(int32_t i = -9; i <= 9; ++i)
                nums.insert(i);
            std::set_difference(nums.begin(), nums.end(),
                                first.begin(), first.end(),
                                std::inserter(createdSet, createdSet.begin()));
        break;
    }
    std::cout << "Результат вычислений сохранен во множестве ";
    if(action == Action::ADDITION)
    {
        group.erase(firstSetName);
        group.insert(std::make_pair(firstSetName, createdSet));
        std::cout << firstSetName << ": ";
    }
    else
    {
        std::cout << letters[group.size()] << ": ";
        group.insert(std::make_pair(letters[group.size()], createdSet));
    }
        
    for(int32_t element : createdSet)
        std::cout << element << " ";
    std::cout << "\n\n";
}

int main()
{
    std::array<char, COUNT_OF_SETS * 2> letters;
    std::iota(letters.begin(), letters.end(), 65);
    std::map<char, std::set<int32_t>> group;
    while(int16_t action = menu())
    {
        switch(static_cast<Action>(action))
        {
            case Action::CREATE_NEW_SET :
                createNewSet(group, letters);
            break;
            case Action::PRINT_ALL_SETS :
                printAllSets(group);
            break;
            case Action::REMOVE_SET :
                removeSet(group, letters);
            break;
            case Action::UNION : 
                actionsWithSets(Action::UNION, group, letters);
            break;
            case Action::INTERSECTION :
                actionsWithSets(Action::INTERSECTION, group, letters);
            break;
            case Action::DIFFERENCE : 
                actionsWithSets(Action::DIFFERENCE, group, letters);
            break;
            case Action::SYMMETRIC_DIFFERENCE :
                actionsWithSets(Action::SYMMETRIC_DIFFERENCE, group, letters);
            break;
            case Action::ADDITION :
                actionsWithSets(Action::ADDITION, group, letters);
            break;
        }
    }
}