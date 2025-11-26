#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
// #include <format>

std::mt19937 rng(std::random_device{}());

int randint(int a, int b)
{
    std::uniform_int_distribution<int> dist_int(a, b);
    return dist_int(rng);
}

std::vector<int> random_numbers(int size, int a, int b)
{
    std::vector<int> res(size);
    for (int i = 0; i < size; i++) {
        res[i] = randint(a, b);
        while (true) {
            bool is_unique = true;
            for (int j = i - 1; j >= 0; j--) {
                if (res[i] == res[j]) {
                    is_unique = false;
                    res[i] = randint(a, b);
                }
            }
            if (is_unique) break;
        }
    }
    return res;
}

namespace Messages
{

const std::string WELLCOME_MESSAGE = u8R"(Hunt the Wumpus!

Ты в пещере с 20 комнатами, и из каждой комнаты ведут 3 туннеля.
В пещере разбросаны 3 летучие мыши и 3 ямы, а в колчане у тебя 5 особых супер стрел против злого Вумпуса. Удачи.

)";

const std::string HELP_MESSAGE = u8R"(Добро пожаловать в игру «Охота на Вумпуса».

Вумпус обычно обитает в пещере из двадцати комнат, и в каждой комнате есть три тоннеля, ведущие в другие комнаты пещеры.
Однако пещеры могут отличаться в зависимости от параметров, заданных при запуске игры.

В игре есть следующие опасности для отважных искателей приключений:

- Ямы -- если вы упадёте в одну из бездонных ям, вас выкинет на противоположную сторону Земли,
         и вы окажетесь в весьма плачевном состоянии для продолжения квеста, поскольку вы мертвы.

- Летучие мыши -- как и в любой другой пещере, в пещере Вумпуса водятся летучие мыши.
                  Они немного опаснее: если вы наткнётесь на одну из их комнат,
                  они схватят вас и унесут в другое место пещеры.

- Вумпус -- если вы случайно войдёте в комнату, где находится Вумпус,
            вы обнаружите, что он с большим аппетитом относится к молодым отважным людям!

Вумпуса не беспокоят эти опасности, так как у него присоски на лапах,
и он слишком велик, чтобы летучие мыши могли его поднять. По натуре он не особо подвижен,
но если вы попытаетесь выстрелить в него и промахнётесь, есть шанс, что он сам переместится в другую комнату.

В каждом ходу вы можете либо переместиться, либо выстрелить кривой стрелой.
Переместиться — укажите команду 'm' и номер комнаты назначения.
Выстрелить — укажите команду 's' и список комнат, через которые должна пролететь смертоносная стрела. Например: m9, s8 4.

Если указанный путь для стрелы неверен, она запутается в комнате,
которую не поймёт, и случайно выберет один из тоннелей, чтобы продолжить полёт.
Вы можете случайно выстрелить себе в ногу, если будете невнимательны!
С другой стороны, если вы поразите Вумпуса — вы ВЫИГРАЛИ!

Удачи.)";

const std::string INFO_MESSAGE = u8R"(Ты в комнате {} пещеры, и у тебя осталось 5 стрел.)";

const std::string PITS_MESSAGE = u8"*вжух* (я чувствую сквозняк от каких‑то ям)";

const std::string WUMPUS_MESSAGE = u8"*нюх* (я чу́ю зло Вумпуса поблизости!)";

const std::string BATS_AROUND = u8"*шуршание* *шуршание* (должны быть летучие мыши поблизости)";

const std::string TUNNELS_MESSAGE = u8"Отсюда туннели ведут в комнаты {}, {} и {}.";

const std::string INCORRECT_ARROWS_WAY = u8R"(*тюк* Стрела не смогла найти путь из {} в {}
    Она случайно летит в комнату 17!)";

const std::string FAIL_INTO_PIT = u8R"(*AAAAUUUUGGGGHHHHHhhhhhhhhhh...*
Звук свиста и восходящий поток воздуха, когда ты входил в эту комнату пещеры,
явно не дали тебе понять о наличии бездонной ямы. У тебя уймётся много времени,
чтобы обдумать эту ошибку, пока ты падаешь на многие мили к ядру Земли.
Смотри с позитивной стороны: по крайней мере ты сможешь выяснить, был ли Жюль Верн прав...)";

const std::string ESCAPE_FROM_PIT = u8R"(Без сознательного усилия вы хватаетесь за край пещеры и удачно схватываетеся за скалистый выступ.
Под вашими ногами простираются бескрайние глубины бездонной пропасти!
Камень осыпается у вас из-под ног!)";

const std::string BATS_EVENT = u8"*шлёп* *шлёп* *шлёп* (огромные летучие мыши поднимают тебя и переносят в другую комнату!)";

const std::string DEATH_BY_WUMPUS = u8R"(«РРРР!» «хрум» «нюх» «хрум»!
К великому удовольствию Вумпуса, ты прямо шагнул ему в пасть, став одним из самых лёгких ужинов,
которых он когда-либо имел! Для тебя же это довольно неприятная смерть.
Единственное хорошее — ему так давно не чистили зубы, что ты тут же потерял сознание от вони!)";

const std::string RICOCHET = u8R"(Хрясь! Внезапная пронизывающая боль сообщает вам, что рикошет вашей безумной стрелы привёл к тому,
что она застряла в вашем боку, причиняя неимоверную агонию. Злой Вумпус, обладающий психическими силами,
замечает это и немедленно бросается к вам, не чтобы помочь, увы, а чтобы СЪЕСТЬ ВАС! (ЧАВК))";

