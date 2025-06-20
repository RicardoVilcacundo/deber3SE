// -------------------- DECLARACIÓN DE FUNCIONES --------------------
void DelayNote() { Delay_ms(50); }

void Tone(unsigned int freq, unsigned int duration) {
   Sound_Play(freq, duration);
   DelayNote();
}

// ---------- MELODÍA 1: INICIO (Super Mario Bros adaptado) ----------
void Melody_Intro() {
   Tone(659, 200); Tone(659, 200); Tone(659, 200);
   Tone(523, 200); Tone(659, 200); Tone(784, 200);
   Tone(392, 400);
}

// ---------- MELODÍA 2: GANASTE NIVEL (Zelda) ----------
void Melody_WinLevel() {
   Tone(659, 150); Tone(784, 150); Tone(659, 150);
   Tone(784, 150); Tone(659, 150); Tone(880, 300);
}

// ---------- MELODÍA 3: DERROTA (Pac-Man muerte) ----------
void Melody_Lose() {
   Tone(880, 150); Tone(830, 150); Tone(784, 150);
   Tone(740, 150); Tone(698, 300); Tone(659, 300);
}

// ---------- MELODÍA 4: JUEGO COMPLETADO (Final Fantasy Victory) ----------
void Melody_WinGame() {
   Tone(523, 150); Tone(659, 150); Tone(784, 150); Tone(1046, 300);
   Tone(784, 150); Tone(880, 150); Tone(988, 300); Tone(1046, 300);
}

// ---------- MELODÍA INICIO: Tetris Type A ----------
void Melody_Intro_Tetris() {
   Tone(659, 150); Tone(494, 150); Tone(523, 150); Tone(587, 150);
   Tone(523, 100); Tone(494, 100); Tone(440, 150);
   Tone(440, 100); Tone(523, 100); Tone(659, 150);
   Tone(587, 100); Tone(523, 100); Tone(494, 200);
}

// ---------- MELODÍA VICTORIA: Sonic Stage Clear ----------
void Melody_WinLevel_Sonic() {
   Tone(659, 150); Tone(784, 150); Tone(880, 200);
   Tone(784, 150); Tone(659, 300);
}

// ---------- MELODÍA DERROTA: Donkey Kong Game Over ----------
void Melody_Lose_DonkeyKong() {
   Tone(440, 300); Tone(392, 300);
   Tone(370, 300); Tone(349, 400);
}

// ---------- MELODÍA JUEGO COMPLETADO: Pokémon Level Up ----------
void Melody_WinGame_Pokemon() {
   Tone(659, 100); Tone(698, 100); Tone(784, 200);
   Tone(880, 150); Tone(988, 300);
}


// -------------------- PROGRAMA PRINCIPAL --------------------
void main() {
   // Configuración de puertos
   ANSEL = 0; ANSELH = 0;        // Todos los pines como digitales
   C1ON_bit = 0; C2ON_bit = 0;   // Comparadores OFF
   TRISC = 0x00;                 // RC3 como salida
   Sound_Init(&PORTC, 3);        // Inicializar sonido en RC3

   while (1) {
         Melody_Intro();
         Delay_ms(2000);
         Melody_WinLevel();
         Delay_ms(2000);
         Melody_Lose();
         Delay_ms(2000);
         Melody_WinGame();
         Delay_ms(2000);
   }
}



