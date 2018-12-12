#ifndef __CONTROL_H__
#define __CONTROL_H__

#define UP 4
#define DOWN 5

int key_init();
int key_run();
void key_end();
void checkControl(int *menu, int *key);

int* getView();
void i2c_writeByte(char byte);
char i2c_readByte();

#endif