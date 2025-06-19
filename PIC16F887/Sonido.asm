
_DelayNote:

;Sonido.c,14 :: 		void DelayNote() { Delay_ms(50); }
	MOVLW      130
	MOVWF      R12+0
	MOVLW      221
	MOVWF      R13+0
L_DelayNote0:
	DECFSZ     R13+0, 1
	GOTO       L_DelayNote0
	DECFSZ     R12+0, 1
	GOTO       L_DelayNote0
	NOP
	NOP
L_end_DelayNote:
	RETURN
; end of _DelayNote

_Tone:

;Sonido.c,16 :: 		void Tone(unsigned int freq, unsigned int duration) {
;Sonido.c,17 :: 		Sound_Play(freq, duration);
	MOVF       FARG_Tone_freq+0, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+0
	MOVF       FARG_Tone_freq+1, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+1
	MOVF       FARG_Tone_duration+0, 0
	MOVWF      FARG_Sound_Play_duration_ms+0
	MOVF       FARG_Tone_duration+1, 0
	MOVWF      FARG_Sound_Play_duration_ms+1
	CALL       _Sound_Play+0
;Sonido.c,18 :: 		DelayNote();
	CALL       _DelayNote+0
;Sonido.c,19 :: 		}
L_end_Tone:
	RETURN
; end of _Tone

_Melody_Intro:

;Sonido.c,22 :: 		void Melody_Intro() {
;Sonido.c,23 :: 		Tone(659, 200); Tone(659, 200); Tone(659, 200);
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,24 :: 		Tone(523, 200); Tone(659, 200); Tone(784, 200);
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,25 :: 		Tone(392, 400);
	MOVLW      136
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      144
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,26 :: 		}
L_end_Melody_Intro:
	RETURN
; end of _Melody_Intro

_Melody_WinLevel:

;Sonido.c,29 :: 		void Melody_WinLevel() {
;Sonido.c,30 :: 		Tone(659, 150); Tone(784, 150); Tone(659, 150);
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,31 :: 		Tone(784, 150); Tone(659, 150); Tone(880, 300);
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      112
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,32 :: 		}
L_end_Melody_WinLevel:
	RETURN
; end of _Melody_WinLevel

_Melody_Lose:

;Sonido.c,35 :: 		void Melody_Lose() {
;Sonido.c,36 :: 		Tone(880, 150); Tone(830, 150); Tone(784, 150);
	MOVLW      112
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      62
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,37 :: 		Tone(740, 150); Tone(698, 300); Tone(659, 300);
	MOVLW      228
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      186
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,38 :: 		}
L_end_Melody_Lose:
	RETURN
; end of _Melody_Lose

_Melody_WinGame:

;Sonido.c,41 :: 		void Melody_WinGame() {
;Sonido.c,42 :: 		Tone(523, 150); Tone(659, 150); Tone(784, 150); Tone(1046, 300);
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      22
	MOVWF      FARG_Tone_freq+0
	MOVLW      4
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,43 :: 		Tone(784, 150); Tone(880, 150); Tone(988, 300); Tone(1046, 300);
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      112
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      220
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      22
	MOVWF      FARG_Tone_freq+0
	MOVLW      4
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,44 :: 		}
L_end_Melody_WinGame:
	RETURN
; end of _Melody_WinGame

_Melody_Intro_Tetris:

;Sonido.c,47 :: 		void Melody_Intro_Tetris() {
;Sonido.c,48 :: 		Tone(659, 150); Tone(494, 150); Tone(523, 150); Tone(587, 150);
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      238
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      75
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,49 :: 		Tone(523, 100); Tone(494, 100); Tone(440, 150);
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      238
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      184
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,50 :: 		Tone(440, 100); Tone(523, 100); Tone(659, 150);
	MOVLW      184
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,51 :: 		Tone(587, 100); Tone(523, 100); Tone(494, 200);
	MOVLW      75
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      11
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      238
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,52 :: 		}
L_end_Melody_Intro_Tetris:
	RETURN
