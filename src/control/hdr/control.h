#ifndef __CONTROL_H__
#define __CONTROL_H__

int SELECTED_VIEW = 0;

int key_init();
int key_run();
void key_end();
int checkControl(int menu);

void getView(int* view)
void i2c_writeByte(char byte);
char i2c_readByte();

#endif