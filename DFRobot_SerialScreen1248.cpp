#include "DFRobot_SerialScreen1248.h"

Stream *dbg = NULL;

DFRobot_SerialScreen1248::DFRobot_SerialScreen1248()
  :s(NULL){
      memset(sendBuf, 0, BUFSIZE);
}

DFRobot_SerialScreen1248::~DFRobot_SerialScreen1248()
{
}

bool DFRobot_SerialScreen1248::powerOn(){
    char mess[20-sizeof(sPacketHeader_t)];
    memset(mess, 0x00, sizeof(mess));
    mess[0] = 0x00;
    pPacketHeader_t header = packed(TYPE_BOOT, mess, sizeof(mess));
    if(header == NULL){
        DBG("Memory ERROR!");
        return false;
    }
    DBG("payload:");DBG((const char *)header->payload);
    sendPacket(header);
    DBG("payload:");DBG((const char *)header->payload);
    free(header);
    bootFlag = true;
    return true;
}

bool DFRobot_SerialScreen1248::shutDown(){
    char mess[20-sizeof(sPacketHeader_t)];
    memset(mess, 0x00, sizeof(mess));
    pPacketHeader_t header = packed(TYPE_SHUTDOWN, mess, sizeof(mess));
    if(header == NULL){
        DBG("Memory ERROR!");
        return false;
    }
    DBG("payload:");DBG((const char *)header->payload);
    sendPacket(header);
    DBG("payload:");DBG((const char *)header->payload);
    free(header);
    bootFlag = false;
    return true;
}

bool DFRobot_SerialScreen1248::DFRobot_SerialScreen1248::begin(Stream &s_){
    s = &s_;
    if(s == NULL){
        return false;
    }
    return true;
}

bool DFRobot_SerialScreen1248::setBrightness(eBrightLevel_t b_){
    if(!bootFlag){
        while(!powerOn()){
            delay(2);
        }
    }
    char mess[20-sizeof(sPacketHeader_t)];
    memset(mess, 0x00, sizeof(mess));
    mess[0] = b_;
    pPacketHeader_t header = packed(TYPE_BRIGHT, mess, sizeof(mess));
    if(header == NULL){
        DBG("Memory ERROR!");
        return false;
    }
    DBG("payload:");DBG((const char *)header->payload);
    sendPacket(header);
    DBG("payload:");DBG((const char *)header->payload);
    free(header);
    return true;
}

bool DFRobot_SerialScreen1248::setMoveSpeed(eSpeedLevel_t s_){
    if(!bootFlag){
        while(!powerOn()){
            delay(2);
        }
    }
    char mess[20-sizeof(sPacketHeader_t)];
    memset(mess, 0x00, sizeof(mess));
    mess[0] = s_;
    pPacketHeader_t header = packed(TYPE_SPEED, mess, sizeof(mess));
    if(header == NULL){
        DBG("Memory ERROR!");
        return false;
    }
    DBG("payload:");DBG((const char *)header->payload);
    sendPacket(header);
    DBG("payload:");DBG((const char *)header->payload);
    free(header);
    return true;
}
bool DFRobot_SerialScreen1248::disChiCharacter(eMoveMode_t m_, eColorMode_t c_, const unsigned char *message_, uint16_t len_){
    if(len_ < 1){
        return false;
    }
    if(len_ > BUFSIZE){
        len_ = BUFSIZE;
    }
    if(!bootFlag){
        powerOn();
    }
    uint16_t len = 0;
    moveMode = m_;
    color = c_;
    sig_H = (len_/12)*8;
    firstFrameData();
    char mess[512];
    memset(mess, 0, sizeof(mess));
    mess[0] = 0x00;
    switch(priColor){
        case 0x01:
                len = len_ + 3;
                memcpy((mess+1), message_, len_);
                break;
        case 0x03:
                len = len_*3+2+1;
                int j = 0;
                for(int i = 2; i >= 0; i--){
                    if(((color >> i)&0x01) == 0x01){
                        memcpy((mess+1+(2-i)*len_), message_, len_);
                        j += len_;
                    }
                }
                break;
    }
    mess[len-2] = getCs(mess, len);
    mess[len-1] = '\0';
    sendMessage(mess, len);
    return true;
}
bool DFRobot_SerialScreen1248::disString(eMoveMode_t m_, eColorMode_t c_,const unsigned char *message_, uint16_t len_){
    if(len_ < 1){
        return false;
    }
    if(len_ > 42){
        len_ = 42;
    }
    length = len_;
    offset = 0;
    unsigned char s[length];
    unsigned char mess[50];
    memset(sendBuf, 0, sizeof(sendBuf));
    memset(mess, 0, sizeof(mess));
    memcpy(mess, message_, length);
    for(uint16_t n = 0; n < FONTSIZE; n++){
        offset = n;
        for(uint16_t i = 0; i < len_; i++){
            s[i] = findCharacter(mess[i]);
        }
        conversion(s, len_);
        memcpy((sendBuf+(n*length)), s, length);
        memset(s, 0, len_);
    }
    offset = 0;
    disChiCharacter(m_, c_, sendBuf, length*FONTSIZE);
    length = 0;
    return true;
}

