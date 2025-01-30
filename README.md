# Semáforo com Temporizador Periódico no Raspberry Pi Pico W

## Descrição
Este projeto implementa um sistema de temporização periódico utilizando a função `add_repeating_timer_ms()` do Pico SDK para controlar um semáforo com três LEDs (vermelho, amarelo e verde).

## Funcionalidade
1. O sistema alterna entre os estados do semáforo a cada 3 segundos.
2. O LED vermelho acende primeiro, seguido pelo amarelo e depois pelo verde.
3. O ciclo se repete continuamente.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W
- **LEDs:** 3 LEDs (vermelho, amarelo e verde)
- **Software:** Pico SDK

## Configuração dos GPIOs
| Componente | GPIO |
|------------|------|
| LED Vermelho | 11 |
| LED Amarelo  | 12 |
| LED Verde    | 13 |

## Código
```c
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
```

## Como Compilar e Executar
1. Instale o [Pico SDK](https://github.com/raspberrypi/pico-sdk).
2. Clone este repositório e configure o ambiente do Pico SDK.
3. Compile o código:  "UN-4-Atividade-1-Temporizador-periodico.c" no VSCODE

   ```
4. Suba o arquivo `.uf2` gerado para o Raspberry Pi Pico W.
5. Observe a sequência do semáforo funcionando.

## Melhorias Futuras
- Ajuste dinâmico do tempo de troca do semáforo.
- Adição de botoes para controle manual.

## Autor
Renan dos Santos Ferreira

