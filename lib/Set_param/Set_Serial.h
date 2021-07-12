#ifndef __SET_SERIAL_H__
#define __SET_SERIAL_H__

#include <Arduino.h>

#define S 0
#define CMD 1
#define WEEL 2
#define MAX 16
#define CAN_MAX 8

enum error{
    START_SYMBOL = 30000,   //стартовый символ не S/s
    NOT_CMD,                //Символ не входит в список команд
    END_SYMBOL,             //конечный символ не E/e
    LENGTH_BYTE,            //длина меньше 15 байт
    NOT_L_or_R,             //Символ не является ни одним из перечисленных  ('L' / 'l'/'R' / 'r')
    SIGN_T_L,               //Не  '-' или '+'  для левого колеса (T)
    SIGN_T_R,               //Не  '-' или '+'  для правого колеса (T)
    SIGN_C_P,               //Не  '-' или '+'  для первого коэффициента (С)
    SIGN_C_D,               //Не  '-' или '+'  для второго коэффициента (С)
    INTERVAL_T_L,           //Не входит в заданный интервал для левого колеса (T) [-300;300]
    INTERVAL_T_R,           //Не входит в заданный интервал для правого колеса (T) [-300;300]
    INTERVAL_F,             //Не входит в заданный интервал для периода отправки [50;1000]
    NOT_NUM,                //Некорректная запись (char вместо int) 
    ERR_ID                  //неверный ID
};

class Set_Serial{
    private:
    int16_t val = 0;
    uint8_t CAN_data[CAN_MAX];
    public:
    Set_Serial();
    ~Set_Serial();
    int16_t check_error_t(uint8_t *buf, bool num);
    int16_t check_error_c(uint8_t *buf, bool num, uint8_t LR);
    int16_t check_error_f(uint8_t *buf);
    int16_t read_command(uint8_t *buf, uint8_t size);
    void read_US();
    bool check_US(int16_t val);
    void read_val(uint8_t *buf);
    void print(uint8_t *data, uint32_t D);
};


#endif