#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <random>
#include <Windows.h>


std::mutex mtx; // Mutex для защиты доступа к стандартному выводу

// Функция для сортировки и вывода данных
template <typename T>
void sortAndPrint(const T& data, const std::string& collectionType) {
    T sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    std::lock_guard<std::mutex> lock(mtx); // Блокировка mutex'а на время вывода
    std::cout << "[" << std::this_thread::get_id() << "] (" << collectionType << "): ";
    for (const auto& item : sortedData) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    // Два вектора с случайными данными
    std::vector<int> vecData1(20);
    std::vector<int> vecData2(15);

    for (int i = 0; i < 20; ++i) vecData1[i] = distrib(gen);
    for (int i = 0; i < 15; ++i) vecData2[i] = distrib(gen);


    // Создание и запуск потоков
    std::thread thread1(sortAndPrint<std::vector<int>>, vecData1, "vector1");
    std::thread thread2(sortAndPrint<std::vector<int>>, vecData2, "vector2");


    // Ожидание завершения потоков
    thread1.join();
    thread2.join();

    std::cout << "Все потоки завершены." << std::endl;

    system("pause");
    return 0;
}
