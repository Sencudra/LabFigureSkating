#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Результаты соревнований фигуристов по одному из видов многоборья представлены оценками
//7 судей в баллах (от 0,0 до 6,0).
//По результатам оценок судьи определяется место каждого участника у этого судьи.
//Места участников определяются далее по сумме мест, которые каждый участник занял у всех судей.
//Составить программу, определяющую по исходной таблице оценок фамилии и сумму мест участников в порядке занятых мест.


// максимальное кол-во участников
const int lmax = 100;

// Вспомогательная функция - сортировка пузырьком :3
void sortData();

class Player
{
    public:
        // Конструктор класс, задаем имя игроку и инициализируем сумму мест
        Player(int newId, string newName){id = newId; name = newName ;placeSum = 0;}

        int getPoints(){return placeSum;}

    private:
        int id;
        string name;
        int placeSum;
};

class Judge
{
    public:
        Judge(int newId){id = newId;}

        void record(int id,int mark); // Запись в data
        int returnPlace(int id); // ...

    private:
        int id;
        // первая колонка - id участника, вторая - оценка
        float data[lmax][2];
    };



class Tournament
{
    public:
        Tournament();
        void result();

    private:
        // база участников [id][placeSum]
        int base[lmax][2];

};



int main(int argc, char *argv[])
{

    return 0;
}
