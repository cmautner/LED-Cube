EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
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
LIBS:shield_arduino
LIBS:LED breakout board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L 8x8_LED_Matrix U?
U 1 1 56F4BEA6
P 2950 2000
F 0 "U?" H 3150 850 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 2900 2850 60  0000 C CNN
F 2 "" H 2900 2850 60  0000 C CNN
F 3 "" H 2900 2850 60  0000 C CNN
	1    2950 2000
	1    0    0    -1  
$EndComp
$Comp
L 8x8_LED_Matrix U?
U 1 1 56F4BEAD
P 2950 4600
F 0 "U?" H 3150 3450 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 2900 5450 60  0000 C CNN
F 2 "" H 2900 5450 60  0000 C CNN
F 3 "" H 2900 5450 60  0000 C CNN
	1    2950 4600
	1    0    0    -1  
$EndComp
$Comp
L 8x8_LED_Matrix U?
U 1 1 56F4BEB4
P 5900 4600
F 0 "U?" H 6100 3450 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 5850 5450 60  0000 C CNN
F 2 "" H 5850 5450 60  0000 C CNN
F 3 "" H 5850 5450 60  0000 C CNN
	1    5900 4600
	1    0    0    -1  
$EndComp
$Comp
L 8x8_LED_Matrix U?
U 1 1 56F4BEBB
P 5900 2000
F 0 "U?" H 6100 850 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 5850 2850 60  0000 C CNN
F 2 "" H 5850 2850 60  0000 C CNN
F 3 "" H 5850 2850 60  0000 C CNN
	1    5900 2000
	1    0    0    -1  
$EndComp
$Comp
L 8x8_LED_Matrix U?
U 1 1 56F4BEC2
P 8800 2000
F 0 "U?" H 9000 850 60  0000 C CNN
F 1 "8x8_LED_Matrix" H 8750 2850 60  0000 C CNN
F 2 "" H 8750 2850 60  0000 C CNN
F 3 "" H 8750 2850 60  0000 C CNN
	1    8800 2000
	1    0    0    -1  
$EndComp
Entry Bus Bus
	4600 800  4700 900 
Text HLabel 1450 800  0    60   Input ~ 0
ROW[0..7]
Text Label 2550 800  0    60   ~ 0
ROW[0..7]
Entry Bus Bus
	7500 800  7600 900 
Text HLabel 10450 5800 2    60   Output ~ 0
RED[0..7]
Text HLabel 10450 6200 2    60   Output ~ 0
BLU[0..7]
Text HLabel 10450 6000 2    60   Output ~ 0
GRN[0..7]
Entry Bus Bus
	1650 800  1750 900 
Entry Bus Bus
	4500 6100 4600 6200
Entry Bus Bus
	7400 6100 7500 6200
Entry Wire Line
	4500 4900 4600 4800
Entry Wire Line
	4500 5000 4600 4900
Entry Wire Line
	4500 5100 4600 5000
Entry Wire Line
	4500 5200 4600 5100
Entry Wire Line
	4500 5300 4600 5200
Entry Wire Line
	4500 5400 4600 5300
Entry Wire Line
	4500 5500 4600 5400
Entry Wire Line
	4500 5600 4600 5500
Text Label 4900 4800 0    60   ~ 0
BLU0
Text Label 4900 4900 0    60   ~ 0
BLU1
Text Label 4900 5000 0    60   ~ 0
BLU2
Text Label 4900 5100 0    60   ~ 0
BLU3
Text Label 4900 5200 0    60   ~ 0
BLU4
Text Label 4900 5300 0    60   ~ 0
BLU5
Text Label 4900 5400 0    60   ~ 0
BLU6
Text Label 4900 5500 0    60   ~ 0
BLU7
Entry Wire Line
	4500 2300 4600 2200
Entry Wire Line
	4500 2400 4600 2300
Entry Wire Line
	4500 2500 4600 2400
Entry Wire Line
	4500 2600 4600 2500
Entry Wire Line
	4500 2700 4600 2600
Entry Wire Line
	4500 2800 4600 2700