const std::string ARROW_FLEW_CAVE = u8"Тусклый отблеск подсказывает вам, что стрела прошла через магический туннель!";

const std::string END_OF_ARROWS = u8R"(Вы оборачиваетесь и смотрите на колчан, и с тяжёлым чувством понимаете,
что только что выпустили последнюю стрелу (в переносном смысле тоже).
Почувствовав это своими психическими силами, злой Вумпус яростно прорывается через пещеру,
находит вас и с могучим *РРРАААХ* съедает вас заживо!)";

const std::string WIN_MESSAGE = u8R"(Хрясь! *стон* *грохот*

Ужасный рёв наполняет пещеру, и вы с улыбкой понимаете, что убили злого Вумпуса и выиграли игру!
Задерживаться долго не хочется, однако — Вумпус не только знаменит, но и его труп издаёт такой запах,
что одним только вдохом может погубить самого отважного искателя приключений!!)";

const std::string MOVE_WHERE = u8"\t> Куда идти? Попробуй ввести «m{}».";

const std::string SHOOT_WHERE = u8"\t> В какую комнату стрелять? Попробуй ввести «s{}».";

const std::string INCORRECT_INPUT = u8"\t> Я не понимаю. Попробуйте ввести «?» для справки.";
}

struct Cave {
    int number = 0;
    std::vector<Cave*> nearby;
    bool is_wump_here = false;
    bool is_pit_here = false;
    bool is_bats_here = false;

    explicit Cave(int num) : number(num) {}
    Cave(int num, const std::vector<Cave*>& n) : number(num), nearby(n) {}
    void attach(Cave* n);
};

class Map {
public:
    void move_to(int cave);
    void shoot_to(int cave);
    void print() const;
    Map();
private:
    Cave* current_cave = nullptr;
    Cave** all_caves = nullptr;
    Cave** gen_map();
};

void Cave::attach(Cave* n)
{
    nearby.push_back(n);
    n->nearby.push_back(this);
}

std::vector<int> get_cave_numbers()
{
    std::vector<int> nums;
    nums.reserve(20);
    for (int i = 1; i <= 20; i++) nums.push_back(i);
    std::shuffle(nums.begin(), nums.end(), rng);
    return nums;
}

Map::Map()
{
    if (all_caves) {
        for (int i = 0; i < 20; i++)
            delete all_caves[i];
        delete [] all_caves;
        all_caves = nullptr;
        current_cave = nullptr;
    }
    all_caves = gen_map();
    current_cave = all_caves[0];
}

Cave** Map::gen_map()
{
    std::vector<int> cave_nums = get_cave_numbers();
    Cave** caves = new Cave*[20];

    // создания пещер 1-5
    caves[0] = new Cave(cave_nums[0]);
    for (int i = 1; i < 5; i++) {
        caves[i] = new Cave(cave_nums[i]);
        caves[i]->attach(caves[i - 1]);
    }
    caves[4]->attach(caves[0]);

    // создание пещер 6-12
    for (int i = 5; i < 12; i++) {
        caves[i] = new Cave(cave_nums[i]);
        caves[i]->attach(caves[i - 1]);
    }
    caves[11]->attach(caves[7]);

    // создание пещер 13-20
    std::vector<int> to_be_attached{5,3,10,2,9,1,8,0};
    for (int i = 12; i < 20; i++) {
        caves[i] = new Cave(cave_nums[i]);
        caves[i]->attach(caves[i - 1]);
        caves[i]->attach(caves[to_be_attached[i - 12]]);
    }
    caves[19]->attach(caves[6]);

    // наполнение пещер
    std::vector<int> action_caves = random_numbers(5, 1, 19);
    caves[action_caves[0]]->is_wump_here = true;
    caves[action_caves[1]]->is_pit_here = true;
    caves[action_caves[2]]->is_pit_here = true;
    caves[action_caves[3]]->is_bats_here = true;
    caves[action_caves[4]]->is_bats_here = true;

    return caves;
}

void Map::print() const
{
    if (all_caves == nullptr) {
        std::cout << u8"Карта пуста.\n";
        return;
    }

    int wumpus_cave = 0;
    std::vector<int> pit_caves;
    std::vector<int> bats_caves;

    // вывод сети пещер
    for (int i = 1; i <= 20; i++) {

        std::cout << i << ":\t{";
        Cave* t = all_caves[0];
        // поиск пещеры с номером i
        for (int j = 1; j < 20; j++) {
            if (t->number == i) break;
            else t = all_caves[j];
        }
        // вывод соседей
        for (int j = 0; j < t->nearby.size(); j++) {
            std::cout << t->nearby[j]->number;
            if (j != t->nearby.size() - 1) std::cout << ", ";
        }
        std::cout << "}\n";

        // проверка пещеры на события
        if (t->is_wump_here) wumpus_cave = i;
        if (t->is_bats_here) bats_caves.push_back(i);
        if (t->is_pit_here) pit_caves.push_back(i);
    }

    // вывод расположения событий
    std::cout << u8"Wumpus находится в пещере " << wumpus_cave << '\n';
    std::cout << u8"Ямы расположены в пещерах: ";
    for (int i = 0; i < pit_caves.size(); i++) {
        std::cout << pit_caves[i];
        if (i != pit_caves.size() - 1) std::cout << ", ";
        else std::cout << '\n';
    }
    std::cout << u8"Летучие мыши расположены в пещерах: ";
    for (int i = 0; i < bats_caves.size(); i++) {
        std::cout << bats_caves[i];
        if (i != bats_caves.size() - 1) std::cout << ", ";
        else std::cout << '\n';
    }
}

int main()
{
    Map map;
    map.print();
    return 0;
}
