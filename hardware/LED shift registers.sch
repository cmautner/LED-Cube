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
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 10
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Entry Wire Line
	6900 4850 7000 4950
Entry Wire Line
	6900 4950 7000 5050
Entry Wire Line
	6900 5050 7000 5150
Entry Wire Line
	6900 5150 7000 5250
Entry Wire Line
	6900 5250 7000 5350
Entry Wire Line
	6900 5350 7000 5450
Entry Wire Line
	6900 5450 7000 5550
Entry Wire Line
	6900 5550 7000 5650
Entry Wire Line
	6900 2800 7000 2700
Entry Wire Line
	6900 2700 7000 2600
Entry Wire Line
	6900 2600 7000 2500
Entry Wire Line
	6900 2500 7000 2400
Entry Wire Line
	6900 2400 7000 2300
Entry Wire Line
	6900 2300 7000 2200
Entry Wire Line
	6900 2200 7000 2100
Entry Wire Line
	6900 4050 7000 4150
Entry Wire Line
	6900 4150 7000 4250
Entry Wire Line
	6900 4250 7000 4350
Entry Wire Line
	6900 4350 7000 4450
Entry Wire Line
	6900 4450 7000 4550
Entry Wire Line
	6900 4550 7000 4650
Entry Wire Line
	6900 4750 7000 4850
Text HLabel 900  1200 0    60   Input ~ 0
SIN
Text HLabel 900  2700 0    60   Input ~ 0
BLANK
Text HLabel 900  2800 0    60   Input ~ 0
LAT
Text HLabel 900  2900 0    60   Input ~ 0
SCLK
Wire Wire Line
	5500 4750 6900 4750
Wire Wire Line
	5500 4650 6900 4650
Wire Wire Line
	5500 4550 6900 4550
Wire Wire Line
	5500 4450 6900 4450
Wire Wire Line
	5500 4350 6900 4350
Wire Wire Line
	5500 4250 6900 4250
Wire Wire Line
	5500 4150 6900 4150
Wire Wire Line
	5500 4050 6900 4050
Wire Wire Line
	5500 4950 6900 4950
Wire Wire Line
	5500 5050 6900 5050
Wire Wire Line
	5500 5150 6900 5150
Wire Wire Line
	5500 5250 6900 5250
Wire Wire Line
	5500 5350 6900 5350
Wire Wire Line
	5500 5450 6900 5450
Wire Wire Line
	5500 5550 6900 5550
Wire Bus Line
	7000 4150 7000 4850
Wire Bus Line
	7000 2100 9200 2100
Wire Bus Line
	7000 2100 7000 2800
Wire Wire Line
	4100 3350 6250 3350
Wire Wire Line
	6250 3350 6250 1200
Wire Wire Line
	900  1200 4200 1200
Connection ~ 3300 2700
Connection ~ 3200 2800
Connection ~ 3100 2900
Wire Wire Line
	3300 2700 3300 5350
Wire Wire Line
	3200 2800 3200 5450
Wire Wire Line
	3100 2900 3100 5550
Wire Wire Line
	4100 3350 4100 3850
Wire Wire Line
	4100 3850 4200 3850
Wire Wire Line
	900  2900 4200 2900
Wire Wire Line
	900  2800 4200 2800
Wire Wire Line
	900  2700 4200 2700
Wire Wire Line
	4100 4150 4200 4150
Wire Wire Line
	4100 4150 4100 4250
Wire Wire Line
	4200 1500 4100 1500
Wire Wire Line
	4100 1500 4100 1650
$Comp
L R R1
U 1 1 56F5353C
P 4100 1800
AR Path="/56F4B2FA/56F5353C" Ref="R1"  Part="1" 
AR Path="/56F5A6C5/56F5353C" Ref="R3"  Part="1" 
AR Path="/56F5A6EB/56F5353C" Ref="R5"  Part="1" 
AR Path="/56F58BAF/56F5353C" Ref="R7"  Part="1" 
F 0 "R7" V 4180 1800 50  0000 C CNN
F 1 "2.2K" V 4100 1800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4030 1800 50  0001 C CNN
F 3 "" H 4100 1800 50  0000 C CNN
	1    4100 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1950 4100 2050
