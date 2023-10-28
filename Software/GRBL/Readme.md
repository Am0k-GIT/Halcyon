## Конфигурирование Marlin для работы с платой Halcyon_v1

Рекомендуется использовать модицикацию последней стабильной версии оригинальной прошивки.
Готовая прошивка предлагается как пример, где можно подсмотреть настройки концевиков и прочего,
она созданна для конкретной физической машины с ее особенностями. Для добавления поддержки платы
в оригинальную прошивку выполните следующие пункты:

1.	Добавляем файл определения пинов: `..\Inc\halcyon_v1_map.h`

2.	Добавляем LD скрипт: `..\STM32F401RC_FLASH.ld`

3.	Добавляем необходимое окружение в файл `..\platformio.ini`:

```C
[env:Halcyon_v1]
board                = genericSTM32F401RC
board_build.ldscript = STM32F401RC_FLASH.ld
build_flags          = ${common.build_flags}
  # See Inc/my_machine.h for options
                     -D BOARD_HALCYON_V1=
                     -D HSE_VALUE=8000000
                     -D USB_SERIAL_CDC=1
                     -D SDCARD_ENABLE=1
                     -D _VOLUMES=1
                     -D KEYPAD_ENABLE=1
                     -D EEPROM_IS_FRAM=1
lib_deps             = ${common.lib_deps}
					eeprom
					trinamic
					FatFs
					sdcard
lib_extra_dirs       = ${common.lib_extra_dirs}

[env:Halcyon_v1_dfu]
extends              = env:Halcyon_v1
upload_protocol      = dfu

[env:Halcyon_v1_stlink]
extends              = env:Halcyon_v1
upload_protocol      = stlink
```

4.	Добавляем в файл `..\Inc\driver.h `:

```C
#elif defined(BOARD_HALCYON_V1)
  #include "halcyon_v1_map.h"
```

5.	Добавляем в файл `..\grbl\config.h`:

```C
#include "Halcyon_cfg.h"
```

6.	Добавляем файл настроек станка `..\grbl\Halcyon_cfg.h` 

