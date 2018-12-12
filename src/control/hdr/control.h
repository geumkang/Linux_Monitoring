#ifndef __CONTROL_H__
#define __CONTROL_H__

int key_init();
int key_run();
void key_end();
int checkControl(int menu, int view);

int* getView();
void i2c_writeByte(char byte);
char i2c_readByte();

#endif