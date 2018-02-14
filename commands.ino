#include "src/SerialCommand/SerialCommand.h"
SerialCommand sCmd;

void commands_init(){
  sCmd.addCommand("GOTO", goto_command);
  sCmd.addCommand("SPOS", setpos_command);
}
void commands_update(){
  sCmd.readSerial();
}
void goto_command() {
  mb.moveTo(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
void setpos_command() {
  mb.setPosition(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
