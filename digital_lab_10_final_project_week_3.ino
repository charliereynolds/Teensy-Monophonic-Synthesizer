#include "BetterButton.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=212,369
AudioSynthWaveform       waveform2;      //xy=214,307
AudioSynthWaveform       waveform1;      //xy=216,241
AudioMixer4              mixer1;         //xy=415,313
AudioEffectEnvelope      envelope1;      //xy=569,315
AudioOutputAnalog        dac1;           //xy=778,325
AudioConnection          patchCord1(waveform3, 0, mixer1, 2);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(waveform1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, envelope1);
AudioConnection          patchCord5(envelope1, dac1);
// GUItool: end automatically generated code
int button1Pin = 6;
int button2Pin = 7;
int button3Pin = 8;
int button4Pin = 9;
int button5Pin = 10;
int button6Pin = 11;
int button7Pin = 12;
int button8Pin = 24;
int button9Pin = 25;
int button10Pin = 26;
int button11Pin = 27;
int button12Pin = 28;

float volume1 = 0.5;
float volume2 = 0.5;

int notes[12] = { 261.63, 277.18 ,293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 493.88, 523.25};
int overtones[12] = { 261.63, 277.18 ,293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 493.88, 523.25};

int attackTime = 0;
int decayTime  = 0;
int sustainTime = 0;
int releaseTime  = 0;

BetterButton button1(button1Pin, 0);
BetterButton button2(button2Pin, 1);
BetterButton button3(button3Pin, 2);
BetterButton button4(button4Pin, 3);
BetterButton button5(button5Pin, 4);
BetterButton button6(button6Pin, 5);
BetterButton button7(button7Pin, 6);
BetterButton button8(button8Pin, 7);
BetterButton button9(button9Pin, 8);
BetterButton button10(button10Pin, 9);
BetterButton button11(button11Pin, 10);
BetterButton button12(button12Pin, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  AudioMemory(12);
  
  waveform1.begin(WAVEFORM_SINE);
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.10);
  waveform2.amplitude(0.01);
  
//  envelope1.attack(0);
//  envelope1.decay(0);
//  envelope1.sustain(1);
//  envelope1.release(500);
  
  button1.pressHandler(onPress);
  button1.releaseHandler(onRelease);
  button2.pressHandler(onPress);
  button2.releaseHandler(onRelease);
  button3.pressHandler(onPress);
  button3.releaseHandler(onRelease);
  button4.pressHandler(onPress);
  button4.releaseHandler(onRelease);
  button5.pressHandler(onPress);
  button5.releaseHandler(onRelease);
  button6.pressHandler(onPress);
  button6.releaseHandler(onRelease);
  button7.pressHandler(onPress);
  button7.releaseHandler(onRelease);
  button8.pressHandler(onPress);
  button8.releaseHandler(onRelease);
  button9.pressHandler(onPress);
  button9.releaseHandler(onRelease);
  button10.pressHandler(onPress);
  button10.releaseHandler(onRelease);
  button11.pressHandler(onPress);
  button11.releaseHandler(onRelease);
  button12.pressHandler(onPress);
  button12.releaseHandler(onRelease);
}

void loop() {
  // put your main code here, to run repeatedly:
  amplitudeReadWaveform1();
  amplitudeReadWaveform2();
  aDSR();
  button1.process();
  button2.process();
  button3.process();
  button4.process();
  button5.process();
  button6.process();
  button7.process();
  button8.process();
  button9.process();
  button10.process();
  button11.process();
  button12.process();
}


void onPress(int val) {
  Serial.print(val);
  envelope1.noteOn();
  envelope1.attack(attackTime);
  waveform1.frequency(notes[val]);
  waveform2.frequency(overtones[val]);

 
  delay(5);
  //usbMIDI.sendNoteOn(val, 127, 1);
  Serial.println("on");
  
}

void onRelease(int val) {
  Serial.print(val);
  envelope1.release(releaseTime);
//  waveform1.frequency(0);
//  waveform2.frequency(0);
  envelope1.noteOff();
  delay(5);
  //usbMIDI.sendNoteOff(val, 0, 1);
  Serial.println("off");
}


void amplitudeReadWaveform1(){
  volume1 = map(analogRead(A18), 0, 1023, 0, 500);
  waveform1.amplitude(volume1 / 1000.0);
}

void amplitudeReadWaveform2(){
  volume2 = map(analogRead(A19), 0, 1023, 0, 500);
  waveform2.amplitude(volume2 / 2000.0);
  //^^ cause saws are loud 
}

void aDSR(){
  attackTime = map(analogRead(A14), 0, 1023, 11, 5000);
  decayTime  = 0;
  sustainTime = 0;
  releaseTime  = map(analogRead(A15), 0, 1023, 0, 5000);
  envelope1.decay(1000);
  envelope1.sustain(1000);
 
 
}





//DO NOTE ON WHEN BUTTON IS TRIGGERED
//NOTE OFF when button is released


//waveform.begin changes it wherever
//void keyPressed() {
//  lastButtonState = buttonState;
//  buttonState = digitalRead(musicalKey);
//
//  if (lastButtonState == LOW and buttonState == HIGH){
//   
//  }
//  if (lastButtonState == HIGH and buttonState == LOW){
//   
//  }
//}
