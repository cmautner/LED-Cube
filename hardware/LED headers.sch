EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:LED breakout board
LIBS:transistors
LIBS:LED breakout board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 10
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
L 8x8_LED_Matrix U8
U 1 1 56F4BEA6
P 5200 3250
AR Path="/56F793F6/56F4BEA6" Ref="U8"  Part="1" 
AR Path="/570B3A83/56F4BEA6" Ref="U11"  Part="1" 
AR Path="/570B3C96/56F4BEA6" Ref="U12"  Part="1" 
AR Path="/570B3EE5/56F4BEA6" Ref="U13"  Part="1" 
AR Path="/570B4188/56F4BEA6" Ref="U14"  Part="1" 
F 0 "U14" H 5400 2100 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 5150 4100 60  0000 C CNN
F 2 "LED breakout board:8x8_LED_Matrix" H 5150 4100 60  0001 C CNN
F 3 "" H 5150 4100 60  0000 C CNN
	1    5200 3250
	1    0    0    -1  
$EndComp
Text HLabel 2450 2100 0    60   Input ~ 0
ROW[0..7]
Text HLabel 2450 4600 0    60   Input ~ 0
BLU[0..7]
Text HLabel 2450 2000 0    60   Input ~ 0
RED[0..7]
Text HLabel 2450 4700 0    60   Input ~ 0
GRN[0..7]
Wire Wire Line
	4500 2550 3950 2550
Wire Wire Line
	3950 2650 4500 2650
Wire Wire Line
	3950 2750 4500 2750
Wire Wire Line
	3950 2850 4500 2850
Wire Wire Line
	3950 2950 4500 2950
Wire Wire Line
	3950 3050 4500 3050
Wire Wire Line
	3950 3150 4500 3150
Wire Wire Line
	3950 3250 4500 3250
Wire Wire Line
	4500 3450 3950 3450
Wire Wire Line
	4500 3550 3950 3550
Wire Wire Line
	4500 3650 3950 3650
Wire Wire Line
	4500 3750 3950 3750
Wire Wire Line
	4500 3850 3950 3850
Wire Wire Line
	4500 3950 3950 3950
Wire Wire Line
	4500 4050 3950 4050
Wire Wire Line
	4500 4150 3950 4150
Wire Wire Line
	5800 2550 6350 2550
Wire Wire Line
	5800 2650 6350 2650
Wire Wire Line
	5800 2750 6350 2750
Wire Wire Line
	5800 2850 6350 2850
Wire Wire Line
	5800 2950 6350 2950
Wire Wire Line
	5800 3050 6350 3050
Wire Wire Line
	5800 3150 6350 3150
Wire Wire Line
	5800 3250 6350 3250
Wire Wire Line
	5800 3450 6350 3450
Wire Wire Line
	5800 3550 6350 3550
Wire Wire Line
	5800 3650 6350 3650
Wire Wire Line
	5800 3750 6350 3750
Wire Wire Line
	5800 3850 6350 3850
Wire Wire Line
	5800 3950 6350 3950
Wire Wire Line
	5800 4050 6350 4050
Wire Wire Line
	5800 4150 6350 4150
Entry Wire Line
	3850 2450 3950 2550
Entry Wire Line
	3850 2550 3950 2650
Entry Wire Line
	3850 2650 3950 2750
Entry Wire Line
	3850 2750 3950 2850
Entry Wire Line
	3850 2850 3950 2950
Entry Wire Line
	3850 2950 3950 3050
Entry Wire Line
	3850 3050 3950 3150
Entry Wire Line
	3850 3150 3950 3250
Entry Wire Line
	6350 3450 6450 3550
Entry Wire Line
	6350 3550 6450 3650
Entry Wire Line
	6350 3650 6450 3750
Entry Wire Line
	6350 3750 6450 3850
Entry Wire Line
	6350 3850 6450 3950
Entry Wire Line
	6350 3950 6450 4050
Entry Wire Line
	6350 4050 6450 4150
Entry Wire Line
	6350 4150 6450 4250
Entry Wire Line
	6350 2550 6450 2450
Entry Wire Line
	6350 2650 6450 2550
Entry Wire Line
	6350 2750 6450 2650
Entry Wire Line
	6350 2850 6450 2750
Entry Wire Line
	6350 2950 6450 2850
Entry Wire Line
	6350 3050 6450 2950
Entry Wire Line
	6350 3150 6450 3050
Entry Wire Line
	6350 3250 6450 3150
Entry Wire Line
	3850 3550 3950 3450
Entry Wire Line
	3850 3650 3950 3550
Entry Wire Line
	3850 3750 3950 3650
Entry Wire Line
	3850 3850 3950 3750
Entry Wire Line
	3850 3950 3950 3850
Entry Wire Line
	3850 4050 3950 3950
Entry Wire Line
	3850 4150 3950 4050
Entry Wire Line
	3850 4250 3950 4150
Wire Bus Line
	2450 2100 3850 2100
Wire Bus Line
	3850 2100 3850 3150
Wire Bus Line
	3850 3550 3850 4600
Wire Bus Line
	3850 4600 2450 4600
Wire Bus Line
	2450 4700 6450 4700
Wire Bus Line
	6450 4700 6450 3550
Wire Bus Line
	6450 3150 6450 2000
Wire Bus Line
	6450 2000 2450 2000
Text Label 4050 2550 0    60   ~ 0
ROW0
Text Label 4050 2650 0    60   ~ 0
ROW1
Text Label 4050 2750 0    60   ~ 0
ROW2
Text Label 4050 2850 0    60   ~ 0
ROW3
Text Label 4050 2950 0    60   ~ 0
ROW4
Text Label 4050 3050 0    60   ~ 0
ROW5
Text Label 4050 3150 0    60   ~ 0
ROW6
Text Label 4050 3250 0    60   ~ 0
ROW7
Text Label 4050 3450 0    60   ~ 0
BLU0
Text Label 4050 3550 0    60   ~ 0
BLU1
Text Label 4050 3650 0    60   ~ 0
BLU2
Text Label 4050 3750 0    60   ~ 0
BLU3
Text Label 4050 3850 0    60   ~ 0
BLU4
Text Label 4050 3950 0    60   ~ 0
BLU5
Text Label 4050 4050 0    60   ~ 0
BLU6
Text Label 4050 4150 0    60   ~ 0
BLU7
Text Label 5950 2550 0    60   ~ 0
RED0
Text Label 5950 2650 0    60   ~ 0
RED1
Text Label 5950 2750 0    60   ~ 0
RED2
Text Label 5950 2850 0    60   ~ 0
RED3
Text Label 5950 2950 0    60   ~ 0
RED4
Text Label 5950 3050 0    60   ~ 0
RED5
Text Label 5950 3150 0    60   ~ 0
RED6
Text Label 5950 3250 0    60   ~ 0
RED7
Text Label 5950 3450 0    60   ~ 0
GRN0
Text Label 5950 3550 0    60   ~ 0
GRN1
Text Label 5950 3650 0    60   ~ 0
GRN2
Text Label 5950 3750 0    60   ~ 0
GRN3
Text Label 5950 3850 0    60   ~ 0
GRN4
Text Label 5950 3950 0    60   ~ 0
GRN5
Text Label 5950 4050 0    60   ~ 0
GRN6
Text Label 5950 4150 0    60   ~ 0
GRN7
$EndSCHEMATC