$Comp
L GND #PWR033
U 1 1 56F535C0
P 4100 2050
AR Path="/56F4B2FA/56F535C0" Ref="#PWR033"  Part="1" 
AR Path="/56F5A6C5/56F535C0" Ref="#PWR039"  Part="1" 
AR Path="/56F5A6EB/56F535C0" Ref="#PWR045"  Part="1" 
AR Path="/56F58BAF/56F535C0" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 4100 1800 50  0001 C CNN
F 1 "GND" H 4100 1900 50  0000 C CNN
F 2 "" H 4100 2050 50  0000 C CNN
F 3 "" H 4100 2050 50  0000 C CNN
	1    4100 2050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 56F536FF
P 4100 4400
AR Path="/56F4B2FA/56F536FF" Ref="R2"  Part="1" 
AR Path="/56F5A6C5/56F536FF" Ref="R4"  Part="1" 
AR Path="/56F5A6EB/56F536FF" Ref="R6"  Part="1" 
AR Path="/56F58BAF/56F536FF" Ref="R8"  Part="1" 
F 0 "R8" V 4180 4400 50  0000 C CNN
F 1 "2.2K" V 4100 4400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4030 4400 50  0001 C CNN
F 3 "" H 4100 4400 50  0000 C CNN
	1    4100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4550 4100 4650
$Comp
L GND #PWR034
U 1 1 56F53707
P 4100 4650
AR Path="/56F4B2FA/56F53707" Ref="#PWR034"  Part="1" 
AR Path="/56F5A6C5/56F53707" Ref="#PWR040"  Part="1" 
AR Path="/56F5A6EB/56F53707" Ref="#PWR046"  Part="1" 
AR Path="/56F58BAF/56F53707" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 4100 4400 50  0001 C CNN
F 1 "GND" H 4100 4500 50  0000 C CNN
F 2 "" H 4100 4650 50  0000 C CNN
F 3 "" H 4100 4650 50  0000 C CNN
	1    4100 4650
	1    0    0    -1  
$EndComp
Wire Bus Line
	7000 4850 9200 4850
Wire Wire Line
	5500 3850 9200 3850
Entry Wire Line
	6900 2900 7000 2800
Wire Wire Line
	6250 1200 5500 1200
Text Label 7100 2100 0    60   ~ 0
B[0..7]
Text Label 7100 4850 0    60   ~ 0
C[0..7]
Text Label 7150 5650 0    60   ~ 0
D[0..7]
Text HLabel 9200 5650 2    60   Output ~ 0
D[0..7]
Text HLabel 9200 4850 2    60   Output ~ 0
C[0..7]
Text HLabel 9200 3850 2    60   Output ~ 0
SOUT
Text HLabel 9200 2100 2    60   Output ~ 0
B[0..7]
Text Label 3650 1200 0    60   ~ 0
SIN
Text Label 6450 3850 0    60   ~ 0
SOUT
Text Label 6450 1400 0    60   ~ 0
A0
Text Label 6450 1500 0    60   ~ 0
A1
Text Label 6450 1600 0    60   ~ 0
A2
Text Label 6450 1700 0    60   ~ 0
A3
Text Label 6450 1800 0    60   ~ 0
A4
Text Label 6450 1900 0    60   ~ 0
A5
Text Label 6450 2000 0    60   ~ 0
A6
Text Label 6450 2100 0    60   ~ 0
A7
$Comp
L TLC5928 U2
U 1 1 56F87B17
P 4850 1750
AR Path="/56F4B2FA/56F87B17" Ref="U2"  Part="1" 
AR Path="/56F5A6C5/56F87B17" Ref="U4"  Part="1" 
AR Path="/56F5A6EB/56F87B17" Ref="U6"  Part="1" 
AR Path="/56F58BAF/56F87B17" Ref="U9"  Part="1" 
F 0 "U9" H 5100 500 60  0000 C CNN
F 1 "TLC5928" H 4850 2450 60  0000 C CNN
F 2 "Housings_DIP:DIP-24_W7.62mm" H 4850 1750 60  0001 C CNN
F 3 "" H 4850 1750 60  0000 C CNN
	1    4850 1750
	1    0    0    -1  
