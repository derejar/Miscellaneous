#include "graph.h"
#include <cassert>

Graph::Graph() : m_matrix(), m_size(0)
{}

Graph::Graph(matrix_t& matrix) : m_matrix(std::move(matrix)), m_size(m_matrix.size()), m_colors(m_size)
{
    assert(!m_matrix.empty());
    assert(m_matrix.size() == m_matrix[0].size());
    colorize();
}

void Graph::colorize()
{
    matrix_t colorized(m_size, std::vector<int>(m_size, 0));
    for(std::size_t i = 0; i < m_size; ++i)
    {
        int color = 1;
        for(std::size_t j = 0; j < m_size;++j)
            if(colorized[i][j] == color)
                ++color, j = 0;
        m_colors[i] = color;
        for(std::size_t j = 0; j < m_size; ++j)
            if((*this)[j][i])
                colorized[j][i] = color;
    }
}

std::vector<int> Graph::getColors() const noexcept
{
    return m_colors;
}

matrix_t Graph::getMatrix() const noexcept
{
    return m_matrix;
}

void Graph::setMatrix(const matrix_t& matrix) noexcept
{
    m_matrix = matrix;
    m_size = m_matrix.size();
    m_colors.resize(m_size);
    colorize();
}

std::size_t Graph::size() const noexcept
{
    return m_size;
}

const std::vector<int32_t>& Graph::operator[](std::size_t index) const noexcept
{
    return m_matrix[index];
}

void operator>>(std::ifstream& ifile, Graph& graph)
{
    ifile >> graph.m_size;
    matrix_t matrix(graph.m_size, std::vector<int>(graph.m_size));
    for(std::size_t i = 0; i < graph.m_size; ++i)
        for(std::size_t j = 0; j < graph.m_size; ++j)
            ifile >> matrix[i][j];
    graph.setMatrix(matrix);
}
