## Конфигурирование GRBL для работы с платой Halcyon_v1

Поддержка платы добавлена в оригинальную прошивку <a href="https://github.com/grblHAL/STM32F4xx">GRBL HAL Driver</a>
На данном этапе все что необходимо сделать - настроить файл конфигурации под свое оборудование.
Для того чтобы не модифицировать исходный файл `..\grbl\config.h`, вы просто можете добавить в него строку
```C
#include "Halcyon_cfg.h"
```
с названием своего файла конфигурации, и добавить сам файл настроек станка `..\grbl\Halcyon_cfg.h`.

Однако, если вы хотите использовать неоригинальную версию прошивки (более старую, либо форк):

1.	Добавляем файл определения пинов: `..\Inc\halcyon_v1_map.h`

2.	Добавляем LD скрипты: 
`..\STM32F401RC_FLASH.ld` для прошивки без bootloader'а версии STM32F401RC
`..\STM32F401RC_BL16K_FLASH.ld` для прошивки с bootloader'ом версии STM32F401RC
`..\STM32F401RE_FLASH.ld` для прошивки без bootloader'а версии STM32F401RE
`..\STM32F401RE_BL16K_FLASH.ld` для прошивки с bootloader'ом версии STM32F401RE

3.	Добавляем необходимое окружение в файл `..\platformio.ini`:

```C
[env:Halcyon_v1_RC]
board                = genericSTM32F401RC
board_build.ldscript = STM32F401RC_FLASH.ld
build_flags          = ${common.build_flags}
  -D BOARD_HALCYON_V1=
  -D HSE_VALUE=8000000
  -D USB_SERIAL_CDC=1
  -D SDCARD_ENABLE=1
  -D EEPROM_IS_FRAM=1
lib_deps             = ${common.lib_deps}
  eeprom
  FatFs
  sdcard
lib_extra_dirs       = ${common.lib_extra_dirs}
upload_protocol      = stlink

[env:Halcyon_v1_RC_BL]
# With the default boot loader, you must deploy new firmware by copying
# .pio/build/<env name>/firmware.bin (produced by `pio run`) to the SD card.
extends              = env:Halcyon_v1_RC
board_build.ldscript = STM32F401RC_BL16K_FLASH.ld
build_flags          = ${common.build_flags}
  -D BOARD_HALCYON_V1=
  -D HSE_VALUE=8000000
  -D HAS_BOOTLOADER=1
  -D USB_SERIAL_CDC=1
  -D SDCARD_ENABLE=1
  -D EEPROM_IS_FRAM=1
lib_deps             = ${common.lib_deps}
  eeprom
  FatFs
  sdcard
lib_extra_dirs       = ${common.lib_extra_dirs}

[env:Halcyon_v1_RE]
board                = genericSTM32F401RE
board_build.ldscript = STM32F401RE_FLASH.ld
build_flags          = ${common.build_flags}
  -D BOARD_HALCYON_V1=
  -D HSE_VALUE=8000000
  -D USB_SERIAL_CDC=1
  -D SDCARD_ENABLE=1
  -D KEYPAD_ENABLE=1
  -D EEPROM_IS_FRAM=1
lib_deps             = ${common.lib_deps}
  eeprom
  trinamic
  FatFs
  sdcard
lib_extra_dirs       = ${common.lib_extra_dirs}
upload_protocol      = stlink

[env:Halcyon_v1_RE_BL]
# With the default boot loader, you must deploy new firmware by copying
# .pio/build/<env name>/firmware.bin (produced by `pio run`) to the SD card.
extends              = env:Halcyon_v1_RE
board_build.ldscript = STM32F401RE_BL16K_FLASH.ld
build_flags          = ${common.build_flags}
  -D BOARD_HALCYON_V1=
  -D HSE_VALUE=8000000
  -D HAS_BOOTLOADER=1
  -D USB_SERIAL_CDC=1
  -D SDCARD_ENABLE=1
  -D KEYPAD_ENABLE=1
  -D EEPROM_IS_FRAM=1
lib_deps             = ${common.lib_deps}
  eeprom
  trinamic
  FatFs
  sdcard
lib_extra_dirs       = ${common.lib_extra_dirs}
```

4.	Добавляем в файл `..\Inc\driver.h `:

```C
#elif defined(BOARD_HALCYON_V1)
  #include "halcyon_v1_map.h"
```