Entry Wire Line
	4500 2900 4600 2800
Entry Wire Line
	4500 3000 4600 2900
Text Label 4900 2200 0    60   ~ 0
BLU0
Text Label 4900 2300 0    60   ~ 0
BLU1
Text Label 4900 2500 0    60   ~ 0
BLU3
Text Label 4900 2600 0    60   ~ 0
BLU4
Text Label 4900 2700 0    60   ~ 0
BLU5
Text Label 4900 2800 0    60   ~ 0
BLU6
Text Label 4900 2900 0    60   ~ 0
BLU7
Text Label 4900 2400 0    60   ~ 0
BLU2
Text Label 8100 6200 0    60   ~ 0
BLU[0..7]
Text Label 9450 1300 0    60   ~ 0
RED0
Text Label 9450 1400 0    60   ~ 0
RED1
Text Label 9450 1500 0    60   ~ 0
RED2
Text Label 9450 1600 0    60   ~ 0
RED3
Text Label 9450 1700 0    60   ~ 0
RED4
Text Label 9450 1800 0    60   ~ 0
RED5
Text Label 9450 1900 0    60   ~ 0
RED6
Text Label 9450 2000 0    60   ~ 0
RED7
Entry Wire Line
	9750 1300 9850 1400
Entry Wire Line
	9750 1400 9850 1500
Entry Wire Line
	9750 1500 9850 1600
Entry Wire Line
	9750 1600 9850 1700
Entry Wire Line
	9750 1700 9850 1800
Entry Wire Line
	9750 1800 9850 1900
Entry Wire Line
	9750 1900 9850 2000
Entry Wire Line
	9750 2000 9850 2100
Text Label 9450 2200 0    60   ~ 0
GRN0
Text Label 9450 2300 0    60   ~ 0
GRN1
Text Label 9450 2400 0    60   ~ 0
GRN2
Text Label 9450 2500 0    60   ~ 0
GRN3
Text Label 9450 2600 0    60   ~ 0
GRN4
Text Label 9450 2700 0    60   ~ 0
GRN5
Text Label 9450 2800 0    60   ~ 0
GRN6
Text Label 9450 2900 0    60   ~ 0
GRN7
Entry Wire Line
	9950 2200 10050 2300
Entry Wire Line
	9950 2300 10050 2400
Entry Wire Line
	9950 2400 10050 2500
Entry Wire Line
	9950 2500 10050 2600
Entry Wire Line
	9950 2600 10050 2700
Entry Wire Line
	9950 2700 10050 2800
Entry Wire Line
	9950 2800 10050 2900
Entry Wire Line
	9950 2900 10050 3000
Text Label 4900 1300 0    60   ~ 0
ROW0
Text Label 4900 1500 0    60   ~ 0
ROW2
Entry Wire Line
	4700 1200 4800 1300
Entry Wire Line
	4700 1300 4800 1400
Entry Wire Line
	4700 1400 4800 1500
Entry Wire Line
	4700 1500 4800 1600
Entry Wire Line
	4700 1600 4800 1700
Entry Wire Line
	4700 1700 4800 1800
Entry Wire Line
	4700 1800 4800 1900
Entry Wire Line
	4700 1900 4800 2000
Text Label 4900 1400 0    60   ~ 0
ROW1
Text Label 4900 1600 0    60   ~ 0
ROW3
Text Label 4900 1700 0    60   ~ 0
ROW4
Text Label 4900 1800 0    60   ~ 0
ROW5
Text Label 4900 1900 0    60   ~ 0
ROW6
Text Label 4900 2000 0    60   ~ 0
ROW7
Text Label 4900 3900 0    60   ~ 0
ROW0
Text Label 4900 4100 0    60   ~ 0
ROW2
Entry Wire Line
	4700 3800 4800 3900
Entry Wire Line
	4700 3900 4800 4000
Entry Wire Line
	4700 4000 4800 4100
Entry Wire Line
	4700 4100 4800 4200
Entry Wire Line
	4700 4200 4800 4300
Entry Wire Line
	4700 4300 4800 4400
