#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>
#include <atomic>

class YouTuber {
public:
    YouTuber() : money(0), energy(100), videosRecorded(0), streamers(1), subscribers(0), popularity(1) {
        // Запуск потока для восстановления энергии
        energyRecoveryThread = std::thread(&YouTuber::recoverEnergy, this);
    }

    ~YouTuber() {
        running = false; // Остановка потока при уничтожении объекта
        if (energyRecoveryThread.joinable()) {
            energyRecoveryThread.join();
        }
    }

    void recordVideo() {
        if (energy < 20) {
            std::cout << "Недостаточно энергии для записи видео!" << std::endl;
            return;
        }

        // Случайные трудности
        handleRandomEvents();

        // Выбор жанра видео
        std::string genres[3] = { "Влог", "Обзор", "Геймплей" };
        int genreIndex = rand() % 3;

        int baseEarnings = (rand() % 100 + 50) * popularity; // Заработок зависит от популярности
        money += baseEarnings;
        videosRecorded++;
        subscribers += rand() % 10 + 5; // Подписчики за видео

        energy -= 20;

        std::cout << "Записано видео в жанре: " << genres[genreIndex] << "! Заработано: $" << baseEarnings << std::endl;
        std::cout << "Новые подписчики: " << (rand() % 10 + 5) << std::endl;
        std::cout << "Ваша энергия: " << energy << std::endl;
    }

    void startStream() {
        if (energy < 30) {
            std::cout << "Недостаточно энергии для стрима!" << std::endl;
            return;
        }

        // Случайные трудности
        handleRandomEvents();

        energy -= 30;
        std::cout << "Стрим начат! Продолжительность: 30 секунд." << std::endl;

        for (int i = 0; i < 6; ++i) { // Стрим длится 30 секунд, донаты каждые 5 секунд
            std::this_thread::sleep_for(std::chrono::seconds(5));
            int donation = (rand() % 50 + 10) * popularity; // Донат зависит от популярности
            money += donation;
            std::cout << "Донат пришёл: $" << donation << std::endl;
        }

        energy -= 10; // Энергия после стрима
        std::cout << "Стрим завершён!" << std::endl;
        std::cout << "Ваша энергия: " << energy << std::endl;
    }

    void investInEquipment() {
        int choice;
        std::cout << "Инвестиции в оборудование:" << std::endl;
        std::cout << "1. Красивая подсветка на фон -  $500" << std::endl;
        std::cout << "2. Улучшенная камера - $1500" << std::endl;
        std::cout << "3. Профессиональный микрофон - $3000" << std::endl;
        std::cout << "4. Улучшенная клавиатура - $4500" << std::endl;
        std::cout << "5. Профессиональная игровая клавиатура - $5500" << std::endl;
        std::cout << "Выберите товар: ";
        std::cin >> choice;

        if (choice == 1 && money >= 500) {
            money -= 500;
            int increase = 1; // Увеличение популярности
            popularity += increase;
            std::cout << "Куплена красивая подсветка на фон! Популярность увеличена на " << increase << std::endl;
        }
        else if (choice == 2 && money >= 1500) {
            money -= 1500;
            int increase = 2; // Увеличение популярности
            popularity += increase;
            std::cout << "Куплена улучшенная камера! Популярность увеличена на " << increase << std::endl;
        }
        else if (choice == 3 && money >= 3000) {
            money -= 3000;
            int increase = 3; // Увеличение популярности
            popularity += increase;
            std::cout << "Куплен профессиональный микрофон! Популярность увеличена на " << increase << std::endl;
        }
        else if (choice == 4 && money >= 4500) {
            money -= 4500;
            int increase = 4; // Увеличение популярности
            popularity += increase;
            std::cout << "Куплена улучшенная клавиатура! Популярность увеличена на " << increase << std::endl;
        }
        else if (choice == 5 && money >= 5500) {
            money -= 5500;
            int increase = 5; // Увеличение популярности
            popularity += increase;
            std::cout << "Куплена профессиональная игровая клавиатура! Популярность увеличена на " << increase << std::endl;
        }
        else {
            std::cout << "Недостаточно денег или неверный выбор!" << std::endl;
        }
    }

