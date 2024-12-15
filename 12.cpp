#include <tgbot/tgbot.h> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

using namespace std;
using namespace TgBot;

struct Animal {
    std::string name;
    std::string imageUrl;
};

vector<Animal> loadAnimals() {
    return {
        {"жираф", "https://i.pinimg.com/736x/dd/0f/b1/dd0fb1f1d5624929167600e776412c79.jpg"},
        {"обезьяна", "https://irecommend.ru/sites/default/files/product-images/1992373/NjNz7Sg7XMvWBj2rVdtA.jpg"},
        {"зебра", "https://upload.wikimedia.org/wikipedia/commons/2/2e/Zebra_Standing_Appeal.jpg"},
        {"слон", "https://avatars.mds.yandex.net/i?id=4573aaf1f9f66db5382a82dd7bea29cc0e79745a-9068811-images-thumbs&n=13"}
    };
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Bot bot("7593610060:AAEmohuyXKYkpa7Wc56BFBxBMF1sURqn_Bk");

    vector<Animal> animals = loadAnimals();

    bot.getEvents().onCommand("start", &bot{
        bot.sendMessage(message->chat->id, "Привет! угадай животное. Используй команду /go, чтобы начать.");
        });

    bot.getEvents().onCommand("go", &bot, &animals{
        int correctIndex = rand() % animals.size();
        Animal correctAnimal = animals[correctIndex];

        bot.sendPhoto(message->chat->id, correctAnimal.imageUrl, "Угадай, какое это животное!");

        bot.getEvents().onMessage(&bot, correctAnimal {
            if (message->text) {
                if (message->text == correctAnimal.name) {
                    bot.sendMessage(message->chat->id, "Правильно! Это " + correctAnimal.name + "!");
                }
                else {
                    bot.sendMessage(message->chat->id, "Неправильно. Это не " + message->text + ". Попробуй еще раз!");
                }
            }
            });
        });

    bot.startPolling();

    return 0;
}
