## Конфигурирование Marlin для работы с платой Halcyon_v1

Рекомендуется использовать модицикацию последней стабильной версии оригинальной прошивки.
Готовая прошивка предлагается как пример, где можно подсмотреть настройки концевиков и прочего,
она созданна для конкретной физической машины с ее особенностями. Для добавления поддержки платы
в оригинальную прошивку выполните следующие пункты:

1.	Добавляем файл определения пинов: `..\ Marlin\src\pins\stm32f4\pins_HALCYON_V1`

2.	Добавляем в файл `..\Marlin\src\pins\pins.h`:

```C
#elif MB(HALCYON_V1)
  #include "stm32f4/pins_HALCYON_V1.h"          // STM32F4                                env:Halcyon_v1 env:Halcyon_v1_dfu env:Halcyon_v1_stlink
```

Важно: в закомментированной части строки есть информация о необходимом окружении, она парсится скриптом во время подготовки 
к компиляции, поэтому должна соответствовать имени вашего окружения на шаге 5.

3.	Добавляем в файл `..\Marlin\src\core\boards.h`:

```C
#define BOARD_HALCYON_V1              5302  // HALCYON BOARD
```

Номер после названия платы может быть любым (при выходе свежих версий система нумерации периодически изменяется, а уже 
существующие номера сдвигаются), главное чтобы он был уникальным.

4.	В файлe `..\Marlin\Configuration.h` производим необходимые изменения и указываем нашу плату:

```C
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_HALCYON_V1
#endif
```

5.	В файл `..\ini\stm32f4.ini` добавляем определение окружения:

```C
[env:Halcyon_v1]
extends                     = stm32_variant
platform                    = ststm32
board                       = marlin_STM32F401RC
board_build.offset          = 0x0000
build_flags                 = ${stm32_variant.build_flags} ${stm32f4_I2C1.build_flags}
                            -Os -DHAL_PCD_MODULE_ENABLED
                            -DHAL_UART_MODULE_ENABLED
                            -DPIN_WIRE_SCL=PB6 -DPIN_WIRE_SDA=PB7
                            -DSERIAL_RX_BUFFER_SIZE=1024 -DSERIAL_TX_BUFFER_SIZE=1024
                            -DTIMER_SERVO=TIM2
                            -DSTEP_TIMER_IRQ_PRIO=0
monitor_speed               = 115200

[env:Halcyon_v1_dfu]
extends                     = env:Halcyon_v1
upload_protocol             = dfu

[env:Halcyon_v1_stlink]
extends                     = env:Halcyon_v1
upload_protocol             = stlink
```

6.	Прошиваем выбрав окружение `env:Halcyon_v1_dfu` для прошивки по USB (для этого необходимо перезагрузить плату 
кнопкой RST с зажатой кнопкой BOOT0), либо `env:Halcyon_v1_stlink` для прошивки с помощью ST-LINK через специальный
разъем программирования на плате.

После прошивки не забываем сбросить настройки EEPROM командой `M502` и сохранить их вновь командой `M500`.

## Добавление своих терморезисторов в Marlin.

По умолчанию номинал резистора R501 на входе делителя АЦП равен 1 кОм для повышения точности измерения
температуры в рабочих диапазонах (от 0.23 до 0.67 градусов Цельсия на отсчет АЦП в диапазоне 200-300 градусов Цельсия). 
Большинство существующих плат использует резисторы 4.7 кОм, что дает меньшую точность
установки температуры при высоких температурах (от 0.71 до 3.33 градусов Цельсия на отсчет АЦП в диапазоне 200-300 градусов Цельсия
для терморезистора `5 : 100kΩ  ATC Semitec 104GT-2/104NT-4-R025H42G`), но большую точность измерения температур, близких к комнатным. Для поддержки
такого решения в файле `..\Marlin\Configuration.h` выберите один из терморезисторов с 1 кОм резистором верхнего плеча
в секции `#define TEMP_SENSOR_0 ...`, либо добавьте свой терморезистор и калибровочную таблицу к нему.
Для этого необходимо выполнить следующие пункты:

1.	Создаем header-файл с калибровкой терморезистора и именем `.. \Marlin\src\module\thermistor\thermistor_59.h`:

```C
#pragma once

constexpr temp_entry_t temptable_59[] PROGMEM = {
  { OV(91),   300 },
  { OV(106),  290 },           // res=0.67 degC/count
  { OV(121),  280 },           // res=0.67 degC/count
  { OV(140),  270 },           // res=0.53 degC/count
  { OV(161),  260 },           // res=0.48 degC/count
  { OV(186),  250 },           // res=0.40 degC/count
  { OV(217),  240 },           // res=0.32 degC/count
  { OV(248),  230 },           // res=0.32 degC/count
  { OV(287),  220 },           // res=0.26 degC/count
  { OV(330),  210 },           // res=0.23 degC/count
  { OV(374),  200 },           // res=0.23 degC/count
  { OV(426),  190 },           // res=0.19 degC/count
  { OV(478),  180 },           // res=0.19 degC/count
  { OV(536),  170 },           // res=0.17 degC/count
  { OV(594),  160 },           // res=0.17 degC/count
  { OV(654),  150 },           // res=0.17 degC/count
  { OV(709),  140 },           // res=0.18 degC/count
  { OV(760),  130 },           // res=0.20 degC/count
  { OV(807),  120 },           // res=0.21 degC/count
  { OV(850),  110 },           // res=0.23 degC/count
  { OV(887),  100 },           // res=0.27 degC/count
  { OV(919),   90 },           // res=0.31 degC/count
  { OV(944),   80 },           // res=0.40 degC/count
  { OV(964),   70 },           // res=0.50 degC/count
  { OV(980),   60 },           // res=0.63 degC/count
  { OV(993),   50 },           // res=0.77 degC/count
  { OV(1001),  40 },           // res=1.25 degC/count
  { OV(1007),  30 },           // res=1.67 degC/count
  { OV(1009),  25 },           // res=2.50 degC/count
  { OV(1018),  0  }            // res=2.78 degC/count
};
```

2.	В файл записываем свою таблицу калибровки, показания АЦП (чтобы их видеть в консоли, необходимо раскомментировать 
параметр `#define SHOW_TEMP_ADC_VALUES` в файле `..\Marlin\Configuration_adv.h`) и показания реальной температуры, полученной 
с помощью своей термопары или иным заведомо точным способом. Значения АЦП записываются в 10-битном виде, поэтому если у вас 
АЦП имеет 12 бит, то значения стоит делить на 4 (2 в степени битность вашего АЦП минус 10). Чем чаще шаг по температуре, 
тем лучше, но чаще 10 смысла делать нет, верхний предел записываем тот, который нам необходим.

3.	В файл `..\Marlin\src\module\thermistor\thermistors.h` добавляем строки:

```C
#if ANY_THERMISTOR_IS(59)
  #include "thermistor_59.h"
#endif
```

4.	В файле `..\Marlin\Configuration.h` определяем как используемый наш резистор:

```C
#define TEMP_SENSOR_0 59
```

