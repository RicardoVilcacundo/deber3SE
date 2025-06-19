#line 1 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/Sonido.c"

sbit DATA_PIN_0 at RB0_bit;
sbit DATA_PIN_1 at RB1_bit;
sbit DATA_PIN_2 at RB2_bit;









void DelayNote() { Delay_ms(50); }

void Tone(unsigned int freq, unsigned int duration) {
 Sound_Play(freq, duration);
 DelayNote();
}


void Melody_Intro() {
 Tone(659, 200); Tone(659, 200); Tone(659, 200);
 Tone(523, 200); Tone(659, 200); Tone(784, 200);
 Tone(392, 400);
}


void Melody_WinLevel() {
 Tone(659, 150); Tone(784, 150); Tone(659, 150);
 Tone(784, 150); Tone(659, 150); Tone(880, 300);
}


void Melody_Lose() {
 Tone(880, 150); Tone(830, 150); Tone(784, 150);
 Tone(740, 150); Tone(698, 300); Tone(659, 300);
}


void Melody_WinGame() {
 Tone(523, 150); Tone(659, 150); Tone(784, 150); Tone(1046, 300);
 Tone(784, 150); Tone(880, 150); Tone(988, 300); Tone(1046, 300);
}


void Melody_Intro_Tetris() {
 Tone(659, 150); Tone(494, 150); Tone(523, 150); Tone(587, 150);
 Tone(523, 100); Tone(494, 100); Tone(440, 150);
 Tone(440, 100); Tone(523, 100); Tone(659, 150);
 Tone(587, 100); Tone(523, 100); Tone(494, 200);
}


void Melody_WinLevel_Sonic() {
 Tone(659, 150); Tone(784, 150); Tone(880, 200);
 Tone(784, 150); Tone(659, 300);
}


void Melody_Lose_DonkeyKong() {
 Tone(440, 300); Tone(392, 300);
 Tone(370, 300); Tone(349, 400);
}


void Melody_WinGame_Pokemon() {
 Tone(659, 100); Tone(698, 100); Tone(784, 200);
 Tone(880, 150); Tone(988, 300);
}



void main() {



 unsigned char received_audio_code;


 ANSEL = 0; ANSELH = 0;
 C1ON_bit = 0; C2ON_bit = 0;
 TRISC = 0x00;
 Sound_Init(&PORTC, 3);


 TRISB.B0 = 1;
 TRISB.B1 = 1;
 TRISB.B2 = 1;




 while (1) {

 received_audio_code = 0;


 if (DATA_PIN_0) {
 received_audio_code |= (1 << 0);
 }
 if (DATA_PIN_1) {
 received_audio_code |= (1 << 1);
 }
 if (DATA_PIN_2) {
 received_audio_code |= (1 << 2);
 }


 switch (received_audio_code) {
 case  0b001 :
 Melody_Intro();
 break;
 case  0b010 :
 Melody_Intro_Tetris();
 break;
 case  0b011 :
 Melody_WinLevel_Sonic();
 break;
 case  0b100 :
 Melody_WinGame_Pokemon();
 break;
 case  0b101 :
 Melody_Lose_DonkeyKong();
 break;
 default:

 break;
 }

 Delay_ms(50);
 }
}