Entry Wire Line
	4700 4400 4800 4500
Entry Wire Line
	4700 4500 4800 4600
Text Label 4900 4000 0    60   ~ 0
ROW1
Text Label 4900 4200 0    60   ~ 0
ROW3
Text Label 4900 4300 0    60   ~ 0
ROW4
Text Label 4900 4400 0    60   ~ 0
ROW5
Text Label 4900 4500 0    60   ~ 0
ROW6
Text Label 4900 4600 0    60   ~ 0
ROW7
Text Label 3600 1300 0    60   ~ 0
RED0
Text Label 3600 1400 0    60   ~ 0
RED1
Text Label 3600 1500 0    60   ~ 0
RED2
Text Label 3600 1600 0    60   ~ 0
RED3
Text Label 3600 1700 0    60   ~ 0
RED4
Text Label 3600 1800 0    60   ~ 0
RED5
Text Label 3600 1900 0    60   ~ 0
RED6
Text Label 3600 2000 0    60   ~ 0
RED7
Entry Wire Line
	3900 1300 4000 1400
Entry Wire Line
	3900 1400 4000 1500
Entry Wire Line
	3900 1500 4000 1600
Entry Wire Line
	3900 1600 4000 1700
Entry Wire Line
	3900 1700 4000 1800
Entry Wire Line
	3900 1800 4000 1900
Entry Wire Line
	3900 1900 4000 2000
Entry Wire Line
	3900 2000 4000 2100
Text Label 3600 2200 0    60   ~ 0
GRN0
Text Label 3600 2300 0    60   ~ 0
GRN1
Text Label 3600 2400 0    60   ~ 0
GRN2
Text Label 3600 2500 0    60   ~ 0
GRN3
Text Label 3600 2600 0    60   ~ 0
GRN4
Text Label 3600 2700 0    60   ~ 0
GRN5
Text Label 3600 2800 0    60   ~ 0
GRN6
Text Label 3600 2900 0    60   ~ 0
GRN7
Entry Wire Line
	4100 2200 4200 2300
Entry Wire Line
	4100 2300 4200 2400
Entry Wire Line
	4100 2400 4200 2500
Entry Wire Line
	4100 2500 4200 2600
Entry Wire Line
	4100 2600 4200 2700
Entry Wire Line
	4100 2700 4200 2800
Entry Wire Line
	4100 2800 4200 2900
Entry Wire Line
	4100 2900 4200 3000
Text Label 3600 3900 0    60   ~ 0
RED0
Text Label 3600 4000 0    60   ~ 0
RED1
Text Label 3600 4100 0    60   ~ 0
RED2
Text Label 3600 4200 0    60   ~ 0
RED3
Text Label 3600 4300 0    60   ~ 0
RED4
Text Label 3600 4400 0    60   ~ 0
RED5
Text Label 3600 4500 0    60   ~ 0
RED6
Text Label 3600 4600 0    60   ~ 0
RED7
Entry Wire Line
	3900 3900 4000 4000
Entry Wire Line
	3900 4000 4000 4100
Entry Wire Line
	3900 4100 4000 4200
Entry Wire Line
	3900 4200 4000 4300
Entry Wire Line
	3900 4300 4000 4400
Entry Wire Line
	3900 4400 4000 4500
Entry Wire Line
	3900 4500 4000 4600
Entry Wire Line
	3900 4600 4000 4700
Text Label 3600 4800 0    60   ~ 0
GRN0
Text Label 3600 4900 0    60   ~ 0
GRN1
Text Label 3600 5000 0    60   ~ 0
GRN2
Text Label 3600 5100 0    60   ~ 0
GRN3
Text Label 3600 5200 0    60   ~ 0
GRN4
Text Label 3600 5300 0    60   ~ 0
GRN5
Text Label 3600 5400 0    60   ~ 0
GRN6
Text Label 3600 5500 0    60   ~ 0
GRN7
Entry Wire Line
	4100 4800 4200 4900
Entry Wire Line
	4100 4900 4200 5000
Entry Wire Line
	4100 5000 4200 5100
