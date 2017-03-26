#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> // rand, srand
#include <ctime>

using namespace std;

//Результаты соревнований фигуристов по одному из видов многоборья представлены оценками
//7 судей в баллах (от 0,0 до 6,0).
//По результатам оценок судьи определяется место каждого участника у этого судьи.
//Места участников определяются далее по сумме мест, которые каждый участник занял у всех судей.
//Составить программу, определяющую по исходной таблице оценок фамилии и сумму мест участников в порядке занятых мест.


// максимальное кол-во участников
const int lmax = 120;

class Player
{
    public:
        // Конструктор класс, задаем имя игроку и инициализируем сумму мест
        Player(int newId, string newName){id = newId; name = newName ;placeSum = 0;}

        int addPoints(int pts){placeSum+=pts;}
        int getId(){return id;}
        int getPoints(){return placeSum;}
        string getName(){return name;}

    private:
        int id;
        string name;
        int placeSum;
};

class Judge
{
    public:
        Judge(int newId){id = newId;playerNum = 0;}

        void record(int id,float mark){data[playerNum][1]= id;data[playerNum][2]= mark;playerNum++;} // Запись в data

        // Пузырьковая сортировка
        void pSort(){
            for (int i = 0; i < playerNum;i++)
                for(int j = playerNum - 1; j > i; j--)
                    if(data[j][2] > data[j-1][2])
                    {
                        swap(data[j][1],data[j-1][1]); // меняю местами
                        swap(data[j][2],data[j-1][2]); // меняю местами
                    }

        }

        int getPlace(int id){
            int i = 0;

            // Досрочный выход
            while (id != data[i][1])
                i++;
            return i;
        } // возвращаем место игрока у Судьи

    private:
        int id;
        // первая колонка - id участника, вторая - оценка
        float data[lmax][2];
        int playerNum;
    };



class Tournament
{
    public:
        Tournament(){
            playerNum = 0;
            for(int i = 0; i < 7; i++){
                Judge* newJudge = new Judge(i);
                judges[i] = newJudge;
            }
        }
        void recordMark(int judgeId,int playerId,float mark){ judges[judgeId]->record(playerId,mark);} //Запись оценки
        void regNewPlayer(Player* link){base[playerNum] = link;playerNum++;}

        void sortJudges(){
            for(int i = 0; i < 7; i++)
            {
                judges[i]->pSort();
            }

        }
        void countPlace(){
            for (int i = 0; i < playerNum; i++){
                for(int j = 0; j < 7; j++)
                {
                    base[i]->addPoints(judges[j]->getPlace(base[i]->getId()));
                }
            }

        }
        void result(){
                for (int i = 0; i < playerNum;i++)
                    for(int j = playerNum - 1; j > i; j--)
                        if(base[j]->getPoints() < base[j-1]->getPoints())
                        {
                            swap(base[j],base[j-1]); // меняю местами

                        }
            for (int i = 0; i < playerNum;i++)
                cout << i+1 << ") "<< base[i]->getName() << ": " << base[i]->getPoints() << endl;

        } // вывод результата

    private:
        // база судей [id]
        Judge* judges[7];
        // база участников [id]
        Player* base[lmax];
        int playerNum; // Кол-во участников

};



int main(int argc, char *argv[])
{
    ifstream fin;
    fin.open("C:\\Users\\test2.txt"); //местоположение файла

    Tournament game;

    string name;

    int counter = 0; // счетчик id участников
    srand (time(NULL)); // Для рандома

    while (fin >> name){
        counter++;
        cout << counter << ") " << name << " ";

        Player* newPLayer = new Player(counter,name);
        game.regNewPlayer(newPLayer);

        for(int i = 0; i < 7; i++){
            float points;
            fin >> points; 
            points = (rand() % 60)/10.0; // Перезаписываю переменную для ранома
            game.recordMark(i,counter,points);

            cout << points << " ";
        }
        cout << endl;
    }

    game.sortJudges();
    game.countPlace();
    game.result();
    
    return 0;
}
