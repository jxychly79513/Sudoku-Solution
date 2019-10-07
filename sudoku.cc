#include <iostream>
#include <vector>
#include <tuple>

class Sudoku {
private:
    int m_rows[9];
    int m_cols[9];
    int m_boxes[9];
    int m_lattice[9][9];
    int *m_origin;
    std::vector<std::tuple<int, int, int> > m_stack; 

    int get_box(int i, int j) {
        return i / 3 * 3 + j / 3;
    }
    
    bool can_set(int i, int j, int n) {
        int bit = 1 << n;
        return !(m_rows[i] & bit) && !(m_cols[j] & bit) && !(m_boxes[get_box(i, j)] & bit);
    }

    void set_num(int i, int j, int n) {
        int bit = 1 << n;
        m_rows[i] |= bit;
        m_cols[j] |= bit;
        m_boxes[get_box(i, j)] |= bit;
        m_lattice[i][j] = n;
    }

    void del_num(int i, int j, int n) {
        int bit = ~(1 << n);
        m_rows[i] &= bit;
        m_cols[j] &= bit;
        m_boxes[get_box(i, j)] &= bit;
        m_lattice[i][j] = 0;
    }

    void back_stack() {
        do {
            m_stack.pop_back();
        } while (!m_stack.empty() && std::get<2>(*(m_stack.end() - 1)) == 0);
    }

public: 
    Sudoku(int lattice[][9])
        : m_rows{0}, m_cols{0}, m_boxes{0}, m_lattice{0}, m_origin(reinterpret_cast<int*>(lattice))
    {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (lattice[i][j] != 0) {
                    set_num(i, j, lattice[i][j]);
                    m_lattice[i][j] = lattice[i][j];
                }
            }
        }
        m_stack.emplace_back(0, 0, 0);
    }

    int get(int i, int j) {
        return m_lattice[i][j];
    }

    bool calc() {
        while (!m_stack.empty()) {
            auto pair = m_stack.end() - 1;
            int i = std::get<0>(*pair), j = std::get<1>(*pair);
            int n = std::get<2>(*pair);

            if (i >= 9) {
                back_stack();
                return true;
            }

            if (n > 0) del_num(i, j, n);

            if (m_origin[i * 9 + j] == 0) {
                bool setted = false;
                for (int t = n + 1; t <= 9; ++t) {
                    if (can_set(i, j, t)) {
                        set_num(i, j, t);
                        std::get<2>(*pair) = t;
                        m_stack.emplace_back(i + (j + 1) / 9, (j + 1) % 9, 0);
                        setted = true;
                        break;
                    }
                }
                if (!setted) 
                    back_stack();

            } else {
                m_stack.emplace_back(i + (j + 1) / 9, (j + 1) % 9, 0);
            }
        }
        
        return false;
    }
};

int main()
{
    int lattice[][9] = {
        // {5, 3, 0, 0, 7, 0, 0, 0, 0},
        // {6, 0, 0, 1, 9, 5, 0, 0, 0},
        // {0, 9, 8, 0, 0, 0, 0, 6, 0},
        // {8, 0, 0, 0, 6, 0, 0, 0, 3},
        // {4, 0, 0, 8, 0, 3, 0, 0, 1},
        // {7, 0, 0, 0, 2, 0, 0, 0, 6},
        // {0, 6, 0, 0, 0, 0, 2, 8, 0},
        // {0, 0, 0, 4, 1, 9, 0, 0, 5},
        // {0, 0, 0, 0, 8, 0, 0, 7, 9},
        
        {0, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 0, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 0},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 0, 1, 9, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},

        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
        // {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    Sudoku su(lattice);
    std::cout << "----------------------------------------" << su.calc() << std::endl;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << su.get(i, j) << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "----------------------------------------" << su.calc() << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << su.get(i, j) << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}