$EndComp
$Comp
L TLC5928 U3
U 1 1 56F87B4F
P 4850 4400
AR Path="/56F4B2FA/56F87B4F" Ref="U3"  Part="1" 
AR Path="/56F5A6C5/56F87B4F" Ref="U5"  Part="1" 
AR Path="/56F5A6EB/56F87B4F" Ref="U7"  Part="1" 
AR Path="/56F58BAF/56F87B4F" Ref="U10"  Part="1" 
F 0 "U10" H 5100 3150 60  0000 C CNN
F 1 "TLC5928" H 4850 5100 60  0000 C CNN
F 2 "Housings_DIP:DIP-24_W7.62mm" H 4850 4400 60  0001 C CNN
F 3 "" H 4850 4400 60  0000 C CNN
	1    4850 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1400 6900 1400
Wire Wire Line
	6900 1500 5500 1500
Wire Wire Line
	6900 1600 5500 1600
Wire Wire Line
	5500 2200 6900 2200
Wire Wire Line
	5500 2300 6900 2300
Wire Wire Line
	5500 2400 6900 2400
Wire Wire Line
	6900 2500 5500 2500
Wire Wire Line
	5500 2600 6900 2600
Wire Wire Line
	6900 2700 5500 2700
Wire Wire Line
	5500 2800 6900 2800
Wire Wire Line
	6900 2900 5500 2900
Wire Wire Line
	5500 2100 6900 2100
Wire Wire Line
	6900 2000 5500 2000
Wire Wire Line
	6900 1900 5500 1900
Wire Wire Line
	6900 1800 5500 1800
Wire Wire Line
	6900 1700 5500 1700
Entry Wire Line
	6900 2000 7000 1900
Entry Wire Line
	6900 1900 7000 1800
Entry Wire Line
	6900 1800 7000 1700
Entry Wire Line
	6900 1700 7000 1600
Entry Wire Line
	6900 1600 7000 1500
Entry Wire Line
	6900 1500 7000 1400
Entry Wire Line
	6900 1400 7000 1300
Wire Bus Line
	7000 1300 7000 2000
Entry Wire Line
	6900 2100 7000 2000
Wire Bus Line
	7000 1300 9200 1300
Text HLabel 9200 1300 2    60   Output ~ 0
A[0..7]
Entry Wire Line
	6900 4650 7000 4750
Text Label 6450 4050 0    60   ~ 0
C0
Text Label 6450 4150 0    60   ~ 0
C1
Text Label 6450 4250 0    60   ~ 0
C2
Text Label 6450 4350 0    60   ~ 0
C3
Text Label 6450 4450 0    60   ~ 0
C4
Text Label 6450 4550 0    60   ~ 0
C5
Text Label 6450 4650 0    60   ~ 0
C6
Text Label 6450 4750 0    60   ~ 0
C7
Text Label 7100 1300 0    60   ~ 0
A[0..7]
Wire Bus Line
	7000 4950 7000 5650
Wire Bus Line
	7000 5650 9200 5650
Wire Wire Line
	6900 4850 5500 4850
$Comp
L C C12
U 1 1 5708C939
P 3750 4500
AR Path="/56F4B2FA/5708C939" Ref="C12"  Part="1" 
AR Path="/56F5A6C5/5708C939" Ref="C14"  Part="1" 
AR Path="/56F5A6EB/5708C939" Ref="C16"  Part="1" 
AR Path="/56F58BAF/5708C939" Ref="C18"  Part="1" 
F 0 "C18" H 3775 4600 50  0000 L CNN
F 1 ".01uF" H 3775 4400 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3788 4350 50  0001 C CNN
F 3 "" H 3750 4500 50  0000 C CNN
	1    3750 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 5708C940
