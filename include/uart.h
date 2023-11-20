#define BAUD 9600
#define UBRR (((F_CPU / (16UL * BAUD))) - 1)

namespace UART
{
    void init();
    char recieve();
    void send(char ch);
}