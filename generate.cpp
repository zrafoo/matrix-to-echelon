#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>  // Для засекания времени

// Функция для генерации случайной матрицы
std::vector<std::vector<double>> generateMatrix(int rows, int cols) {
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    srand(time(0)); // Инициализация генератора случайных чисел
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = static_cast<double>(rand() % 100) / 10.0; // Заполняем матрицу случайными числами
        }
    }
    return matrix;
}

// Функция для записи матрицы в файл
void saveMatrixToFile(const std::vector<std::vector<double>>& matrix, std::ofstream& outFile) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Записываем размер матрицы
    outFile.write(reinterpret_cast<const char*>(&rows), sizeof(int));
    outFile.write(reinterpret_cast<const char*>(&cols), sizeof(int));
    
    // Записываем элементы матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outFile.write(reinterpret_cast<const char*>(&matrix[i][j]), sizeof(double));
        }
    }
}

int main() {
    int numMatrices, rows, cols;
    std::string fileName;
    
    std::cout << "Введите имя файла для сохранения матриц: ";
    std::cin >> fileName;
    
    std::cout << "Введите количество матриц: ";
    std::cin >> numMatrices;
    
    std::cout << "Введите количество строк в матрице: ";
    std::cin >> rows;
    
    std::cout << "Введите количество столбцов в матрице: ";
    std::cin >> cols;
    
    // Открываем файл для записи в бинарном формате
    std::ofstream outFile(fileName, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }
    
    // Засекаем время начала генерации
    auto start = std::chrono::high_resolution_clock::now();
    
    // Генерация и запись матриц в файл
    for (int i = 0; i < numMatrices; ++i) {
        std::vector<std::vector<double>> matrix = generateMatrix(rows, cols);
        saveMatrixToFile(matrix, outFile);
    }
    
    // Засекаем время окончания генерации
    auto end = std::chrono::high_resolution_clock::now();
    
    // Рассчитываем время генерации
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Время генерации и записи матриц: " << elapsed.count() << " секунд." << std::endl;
    
    outFile.close();
    std::cout << "Запись завершена. Матрицы сохранены в файл: " << fileName << std::endl;
    
    return 0;
}
