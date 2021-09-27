#include "stm32_base.h"
#pragma once

#define FEND    0xC0
#define FESC    0xDB
#define TFEND   0xDC
#define TFESC   0xDD

struct wake_packet_t {
    uint8_t to;
    uint8_t cmd;
    uint8_t length;
    uint8_t *data;
    uint8_t *buf;
    uint8_t length_buf;
    uint8_t err;
};

class wake {
private:
    uint8_t *buf;
    uint8_t iter;
    void AddToBuf(uint8_t data);
    void AddToPacket(uint8_t data);
    void TakeFromPacket(uint8_t *data);
public:
    wake() : iter(0) {}
    void PacketBoxing(wake_packet_t *packet);
    void PacketUnboxing(wake_packet_t *packet);
};
