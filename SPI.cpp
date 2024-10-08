Code1:
Program (Master)

#include “mbed.h”
SPI spi(PB_15,PB_14,PB_13);
DigitalOut cs(PB_12);
Serial pc(USBTX,USBRX);
int main(){
char send_val;
pc.printf(“Press any key to start…\n”);
while(1){
send_val=pc.getc();
pc.printf(“%c”,send_val);
cs=0;
spi.write(send_val);
cs=1;
wait(0.01);
}
}

Program (Slave)

#include “mbed.h”
SPISlave spi(PB_15,PB_14,PB_13,PB_12);
Serial pc(USBTX,USBRX);
Char recd_val;
int main(){
pc.printf(“Received word is…\n”);
while(1){
if(spi.receive()){
recd_val=spi.read();
pc.printf(“%c”,recd_val);
}
}
}

Code2:

Program (Master)

#include “mbed.h”
SPI ser_port(PB_15,PB_14,PB_13);
Digitalout led(PC_8);
DigitalIn switch_ip(PC_4);
DigitalOut cs(PB_12);
char switch_word;
char recd_val;
int main()
{
while(1)
{
switch_word=0xa0;
if(switch_ip==1)
switch_word=switch_word|0x01;
cs=0;
recd_val=ser_port.write(switch_word);
cs=1;
wait(0.01);
led=0;
recd_val=recd_val&0x01;
if(recd_val==1)
led=1;
}
}

Program (Slave)

#include “mbed.h”
SPISlave ser_port(PB_15,PB_14,PB_13,PB_12);
DigitalOut led(PC_8);
DigitalIn switch_ip(PC_4);
char recd_val;
int main()
{
while(1) 
{
switch_word=0xa0;
if(switch_ip==1)
switch_word=switch_word|0x01;
if(ser_port.receive())
{
recd_val=ser_port.read();
ser_port.reply(switch_word);
}
led=0;
recd_val=recd_val&0x01;
if(recd_val==1)
led=1;
}
}


