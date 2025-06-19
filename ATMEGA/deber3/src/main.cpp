#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// Botones
#define BTN_IZQ PC0
#define BTN_DER PC1
#define BTN_ARR PC2
#define BTN_ABA PC3

// LEDs de estado
#define PIN_ENTRADA PD6
#define PIN_META    PD7

// Jugador
uint8_t jugador_x = 5;
uint8_t jugador_y = 0;

// Meta final
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

// Mapeo de filas
const uint8_t filas[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void init_ports() {
    DDRD = 0xFF;
    DDRB = 0xFF;
    DDRC &= ~((1<<BTN_IZQ)|(1<<BTN_DER)|(1<<BTN_ARR)|(1<<BTN_ABA));
    PORTC |= (1<<BTN_IZQ)|(1<<BTN_DER)|(1<<BTN_ARR)|(1<<BTN_ABA);
}

const uint8_t* obtener_laberinto() {
    switch (nivel_actual) {
        case 1: return laberinto_nivel1;
        case 2: return laberinto_nivel2;
        case 3: return laberinto_nivel3;
        default: return laberinto_nivel1;
    }
}

uint8_t es_pared(uint8_t x, uint8_t y) {
    return obtener_laberinto()[y] & (1 << x);
}

void mostrar_laberinto(uint8_t incluir_jugador) {
    for (uint8_t fila = 0; fila < 8; fila++) {
        PORTD = filas[fila];

        uint8_t salida = obtener_laberinto()[fila];

        if (incluir_jugador && fila == jugador_y) salida |= (1 << jugador_x);
        if (fila == meta_y) salida &= ~(1 << meta_x); // puerta salida

        PORTB = ~salida;
        _delay_ms(0.5);
    }
    PORTD = 0;
}

//animacion de victoria
void mostrar_victoria() {
    for (uint8_t i = 0; i < 10; i++) {
        PORTB = 0x00;
        PORTD = 0xFF;
        _delay_ms(20);
        PORTD = 0x00;
        _delay_ms(20);
    }
}

//animacion de derrota
void mostrar_derrota() {
    for (uint8_t i = 0; i < 5; i++) {
        PORTD = 0b10101010;
        PORTB = 0b01010101;
        _delay_ms(100);
        PORTD = 0x00;
        PORTB = 0xFF;
        _delay_ms(100);
    }
}

void mover_jugador() {
    static uint8_t last_state = 0;
    uint8_t actual_state = PINC;

    if (!(actual_state & (1 << BTN_IZQ)) && (last_state & (1 << BTN_IZQ))) {
        if (jugador_x > 0 && !es_pared(jugador_x - 1, jugador_y)) jugador_x--;
    }

    if (!(actual_state & (1 << BTN_DER)) && (last_state & (1 << BTN_DER))) {
        if (jugador_x < 7 && !es_pared(jugador_x + 1, jugador_y)) jugador_x++;
    }

    if (!(actual_state & (1 << BTN_ARR)) && (last_state & (1 << BTN_ARR))) {
        if (jugador_y > 0 && !es_pared(jugador_x, jugador_y - 1)) jugador_y--;
    }

    if (!(actual_state & (1 << BTN_ABA)) && (last_state & (1 << BTN_ABA))) {
        if (jugador_y < 7 && !es_pared(jugador_x, jugador_y + 1)) jugador_y++;
    }

    last_state = actual_state;
}

void actualizar_led_estado() {
    if (jugador_x == 1 && jugador_y == 1) {
        PORTD |= (1 << PIN_ENTRADA);
    } else {
        PORTD &= ~(1 << PIN_ENTRADA);
    }

    if (jugador_x == meta_x && jugador_y == meta_y) {
        PORTD |= (1 << PIN_META);
    } else {
        PORTD &= ~(1 << PIN_META);
    }
}

void siguiente_nivel() {
    mostrar_victoria();
    nivel_actual++;
    jugador_x = 5;
    jugador_y = 0;

    if (nivel_actual == 3) {
        tiempo_restante = 180; 
        meta_x = 2;
        meta_y = 7;
    }
}

int main(void) {
    init_ports();

    while (1) {
        mover_jugador();
        actualizar_led_estado();

        for (uint8_t i = 0; i < 5; i++) {
            mostrar_laberinto(1);
        }

        if (nivel_actual == 3) {
            if (tiempo_restante > 0) {
                tiempo_restante--;
            } else {
                mostrar_derrota();
                nivel_actual = 1;
                jugador_x = 5;
                jugador_y = 0;
                continue;
            }
        }

        if (jugador_x == meta_x && jugador_y == meta_y) {
            if (nivel_actual == 3) {
                mostrar_victoria();
                while (1); // fin del juego
            } else {
                siguiente_nivel();
            }
        }

        _delay_ms(0.5);
    }
}
