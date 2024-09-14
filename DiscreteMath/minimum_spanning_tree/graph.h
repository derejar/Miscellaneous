#include <vector>
#include <cstdint>
#include <fstream>
typedef std::vector<std::vector<int32_t>> matrix_t;
class Graph
{
public:
    Graph();
    explicit Graph(matrix_t& matrix);
    matrix_t getMatrix() const noexcept;
    std::vector<int> getColors() const noexcept;
    void setMatrix(const matrix_t& matrix) noexcept;
    std::size_t size() const noexcept;
    friend void operator>>(std::ifstream& ifile, Graph& graph);
    const std::vector<int32_t>& operator[](std::size_t index) const noexcept;
private:
    void colorize();
private:
    matrix_t m_matrix;
    std::size_t m_size;
    std::vector<int> m_colors;
};
