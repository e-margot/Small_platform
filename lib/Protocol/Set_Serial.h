#ifndef __SET_SERIAL_H__
#define __SET_SERIAL_H__

#include <Arduino.h>

#define CAN_MAX 8

enum error{
    START_SYMBOL = 30000,   //стартовый символ не S/s
    NOT_CMD,                //Символ не входит в список команд
    END_SYMBOL,             //конечный символ не E/e
    LENGTH_BYTES,            //длина меньше 16 байт
    NOT_L_or_R,             //Символ не является ни одним из перечисленных  ('L' / 'l'/'R' / 'r')
    SIGN_T_L,               //Не  '-' или '+'  для левого колеса (T)
    SIGN_T_R,               //Не  '-' или '+'  для правого колеса (T)
    SIGN_C_P,               //Не  '-' или '+'  для первого коэффициента (С)
    SIGN_C_D,               //Не  '-' или '+'  для второго коэффициента (С)
    INTERVAL_T_L,           //Не входит в заданный интервал для левого колеса (T) [-300;300]
    INTERVAL_T_R,           //Не входит в заданный интервал для правого колеса (T) [-300;300]
    INTERVAL_F,             //Не входит в заданный интервал для периода отправки [50;1000]
    NOT_NUM,                //Некорректная запись (не входит в интеравал ['0';'9']) 
};
enum Symbols{
    S = 0,
    CMD = 1,
    WEEL = 2,
    SET_MAX = 16
};
class Set_Serial{
    private:
    int16_t val;
    uint8_t size;
    uint8_t CAN_data[CAN_MAX];
    char* tmp;
    public:
    Set_Serial();
    ~Set_Serial();
    int16_t check_error_t(uint8_t *buf, bool num); //num - left(0) or right(1)
    int16_t check_error_c(uint8_t *buf, bool num, uint8_t LR); //num - Coeff P(0) or D(1)
    int16_t check_error_f(uint8_t *buf);
    int16_t read_command(uint8_t *buf, uint8_t size);
    bool check_US(int16_t val);
    void read_val(uint8_t *buf);
};

#endif