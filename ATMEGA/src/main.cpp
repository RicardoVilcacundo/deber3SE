#define F_CPU 8000000UL // Frecuencia del CPU a 8 MHz
#include <avr/io.h>
#include <util/delay.h>

// Botones (Pines de entrada con pull-ups internos activados)
#define BTN_IZQ PC0
#define BTN_DER PC1
#define BTN_ARR PC2
#define BTN_ABA PC3

// LEDs de estado (Pines de salida)
#define PIN_ENTRADA PD6
#define PIN_META    PD7

// Pines de comunicación con el PIC para el audio (Pines de salida)
// Conectar PC4 del ATMEGA a RB0 del PIC
// Conectar PC5 del ATMEGA a RB1 del PIC
// Conectar PC6 del ATMEGA a RB2 del PIC
#define AUDIO_PIN_0 PC4
#define AUDIO_PIN_1 PC5
#define AUDIO_PIN_2 PC6

// Códigos para las melodías que se enviarán al PIC
// Estos valores deben coincidir con los #define en el código del PIC
#define AUDIO_INICIO_NIVEL_1        0b001 // Melody_Intro() o similar
#define AUDIO_INICIO_NIVEL_2_3      0b010 // Melody_Intro_Tetris() o similar
#define AUDIO_VICTORIA_NIVEL_1_2    0b011 // Melody_WinLevel_Sonic() o similar
#define AUDIO_VICTORIA_NIVEL_3      0b100 // Melody_WinGame_Pokemon() o similar
#define AUDIO_DERROTA               0b101 // Melody_Lose_DonkeyKong() o similar


// Variables del juego
uint8_t jugador_x = 5;
uint8_t jugador_y = 0;

// Meta final (cambia en nivel 3)
uint8_t meta_x = 2;
uint8_t meta_y = 7;

// Nivel actual y timer
uint8_t nivel_actual = 1;
uint16_t tiempo_restante = 0;

// Laberintos
const uint8_t laberinto_nivel1[8] = {
    0b10001111, 0b10000001, 0b10000001, 0b10000001,
    0b10000001, 0b10000001, 0b10000001, 0b11110001
};
const uint8_t laberinto_nivel2[8] = {
    0b10001111, 0b10000001, 0b10101101, 0b10101101,
    0b10000001, 0b10110001, 0b10110001, 0b11110001
};
const uint8_t laberinto_nivel3[8] = {
    0b10001111, 0b11010001, 0b11000101, 0b11111101,
    0b10000001, 0b11011111, 0b10000001, 0b11110001
};

