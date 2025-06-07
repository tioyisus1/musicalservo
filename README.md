# Sistema Musical Interactivo con Servos, Piezoeléctricos y LEDs

Este proyecto Arduino reproduce una melodía mientras mueve 3 servos y activa LEDs de forma interactiva. Utiliza un potenciómetro para controlar la velocidad de la música y responde visualmente con movimientos de servos y luces según las frecuencias musicales.

## Características

- Reproducción de melodía usando dos piezoeléctricos alternados.
- Movimiento de 3 servomotores según la frecuencia de la nota.
- Control de velocidad de reproducción con potenciómetro.
- Iluminación con LEDs sincronizada con la música.
- Salida de monitoreo en el Monitor Serial para depuración y visualización.

## Componentes necesarios

- Arduino UNO o compatible
- 3 Servos (SG90 o similares)
- 2 Piezoeléctricos (buzzer pasivo)
- 2 LEDs
- 2 resistencias (220Ω) para los LEDs
- 1 Potenciómetro
- Cables y protoboard

## Conexiones

| Componente          | Pin Arduino |
|---------------------|-------------|
| Servo 1             | 9           |
| Servo 2             | 10          |
| Servo 3             | 11          |
| Piezoeléctrico 1    | 8           |
| Piezoeléctrico 2    | 12          |
| LED 1               | 5           |
| LED 2               | 6           |
| Potenciómetro (centro) | A0       |

> Asegúrate de conectar los extremos del potenciómetro a GND y 5V.

## Funcionamiento

- La melodía está definida con notas musicales (`pitches.h`) y duraciones.
- Cada nota activa uno de los piezoeléctricos alternadamente.
- La nota también activa uno de los servos según su frecuencia:
  - **Notas bajas (≤ 330 Hz):** servo 1
  - **Notas medias (330–440 Hz):** servo 2
  - **Notas altas (> 440 Hz):** servo 3
- La duración de las notas se ajusta con un **potenciómetro**, que permite cambiar la velocidad de reproducción entre 0.5x y 2x.
- LEDs pueden configurarse para reaccionar a notas o simplemente parpadear según los tiempos (puedes personalizarlo).

## Librerías necesarias

- `Servo.h` (incluida por defecto en el IDE de Arduino)
- `pitches.h` (asegúrate de incluir este archivo en el mismo directorio que tu sketch)

## Estructura del código

- **setup():** Configura los pines, inicializa servos y el monitor serial.
- **loop():** Reproduce la melodía, controla los servos y piezoeléctricos, ajusta el tiempo según el potenciómetro.

## Uso

1. Conecta todos los componentes según el diagrama.
2. Abre el IDE de Arduino, carga el código y súbelo a tu placa.
3. Gira el potenciómetro para ajustar la velocidad de reproducción.
4. Observa el comportamiento sincronizado de los servos, sonidos y luces.

## Créditos

Desarrollado por [David Suarez](https://github.com/tioyisus1)

---

¡Disfruta creando música con Arduino y movimiento sincronizado!
