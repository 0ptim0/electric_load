#include "wake.h"
#include "crc.h"

void wake::AddToBuf(uint8_t data) 
{
    buf[iter] = data;
    iter++;
}

void wake::AddToPacket(uint8_t data) 
{
    switch(data) {
        case FEND:
            AddToBuf(FESC);
            AddToBuf(TFEND);
            break;
        case FESC:
            AddToBuf(FESC);
            AddToBuf(TFESC);
            break;
        default:
            AddToBuf(data);
            break;
    }
}

void wake::TakeFromPacket(uint8_t *data) 
{
    if(buf[iter] == FESC && buf[iter + 1] == TFEND) {
        *data = FEND;
        iter = iter + 2;
    } else if(buf[iter] == FESC && buf[iter + 1] == TFESC) {
        *data = FESC;
        iter = iter + 2;
    } else {
        *data = buf[iter];
        iter++;
    }
}

void wake::PacketBoxing(wake_packet_t *packet)
{   
    iter = 0;
    buf = packet->buf;
    if(packet == nullptr) return;
    AddToBuf(FEND);
    AddToPacket(packet->to);
    AddToPacket(packet->cmd);
    AddToPacket(packet->length);
    for(int i = 0; i < packet->length; i++) {
        AddToPacket(packet->data[i]);
    }
    AddToPacket(crc8(packet->data, packet->length));
    packet->length_buf = iter;
    iter = 0;
}

void wake::PacketUnboxing(wake_packet_t *packet)
{
    iter = 0;
    buf = packet->buf;
    if(packet == nullptr) return;
    if(buf[0] != FEND) return;
    iter++;
    TakeFromPacket(&packet->to);
    TakeFromPacket(&packet->cmd);
    TakeFromPacket(&packet->length);
    for(int i = 0; i < packet->length; i++) {
        TakeFromPacket(&packet->data[i]);
    }
    uint8_t crc;
    TakeFromPacket(&crc);
    if(crc != crc8(packet->data, packet->length)) packet->err = ERROR;
    packet->length_buf = iter;
    iter = 0;
}
