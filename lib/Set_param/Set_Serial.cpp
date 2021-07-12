#include "Set_Serial.h"

Set_Serial::Set_Serial(){
    val = 0;
}

Set_Serial::~Set_Serial(){
    val = 0;
}
int16_t Set_Serial::check_error_t(uint8_t *buf, bool num){
  val = 0;
  read_val(buf);
    if (val > 300 || val < -300){
       if (!num){  return INTERVAL_T_L;}
       else return INTERVAL_T_R;
    }
    if (buf[0] == '-')
    val*=-1;
    else if (buf[0] != '+') {
    if (!num){  return SIGN_T_L;}
    else return SIGN_T_R;
    }
    return val;
}

int16_t Set_Serial::check_error_c(uint8_t *buf, bool num, uint8_t LR){
    val = 0;
    read_val(buf);
    if (buf[0] == '-')
    val*=-1;
    else if (buf[0] != '+') {
    if (!num){  return SIGN_C_P;}
       else return SIGN_C_D;
    }
    if (LR != 'L' && LR != 'l' && LR != 'R' && LR != 'r') return NOT_L_or_R;
    return val;
}

int16_t Set_Serial::check_error_f(uint8_t *buf){
    val = 0;
    read_val(buf);
    if (val >= 10000 ){
        return INTERVAL_F;
    }
   return val;
}

void Set_Serial::read_val(uint8_t *buf) {
    for(int i = 1; i < 6; ++i) {
        if(('0' <= buf[i]) && (buf[i] <= '9')) {
            val *= 10;
            val += buf[i] - '0';
        }
        else {
            val = NOT_NUM;
            return; 
        }
    }
}
int16_t Set_Serial::read_command(uint8_t *buf, uint8_t size) {
    if((buf[S] != 's') && (buf[S] != 'S')) {
        if((buf[S] != '\r') && (buf[S] != '\n')) {return START_SYMBOL;}
        return 0;
    }
   if(size < (MAX)) {return LENGTH_BYTE;}
   if((buf[MAX-1] != 'e') && (buf[MAX-1] != 'E')) {return END_SYMBOL;}
   if (buf[CMD] == 't' || buf[CMD] == 'c' || buf[CMD] == 'f')
   {
       buf[CMD] -= 32;
   }
   switch(buf[CMD]){
        case 'T':
            return 1;
        case 'C':
            return 2;
        case 'F':
            return 3;
        default:
            return NOT_CMD;
    } 
}

void Set_Serial:: read_US(){
    uint8_t buf[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int16_t val1 = 0; 
   // Serial2.readBytes(&buf[0], 12);
    for(uint8_t i = 0; i < 12; ++i) {
        for (uint8_t j = 0; j < 3; j++){
            if(('0' <= buf[i]) && (buf[i] <= '9')) {
                val1 *= 10;
                val1 += buf[i] - '0';
            }
            else break;
        } 
        if (val1 > 300) break;
        val1 = 0;
    }
    uint8_t buffer[16];
    for (uint8_t i = 0; i < 16; i++){
        buffer[i] = 0;
    }
    buffer[0] = 'S';
    buffer[1] = 'U';
    buffer[15] = 'E';
    uint8_t j=0;
    for (uint8_t i = 2; i < 14; i++){
         buffer[i] = buf[j++];
    }
    for (uint8_t i = 0; i < 16; i++){
        Serial.print(buffer[i], DEC);
    }
}