P 3750 4650
AR Path="/56F4B2FA/5708C940" Ref="#PWR035"  Part="1" 
AR Path="/56F5A6C5/5708C940" Ref="#PWR041"  Part="1" 
AR Path="/56F5A6EB/5708C940" Ref="#PWR047"  Part="1" 
AR Path="/56F58BAF/5708C940" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 3750 4400 50  0001 C CNN
F 1 "GND" H 3750 4500 50  0000 C CNN
F 2 "" H 3750 4650 50  0000 C CNN
F 3 "" H 3750 4650 50  0000 C CNN
	1    3750 4650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR036
U 1 1 5708C946
P 3750 4350
AR Path="/56F4B2FA/5708C946" Ref="#PWR036"  Part="1" 
AR Path="/56F5A6C5/5708C946" Ref="#PWR042"  Part="1" 
AR Path="/56F5A6EB/5708C946" Ref="#PWR048"  Part="1" 
AR Path="/56F58BAF/5708C946" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 3750 4200 50  0001 C CNN
F 1 "VCC" H 3750 4500 50  0000 C CNN
F 2 "" H 3750 4350 50  0000 C CNN
F 3 "" H 3750 4350 50  0000 C CNN
	1    3750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 5350 4200 5350
Wire Wire Line
	3200 5450 4200 5450
Wire Wire Line
	3100 5550 4200 5550
$Comp
L C C11
U 1 1 5708D23F
P 3750 1900
AR Path="/56F4B2FA/5708D23F" Ref="C11"  Part="1" 
AR Path="/56F5A6C5/5708D23F" Ref="C13"  Part="1" 
AR Path="/56F5A6EB/5708D23F" Ref="C15"  Part="1" 
AR Path="/56F58BAF/5708D23F" Ref="C17"  Part="1" 
F 0 "C17" H 3775 2000 50  0000 L CNN
F 1 ".01uF" H 3775 1800 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D3_P2.5" H 3788 1750 50  0001 C CNN
F 3 "" H 3750 1900 50  0000 C CNN
	1    3750 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 5708D246
P 3750 2050
AR Path="/56F4B2FA/5708D246" Ref="#PWR037"  Part="1" 
AR Path="/56F5A6C5/5708D246" Ref="#PWR043"  Part="1" 
AR Path="/56F5A6EB/5708D246" Ref="#PWR049"  Part="1" 
AR Path="/56F58BAF/5708D246" Ref="#PWR055"  Part="1" 
F 0 "#PWR055" H 3750 1800 50  0001 C CNN
F 1 "GND" H 3750 1900 50  0000 C CNN
F 2 "" H 3750 2050 50  0000 C CNN
F 3 "" H 3750 2050 50  0000 C CNN
	1    3750 2050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR038
U 1 1 5708D24C
P 3750 1750
AR Path="/56F4B2FA/5708D24C" Ref="#PWR038"  Part="1" 
AR Path="/56F5A6C5/5708D24C" Ref="#PWR044"  Part="1" 
AR Path="/56F5A6EB/5708D24C" Ref="#PWR050"  Part="1" 
AR Path="/56F58BAF/5708D24C" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 3750 1600 50  0001 C CNN
F 1 "VCC" H 3750 1900 50  0000 C CNN
F 2 "" H 3750 1750 50  0000 C CNN
F 3 "" H 3750 1750 50  0000 C CNN
	1    3750 1750
	1    0    0    -1  
$EndComp
Text Label 6450 2200 0    60   ~ 0
B0
Text Label 6450 2300 0    60   ~ 0
B1
Text Label 6450 2400 0    60   ~ 0
B2
Text Label 6450 2500 0    60   ~ 0
B3
Text Label 6450 2600 0    60   ~ 0
B4
Text Label 6450 2700 0    60   ~ 0
B5
Text Label 6450 2800 0    60   ~ 0
B6
Text Label 6450 2900 0    60   ~ 0
B7
Text Label 6450 4850 0    60   ~ 0
D0
Text Label 6450 4950 0    60   ~ 0
D1
Text Label 6450 5050 0    60   ~ 0
D2
Text Label 6450 5150 0    60   ~ 0
D3
Text Label 6450 5250 0    60   ~ 0
D4
Text Label 6450 5350 0    60   ~ 0
D5
Text Label 6450 5450 0    60   ~ 0
D6
Text Label 6450 5550 0    60   ~ 0
D7
$EndSCHEMATC
