#include <iostream>
#include <string>

std::string WELLCOME_MESSAGE = u8R"(Hunt the Wumpus!

Ты в пещере с 20 комнатами, и из каждой комнаты ведут 3 туннеля.
В пещере разбросаны 3 летучие мыши и 3 ямы, а в колчане у тебя 5 особых супер стрел против злого Вумпуса. Удачи.

)";

int main()
{
    std::cout << WELLCOME_MESSAGE << '\n';
    return 0;
}
