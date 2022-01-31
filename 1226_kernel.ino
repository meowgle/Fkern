void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
kern_start();
}

void loop() {
  // put your main code here, to run repeatedly:

}

// LICENSE ----------------------------------------------------------------------------------------------------


// Copyright 2021-2022 Luther Fritsche
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// LICENSE ----------------------------------------------------------------------------------------------------




// builtin shell toggle ---------------------------------------------------------------------------------------

int kbltin = 1 ; //   0 : external shell   1 : builtin shell

// builtin shell toggle ---------------------------------------------------------------------------------------




// kernel -----------------------------------------------------------------------------------------------------




// kernel boot text -------------------------------------------------------------------------------------------

void kern_bscreen() {
Serial.println("[Fritsche Kernel]");
Serial.println("KERNEL Build 1226");
}

// kernel boot text -------------------------------------------------------------------------------------------




// kernel loop ------------------------------------------------------------------------------------------------

void kern_loop() {
kern_traffic();
}

// kernel loop ------------------------------------------------------------------------------------------------




// kernel essentials ------------------------------------------------------------------------------------------

void kern_essential() {
kern_traffic();
kern_bugchk();
}

// kernel essentials ------------------------------------------------------------------------------------------




// built in shell clear ---------------------------------------------------------------------------------------

void kern_shnl() {
if (kbltin == 0){
Serial.println(" ");
ext_sh();
}
Serial.println(" ");
Serial.print("BLTIN-SH~$");
Serial.println(" ");
}

// built in shell clear ---------------------------------------------------------------------------------------

int diskstat = diskstat;

// built in shell start ---------------------------------------------------------------------------------------

void kern_sh() {
delay(900);
if (kbltin == 0){
Serial.println("Exiting KERN_SH.......");
Serial.println("Starting EXT_SH.......");
ext_sh();
}

Serial.println("______________________________________________________________________");
Serial.println("                                                                      ");
Serial.println("Copyright 2021-2022 Luther Fritsche");
Serial.println(" ");
Serial.println("Licensed under the Apache License, Version 2.0 (the License);");
Serial.println("you may not use this file except in compliance with the License.");
Serial.println("You may obtain a copy of the License at");
Serial.println("    http://www.apache.org/licenses/LICENSE-2.0");
Serial.println(" ");
Serial.println("Unless required by applicable law or agreed to in writing, software");
Serial.println("distributed under the License is distributed on an AS IS BASIS,");
Serial.println("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.");
Serial.println("See the License for the specific language governing permissions and");
Serial.println("limitations under the License.");
Serial.println("   ");
Serial.println("BLTIN-SH~$");
kern_shl();
}

// built in shell start ---------------------------------------------------------------------------------------




// built in shell logic ---------------------------------------------------------------------------------------

void kern_shl() {
if (kbltin == 0){
ext_sh();
}
kern_exec();
if (Serial.available()){
if (Serial.read() == 'r'){
Serial.flush();
delay(100);
Serial.flush();
kern_read();
}
}
if (Serial.available()){
if (Serial.read() == 's'){
Serial.flush();
delay(100);
Serial.flush();
kern_save();
}
}
if (Serial.available()){
if (Serial.read() == 'i'){
Serial.flush();
delay(100);
Serial.flush();
kern_info();
}
}
if (Serial.available()){
if (Serial.read() == 'e'){
Serial.flush();
delay(100);
Serial.flush();
ext_sh();
}
}
kern_bugchk();
kern_traffic();
kern_shl();
}

// built in shell logic ---------------------------------------------------------------------------------------




// external shell ---------------------------------------------------------------------------------------------

void ext_sh() {
kern_save();
kern_read();
// your custom shell here
kern_essential();
ext_sh();
}

// external shell ---------------------------------------------------------------------------------------------




// kernel startpoint ------------------------------------------------------------------------------------------

void kern_start() {

kern_bscreen();
if (1 != diskstat){
Serial.println("SRAMDISK Clear.......");
}
Serial.print("Running at ");
Serial.print(kern_clockspeed());
Serial.print(" MHz.......");
Serial.println("");
Serial.println("Starting KERN_MEMTEST.......");
kern_memtest();
Serial.println("Starting KERN_SH.......");
Serial.println("Starting KERN_TRAFFIC.......");
Serial.println("Starting KERN_BUGCHK.......");
kern_sh();
}

// kernel startpoint ------------------------------------------------------------------------------------------




// kernel clockspeed ------------------------------------------------------------------------------------------

int kern_clockspeed() {
char clock1 = micros();
digitalWrite(LED_BUILTIN, HIGH);
char clock2 = micros();
delay(100);
int clockspeed = 0;
clockspeed = clock2 - clock1;
return clockspeed;
}

// kernel clockspeed ------------------------------------------------------------------------------------------




// kernel info ------------------------------------------------------------------------------------------------