; end of _Melody_Intro_Tetris

_Melody_WinLevel_Sonic:

;Sonido.c,55 :: 		void Melody_WinLevel_Sonic() {
;Sonido.c,56 :: 		Tone(659, 150); Tone(784, 150); Tone(880, 200);
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      112
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,57 :: 		Tone(784, 150); Tone(659, 300);
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,58 :: 		}
L_end_Melody_WinLevel_Sonic:
	RETURN
; end of _Melody_WinLevel_Sonic

_Melody_Lose_DonkeyKong:

;Sonido.c,61 :: 		void Melody_Lose_DonkeyKong() {
;Sonido.c,62 :: 		Tone(440, 300); Tone(392, 300);
	MOVLW      184
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      136
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,63 :: 		Tone(370, 300); Tone(349, 400);
	MOVLW      114
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      93
	MOVWF      FARG_Tone_freq+0
	MOVLW      1
	MOVWF      FARG_Tone_freq+1
	MOVLW      144
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,64 :: 		}
L_end_Melody_Lose_DonkeyKong:
	RETURN
; end of _Melody_Lose_DonkeyKong

_Melody_WinGame_Pokemon:

;Sonido.c,67 :: 		void Melody_WinGame_Pokemon() {
;Sonido.c,68 :: 		Tone(659, 100); Tone(698, 100); Tone(784, 200);
	MOVLW      147
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      186
	MOVWF      FARG_Tone_freq+0
	MOVLW      2
	MOVWF      FARG_Tone_freq+1
	MOVLW      100
	MOVWF      FARG_Tone_duration+0
	MOVLW      0
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      16
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      200
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,69 :: 		Tone(880, 150); Tone(988, 300);
	MOVLW      112
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      150
	MOVWF      FARG_Tone_duration+0
	CLRF       FARG_Tone_duration+1
	CALL       _Tone+0
	MOVLW      220
	MOVWF      FARG_Tone_freq+0
	MOVLW      3
	MOVWF      FARG_Tone_freq+1
	MOVLW      44
	MOVWF      FARG_Tone_duration+0
	MOVLW      1
	MOVWF      FARG_Tone_duration+1
	CALL       _Tone+0
;Sonido.c,70 :: 		}
L_end_Melody_WinGame_Pokemon:
	RETURN
; end of _Melody_WinGame_Pokemon

_main:

;Sonido.c,74 :: 		void main() {
;Sonido.c,81 :: 		ANSEL = 0; ANSELH = 0;        // Todos los pines como digitales
	CLRF       ANSEL+0
	CLRF       ANSELH+0
;Sonido.c,82 :: 		C1ON_bit = 0; C2ON_bit = 0;   // Comparadores OFF
	BCF        C1ON_bit+0, BitPos(C1ON_bit+0)
	BCF        C2ON_bit+0, BitPos(C2ON_bit+0)
;Sonido.c,83 :: 		TRISC = 0x00;                  // RC3 como salida para el sonido
	CLRF       TRISC+0
;Sonido.c,84 :: 		Sound_Init(&PORTC, 3);        // Inicializar sonido en RC3
	MOVLW      PORTC+0
	MOVWF      FARG_Sound_Init_snd_port+0
	MOVLW      3
	MOVWF      FARG_Sound_Init_snd_pin+0
	CALL       _Sound_Init+0
;Sonido.c,87 :: 		TRISB.B0 = 1; // RB0 como entrada
	BSF        TRISB+0, 0
;Sonido.c,88 :: 		TRISB.B1 = 1; // RB1 como entrada
	BSF        TRISB+0, 1
;Sonido.c,89 :: 		TRISB.B2 = 1; // RB2 como entrada
	BSF        TRISB+0, 2
;Sonido.c,94 :: 		while (1) {
L_main1:
;Sonido.c,96 :: 		received_audio_code = 0; // Initialize to 0 at the start of each loop iteration
	CLRF       main_received_audio_code_L0+0
;Sonido.c,99 :: 		if (DATA_PIN_0) {
	BTFSS      RB0_bit+0, BitPos(RB0_bit+0)
	GOTO       L_main3
;Sonido.c,100 :: 		received_audio_code |= (1 << 0);
	BSF        main_received_audio_code_L0+0, 0
;Sonido.c,101 :: 		}
L_main3:
;Sonido.c,102 :: 		if (DATA_PIN_1) {
	BTFSS      RB1_bit+0, BitPos(RB1_bit+0)
	GOTO       L_main4
;Sonido.c,103 :: 		received_audio_code |= (1 << 1);
	BSF        main_received_audio_code_L0+0, 1
;Sonido.c,104 :: 		}
L_main4:
;Sonido.c,105 :: 		if (DATA_PIN_2) {
	BTFSS      RB2_bit+0, BitPos(RB2_bit+0)
	GOTO       L_main5
;Sonido.c,106 :: 		received_audio_code |= (1 << 2);
	BSF        main_received_audio_code_L0+0, 2
;Sonido.c,107 :: 		}
L_main5:
;Sonido.c,110 :: 		switch (received_audio_code) {
	GOTO       L_main6
;Sonido.c,111 :: 		case AUDIO_INICIO_NIVEL_1_CODE:
L_main8:
;Sonido.c,112 :: 		Melody_Intro();
	CALL       _Melody_Intro+0
;Sonido.c,113 :: 		break;
	GOTO       L_main7
;Sonido.c,114 :: 		case AUDIO_INICIO_NIVEL_2_3_CODE:
L_main9:
;Sonido.c,115 :: 		Melody_Intro_Tetris();
	CALL       _Melody_Intro_Tetris+0
;Sonido.c,116 :: 		break;
	GOTO       L_main7
;Sonido.c,117 :: 		case AUDIO_VICTORIA_NIVEL_1_2_CODE:
L_main10:
;Sonido.c,118 :: 		Melody_WinLevel_Sonic();
	CALL       _Melody_WinLevel_Sonic+0
;Sonido.c,119 :: 		break;
	GOTO       L_main7
;Sonido.c,120 :: 		case AUDIO_VICTORIA_NIVEL_3_CODE:
L_main11:
;Sonido.c,121 :: 		Melody_WinGame_Pokemon();
	CALL       _Melody_WinGame_Pokemon+0
;Sonido.c,122 :: 		break;
	GOTO       L_main7
;Sonido.c,123 :: 		case AUDIO_DERROTA_CODE:
L_main12:
;Sonido.c,124 :: 		Melody_Lose_DonkeyKong();
	CALL       _Melody_Lose_DonkeyKong+0
;Sonido.c,125 :: 		break;
	GOTO       L_main7
;Sonido.c,126 :: 		default:
L_main13:
;Sonido.c,128 :: 		break;
	GOTO       L_main7
;Sonido.c,129 :: 		}
L_main6:
	MOVF       main_received_audio_code_L0+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_main8
	MOVF       main_received_audio_code_L0+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_main9
	MOVF       main_received_audio_code_L0+0, 0
	XORLW      3
	BTFSC      STATUS+0, 2
	GOTO       L_main10
	MOVF       main_received_audio_code_L0+0, 0
	XORLW      4
	BTFSC      STATUS+0, 2
	GOTO       L_main11
	MOVF       main_received_audio_code_L0+0, 0
	XORLW      5
	BTFSC      STATUS+0, 2
	GOTO       L_main12
	GOTO       L_main13
L_main7:
;Sonido.c,131 :: 		Delay_ms(50);
	MOVLW      130
	MOVWF      R12+0
	MOVLW      221
	MOVWF      R13+0
L_main14:
	DECFSZ     R13+0, 1
	GOTO       L_main14
	DECFSZ     R12+0, 1
	GOTO       L_main14
	NOP
	NOP
;Sonido.c,132 :: 		}
	GOTO       L_main1
;Sonido.c,133 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
