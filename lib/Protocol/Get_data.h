#include <Arduino.h>
#define ERR_ID 30013                 //неверный ID при передаче по CAN-шине

enum Symbol{
    US_MAX = 1, //поля данных
    IR_MAX = 8, //поля данных
    R_MAX = 1, //fields of data for rapidity (Left/Right)
    SERIAL_US = 4, //служебные поля
    SERIAL_IR = 3, //служебные поля
    SERIAL_R = 4 //сдужебные поля
};
enum ID_CAN{
    ID_R = 9,
    ID_IR = 10,
    ID_US_F = 11,
    ID_US_B = 12,
    ID_US_L = 13,
    ID_US_R = 14,
};

class Get_data{
    private: 
    char* tmp;
    public:
    Get_data();
    ~Get_data();
    void print(uint8_t *data, uint32_t ID);
    void print(int32_t data, uint32_t ID);
    void format_byte(uint8_t *data, uint8_t len, uint8_t size);
    void format_byte(int32_t data, uint8_t len, uint8_t size);
};