    void saveProgress() {
        std::ofstream file("progress.txt");
        if (file.is_open()) {
            file << money << "\n"
                << energy << "\n"
                << videosRecorded << "\n"
                << streamers << "\n"
                << subscribers << "\n"
                << popularity << "\n";
            file.close();
            std::cout << "Прогресс сохранён!" << std::endl;
        }
        else {
            std::cout << "Ошибка при сохранении прогресса!" << std::endl;
        }
    }

    void loadProgress() {
        std::ifstream file("progress.txt");
        if (file.is_open()) {
            file >> money >> energy >> videosRecorded >> streamers >> subscribers >> popularity;
            file.close();
            std::cout << "Прогресс загружен!" << std::endl;
        }
        else {
            std::cout << "Ошибка при загрузке прогресса!" << std::endl;
        }
    }

    void showStatistics() const {
        std::cout << "Статистика:" << std::endl;
        std::cout << "Деньги: $" << money << std::endl;
        std::cout << "Энергия: " << energy << std::endl;
        std::cout << "Количество записанных видео: " << videosRecorded << std::endl;
        std::cout << "Количество стримов: " << streamers << std::endl;
        std::cout << "Подписчики: " << subscribers << std::endl;
        std::cout << "Популярность: " << popularity << std::endl;
    }

private:
    int money;
    int energy;
    int videosRecorded;
    int streamers;
    int subscribers;
    int popularity;

    // Поток для восстановления энергии
    std::atomic<bool> running{ true };
    std::thread energyRecoveryThread;

    void recoverEnergy() {
        while (running) {
            if (energy < 100) {
                energy += 5; // Восстановление энергии
                if (energy > 100) energy = 100; // Ограничение на максимум
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Ожидание 1 секунда
            }
            else {
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Ожидание, если энергия полная
            }
        }
    }

    void handleRandomEvents() {
        int eventChance = rand() % 100;

        // Событие плохой погоды
        if (eventChance < 15) { // 20% шанс
            int energyLoss = rand() % 20 + 10; // Потеря энергии от 10 до 30
            energy -= energyLoss;
            if (energy < 0) energy = 0; // Ограничение на минимум
            int incomeReduction = rand() % 10 + 25; // Снижение дохода от 20 до 70
            money -= incomeReduction;
            if (money < 0) money = 0; // Ограничение на минимум
            std::cout << "Проблема: Плохая погода! Энергия снижена на "
                << energyLoss << ", доход уменьшен на $"
                << incomeReduction << "." << std::endl;
        }

        // Событие критики
        if (eventChance >= 5 && eventChance < 20) { // 20% шанс
            int popularityChange = rand() % 3 + 1; // Изменение популярности от -3 до +3
            popularity -= popularityChange;
            if (popularity < 0) popularity = 0; // Ограничение на минимум
            std::cout << "Проблема: Получена критика! Популярность снижена на "
                << popularityChange << "." << std::endl;
        }

        // Положительный отзыв
        if (eventChance >= 5 && eventChance < 20) { // 20% шанс
            int popularityBoost = rand() % 2 + 1; // Увеличение популярности от +1 до +2
            popularity += popularityBoost;
            std::cout << "Отлично! Получен положительный отзыв! Популярность увеличена на "
                << popularityBoost << "." << std::endl;
        }
    }
};

int main() {
    setlocale(0, "");
    srand(static_cast<unsigned>(time(0)));
    YouTuber youtuber;

    // Попробуем загрузить прогресс
    youtuber.loadProgress();

    while (true) {
        int choice;
        std::cout << "\nГлавное меню:" << std::endl;
        std::cout << "1. Записать видео-ролик" << std::endl;
        std::cout << "2. Запустить стрим" << std::endl;
        std::cout << "3. Инвестировать в оборудование" << std::endl;
        std::cout << "4. Моя статистика" << std::endl;
        std::cout << "5. Сохранить прогресс" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            youtuber.recordVideo();
            break;
        case 2:
            youtuber.startStream();
            break;
        case 3:
            youtuber.investInEquipment();
            break;
        case 4:
            youtuber.showStatistics();
            break;
        case 5:
            youtuber.saveProgress();
            break;
        case 6:
            exit(0);
            break;
        default:
            std::cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
            break;
        }
    }

    return 0;
}