void DFRobot_SerialScreen1248::setFullScreenColor(eColorMode_t color_){
    uint16_t len = 72*3+3;
    color = color_;
    priColor = 0x03;
    sig_H = 0x30;
    moveMode = eMove_hold;
    firstFrameData();
    char mess[512];
    memset(mess, 0, sizeof(mess));
    mess[0] = 0x00;
    priColor = 0x03;
    for(int i = 2; i >= 0; i--){
        if(((color >> i)&0x01) == 0x01){
            memset((mess+1+(2-i)*72), 0xFF,72);
        }
    }
    mess[len-2] = getCs(mess, len);
    mess[len-1] = '\0';
    delay(50);
    sendMessage(mess, len);
}

pPacketHeader_t DFRobot_SerialScreen1248::packed(uint8_t type, const char *pay_, uint16_t len){
    DBG(sizeof(sPacketHeader_t));
    pPacketHeader_t header;
    if((header = (pPacketHeader_t)malloc(sizeof(sPacketHeader_t)+len+1)) == NULL){
            DBG("Memory ERROR");
            return NULL;
        }
    header->head.head1 = 0x58; //X
    header->head.head2 = 0x43; //C
    header->head.head3 = 0x31; //1
    header->head.head4 = 0x38; //8
    header->type = type;
    length = len;
    memcpy((char *)header->payload, pay_, len);
    header->payload[len] = getCs(header);
    header->payload[len+1] = '\0';
    DBG("payload: ");DBG((char *)header->payload);
    return header;
}

uint8_t DFRobot_SerialScreen1248::getCs(pPacketHeader_t header){
    uint8_t cs = header->type;;
    for(uint16_t i = 0; i < length; i++){
        cs ^= header->payload[i];
        DBG("biao: ");DBG(i);DBG(header->payload[i], HEX);
    }
    DBG(cs, HEX);
    return cs;
}
uint8_t DFRobot_SerialScreen1248::getCs(char *m_, uint16_t len_){
    uint8_t cs = 0;
    for(uint16_t i = 1; i < len_-2; i++){
        cs ^=m_[i];
    }
    return cs;
}

bool DFRobot_SerialScreen1248::firstFrameData(){
    char mess[40-sizeof(sPacketHeader_t)] = {0x0C, 0x00, (char)sig_H, (char)priColor, (char)list, 0x00, (char)moveMode};
    memset(mess+7, 0x00, sizeof(mess)-7);
    pPacketHeader_t header = packed(TYPE_DATA, mess, sizeof(mess));
    if(header == NULL){
        DBG("Memory ERROR!");
        return false;
    }
    DBG("payload:");DBG((const char *)header->payload);
    sendPacket(header);
    DBG("payload:");DBG((const char *)header->payload);
    free(header);
    return true;
}

void DFRobot_SerialScreen1248::sendPacket(pPacketHeader_t header){
    DBG("head1:");DBG(header->head.head1,HEX);
    DBG("head2:");DBG(header->head.head2,HEX);
    DBG("head3:");DBG(header->head.head3,HEX);
    DBG("head4:");DBG(header->head.head4,HEX);
    DBG("type: ");DBG(header->type,HEX);
    s->write((uint8_t *)header, length + sizeof(sPacketHeader_t));
    delay(100);
}
void DFRobot_SerialScreen1248::sendMessage(char *m_, uint16_t len_){
    s->write((uint8_t *)m_, len_);
    delay(100);
}

unsigned char DFRobot_SerialScreen1248::findCharacter(char c_){
    if(c_ < 0x20 || c_ > 0x7E){
        return false;
    }
    uint16_t index = ((c_ - 0x20)*FONTSIZE);
    return font6_12[index+offset];
}

void DFRobot_SerialScreen1248::conversion(unsigned char *s_, uint16_t len_){
    unsigned char mess[len_];
    memcpy(mess, s_, len_);
    uint16_t n = 0;
    if((len_*FONTWIDTH)%FONTBYTE == 0){
        n = (len_*FONTWIDTH)/FONTBYTE;
    }else{
        n = (len_*FONTWIDTH)/FONTBYTE + 1;
    }
    for(uint16_t i = 1; i <= n; i++){
        uint16_t indexStart = (i-1)*FONTBYTE;
        uint16_t indexEnd = i*FONTBYTE;
        uint16_t index = 1;
        for(uint16_t j = index; j <= len_; j++){
            if(((((j - 1) * FONTWIDTH) <= indexStart) &&(j*FONTWIDTH > indexStart))){
                mess[i-1] = (mess[j-1] << (FONTWIDTH-(j*FONTWIDTH - indexStart)));
            }
            if(((((j - 1) * FONTWIDTH) < indexEnd) &&(j*FONTWIDTH >= indexEnd))){
                mess[i-1] |= (mess[j-1] >> (FONTBYTE - (indexEnd - ((j - 1) * FONTWIDTH))));
                index = j;
                break;
            }
        }
    }
    memcpy(s_, mess, n);
    length = n;
}