Entry Wire Line
	4100 5100 4200 5200
Entry Wire Line
	4100 5200 4200 5300
Entry Wire Line
	4100 5300 4200 5400
Entry Wire Line
	4100 5400 4200 5500
Entry Wire Line
	4100 5500 4200 5600
Entry Bus Bus
	4200 5900 4300 6000
Entry Bus Bus
	4000 5700 4100 5800
Entry Wire Line
	1550 2300 1650 2200
Entry Wire Line
	1550 2400 1650 2300
Entry Wire Line
	1550 2500 1650 2400
Entry Wire Line
	1550 2600 1650 2500
Entry Wire Line
	1550 2700 1650 2600
Entry Wire Line
	1550 2800 1650 2700
Entry Wire Line
	1550 2900 1650 2800
Entry Wire Line
	1550 3000 1650 2900
Text Label 1950 2200 0    60   ~ 0
BLU0
Text Label 1950 2300 0    60   ~ 0
BLU1
Text Label 1950 2500 0    60   ~ 0
BLU3
Text Label 1950 2600 0    60   ~ 0
BLU4
Text Label 1950 2700 0    60   ~ 0
BLU5
Text Label 1950 2800 0    60   ~ 0
BLU6
Text Label 1950 2900 0    60   ~ 0
BLU7
Text Label 1950 2400 0    60   ~ 0
BLU2
Text Label 1950 1300 0    60   ~ 0
ROW0
Text Label 1950 1500 0    60   ~ 0
ROW2
Entry Wire Line
	1750 1200 1850 1300
Entry Wire Line
	1750 1300 1850 1400
Entry Wire Line
	1750 1400 1850 1500
Entry Wire Line
	1750 1500 1850 1600
Entry Wire Line
	1750 1600 1850 1700
Entry Wire Line
	1750 1700 1850 1800
Entry Wire Line
	1750 1800 1850 1900
Entry Wire Line
	1750 1900 1850 2000
Text Label 1950 1400 0    60   ~ 0
ROW1
Text Label 1950 1600 0    60   ~ 0
ROW3
Text Label 1950 1700 0    60   ~ 0
ROW4
Text Label 1950 1800 0    60   ~ 0
ROW5
Text Label 1950 1900 0    60   ~ 0
ROW6
Text Label 1950 2000 0    60   ~ 0
ROW7
Entry Wire Line
	1550 4900 1650 4800
Entry Wire Line
	1550 5000 1650 4900
Entry Wire Line
	1550 5100 1650 5000
Entry Wire Line
	1550 5200 1650 5100
Entry Wire Line
	1550 5300 1650 5200
Entry Wire Line
	1550 5400 1650 5300
Entry Wire Line
	1550 5500 1650 5400
Entry Wire Line
	1550 5600 1650 5500
Text Label 1950 4800 0    60   ~ 0
BLU0
Text Label 1950 4900 0    60   ~ 0
BLU1
Text Label 1950 5100 0    60   ~ 0
BLU3
Text Label 1950 5200 0    60   ~ 0
BLU4
Text Label 1950 5300 0    60   ~ 0
BLU5
Text Label 1950 5400 0    60   ~ 0
BLU6
Text Label 1950 5500 0    60   ~ 0
BLU7
Text Label 1950 5000 0    60   ~ 0
BLU2
Text Label 1950 3900 0    60   ~ 0
ROW0
Text Label 1950 4100 0    60   ~ 0
ROW2
Entry Wire Line
	1750 3800 1850 3900
Entry Wire Line
	1750 3900 1850 4000
Entry Wire Line
	1750 4000 1850 4100
Entry Wire Line
	1750 4100 1850 4200
Entry Wire Line
	1750 4200 1850 4300
Entry Wire Line
	1750 4300 1850 4400
Entry Wire Line
	1750 4400 1850 4500
Entry Wire Line
	1750 4500 1850 4600
