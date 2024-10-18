#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>  // Для засекания времени

// Функция для чтения матрицы из файла
std::vector<std::vector<double>> readMatrixFromFile(std::ifstream& inFile) {
    int rows, cols;
    // Читаем размер матрицы
    inFile.read(reinterpret_cast<char*>(&rows), sizeof(int));
    inFile.read(reinterpret_cast<char*>(&cols), sizeof(int));
    
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    
    // Читаем элементы матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inFile.read(reinterpret_cast<char*>(&matrix[i][j]), sizeof(double));
        }
    }
    return matrix;
}

// Функция для приведения матрицы к ступенчатому виду
void toRowEchelonForm(std::vector<std::vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int lead = 0; // Ведущий элемент
    
    for (int r = 0; r < rows; ++r) {
        if (lead >= cols) {
            return;
        }
        int i = r;
        while (matrix[i][lead] == 0) {
            ++i;
            if (i == rows) {
                i = r;
                ++lead;
                if (lead == cols) {
                    return;
                }
            }
        }
        std::swap(matrix[i], matrix[r]); // Меняем местами строки
        double leadValue = matrix[r][lead];
        
        for (int j = 0; j < cols; ++j) {
            matrix[r][j] /= leadValue; // Нормализуем ведущий элемент
        }
        
        for (int i = 0; i < rows; ++i) {
            if (i != r) {
                double leadFactor = matrix[i][lead];
                for (int j = 0; j < cols; ++j) {
                    matrix[i][j] -= leadFactor * matrix[r][j]; // Обнуляем элементы в других строках
                }
            }
        }
        ++lead;
    }
}

// Функция для вывода матрицы
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            std::cout << std::setw(8) << element << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string fileName;
    
    std::cout << "Введите имя файла для чтения матриц: ";
    std::cin >> fileName;
    
    // Открываем файл для чтения в бинарном формате
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл для чтения!" << std::endl;
        return 1;
    }
    
    // Засекаем время начала обработки
    auto start = std::chrono::high_resolution_clock::now();
    
    // Обрабатываем все матрицы в файле
    while (inFile.peek() != EOF) {
        // Читаем матрицу из файла
        std::vector<std::vector<double>> matrix = readMatrixFromFile(inFile);
        // Приводим матрицу к ступенчатому виду
        toRowEchelonForm(matrix);
    }
    
    // Засекаем время окончания обработки
    auto end = std::chrono::high_resolution_clock::now();
    
    // Рассчитываем время выполнения
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Время обработки матриц: " << elapsed.count() << " секунд." << std::endl;
    
    inFile.close();
    
    return 0;
}
