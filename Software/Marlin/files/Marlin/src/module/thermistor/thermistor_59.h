/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

// R25 = 100 kOhm, 1 kOhm pull-up

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
