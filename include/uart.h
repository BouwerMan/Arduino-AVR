#define BAUD 9600
#define UBRR (((F_CPU / (16UL * BAUD))) - 1)

namespace UART
{
    void init();
    void send(const char ch);
    void send(const char *ch);
    char recieveChar();
    char* recieveStr(unsigned int max_size);
}