Text Label 1950 4000 0    60   ~ 0
ROW1
Text Label 1950 4200 0    60   ~ 0
ROW3
Text Label 1950 4300 0    60   ~ 0
ROW4
Text Label 1950 4400 0    60   ~ 0
ROW5
Text Label 1950 4500 0    60   ~ 0
ROW6
Text Label 1950 4600 0    60   ~ 0
ROW7
Entry Wire Line
	7400 2300 7500 2200
Entry Wire Line
	7400 2400 7500 2300
Entry Wire Line
	7400 2500 7500 2400
Entry Wire Line
	7400 2600 7500 2500
Entry Wire Line
	7400 2700 7500 2600
Entry Wire Line
	7400 2800 7500 2700
Entry Wire Line
	7400 2900 7500 2800
Entry Wire Line
	7400 3000 7500 2900
Text Label 7800 2200 0    60   ~ 0
BLU0
Text Label 7800 2300 0    60   ~ 0
BLU1
Text Label 7800 2500 0    60   ~ 0
BLU3
Text Label 7800 2600 0    60   ~ 0
BLU4
Text Label 7800 2700 0    60   ~ 0
BLU5
Text Label 7800 2800 0    60   ~ 0
BLU6
Text Label 7800 2900 0    60   ~ 0
BLU7
Text Label 7800 2400 0    60   ~ 0
BLU2
Text Label 7800 1300 0    60   ~ 0
ROW0
Text Label 7800 1500 0    60   ~ 0
ROW2
Entry Wire Line
	7600 1200 7700 1300
Entry Wire Line
	7600 1300 7700 1400
Entry Wire Line
	7600 1400 7700 1500
Entry Wire Line
	7600 1500 7700 1600
Entry Wire Line
	7600 1600 7700 1700
Entry Wire Line
	7600 1700 7700 1800
Entry Wire Line
	7600 1800 7700 1900
Entry Wire Line
	7600 1900 7700 2000
Text Label 7800 1400 0    60   ~ 0
ROW1
Text Label 7800 1600 0    60   ~ 0
ROW3
Text Label 7800 1700 0    60   ~ 0
ROW4
Text Label 7800 1800 0    60   ~ 0
ROW5
Text Label 7800 1900 0    60   ~ 0
ROW6
Text Label 7800 2000 0    60   ~ 0
ROW7
Entry Bus Bus
	1550 6100 1650 6200
Wire Bus Line
	1450 800  7500 800 
Wire Bus Line
	4700 900  4700 4500
Wire Wire Line
	4600 4800 5400 4800
Wire Wire Line
	5400 4900 4600 4900
Wire Wire Line
	4600 5000 5400 5000
Wire Wire Line
	5400 5100 4600 5100
Wire Wire Line
	4600 5200 5400 5200
Wire Wire Line
	5400 5300 4600 5300
Wire Wire Line
	4600 5400 5400 5400
Wire Wire Line
	5400 5500 4600 5500
Wire Wire Line
	4600 2600 5200 2600
Wire Wire Line
	4600 2700 5200 2700
Wire Wire Line
	4600 2800 5200 2800
Wire Wire Line
	4600 2900 5200 2900
Wire Wire Line
	4600 2200 5200 2200
Wire Wire Line
	4600 2300 5200 2300
Wire Wire Line
	5200 2400 4600 2400
Wire Wire Line
	4600 2500 5200 2500
Wire Bus Line
	4500 2300 4500 6100
Wire Wire Line
	9400 1300 9750 1300
Wire Wire Line
	9400 1400 9750 1400
Wire Wire Line
	9400 1500 9750 1500
Wire Wire Line
	9400 1600 9750 1600
Wire Wire Line
	9400 1700 9750 1700
Wire Wire Line
	9400 1800 9750 1800
Wire Wire Line
	9400 1900 9750 1900
Wire Wire Line
	9400 2000 9750 2000
Wire Wire Line
	9400 2200 9950 2200
Wire Wire Line
	9400 2300 9950 2300
Wire Wire Line
	9400 2400 9950 2400
Wire Wire Line
	9400 2500 9950 2500
Wire Wire Line
	9400 2600 9950 2600
Wire Wire Line
	9400 2700 9950 2700
