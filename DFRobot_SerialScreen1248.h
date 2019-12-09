#ifndef __DFROBOT_SERIALSCREEN1248_H
#define __DFROBOT_SERIALSCREEN1248_H
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <font_6x12.h>
#if 0
#define DBG(...) if(dbg) {dbg->print("["); dbg->print(__FUNCTION__); dbg->print("(): "); dbg->print(__LINE__); dbg->print(" ] "); dbg->println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define BUFSIZE   512

#define TYPE_SHUTDOWN     0X00
#define TYPE_BOOT         0X01
#define TYPE_DATA         0X03
#define TYPE_LIST         0X04
#define TYPE_SPEED        0X05
#define TYPE_BRIGHT       0x06
#define FONTSIZE          12
#define FONTWIDTH         6
#define FONTBYTE          8
#ifndef pgm_read_byte
 #define pgm_read_byte(addr)  (*(const unsigned char *)(addr))
#endif
#ifndef pgm_read_word
 #define pgm_read_word(addr)  (*(const unsigned short *)(addr))
#endif
#ifndef pgm_read_dword
 #define pgm_read_dword(addr)  (*(const unsigned long *)(addr))
#endif


extern Stream *dbg;

typedef struct{
    uint8_t head1;
    uint8_t head2;
    uint8_t head3;
    uint8_t head4;
}__attribute__ ((packed)) sHeader_t, *pHeader_t;

typedef struct{
    sHeader_t  head;
    uint8_t type;//shutdown/boot/speed/speed/data(english chinese)
    uint8_t payload[0];
    uint8_t cs;
}__attribute__ ((packed)) sPacketHeader_t, *pPacketHeader_t;

typedef enum{
    ON = 0x01,
    OFF = 0x00
}ePowerState_t;

typedef enum{
    success = 0x53,
    fail = 0x45
}eReValue_t;

typedef enum{
    eMove_left = 0x01,
    eMove_right = 0x02,
    eMove_hold = 0x03,
    eMove_up = 0x05,
    eMove_down = 0x06,
    eMove_flash = 0x07,
    eMove_marquee = 0x08//Marquee
}eMoveMode_t;

typedef enum{
    eColor_red = 0x04,
    eColor_yellow = 0x06,
    eColor_green = 0x02,
    eColor_cyan = 0x03,
    eColor_blue = 0x01,
    eColor_purple = 0x05,
    eColor_white = 0x07,
}eColorMode_t;

typedef enum{
    eBrightLevel_1 = 0x01,
    eBrightLevel_2 = 0x02,
    eBrightLevel_3 = 0x03,
    eBrightLevel_4 = 0x04,
    eBrightLevel_5 = 0x05,
    eBrightLevel_6 = 0x06,
    eBrightLevel_7 = 0x07,
    eBrightLevel_8 = 0x08
}eBrightLevel_t;

typedef enum{
    eSpeedLevel_1 = 0x01,
    eSpeedLevel_2 = 0x02,
    eSpeedLevel_3 = 0x03,
    eSpeedLevel_4 = 0x04,
    eSpeedLevel_5 = 0x05,
    eSpeedLevel_6 = 0x06,
    eSpeedLevel_7 = 0x07,
    eSpeedLevel_8 = 0x08
}eSpeedLevel_t;

class DFRobot_SerialScreen1248{
public:
    DFRobot_SerialScreen1248();
    ~DFRobot_SerialScreen1248();
    void setDbgSerial(Stream &s_){dbg = &s_;}
    bool begin(Stream &s_);
    bool powerOn();
    bool shutDown();
    bool setBrightness(eBrightLevel_t b_);
    bool setMoveSpeed(eSpeedLevel_t s_);
    bool disChiCharacter(eMoveMode_t m_, eColorMode_t c_,const unsigned char *message_, uint16_t len_);
    bool disString(eMoveMode_t m_, eColorMode_t c_,const unsigned char *message_, uint16_t len_);
    void setFullScreenColor(eColorMode_t color_);
protected:
    pPacketHeader_t packed(uint8_t type, const char *pay_, uint16_t len);
    uint8_t getCs(pPacketHeader_t header);
    uint8_t getCs(char *m_, uint16_t len_);
    bool firstFrameData();
    void sendPacket(pPacketHeader_t header);
    void sendMessage(char *m_, uint16_t len_);
    unsigned char findCharacter(char c_);
    void conversion(unsigned char *s_, uint16_t len_);
private:
    Stream *s;
    bool bootFlag = true;  //false: shut down  true:booted
    bool chineseFlag = true; //false:English true:chinese
    uint16_t length = 0;
    uint8_t sig_H = 0x08;
    uint8_t priColor = 0x03;
    uint8_t list = 0x01;
    eMoveMode_t moveMode = eMove_hold;
    eColorMode_t color = eColor_blue;
    unsigned char sendBuf[BUFSIZE];
    uint16_t offset = 0;
};
#endif