// Mapeo de filas para la pantalla 8x8 (multiplexación)
const uint8_t filas[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

// --- Prototipos de funciones (buena práctica) ---
void init_ports(void);
const uint8_t* obtener_laberinto(void);
uint8_t es_pared(uint8_t x, uint8_t y);
void mostrar_laberinto(uint8_t incluir_jugador);
void mostrar_victoria(void);
void mostrar_derrota(void);
void mover_jugador(void);
void actualizar_led_estado(void);
void siguiente_nivel(void);
void enviar_audio_pic(uint8_t codigo_audio);


// --- Implementación de Funciones ---

// Inicialización de puertos
void init_ports() {
    // Puerto D y B como salidas para la pantalla (filas y columnas)
    DDRD = 0xFF;
    DDRB = 0xFF;

    // Puerto C: Botones como entradas con pull-ups activados
    // PC0, PC1, PC2, PC3 como entradas
    DDRC &= ~((1<<BTN_IZQ)|(1<<BTN_DER)|(1<<BTN_ARR)|(1<<BTN_ABA));
    // Activar pull-ups internos para los botones
    PORTC |= (1<<BTN_IZQ)|(1<<BTN_DER)|(1<<BTN_ARR)|(1<<BTN_ABA);

    // Puerto C: Pines de comunicación con el PIC como salidas
    // PC4, PC5, PC6 como salidas
    DDRC |= (1 << AUDIO_PIN_0) | (1 << AUDIO_PIN_1) | (1 << AUDIO_PIN_2);
    // Asegurarse de que estén en bajo inicialmente
    PORTC &= ~((1 << AUDIO_PIN_0) | (1 << AUDIO_PIN_1) | (1 << AUDIO_PIN_2));
}

// Obtener el laberinto actual según el nivel
const uint8_t* obtener_laberinto() {
    switch (nivel_actual) {
        case 1: return laberinto_nivel1;
        case 2: return laberinto_nivel2;
        case 3: return laberinto_nivel3;
        default: return laberinto_nivel1; // Por defecto, nivel 1
    }
}

// Verificar si una posición es una pared
uint8_t es_pared(uint8_t x, uint8_t y) {
    return (obtener_laberinto()[y] >> x) & 0b00000001; // Verifica el bit en la posición x
}


// Mostrar el laberinto en la pantalla 8x8
void mostrar_laberinto(uint8_t incluir_jugador) {
    for (uint8_t fila = 0; fila < 8; fila++) {
        PORTD = filas[fila]; // Activa la fila correspondiente

        uint8_t salida_columnas = obtener_laberinto()[fila];

        // Dibuja el jugador si se solicita
        if (incluir_jugador && fila == jugador_y) {
            salida_columnas |= (1 << jugador_x); // Enciende el LED del jugador
        }

        // Dibuja la meta (siempre un espacio libre)
        if (fila == meta_y && (nivel_actual == 1 || nivel_actual == 2 || nivel_actual == 3)) {
            salida_columnas &= ~(1 << meta_x); // Apaga el LED de la meta (se ve como un espacio)
        }

        // Envía la configuración de columnas (invertido para LEDs de cátodo común si aplica)
        PORTB = ~salida_columnas;
        _delay_ms(0.5);
    }
    PORTD = 0;
}

// Animación de victoria (todos los LEDs parpadean)
void mostrar_victoria() {
    for (uint8_t i = 0; i < 10; i++) {
        PORTB = 0x00; // Todos los LEDs encendidos
        PORTD = 0xFF; // Todas las filas encendidas
        _delay_ms(100);
        PORTD = 0x00; // Todas las filas apagadas
        _delay_ms(100);
    }
}

// Animación de derrota (patrón de LEDs parpadea)
void mostrar_derrota() {
    for (uint8_t i = 0; i < 5; i++) {
        PORTD = 0b10101010; // Patrón en filas
        PORTB = 0b01010101; // Patrón en columnas
        _delay_ms(200);
        PORTD = 0x00; // Apaga
        PORTB = 0xFF; // Enciende (depende de tu configuración de LEDs)
        _delay_ms(200);
    }
}

// Movimiento del jugador
void mover_jugador() {
    static uint8_t last_pin_state = 0xFF; // Estado anterior de los pines del puerto C (todos en alto por pull-ups)
    uint8_t current_pin_state = PINC; // Lee el estado actual de los pines del puerto C

    // Mover Izquierda
    if (!(current_pin_state & (1 << BTN_IZQ)) && (last_pin_state & (1 << BTN_IZQ))) {
        if (jugador_x > 0 && !es_pared(jugador_x - 1, jugador_y)) jugador_x--;
    }

    // Mover Derecha
    if (!(current_pin_state & (1 << BTN_DER)) && (last_pin_state & (1 << BTN_DER))) {
        if (jugador_x < 7 && !es_pared(jugador_x + 1, jugador_y)) jugador_x++;
    }

    // Mover Arriba
    if (!(current_pin_state & (1 << BTN_ARR)) && (last_pin_state & (1 << BTN_ARR))) {
        if (jugador_y > 0 && !es_pared(jugador_x, jugador_y - 1)) jugador_y--;
    }

    // Mover Abajo
    if (!(current_pin_state & (1 << BTN_ABA)) && (last_pin_state & (1 << BTN_ABA))) {
        if (jugador_y < 7 && !es_pared(jugador_x, jugador_y + 1)) jugador_y++;
    }

    last_pin_state = current_pin_state; // Actualiza el estado anterior
}

// Actualizar LEDs de estado (entrada y meta)
void actualizar_led_estado() {
    // LED de entrada (PD6) - un ejemplo de activación, puedes ajustarlo
    if (jugador_x == 1 && jugador_y == 1) { // Si el jugador está en una posición específica
        PORTD |= (1 << PIN_ENTRADA);
    } else {
        PORTD &= ~(1 << PIN_ENTRADA);
    }

    // LED de meta (PD7)
    if (jugador_x == meta_x && jugador_y == meta_y) {
        PORTD |= (1 << PIN_META);
    } else {
        PORTD &= ~(1 << PIN_META);
    }
}

// Función para avanzar al siguiente nivel
void siguiente_nivel() {
    // Enviar audio de victoria de nivel 1 o 2 ANTES de la animación y el cambio de nivel
    if (nivel_actual == 1 || nivel_actual == 2) {
        enviar_audio_pic(AUDIO_VICTORIA_NIVEL_1_2);
        _delay_ms(500); // Dar tiempo para que se reproduzca parte del audio de victoria
    }

    mostrar_victoria(); // Animación visual de victoria

    nivel_actual++;     // Avanza al siguiente nivel
    jugador_x = 5;      // Reinicia posición del jugador
    jugador_y = 0;

    // Configuración específica para el Nivel 3
    if (nivel_actual == 3) {
        enviar_audio_pic(AUDIO_INICIO_NIVEL_2_3);
        _delay_ms(500);
        tiempo_restante = 180;
        meta_x = 2;
        meta_y = 7;
    } else if (nivel_actual == 2) { // Para el inicio del Nivel 2
        enviar_audio_pic(AUDIO_INICIO_NIVEL_2_3);
        _delay_ms(500); // Dar tiempo para que se reproduzca parte del audio
    }
}

// Función para enviar un código de audio al PIC
void enviar_audio_pic(uint8_t codigo_audio) {
    // Primero, apaga todos los pines de audio para asegurar un estado conocido
    PORTC &= ~((1 << AUDIO_PIN_0) | (1 << AUDIO_PIN_1) | (1 << AUDIO_PIN_2));

    // Configura los pines según el código binario recibido
    // Bit 0 del código controla AUDIO_PIN_0
    if (codigo_audio & (1 << 0)) {
        PORTC |= (1 << AUDIO_PIN_0);
    }
    // Bit 1 del código controla AUDIO_PIN_1
    if (codigo_audio & (1 << 1)) {
        PORTC |= (1 << AUDIO_PIN_1);
    }
    // Bit 2 del código controla AUDIO_PIN_2
    if (codigo_audio & (1 << 2)) {
        PORTC |= (1 << AUDIO_PIN_2);
    }
    _delay_ms(20); // Pequeño retardo para que el PIC tenga tiempo de leer el valor
}


// --- Función Principal ---
int main(void) {
    init_ports(); // Inicializa todos los puertos

    // Iniciar el juego con el audio del Nivel 1
    enviar_audio_pic(AUDIO_INICIO_NIVEL_1);
    _delay_ms(1000); // Un retardo para que el audio de inicio se reproduzca

    while (1) { // Bucle principal del juego
        mover_jugador();         
        actualizar_led_estado(); 

        // Muestra el laberinto, el jugador y la meta
        // Se hace varias veces dentro del bucle para mantener una actualización constante
        // y evitar el "flickering" en la pantalla de LEDs.
        for (uint8_t i = 0; i < 5; i++) {
            mostrar_laberinto(1);
        }

        // Lógica del temporizador para el Nivel 3
        if (nivel_actual == 3) {
            if (tiempo_restante > 0) {

            } else {
                enviar_audio_pic(AUDIO_DERROTA); // Audio de derrota por tiempo agotado
                mostrar_derrota(); // Animación de derrota
                // Reiniciar el juego al Nivel 1
                nivel_actual = 1;
                jugador_x = 5;
                jugador_y = 0;
                enviar_audio_pic(AUDIO_INICIO_NIVEL_1); // Audio de inicio de nivel 1 al reiniciar
                _delay_ms(500); // Retardo para el audio
                continue; // Vuelve al inicio del bucle while(1)
            }
        }

        // Condición de victoria
        if (jugador_x == meta_x && jugador_y == meta_y) {
            if (nivel_actual == 3) {
                enviar_audio_pic(AUDIO_VICTORIA_NIVEL_3); // Audio de victoria del Nivel 3 (Juego completado)
                mostrar_victoria(); // Animación de victoria final
                while (1); // Bucle infinito, fin del juego
            } else {
                siguiente_nivel(); // Avanza al siguiente nivel (maneja audios y animaciones internas)
            }
        }

        _delay_ms(0.5); // Retardo general del bucle, ajusta según la reactividad deseada
    }
}