Wire Wire Line
	9400 2800 9950 2800
Wire Wire Line
	9400 2900 9950 2900
Wire Bus Line
	9850 1400 9850 5700
Wire Bus Line
	10050 2300 10050 5900
Wire Wire Line
	4800 1300 5200 1300
Wire Wire Line
	5200 1400 4800 1400
Wire Wire Line
	4800 1500 5200 1500
Wire Wire Line
	4800 1600 5200 1600
Wire Wire Line
	4800 1700 5200 1700
Wire Wire Line
	4800 2000 5200 2000
Wire Wire Line
	5200 1900 4800 1900
Wire Wire Line
	4800 1800 5200 1800
Wire Wire Line
	4800 3900 5200 3900
Wire Wire Line
	5200 4000 4800 4000
Wire Wire Line
	4800 4100 5200 4100
Wire Wire Line
	4800 4200 5200 4200
Wire Wire Line
	4800 4300 5200 4300
Wire Wire Line
	4800 4600 5200 4600
Wire Wire Line
	5200 4500 4800 4500
Wire Wire Line
	4800 4400 5200 4400
Wire Wire Line
	3550 1300 3900 1300
Wire Wire Line
	3550 1400 3900 1400
Wire Wire Line
	3550 1500 3900 1500
Wire Wire Line
	3550 1600 3900 1600
Wire Wire Line
	3550 1700 3900 1700
Wire Wire Line
	3550 1800 3900 1800
Wire Wire Line
	3550 1900 3900 1900
Wire Wire Line
	3550 2000 3900 2000
Wire Wire Line
	3550 2200 4100 2200
Wire Wire Line
	3550 2300 4100 2300
Wire Wire Line
	3550 2400 4100 2400
Wire Wire Line
	3550 2500 4100 2500
Wire Wire Line
	3550 2600 4100 2600
Wire Wire Line
	3550 2700 4100 2700
Wire Wire Line
	3550 2800 4100 2800
Wire Wire Line
	3550 2900 4100 2900
Wire Wire Line
	3550 3900 3900 3900
Wire Wire Line
	3550 4000 3900 4000
Wire Wire Line
	3550 4100 3900 4100
Wire Wire Line
	3550 4200 3900 4200
Wire Wire Line
	3550 4300 3900 4300
Wire Wire Line
	3550 4400 3900 4400
Wire Wire Line
	3550 4500 3900 4500
Wire Wire Line
	3550 4600 3900 4600
Wire Wire Line
	3550 4800 4100 4800
Wire Wire Line
	3550 4900 4100 4900
Wire Wire Line
	3550 5000 4100 5000
Wire Wire Line
	3550 5100 4100 5100
Wire Wire Line
	3550 5200 4100 5200
Wire Wire Line
	3550 5300 4100 5300
Wire Wire Line
	3550 5400 4100 5400
Wire Wire Line
	3550 5500 4100 5500
Wire Bus Line
	4200 2300 4200 5900
Wire Bus Line
	4300 6000 10450 6000
Wire Bus Line
	4000 1400 4000 5700
Wire Wire Line
	1650 2600 2250 2600
Wire Wire Line
	1650 2700 2250 2700
Wire Wire Line
	1650 2800 2250 2800
Wire Wire Line
	1650 2900 2250 2900
Wire Wire Line
	1650 2200 2250 2200
Wire Wire Line
	1650 2300 2250 2300
Wire Wire Line
	2250 2400 1650 2400
Wire Wire Line
	1650 2500 2250 2500
Wire Wire Line
	1850 1300 2250 1300
Wire Wire Line
	2250 1400 1850 1400
Wire Wire Line
	1850 1500 2250 1500
Wire Wire Line
	1850 1600 2250 1600
Wire Wire Line
	1850 1700 2250 1700
Wire Wire Line
	1850 2000 2250 2000
Wire Wire Line
	2250 1900 1850 1900
Wire Wire Line
	1850 1800 2250 1800
Wire Bus Line
	1750 900  1750 4500
Wire Wire Line
	1650 5200 2250 5200
