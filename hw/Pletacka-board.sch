EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-TTGO-T-Display:ESP32-TTGO-T-Display E1
U 1 1 5F8A9387
P 6000 3800
F 0 "E1" H 6095 4375 50  0000 C CNN
F 1 "ESP32-TTGO-T-Display" H 6095 4284 50  0000 C CNN
F 2 "ESP32-TTGO-T-Display:ESP32-TTGO-T-Display" H 5000 4250 50  0001 C CNN
F 3 "https://github.com/Xinyuan-LilyGO/TTGO-T-Display/blob/master/schematic/ESP32-TFT(6-26).pdf" H 5000 4250 50  0001 C CNN
	1    6000 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F8AE428
P 5500 3450
F 0 "#PWR0101" H 5500 3200 50  0001 C CNN
F 1 "GND" V 5505 3322 50  0000 R CNN
F 2 "" H 5500 3450 50  0001 C CNN
F 3 "" H 5500 3450 50  0001 C CNN
	1    5500 3450
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 5F8AF0A8
P 5500 4450
F 0 "#PWR0102" H 5500 4300 50  0001 C CNN
F 1 "+3V3" V 5515 4578 50  0000 L CNN
F 2 "" H 5500 4450 50  0001 C CNN
F 3 "" H 5500 4450 50  0001 C CNN
	1    5500 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 4450 5650 4450
Wire Wire Line
	5500 3450 5650 3450
Wire Wire Line
	6550 4450 6700 4450
$Comp
L power:+5V #PWR0103
U 1 1 5F8B11B0
P 6700 4450
F 0 "#PWR0103" H 6700 4300 50  0001 C CNN
F 1 "+5V" V 6715 4578 50  0000 L CNN
F 2 "" H 6700 4450 50  0001 C CNN
F 3 "" H 6700 4450 50  0001 C CNN
	1    6700 4450
	0    1    1    0   
$EndComp
$Sheet
S 9450 900  1100 700 
U 5F8BD394
F0 "Buttons" 50
F1 "Buttons.sch" 50
F2 "BTN_RESET" O L 9450 1050 50 
F3 "BTN_1" O L 9450 1200 50 
$EndSheet
Text GLabel 9300 1050 0    50   Input ~ 0
BTN_RESET
Wire Wire Line
	5650 3550 5500 3550
Wire Wire Line
	9450 1050 9300 1050
Text GLabel 9300 1200 0    50   Input ~ 0
BTN_1
Wire Wire Line
	9450 1200 9300 1200
Text GLabel 5500 3550 0    50   Input ~ 0
BTN_1
Text GLabel 5500 4050 0    50   Input ~ 0
BTN_RESET
Wire Wire Line
	5650 3650 5500 3650
Wire Wire Line
	5650 3750 5500 3750
Wire Wire Line
	5650 3850 5500 3850
Wire Wire Line
	5650 3950 5500 3950
Wire Wire Line
	5650 4050 5500 4050
Wire Wire Line
	5500 4150 5650 4150
Wire Wire Line
	6550 3450 6700 3450
Wire Wire Line
	6550 3550 6700 3550
Wire Wire Line
	6550 3650 6700 3650
Wire Wire Line
	6550 3750 6700 3750
Wire Wire Line
	6550 3850 6700 3850
Wire Wire Line
	6550 3950 6700 3950
Wire Wire Line
	6550 4050 6700 4050
Wire Wire Line
	6550 4150 6700 4150
Wire Wire Line
	6550 4250 6700 4250
$Sheet
S 9500 2500 1000 1000
U 5F8DC13F
F0 "Leds" 50
F1 "Leds.sch" 50
F2 "LED_POWER" I L 9500 2900 50 
F3 "LED_SEND" I L 9500 3150 50 
$EndSheet
$Comp
L power:+3V3 #PWR0104
U 1 1 5F8DEB09
P 9350 2900
F 0 "#PWR0104" H 9350 2750 50  0001 C CNN
F 1 "+3V3" V 9365 3028 50  0000 L CNN
F 2 "" H 9350 2900 50  0001 C CNN
F 3 "" H 9350 2900 50  0001 C CNN
	1    9350 2900
	0    -1   -1   0   
$EndComp
$Sheet
S 9500 4000 1000 1500
U 5F8B0B95
F0 "Optocoupler" 79
F1 "Optocoupler.sch" 50
F2 "OPTO_FINSIHED_OUT" O L 9500 4600 50 
F3 "OPTO_STOP_OUT" O L 9500 5250 50 
F4 "OPTO_STOP_IN_PLUS" I L 9500 4950 50 
F5 "OPTO_STOP_IN_MINUS" I L 9500 5100 50 
F6 "OPTO_FINISHED_IN_MINUS" I L 9500 4450 50 
F7 "OPTO_FINISHED_IN_PLUS" I L 9500 4300 50 
$EndSheet
Text GLabel 9350 4600 0    50   Input ~ 0
OPTO_FINSIHED
Text GLabel 9350 5250 0    50   Input ~ 0
OPTO_STOP
Wire Wire Line
	9500 5250 9350 5250
