#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

const int COUNT_OF_VARIABLES = 4;
const int SIZE = 16;
const int LETTER_CASE = 32;

class BinaryFunction
{
public:
    BinaryFunction(const string& functionVector);
    void printTruthTable();
    void printSDNF();
    void printMDNF();
    void printPrimeImplicants();
    void printPrimeImplicantChart();
    
private:
    string getBinaryRepresentation(int number);
    string getWithVariablesNames(const string& tableLine);
    bool calculateMinterms();
    template<class T> void printDNF(T& DNF);
    void fillPrimeImplicantChart();
    void calculateMDNF();
    set<int> findUncovered(list<int> lines);
    void petrickMethod(set<int> uncovered);
    set<set<char>> findMinimalTerms(set<int> uncovered);

    vector<string> m_SDNF;
    set<string> m_MDNF;
    vector<string> m_minterms;
    array<string, SIZE> m_table;
    string m_functionVector;
    vector<vector<int>> m_primeImplicantChart;
};

BinaryFunction::BinaryFunction(const string& functionVector) : m_functionVector(functionVector)
{
    for(int i = 0; i < m_table.size(); ++i)
        m_table[i] = getBinaryRepresentation(i);
        for(int i = 0; i < SIZE; ++i)
            if(m_functionVector[i] == '1')
                m_SDNF.push_back(m_table[i]);
    m_minterms = m_SDNF;
    while(calculateMinterms());
    fillPrimeImplicantChart();
    calculateMDNF();
}

string BinaryFunction::getWithVariablesNames(const string& tableLine)
{
    string result = "";
    for(int i = 0; i < tableLine.length(); ++i)
    {
        char c = static_cast<char>('a' + i);
        if(tableLine[i] == '1')
            result += c;
        else if(tableLine[i] == '0')
            result += static_cast<char>(c - LETTER_CASE);
    }
    return result;
}

string BinaryFunction::getBinaryRepresentation(int number)
{
    string result = "";
    while(number)
    {
        result += to_string(number & 1);
        number >>= 1;
    }
    reverse(result.begin(), result.end());
    while(result.length() < COUNT_OF_VARIABLES)
        result.insert(0, 1, '0');
    return result;
}

void BinaryFunction::printTruthTable()
{
    for(int i = 0; i < COUNT_OF_VARIABLES; ++i)
    {
        cout << static_cast<char>('a' + i);
        if(i != COUNT_OF_VARIABLES - 1)
            cout << "   ";
    }
    cout << " | f\n";
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < COUNT_OF_VARIABLES; ++j)
        {
            cout << m_table[i][j];
            if(j != COUNT_OF_VARIABLES - 1)
                cout << "   "; 
        }
        cout <<  " | " << m_functionVector[i] << "\n";
    }
}

template <class T> void BinaryFunction::printDNF(T& DNF)
{
    for(typename T::iterator i = DNF.begin(); i != DNF.end(); ++i)
    {
        cout << getWithVariablesNames(*(i));
        if(i != (--DNF.end()))
            cout << " V ";
    }
    cout << "\n";
}

void BinaryFunction::printSDNF()
{
    printDNF(m_SDNF);
}

void BinaryFunction::printMDNF()
{
    if(m_MDNF.size() == 1)
    {
        string alwaysTrue = "";
        alwaysTrue.append(COUNT_OF_VARIABLES, '-');
        if((*m_MDNF.begin()) == alwaysTrue)
            cout << "1";
    }
    printDNF(m_MDNF);
}

void BinaryFunction::printPrimeImplicants()
{
    cout << "Количество простых импликант: " << m_minterms.size() << ". Список:\n";
    for(int i = 0; i < m_minterms.size(); ++i)
        cout << static_cast<char>('a' + i) << ": " << getWithVariablesNames(m_minterms[i]) << "\n";
}

void BinaryFunction::printPrimeImplicantChart()
{
    cout << "   ";
    for(int i = 1; i <= m_SDNF.size(); ++i)
        cout << i << "   ";
    cout << "\n";
    
    for(int i = 0; i < m_minterms.size(); ++i)
    {
        cout << static_cast<char>('a' + i) << ": ";
        string spaces = "   ";
        for(int j = 0; j < m_SDNF.size(); ++j)
        {
            if(m_primeImplicantChart[i][j] == 1)
                cout << '+';
            else
                cout << " ";
            if(j == 9)
                spaces = "    ";
            cout << spaces;
        }
        cout << "\n";
    }
}

bool BinaryFunction::calculateMinterms()
{
    vector<string> newMinterms;
    vector<int> toNext(m_minterms.size(), 0); 
    bool anythingChanged = false;
    for(int i = 0; i < m_minterms.size() - 1; ++i)
    {
        for(int j = i + 1; j < m_minterms.size(); ++j)
        {
            int difference = 0; int point = 0;
            for(int k = 0; k < COUNT_OF_VARIABLES; ++k)
            {
                if(m_minterms[i][k] != m_minterms[j][k] && (m_minterms[i][k] != '-' || m_minterms[j][k] != '-'))
                    ++difference, point = k;
            }
            if(difference == 0)
            {
                for(int k = 0; k < COUNT_OF_VARIABLES; ++k)
                    if(m_minterms[i][k] != m_minterms[j][k])
                        ++difference;
                if(difference == 0)
                {
                    m_minterms.erase(m_minterms.begin() + j);
                    toNext.erase(toNext.begin() + j);
                    --j;
                }
            }
            else if(difference == 1)
            {
                string term = m_minterms[i];
                term[point] = '-';
                newMinterms.push_back(term);
                ++toNext[i];
                ++toNext[j];
                anythingChanged = true;
            }
        }
    }
    for(int i = 0; i < m_minterms.size(); ++i)
        if(toNext[i] == 0)
            newMinterms.push_back(m_minterms[i]);
    if(anythingChanged)
        m_minterms = newMinterms;
    return anythingChanged;
}