Wire Wire Line
	1650 5300 2250 5300
Wire Wire Line
	1650 5400 2250 5400
Wire Wire Line
	1650 5500 2250 5500
Wire Wire Line
	1650 4800 2250 4800
Wire Wire Line
	1650 4900 2250 4900
Wire Wire Line
	2250 5000 1650 5000
Wire Wire Line
	1650 5100 2250 5100
Wire Wire Line
	1850 3900 2250 3900
Wire Wire Line
	2250 4000 1850 4000
Wire Wire Line
	1850 4100 2250 4100
Wire Wire Line
	1850 4200 2250 4200
Wire Wire Line
	1850 4300 2250 4300
Wire Wire Line
	1850 4600 2250 4600
Wire Wire Line
	2250 4500 1850 4500
Wire Wire Line
	1850 4400 2250 4400
Wire Bus Line
	1650 6200 10450 6200
Wire Bus Line
	1550 2300 1550 6100
Wire Bus Line
	7600 900  7600 1900
Wire Wire Line
	7500 2600 8100 2600
Wire Wire Line
	7500 2700 8100 2700
Wire Wire Line
	7500 2800 8100 2800
Wire Wire Line
	7500 2900 8100 2900
Wire Wire Line
	7500 2200 8100 2200
Wire Wire Line
	7500 2300 8100 2300
Wire Wire Line
	8100 2400 7500 2400
Wire Wire Line
	7500 2500 8100 2500
Wire Bus Line
	7400 2300 7400 6100
Wire Wire Line
	7700 1300 8100 1300
Wire Wire Line
	8100 1400 7700 1400
Wire Wire Line
	7700 1500 8100 1500
Wire Wire Line
	7700 1600 8100 1600
Wire Wire Line
	7700 1700 8100 1700
Wire Wire Line
	7700 2000 8100 2000
Wire Wire Line
	8100 1900 7700 1900
Wire Wire Line
	7700 1800 8100 1800
Wire Bus Line
	4100 5800 10450 5800
Text Label 6550 1300 0    60   ~ 0
RED0
Text Label 6550 1400 0    60   ~ 0
RED1
Text Label 6550 1500 0    60   ~ 0
RED2
Text Label 6550 1600 0    60   ~ 0
RED3
Text Label 6550 1700 0    60   ~ 0
RED4
Text Label 6550 1800 0    60   ~ 0
RED5
Text Label 6550 1900 0    60   ~ 0
RED6
Text Label 6550 2000 0    60   ~ 0
RED7
Entry Wire Line
	6850 1300 6950 1400
Entry Wire Line
	6850 1400 6950 1500
Entry Wire Line
	6850 1500 6950 1600
Entry Wire Line
	6850 1600 6950 1700
Entry Wire Line
	6850 1700 6950 1800
Entry Wire Line
	6850 1800 6950 1900
Entry Wire Line
	6850 1900 6950 2000
Entry Wire Line
	6850 2000 6950 2100
Text Label 6550 2200 0    60   ~ 0
GRN0
Text Label 6550 2300 0    60   ~ 0
GRN1
Text Label 6550 2400 0    60   ~ 0
GRN2
Text Label 6550 2500 0    60   ~ 0
GRN3
Text Label 6550 2600 0    60   ~ 0
GRN4
Text Label 6550 2700 0    60   ~ 0
GRN5
Text Label 6550 2800 0    60   ~ 0
GRN6
Text Label 6550 2900 0    60   ~ 0
GRN7
Entry Wire Line
	7050 2200 7150 2300
Entry Wire Line
	7050 2300 7150 2400
Entry Wire Line
	7050 2400 7150 2500
Entry Wire Line
	7050 2500 7150 2600
Entry Wire Line
	7050 2600 7150 2700
Entry Wire Line
	7050 2700 7150 2800
Entry Wire Line
	7050 2800 7150 2900
Entry Wire Line
	7050 2900 7150 3000
Wire Wire Line
	6500 1300 6850 1300
Wire Wire Line
	6500 1400 6850 1400
Wire Wire Line
	6500 1500 6850 1500