Text GLabel 6700 3450 2    50   Input ~ 0
OPTO_FINSIHED
Text GLabel 6700 3550 2    50   Input ~ 0
OPTO_STOP
$Sheet
S 1000 1000 1000 1500
U 5F8F7408
F0 "Power" 50
F1 "Power.sch" 50
$EndSheet
$Comp
L Connector:Conn_01x02_Female J4
U 1 1 5F9151EB
P 1300 5650
F 0 "J4" V 1238 5462 50  0000 R CNN
F 1 "Conn_01x02_Female" V 1147 5462 50  0000 R CNN
F 2 "Terminal_block:TerminalBlock_Phoenix_PT-1,5-2-5.0-H_1x02_P5.00mm_Horizontal" H 1300 5650 50  0001 C CNN
F 3 "~" H 1300 5650 50  0001 C CNN
	1    1300 5650
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J5
U 1 1 5F915FED
P 2450 5650
F 0 "J5" V 2388 5462 50  0000 R CNN
F 1 "Conn_01x03_Female" V 2297 5462 50  0000 R CNN
F 2 "Terminal_block:TerminalBlock_Phoenix_PT-1,5-3-5.0-H_1x03_P5.00mm_Horizontal" H 2450 5650 50  0001 C CNN
F 3 "~" H 2450 5650 50  0001 C CNN
	1    2450 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1300 6000 1300 5850
Wire Wire Line
	1400 6000 1400 5850
Wire Wire Line
	2350 6000 2350 5850
Wire Wire Line
	2450 6000 2450 5850
Wire Wire Line
	2550 6000 2550 5850
Text GLabel 1300 6000 3    50   Input ~ 0
OPTO_STOP_IN_PLUS
Text GLabel 1400 6000 3    50   Input ~ 0
OPTO_STOP_IN_MINUS
Text GLabel 2450 6000 3    50   Input ~ 0
OPTO_FINISHED_IN_PLUS
Wire Wire Line
	2550 6000 2650 6000
Wire Wire Line
	2350 6000 2250 6000
$Comp
L power:GND #PWR0116
U 1 1 5F91B916
P 2250 6000
F 0 "#PWR0116" H 2250 5750 50  0001 C CNN
F 1 "GND" V 2255 5872 50  0000 R CNN
F 2 "" H 2250 6000 50  0001 C CNN
F 3 "" H 2250 6000 50  0001 C CNN
	1    2250 6000
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR0117
U 1 1 5F91BD5C
P 2650 6000
F 0 "#PWR0117" H 2650 5850 50  0001 C CNN
F 1 "VCC" V 2667 6128 50  0000 L CNN
F 2 "" H 2650 6000 50  0001 C CNN
F 3 "" H 2650 6000 50  0001 C CNN
	1    2650 6000
	0    1    1    0   
$EndComp
Text GLabel 9350 4950 0    50   Input ~ 0
OPTO_STOP_IN_PLUS
Text GLabel 9350 5100 0    50   Input ~ 0
OPTO_STOP_IN_MINUS
Wire Wire Line
	9350 5100 9500 5100
Wire Wire Line
	9350 4950 9500 4950
Wire Wire Line
	9350 4600 9500 4600
Text GLabel 9350 4300 0    50   Input ~ 0
OPTO_FINISHED_IN_PLUS
Wire Wire Line
	9350 4450 9500 4450
Wire Wire Line
	9500 4300 9350 4300
Text Notes 5600 4850 0    197  ~ 0
ESP32
Wire Notes Line
	1000 5550 3500 5550
Wire Notes Line
	3500 5550 3500 7200
Wire Notes Line
	3500 7200 1000 7200
Wire Notes Line
	1000 7200 1000 5550
Text Notes 1850 5450 0    197  ~ 0
Input
Wire Wire Line
	9350 2900 9500 2900
Wire Wire Line
	9500 3150 9350 3150
Text GLabel 9350 3150 0    50   Input ~ 0
LED_SEND
Text GLabel 6700 4050 2    50   Input ~ 0
LED_SEND
$Comp
L Mechanical:MountingHole H2
U 1 1 5F9A015D
P 6350 7350
F 0 "H2" H 6450 7396 50  0000 L CNN
F 1 "MountingHole" H 6450 7305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_Pad" H 6350 7350 50  0001 C CNN
F 3 "~" H 6350 7350 50  0001 C CNN
	1    6350 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5F9A042D
P 5550 7350
F 0 "H1" H 5650 7396 50  0000 L CNN
F 1 "MountingHole" H 5650 7305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5_Pad" H 5550 7350 50  0001 C CNN
F 3 "~" H 5550 7350 50  0001 C CNN
	1    5550 7350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F9CF981
P 9350 4450
F 0 "#PWR0107" H 9350 4200 50  0001 C CNN
F 1 "GND" V 9355 4322 50  0000 R CNN
F 2 "" H 9350 4450 50  0001 C CNN
F 3 "" H 9350 4450 50  0001 C CNN
	1    9350 4450
	0    1    1    0   
$EndComp
$EndSCHEMATC