void BinaryFunction::calculateMDNF()
{
    list<int> lines;
    for(int i = 0; i < m_primeImplicantChart[0].size(); ++i)
    {
        int count = 0; int point = 0;
        for(int j = 0; j < m_primeImplicantChart.size(); ++j)
            if(m_primeImplicantChart[j][i] == 1)
                ++count, point = j;
        if(count == 1)
            m_MDNF.insert(m_minterms[point]), lines.push_back(point);
    }
    set<int> uncovered = findUncovered(lines);
    if(!uncovered.empty())
        petrickMethod(uncovered);
}

set<int> BinaryFunction::findUncovered(list<int> lines)
{
    set<int> covered;
    for(int l : lines)
    {
        for(int i = 0; i < m_SDNF.size(); ++i)
            if(m_primeImplicantChart[l][i] == 1)
                covered.insert(i);
    }
    set<int> uncovered;
    for(int i = 0; i < m_SDNF.size(); ++i)
        if(covered.find(i) == covered.end())
            uncovered.insert(i);
    return uncovered;
}

set<set<char>> BinaryFunction::findMinimalTerms(set<int> uncovered)
{
    set<set<char>> whole;
    for(int row : uncovered)
    {
        set<char> element;
        for(int i = 0; i < m_minterms.size(); ++i)
        {
            if(m_primeImplicantChart[i][row] == 1)
                element.insert(static_cast<char>('a' + i));
        }
        whole.insert(element);
    }
    set<set<char>> first;
    set<char> second;
    for(set<char> element : whole)
    {
        set<set<char>> result;
        if(first.empty())
        {
            for(char letter : element)
            {
                set<char> temporary;
                temporary.insert(letter);
                first.insert(temporary);
            }
            continue;
        }
        else
            second = element;
        for(char multiplier : second)
        {
            for(set<char> secondMultiplier : first)
            {
                secondMultiplier.insert(multiplier);
                result.insert(secondMultiplier);
            }
        }
        first = result;
    }
    int minimalSize = 10000;
    for(set<char> term : first)
        if(minimalSize > term.size())
            minimalSize = term.size();

    set<set<char>> result;
    for(set<char> term : first)
        if(term.size() == minimalSize)
            result.insert(term);
    return result;   
}

void BinaryFunction::petrickMethod(set<int> uncovered)
{
    set<set<char>> minimalTerms = findMinimalTerms(uncovered);
    int index = 0; int minimalSize = 10000; int minimalSizeIndex = 0;
    for(const set<char>& term : minimalTerms)
    {
        int termSize = 0;
        for(char letter : term)
        {
            int index = static_cast<int>(letter - 'a');
            for(char a : m_minterms[index])
            {
                if(a != '-')
                    ++termSize;
            }
        }
        if(minimalSize > termSize)
            minimalSize = termSize, minimalSizeIndex = index;
        ++index;
    }
    index = 0;
    for(const set<char>& term : minimalTerms)
    {
        if(index == minimalSizeIndex)
        {
            for(char letter : term)
                m_MDNF.insert(m_minterms[static_cast<int>(letter - 'a')]);
            break;
        }
        ++index;
    }
}

void BinaryFunction::fillPrimeImplicantChart()
{
    for(int i = 0; i < m_minterms.size(); ++i)
    {
        vector<int> line(m_SDNF.size(), 0);
        for(int j = 0; j < m_SDNF.size(); ++j)
        {
            int difference = 0;
            for(int k = 0; k < COUNT_OF_VARIABLES && difference == 0; ++k)
            {
                if(m_minterms[i][k] == '-')
                    continue;
                else if(m_minterms[i][k] != m_SDNF[j][k])
                    ++difference;
            }
            if(difference == 0)
                line[j] = 1;
        }
        m_primeImplicantChart.push_back(line);
    }
}

string getBinaryRepresentation(int number)
{
    string result = "";
    while(number)
    {
        result += to_string(number & 1);
        number >>= 1;
    }
    reverse(result.begin(), result.end());
    while(result.length() < 8)
        result.insert(0, 1, '0');
    return result;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    string functionVector;
    for(int i = 0; i < SIZE; ++i)
    {
        char c; cin >> c;
        functionVector += c;
    }

    cout << functionVector << "\n";
    BinaryFunction binaryFunction(functionVector);
    binaryFunction.printTruthTable();
    cout << "\nСДНФ: ";
    binaryFunction.printSDNF(); 
    cout << "\n";
    binaryFunction.printPrimeImplicants();
    cout << "\nТаблица простых импликант:\n";
    binaryFunction.printPrimeImplicantChart();
    cout << "\nМДНФ: ";
    binaryFunction.printMDNF();
}