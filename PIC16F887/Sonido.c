// -------------------- DECLARACIÓN DE PINES DE COMUNICACIÓN --------------------
sbit DATA_PIN_0 at RB0_bit; // Conectar a PC4 del ATMEGA
sbit DATA_PIN_1 at RB1_bit; // Conectar a PC5 del ATMEGA
sbit DATA_PIN_2 at RB2_bit; // Conectar a PC6 del ATMEGA

// Códigos esperados del ATMEGA (deben coincidir con los definidos en el ATMEGA)
#define AUDIO_INICIO_NIVEL_1_CODE    0b001
#define AUDIO_INICIO_NIVEL_2_3_CODE  0b010
#define AUDIO_VICTORIA_NIVEL_1_2_CODE 0b011
#define AUDIO_VICTORIA_NIVEL_3_CODE  0b100
#define AUDIO_DERROTA_CODE           0b101

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

// ---------- MELODÍA JUEGO COMPLETADO: Pok?mon Level Up ----------
void Melody_WinGame_Pokemon() {
   Tone(659, 100); Tone(698, 100); Tone(784, 200);
   Tone(880, 150); Tone(988, 300);
}


// -------------------- PROGRAMA PRINCIPAL --------------------
void main() {
    // ************************************************
    // Mover todas las declaraciones de variables al inicio de la función main()
    // ************************************************
    unsigned char received_audio_code; // Declaración correcta aquí

    // Configuración de puertos
    ANSEL = 0; ANSELH = 0;        // Todos los pines como digitales
    C1ON_bit = 0; C2ON_bit = 0;   // Comparadores OFF
    TRISC = 0x00;                  // RC3 como salida para el sonido
    Sound_Init(&PORTC, 3);        // Inicializar sonido en RC3

    // Configurar pines de RB0, RB1, RB2 como entradas
    TRISB.B0 = 1; // RB0 como entrada
    TRISB.B1 = 1; // RB1 como entrada
    TRISB.B2 = 1; // RB2 como entrada

    // Puedes habilitar pull-ups si es necesario, aunque con pines directamente conectados no suele ser crítico
    // OPTION_REG.B7 = 0; // Habilitar pull-ups (WPUB = 1 en cada pin si usas pull-ups individuales)

    while (1) {
        // Inicialización (o asignación) dentro del bucle o después de la declaración
        received_audio_code = 0; // Initialize to 0 at the start of each loop iteration

        // Leer el estado de los pines de comunicación
        if (DATA_PIN_0) {
            received_audio_code |= (1 << 0);
        }
        if (DATA_PIN_1) {
            received_audio_code |= (1 << 1);
        }
        if (DATA_PIN_2) {
            received_audio_code |= (1 << 2);
        }

        // Si se detecta un código, reproducir la melodía correspondiente
        switch (received_audio_code) {
            case AUDIO_INICIO_NIVEL_1_CODE:
                Melody_Intro();
                break;
            case AUDIO_INICIO_NIVEL_2_3_CODE:
                Melody_Intro_Tetris();
                break;
            case AUDIO_VICTORIA_NIVEL_1_2_CODE:
                Melody_WinLevel_Sonic();
                break;
            case AUDIO_VICTORIA_NIVEL_3_CODE:
                Melody_WinGame_Pokemon();
                break;
            case AUDIO_DERROTA_CODE:
                Melody_Lose_DonkeyKong();
                break;
            default:
                // No hay código de audio o código desconocido, no hacer nada o detener el sonido
                break;
        }

        Delay_ms(50);
    }
}