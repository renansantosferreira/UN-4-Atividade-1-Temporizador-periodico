#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_R 11
#define LED_Y 12
#define LED_G 13

volatile int state = 0;

bool timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(LED_R, 0);
    gpio_put(LED_Y, 0);
    gpio_put(LED_G, 0);

    // Alterna entre os estados do semáforo
    switch (state) {
        case 0:
            gpio_put(LED_R, 1); // Vermelho
            break;
        case 1:
            gpio_put(LED_Y, 1); // Amarelo
            break;
        case 2:
            gpio_put(LED_G, 1); // Verde
            break;
    }

    state = (state + 1) % 3; // Próximo estado

    return true; // Retorna verdadeiro para continuar o timer
}

int main() {
    stdio_init_all();
    gpio_init(LED_R);
    gpio_init(LED_Y);
    gpio_init(LED_G);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_Y, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, timer_callback, NULL, &timer);

    while (1) {
        tight_loop_contents(); // Mantém o programa rodando
    }
}