void kern_info() {
int rntime = millis();
Serial.print("Fritsche Kernel ");
Serial.print("Build 1226");
Serial.print(" uptime:");
Serial.print(rntime);
Serial.print(" architecture:AVR");
kern_clockspeed();
Serial.print(" clockspeed:");
Serial.print(kern_clockspeed());
Serial.print(" MHz");
kern_shnl();
}

// kernel info ------------------------------------------------------------------------------------------------




// sram test --------------------------------------------------------------------------------------------------

void kern_memtest() {
Serial.println("TESTING RAM.......");
char test = '1';
if (test == '1'){
Serial.println("KERN_MEMTEST:OK");
  }
if (test =! '1'){
Serial.println("KERN_MEMTEST:FAIL");
Serial.println("RUNNING KERN_HALT");
kern_halt();
  }
}

// sram test ---------------------------------------------------------------------------------------------------




// bug check ---------------------------------------------------------------------------------------------------

void kern_bugchk() {
int tst1 = millis();
int clc = 1 + 1;
int tst2 = millis();
int rsptime = 0;
rsptime = tst2 - tst1;
if (rsptime >= 10){
if (rsptime >= 10){
Serial.println("                               ");
Serial.println("==[kernel bugcheck]============");
Serial.println("ERR STABLE_STATE_LOST");
Serial.println("HALTED SYSTEM TO PREVENT FURTHER");
Serial.println("DAMAGE");
Serial.println("DUMPING BUGCHK INFO");
Serial.println(rsptime);
Serial.println(clc);
Serial.println("===============================");
kern_halt();
}
}
}
// bug check ---------------------------------------------------------------------------------------------------




// serial flush ------------------------------------------------------------------------------------------------

void kern_flush() {
kern_traffic();
if (Serial.available() == '0'){
Serial.flush();
}
Serial.flush();
if (Serial.available() == '0'){
Serial.flush();
}
}
void kern_traffic() {
if (Serial.available() == '0'){
delay(800);
if (Serial.available() == '0'){
Serial.println("KERN_TRAFFIC:SERIAL DELAY");
Serial.println("KERN_TRAFFIC:FLUSHING PORT");
Serial.flush();
}
}
if (Serial.available() == '1'){
Serial.flush();
}
}
void kern_halt() {
kern_halt();
}

// serial flush -------------------------------------------------------------------------------------------------




// file creator -------------------------------------------------------------------------------------------------

void kern_save() {
Serial.println("enter file address");
Serial.flush();
kern_flush();
delay(3000);
Serial.flush();
char addr = Serial.read();
Serial.flush();
Serial.println("value:");
Serial.flush();
kern_flush();
delay(3000);
Serial.flush();
char value = Serial.read();
Serial.flush();
Serial.println("saving file into SRAMDISK..");
Serial.flush();
int {addr} = value;
Serial.flush();
Serial.println("saved as ");
Serial.println({addr});
Serial.print("Size: ");
Serial.print(sizeof({addr;}));
Serial.print(" Byte");
diskstat = 1;
kern_shnl();
}

// file creator -------------------------------------------------------------------------------------------------




// file reader --------------------------------------------------------------------------------------------------

void kern_read() {
Serial.println("enter file address");
Serial.flush();
kern_flush();
delay(3000);
Serial.flush();
char addr = Serial.read();
Serial.flush();
Serial.println("dumping contents..");
char file = {addr};
Serial.println(file);
kern_shnl();
}

// file reader --------------------------------------------------------------------------------------------------




// program execution --------------------------------------------------------------------------------------------

void kern_exec() {
  delay(700);
  if (Serial.available()){
  if (Serial.read() == '1'){
  Serial.flush();
  delay(100);
  Serial.println(1 + 1);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '2'){
  Serial.flush();
  delay(100);
  Serial.println(2 + 2);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '3'){
  Serial.flush();
  delay(100);
  Serial.println(3 + 3);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '4'){
  Serial.flush();
  delay(100);
  Serial.println(4 + 4);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '5'){
  Serial.flush();
  delay(100);
  Serial.println(5 + 5);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '6'){
  Serial.flush();
  delay(100);
  Serial.println(6 + 6);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '7'){
  Serial.flush();
  delay(100);
  Serial.println(7 + 7);
  kern_shnl();
  } 
  }
  if (Serial.available()){
  if (Serial.read() == '8'){
  Serial.flush();
  delay(100);
  Serial.println(8 + 8);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '9'){
  Serial.flush();
  delay(100);
  Serial.println(9 + 9);
  kern_shnl();
  }
  }
  if (Serial.available()){
  if (Serial.read() == '0'){
  Serial.flush();
  delay(100);
  Serial.println("0");
  kern_shnl();
  }
  }
  kern_traffic();
}

// program execution -----------------------------------------------------------------------------------------------




// kernel ----------------------------------------------------------------------------------------------------------