Wire Wire Line
	6500 1600 6850 1600
Wire Wire Line
	6500 1700 6850 1700
Wire Wire Line
	6500 1800 6850 1800
Wire Wire Line
	6500 1900 6850 1900
Wire Wire Line
	6500 2000 6850 2000
Wire Wire Line
	6500 2200 7050 2200
Wire Wire Line
	6500 2300 7050 2300
Wire Wire Line
	6500 2400 7050 2400
Wire Wire Line
	6500 2500 7050 2500
Wire Wire Line
	6500 2600 7050 2600
Wire Wire Line
	6500 2700 7050 2700
Wire Wire Line
	6500 2800 7050 2800
Wire Wire Line
	6500 2900 7050 2900
Wire Bus Line
	7150 2300 7150 5900
Wire Bus Line
	6950 1400 6950 5700
Text Label 6550 3900 0    60   ~ 0
RED0
Text Label 6550 4000 0    60   ~ 0
RED1
Text Label 6550 4100 0    60   ~ 0
RED2
Text Label 6550 4200 0    60   ~ 0
RED3
Text Label 6550 4300 0    60   ~ 0
RED4
Text Label 6550 4400 0    60   ~ 0
RED5
Text Label 6550 4500 0    60   ~ 0
RED6
Text Label 6550 4600 0    60   ~ 0
RED7
Entry Wire Line
	6850 3900 6950 4000
Entry Wire Line
	6850 4000 6950 4100
Entry Wire Line
	6850 4100 6950 4200
Entry Wire Line
	6850 4200 6950 4300
Entry Wire Line
	6850 4300 6950 4400
Entry Wire Line
	6850 4400 6950 4500
Entry Wire Line
	6850 4500 6950 4600
Entry Wire Line
	6850 4600 6950 4700
Text Label 6550 4800 0    60   ~ 0
GRN0
Text Label 6550 4900 0    60   ~ 0
GRN1
Text Label 6550 5000 0    60   ~ 0
GRN2
Text Label 6550 5100 0    60   ~ 0
GRN3
Text Label 6550 5200 0    60   ~ 0
GRN4
Text Label 6550 5300 0    60   ~ 0
GRN5
Text Label 6550 5400 0    60   ~ 0
GRN6
Text Label 6550 5500 0    60   ~ 0
GRN7
Entry Wire Line
	7050 4800 7150 4900
Entry Wire Line
	7050 4900 7150 5000
Entry Wire Line
	7050 5000 7150 5100
Entry Wire Line
	7050 5100 7150 5200
Entry Wire Line
	7050 5200 7150 5300
Entry Wire Line
	7050 5300 7150 5400
Entry Wire Line
	7050 5400 7150 5500
Entry Wire Line
	7050 5500 7150 5600
Wire Wire Line
	6500 3900 6850 3900
Wire Wire Line
	6500 4000 6850 4000
Wire Wire Line
	6500 4100 6850 4100
Wire Wire Line
	6500 4200 6850 4200
Wire Wire Line
	6500 4300 6850 4300
Wire Wire Line
	6500 4400 6850 4400
Wire Wire Line
	6500 4500 6850 4500
Wire Wire Line
	6500 4600 6850 4600
Wire Wire Line
	6500 4800 7050 4800
Wire Wire Line
	6500 4900 7050 4900
Wire Wire Line
	6500 5000 7050 5000
Wire Wire Line
	6500 5100 7050 5100
Wire Wire Line
	6500 5200 7050 5200
Wire Wire Line
	6500 5300 7050 5300
Wire Wire Line
	6500 5400 7050 5400
Wire Wire Line
	6500 5500 7050 5500
Entry Bus Bus
	7150 5900 7250 6000
Entry Bus Bus
	6950 5700 7050 5800
Text Label 8100 6000 0    60   ~ 0
GRN[0..7]
Text Label 8100 5800 0    60   ~ 0
RED[0..7]
Entry Bus Bus
	9850 5700 9950 5800
Entry Bus Bus
	10050 5900 10150 6000
$EndSCHEMATC
