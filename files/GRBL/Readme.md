## Конфигурирование GRBL для работы с платой Halcyon_v1

Поддержка платы добавлена в оригинальную прошивку <a href="https://github.com/grblHAL/STM32F4xx">GRBL HAL Driver</a>
На данном этапе все что необходимо сделать - настроить файл конфигурации под свое оборудование.
Для того чтобы не модифицировать исходный файл `..\grbl\config.h`, вы просто можете добавить в него строку
```C
#include "Halcyon_cfg.h"
```
со названием своего файла конфигурации, и добавить сам файл настроек станка `..\grbl\Halcyon_cfg.h`.

Однако, если вы хотите использовать неоригинальную версию прошивки (более старую, либо форк):

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

