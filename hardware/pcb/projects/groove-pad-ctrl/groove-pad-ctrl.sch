EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector_Generic:Conn_01x07 J4
U 1 1 5E4B67FF
P 5750 1400
F 0 "J4" H 5668 875 50  0000 C CNN
F 1 "Conn_01x07" H 5668 966 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 5750 1400 50  0001 C CNN
F 3 "~" H 5750 1400 50  0001 C CNN
	1    5750 1400
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J5
U 1 1 5E4B804E
P 7900 1400
F 0 "J5" H 7818 875 50  0000 C CNN
F 1 "Conn_01x07" H 7818 966 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 7900 1400 50  0001 C CNN
F 3 "~" H 7900 1400 50  0001 C CNN
	1    7900 1400
	1    0    0    1   
$EndComp
$Comp
L cqd_touch_pad:C_Small C6
U 1 1 5E4BA9B3
P 2300 1850
F 0 "C6" H 2100 1800 50  0000 L CNN
F 1 "1n" H 2350 1800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2300 1850 50  0001 C CNN
F 3 "" H 2300 1850 50  0000 C CNN
	1    2300 1850
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:C_Small C1
U 1 1 5E4BC28B
P 2300 1500
F 0 "C1" H 2100 1450 50  0000 L CNN
F 1 "1n" H 2350 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2300 1500 50  0001 C CNN
F 3 "" H 2300 1500 50  0000 C CNN
	1    2300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1750 2450 1750
Wire Wire Line
	2450 1750 2450 1600
Wire Wire Line
	2300 1400 2450 1400
$Comp
L cqd_touch_pad:GND #PWR011
U 1 1 5E4BCCDD
P 2300 1600
F 0 "#PWR011" H 2300 1350 50  0001 C CNN
F 1 "GND" H 2200 1550 50  0000 C CNN
F 2 "" H 2300 1600 50  0000 C CNN
F 3 "" H 2300 1600 50  0000 C CNN
	1    2300 1600
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:GND #PWR016
U 1 1 5E4BD189
P 2300 1950
F 0 "#PWR016" H 2300 1700 50  0001 C CNN
F 1 "GND" H 2300 1800 50  0000 C CNN
F 2 "" H 2300 1950 50  0000 C CNN
F 3 "" H 2300 1950 50  0000 C CNN
	1    2300 1950
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:R R10
U 1 1 5E4BDCC6
P 2100 1400
F 0 "R10" V 2000 1400 50  0000 C CNN
F 1 "33" V 2100 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2030 1400 50  0001 C CNN
F 3 "" H 2100 1400 50  0000 C CNN
	1    2100 1400
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R4
U 1 1 5E4BEC96
P 1900 1100
F 0 "R4" H 1800 1100 50  0000 C CNN
F 1 "100k" V 1900 1100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1830 1100 50  0001 C CNN
F 3 "" H 1900 1100 50  0000 C CNN
	1    1900 1100
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 5E4BF4BB
P 1900 950
F 0 "#PWR02" H 1900 800 50  0001 C CNN
F 1 "+3.3V" H 1915 1123 50  0000 C CNN
F 2 "" H 1900 950 50  0001 C CNN
F 3 "" H 1900 950 50  0001 C CNN
	1    1900 950 
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:R R9
U 1 1 5E4BFA7A
P 1700 1400
F 0 "R9" V 1650 1200 50  0000 C CNN
F 1 "1k" V 1700 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 1400 50  0001 C CNN
F 3 "" H 1700 1400 50  0000 C CNN
	1    1700 1400
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R14
U 1 1 5E4BE7E4
P 2100 1750
F 0 "R14" V 2050 1550 50  0000 C CNN
F 1 "1k" V 2100 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2030 1750 50  0001 C CNN
F 3 "" H 2100 1750 50  0000 C CNN
	1    2100 1750
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R15
U 1 1 5E4C6488
P 1700 1850
F 0 "R15" H 1600 1850 50  0000 C CNN
F 1 "47k" V 1700 1850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 1850 50  0001 C CNN
F 3 "" H 1700 1850 50  0000 C CNN
	1    1700 1850
	0    -1   -1   0   
$EndComp
Text Label 1100 1750 0    50   ~ 0
BOOT_PNL
$Comp
L cqd_touch_pad:GND #PWR014
U 1 1 5E4C73D7
P 1500 1850
F 0 "#PWR014" H 1500 1600 50  0001 C CNN
F 1 "GND" H 1500 1700 50  0000 C CNN
F 2 "" H 1500 1850 50  0000 C CNN
F 3 "" H 1500 1850 50  0000 C CNN
	1    1500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1750 2300 1750
Connection ~ 2300 1750
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5E4C7E39
P 900 1400
F 0 "J3" H 818 1717 50  0000 C CNN
F 1 "Conn_01x03" H 818 1626 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 900 1400 50  0001 C CNN
F 3 "~" H 900 1400 50  0001 C CNN
	1    900  1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 1400 1300 1400
NoConn ~ 1100 1500
Text Label 1150 1300 0    50   ~ 0
~RESET_PNL
Wire Wire Line
	1100 1300 1150 1300
Wire Wire Line
	1850 1400 1900 1400
Wire Wire Line
	1900 1250 1900 1400
Connection ~ 1900 1400
Wire Wire Line
	1900 1400 1950 1400
Wire Wire Line
	2250 1400 2300 1400
Connection ~ 2300 1400
Wire Wire Line
	1100 1750 1900 1750
Wire Wire Line
	1500 1850 1550 1850
Wire Wire Line
	1850 1850 1900 1850
Wire Wire Line
	1900 1850 1900 1750
Connection ~ 1900 1750
Wire Wire Line
	1900 1750 1950 1750
$Comp
L Device:Crystal_Small Y1
U 1 1 5E4CCF82
P 2000 2600
F 0 "Y1" V 1954 2688 50  0000 L CNN
F 1 "8MHz" V 2045 2688 50  0000 L CNN
F 2 "kicadlib:Crystal_SMD_Abracon_ABM3-2pin_5.0x3.2mm_hand" H 2000 2600 50  0001 C CNN
F 3 "~" H 2000 2600 50  0001 C CNN
	1    2000 2600
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:C_Small C9
U 1 1 5E4CDF86
P 1750 2700
F 0 "C9" V 1700 2550 50  0000 L CNN
F 1 "18p" V 1800 2750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1750 2700 50  0001 C CNN
F 3 "" H 1750 2700 50  0000 C CNN
	1    1750 2700
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:C_Small C8
U 1 1 5E4D0123
P 1750 2500
F 0 "C8" V 1700 2350 50  0000 L CNN
F 1 "18p" V 1800 2550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1750 2500 50  0001 C CNN
F 3 "" H 1750 2500 50  0000 C CNN
	1    1750 2500
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR020
U 1 1 5E4D0380
P 1500 2700
F 0 "#PWR020" H 1500 2450 50  0001 C CNN
F 1 "GND" H 1500 2550 50  0000 C CNN
F 2 "" H 1500 2700 50  0000 C CNN
F 3 "" H 1500 2700 50  0000 C CNN
	1    1500 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2700 1600 2700
Wire Wire Line
	1600 2700 1600 2500
Wire Wire Line
	1600 2500 1650 2500
Connection ~ 1600 2700
Wire Wire Line
	1600 2700 1650 2700
Wire Wire Line
	1850 2500 2000 2500
Wire Wire Line
	1850 2700 2000 2700
Wire Wire Line
	2000 2700 2450 2700
Connection ~ 2000 2700
Wire Wire Line
	2000 2500 2200 2500
Wire Wire Line
	2200 2500 2200 2600
Wire Wire Line
	2200 2600 2450 2600
Connection ~ 2000 2500
$Comp
L cqd_touch_pad:C_Small C5
U 1 1 5E4D3884
P 6100 1800
F 0 "C5" H 6192 1846 50  0000 L CNN
F 1 "1u" H 6192 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6192 1709 50  0001 L CNN
F 3 "" H 6100 1800 50  0000 C CNN
	1    6100 1800
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:GND #PWR017
U 1 1 5E4D40A0
P 5950 1950
F 0 "#PWR017" H 5950 1700 50  0001 C CNN
F 1 "GND" H 5950 1800 50  0000 C CNN
F 2 "" H 5950 1950 50  0000 C CNN
F 3 "" H 5950 1950 50  0000 C CNN
	1    5950 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1700 5950 1900
Wire Wire Line
	5950 1900 6100 1900
Connection ~ 5950 1900
Wire Wire Line
	5950 1900 5950 1950
Wire Wire Line
	5950 1600 6100 1600
Wire Wire Line
	6100 1600 6100 1700
$Comp
L cqd_touch_pad:GND #PWR05
U 1 1 5E4D6333
P 5950 1100
F 0 "#PWR05" H 5950 850 50  0001 C CNN
F 1 "GND" V 5950 900 50  0000 C CNN
F 2 "" H 5950 1100 50  0000 C CNN
F 3 "" H 5950 1100 50  0000 C CNN
	1    5950 1100
	0    -1   -1   0   
$EndComp
Connection ~ 6100 1600
NoConn ~ 5950 1500
NoConn ~ 5950 1400
Text Label 6000 1300 0    50   ~ 0
PANEL_ACK
Wire Wire Line
	5950 1300 6000 1300
Wire Wire Line
	6100 1550 6100 1600
$Comp
L Device:Ferrite_Bead FB1
U 1 1 5E4DAB5D
P 6500 1600
F 0 "FB1" V 6226 1600 50  0000 C CNN
F 1 "Ferrite_Bead" V 6317 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6430 1600 50  0001 C CNN
F 3 "~" H 6500 1600 50  0001 C CNN
	1    6500 1600
	0    1    1    0   
$EndComp
$Comp
L power:+3.3VA #PWR012
U 1 1 5E4DB642
P 6900 1600
F 0 "#PWR012" H 6900 1450 50  0001 C CNN
F 1 "+3.3VA" V 6915 1728 50  0000 L CNN
F 2 "" H 6900 1600 50  0001 C CNN
F 3 "" H 6900 1600 50  0001 C CNN
	1    6900 1600
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR010
U 1 1 5E4DBE31
P 6100 1550
F 0 "#PWR010" H 6100 1400 50  0001 C CNN
F 1 "+3.3V" H 6115 1723 50  0000 C CNN
F 2 "" H 6100 1550 50  0001 C CNN
F 3 "" H 6100 1550 50  0001 C CNN
	1    6100 1550
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:C_Small C4
U 1 1 5E4DC632
P 6750 1750
F 0 "C4" H 6550 1700 50  0000 L CNN
F 1 "100n" H 6800 1700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6750 1750 50  0001 C CNN
F 3 "" H 6750 1750 50  0000 C CNN
	1    6750 1750
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:GND #PWR018
U 1 1 5E4DD27E
P 6750 1950
F 0 "#PWR018" H 6750 1700 50  0001 C CNN
F 1 "GND" H 6750 1800 50  0000 C CNN
F 2 "" H 6750 1950 50  0000 C CNN
F 3 "" H 6750 1950 50  0000 C CNN
	1    6750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1950 6750 1850
Wire Wire Line
	6650 1600 6750 1600
Wire Wire Line
	6750 1600 6750 1650
Wire Wire Line
	6750 1600 6900 1600
Connection ~ 6750 1600
$Comp
L cqd_touch_pad:R R1
U 1 1 5E4DF0D9
P 6750 1050
F 0 "R1" H 6650 1050 50  0000 C CNN
F 1 "100k" V 6750 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6680 1050 50  0001 C CNN
F 3 "" H 6750 1050 50  0000 C CNN
	1    6750 1050
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5E4E00F6
P 6750 900
F 0 "#PWR01" H 6750 750 50  0001 C CNN
F 1 "+3.3V" H 6765 1073 50  0000 C CNN
F 2 "" H 6750 900 50  0001 C CNN
F 3 "" H 6750 900 50  0001 C CNN
	1    6750 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1200 5950 1200
$Comp
L cqd_touch_pad:GND #PWR013
U 1 1 5E4E1049
P 7700 1700
F 0 "#PWR013" H 7700 1450 50  0001 C CNN
F 1 "GND" V 7700 1500 50  0000 C CNN
F 2 "" H 7700 1700 50  0000 C CNN
F 3 "" H 7700 1700 50  0000 C CNN
	1    7700 1700
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR06
U 1 1 5E4E309B
P 7700 1100
F 0 "#PWR06" H 7700 850 50  0001 C CNN
F 1 "GND" V 7700 900 50  0000 C CNN
F 2 "" H 7700 1100 50  0000 C CNN
F 3 "" H 7700 1100 50  0000 C CNN
	1    7700 1100
	0    1    1    0   
$EndComp
Text Notes 6500 600  0    50   ~ 0
Main Connector
Wire Notes Line
	8100 650  8100 2200
Wire Notes Line
	8100 2200 5550 2200
Wire Notes Line
	5550 2200 5550 650 
Wire Notes Line
	5550 650  8100 650 
Text Label 7200 1200 0    50   ~ 0
BOOT_PNL
Wire Wire Line
	7200 1200 7700 1200
Text Label 7200 1300 0    50   ~ 0
~RESET_PNL
Wire Wire Line
	7200 1300 7700 1300
Text Label 7200 1400 0    50   ~ 0
TX_PNL
Wire Wire Line
	7200 1400 7700 1400
Text Label 7200 1500 0    50   ~ 0
RX_PNL
Text Label 7350 1600 0    50   ~ 0
CK_PNL
Wire Wire Line
	7350 1600 7700 1600
Wire Wire Line
	7200 1500 7700 1500
$Comp
L MCU_ST_STM32F3:STM32F303R8Tx U1
U 1 1 5E4EB293
P 3150 3000
F 0 "U1" H 3150 3050 50  0000 C CNN
F 1 "STM32F303R8Tx" H 3150 2950 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 2550 1300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00092070.pdf" H 3150 3000 50  0001 C CNN
	1    3150 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J8
U 1 1 5E4F1FC5
P 5400 2900
F 0 "J8" H 5350 3300 50  0000 L CNN
F 1 "Conn_01x05" H 5150 3200 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5400 2900 50  0001 C CNN
F 3 "~" H 5400 2900 50  0001 C CNN
	1    5400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2800 5200 2800
Text Notes 5500 2850 0    50   ~ 0
SWCLK
Text Notes 5500 2750 0    50   ~ 0
3.3V
Text Notes 5500 3050 0    50   ~ 0
SWDIO
Text Notes 5500 2950 0    50   ~ 0
GND
$Comp
L power:+3.3V #PWR021
U 1 1 5E4F45A1
P 5200 2700
F 0 "#PWR021" H 5200 2550 50  0001 C CNN
F 1 "+3.3V" V 5215 2828 50  0000 L CNN
F 2 "" H 5200 2700 50  0001 C CNN
F 3 "" H 5200 2700 50  0001 C CNN
	1    5200 2700
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR023
U 1 1 5E4F700B
P 5200 2900
F 0 "#PWR023" H 5200 2650 50  0001 C CNN
F 1 "GND" V 5200 2700 50  0000 C CNN
F 2 "" H 5200 2900 50  0000 C CNN
F 3 "" H 5200 2900 50  0000 C CNN
	1    5200 2900
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5E4F89B6
P 2950 1050
F 0 "#PWR03" H 2950 900 50  0001 C CNN
F 1 "+3.3V" H 2965 1223 50  0000 C CNN
F 2 "" H 2950 1050 50  0001 C CNN
F 3 "" H 2950 1050 50  0001 C CNN
	1    2950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1050 2950 1100
Wire Wire Line
	2950 1100 3050 1100
Wire Wire Line
	3350 1100 3350 1200
Connection ~ 2950 1100
Wire Wire Line
	2950 1100 2950 1200
Wire Wire Line
	3250 1200 3250 1100
Connection ~ 3250 1100
Wire Wire Line
	3250 1100 3350 1100
Wire Wire Line
	3150 1200 3150 1100
Connection ~ 3150 1100
Wire Wire Line
	3150 1100 3250 1100
Wire Wire Line
	3050 1200 3050 1100
Connection ~ 3050 1100
Wire Wire Line
	3050 1100 3150 1100
$Comp
L power:+3.3VA #PWR04
U 1 1 5E4FFAA4
P 3450 1050
F 0 "#PWR04" H 3450 900 50  0001 C CNN
F 1 "+3.3VA" H 3465 1223 50  0000 C CNN
F 2 "" H 3450 1050 50  0001 C CNN
F 3 "" H 3450 1050 50  0001 C CNN
	1    3450 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 1050 3450 1200
$Comp
L cqd_touch_pad:GND #PWR028
U 1 1 5E5017AD
P 2950 4950
F 0 "#PWR028" H 2950 4700 50  0001 C CNN
F 1 "GND" H 2950 4800 50  0000 C CNN
F 2 "" H 2950 4950 50  0000 C CNN
F 3 "" H 2950 4950 50  0000 C CNN
	1    2950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4950 3350 4800
Wire Wire Line
	2950 4950 2950 4850
Wire Wire Line
	2950 4850 3050 4850
Wire Wire Line
	3250 4850 3250 4800
Connection ~ 2950 4850
Wire Wire Line
	2950 4850 2950 4800
Wire Wire Line
	3150 4800 3150 4850
Connection ~ 3150 4850
Wire Wire Line
	3150 4850 3250 4850
Wire Wire Line
	3050 4800 3050 4850
Connection ~ 3050 4850
Wire Wire Line
	3050 4850 3150 4850
$Comp
L power:GNDA #PWR029
U 1 1 5E508728
P 3350 4950
F 0 "#PWR029" H 3350 4700 50  0001 C CNN
F 1 "GNDA" H 3355 4777 50  0000 C CNN
F 2 "" H 3350 4950 50  0001 C CNN
F 3 "" H 3350 4950 50  0001 C CNN
	1    3350 4950
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:GND #PWR039
U 1 1 5E508D0E
P 6000 7250
F 0 "#PWR039" H 6000 7000 50  0001 C CNN
F 1 "GND" H 6000 7100 50  0000 C CNN
F 2 "" H 6000 7250 50  0000 C CNN
F 3 "" H 6000 7250 50  0000 C CNN
	1    6000 7250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR040
U 1 1 5E509597
P 6150 7250
F 0 "#PWR040" H 6150 7000 50  0001 C CNN
F 1 "GNDA" H 6200 7100 50  0000 C CNN
F 2 "" H 6150 7250 50  0001 C CNN
F 3 "" H 6150 7250 50  0001 C CNN
	1    6150 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 7250 6150 7250
$Comp
L cqd_touch_pad:R R27
U 1 1 5E5102F4
P 4200 4300
F 0 "R27" V 4150 4100 50  0000 C CNN
F 1 "47" V 4200 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 4300 50  0001 C CNN
F 3 "" H 4200 4300 50  0000 C CNN
	1    4200 4300
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R29
U 1 1 5E511595
P 4200 4400
F 0 "R29" V 4150 4200 50  0000 C CNN
F 1 "47" V 4200 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 4400 50  0001 C CNN
F 3 "" H 4200 4400 50  0000 C CNN
	1    4200 4400
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R31
U 1 1 5E5118E7
P 4200 4500
F 0 "R31" V 4150 4300 50  0000 C CNN
F 1 "47" V 4200 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 4500 50  0001 C CNN
F 3 "" H 4200 4500 50  0000 C CNN
	1    4200 4500
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:R R33
U 1 1 5E511AD7
P 4200 4600
F 0 "R33" V 4150 4400 50  0000 C CNN
F 1 "47" V 4200 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 4600 50  0001 C CNN
F 3 "" H 4200 4600 50  0000 C CNN
	1    4200 4600
	0    1    1    0   
$EndComp
Text Label 5350 4300 0    50   ~ 0
PANEL_ACK
Text Label 5350 4400 0    50   ~ 0
CK_PNL
Text Label 5350 4500 0    50   ~ 0
TX_PNL
Text Label 5350 4600 0    50   ~ 0
RX_PNL
$Comp
L power:+3.3V #PWR026
U 1 1 5E512486
P 5200 3750
F 0 "#PWR026" H 5200 3600 50  0001 C CNN
F 1 "+3.3V" H 5350 3800 50  0000 C CNN
F 2 "" H 5200 3750 50  0001 C CNN
F 3 "" H 5200 3750 50  0001 C CNN
	1    5200 3750
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:R R21
U 1 1 5E51455B
P 5000 4050
F 0 "R21" V 4950 3900 50  0000 C CNN
F 1 "47" V 5000 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4930 4050 50  0001 C CNN
F 3 "" H 5000 4050 50  0000 C CNN
	1    5000 4050
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R22
U 1 1 5E514CAD
P 5100 4050
F 0 "R22" V 5050 3900 50  0000 C CNN
F 1 "47" V 5100 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5030 4050 50  0001 C CNN
F 3 "" H 5100 4050 50  0000 C CNN
	1    5100 4050
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R23
U 1 1 5E514E93
P 5200 4050
F 0 "R23" V 5150 3900 50  0000 C CNN
F 1 "47" V 5200 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 4050 50  0001 C CNN
F 3 "" H 5200 4050 50  0000 C CNN
	1    5200 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	5000 4200 5000 4400
Wire Wire Line
	5000 4400 4350 4400
Wire Wire Line
	4350 4500 5100 4500
Wire Wire Line
	5100 4500 5100 4200
Wire Wire Line
	4350 4600 5200 4600
Wire Wire Line
	5200 4600 5200 4200
Wire Wire Line
	4350 4300 5350 4300
Wire Wire Line
	5000 4400 5350 4400
Connection ~ 5000 4400
Wire Wire Line
	5100 4500 5350 4500
Connection ~ 5100 4500
Wire Wire Line
	5200 4600 5350 4600
Connection ~ 5200 4600
Wire Wire Line
	3850 4300 4050 4300
Wire Wire Line
	3850 4400 4050 4400
Wire Wire Line
	3850 4500 4050 4500
Wire Wire Line
	3850 4600 4050 4600
Wire Wire Line
	5000 3800 5100 3800
Wire Wire Line
	5100 3800 5100 3900
Wire Wire Line
	5000 3800 5000 3900
Wire Wire Line
	5100 3800 5200 3800
Wire Wire Line
	5200 3800 5200 3900
Connection ~ 5100 3800
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5E5314B4
P 8700 1150
F 0 "J1" H 8618 1467 50  0000 C CNN
F 1 "TOUCH_L" H 8618 1376 50  0000 C CNN
F 2 "kicadlib:CassettePad" H 8700 1150 50  0001 C CNN
F 3 "~" H 8700 1150 50  0001 C CNN
	1    8700 1150
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5E53A442
P 10850 1150
F 0 "J2" H 10800 1500 50  0000 L CNN
F 1 "TOUCH_R" H 10700 1400 50  0000 L CNN
F 2 "kicadlib:CassettePad" H 10850 1150 50  0001 C CNN
F 3 "~" H 10850 1150 50  0001 C CNN
	1    10850 1150
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:R R2
U 1 1 5E53A787
P 9100 1050
F 0 "R2" V 9150 900 50  0000 C CNN
F 1 "1k" V 9100 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9030 1050 50  0001 C CNN
F 3 "" H 9100 1050 50  0000 C CNN
	1    9100 1050
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R5
U 1 1 5E53F455
P 9100 1150
F 0 "R5" V 9150 1000 50  0000 C CNN
F 1 "1k" V 9100 1150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9030 1150 50  0001 C CNN
F 3 "" H 9100 1150 50  0000 C CNN
	1    9100 1150
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R7
U 1 1 5E53F574
P 9100 1250
F 0 "R7" V 9150 1100 50  0000 C CNN
F 1 "1k" V 9100 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9030 1250 50  0001 C CNN
F 3 "" H 9100 1250 50  0000 C CNN
	1    9100 1250
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R3
U 1 1 5E53F679
P 10450 1050
F 0 "R3" V 10500 900 50  0000 C CNN
F 1 "1k" V 10450 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10380 1050 50  0001 C CNN
F 3 "" H 10450 1050 50  0000 C CNN
	1    10450 1050
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R6
U 1 1 5E53F963
P 10450 1150
F 0 "R6" V 10500 1000 50  0000 C CNN
F 1 "1k" V 10450 1150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10380 1150 50  0001 C CNN
F 3 "" H 10450 1150 50  0000 C CNN
	1    10450 1150
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R8
U 1 1 5E53FA3E
P 10450 1250
F 0 "R8" V 10500 1100 50  0000 C CNN
F 1 "1k" V 10450 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10380 1250 50  0001 C CNN
F 3 "" H 10450 1250 50  0000 C CNN
	1    10450 1250
	0    -1   -1   0   
$EndComp
Wire Notes Line
	8500 650  11050 650 
Text Notes 9550 600  0    50   ~ 0
Touch Pad
Text Label 3900 3400 0    50   ~ 0
G5_I01
Text Label 3900 3500 0    50   ~ 0
G5_I02
Text Label 3900 3700 0    50   ~ 0
G5_I03
Wire Wire Line
	5200 3750 5200 3800
Connection ~ 5200 3800
Text Label 3900 3800 0    50   ~ 0
G5_I04
Wire Wire Line
	3850 3400 3900 3400
Wire Wire Line
	3850 3500 3900 3500
Wire Wire Line
	3850 3700 3900 3700
Wire Wire Line
	3850 3800 3900 3800
Text Label 3900 1400 0    50   ~ 0
G1_I01
Text Label 3900 1500 0    50   ~ 0
G1_I02
Text Label 3900 1600 0    50   ~ 0
G1_I03
Text Label 3900 1700 0    50   ~ 0
G1_I04
Wire Wire Line
	3850 1400 3900 1400
Wire Wire Line
	3850 1500 3900 1500
Wire Wire Line
	3850 1600 3900 1600
Wire Wire Line
	3850 1700 3900 1700
Text Label 9300 1250 0    50   ~ 0
G5_I03
Text Label 9300 1050 0    50   ~ 0
G5_I02
Text Label 9300 1150 0    50   ~ 0
G5_I04
Wire Wire Line
	8900 1050 8950 1050
Wire Wire Line
	8900 1150 8950 1150
Wire Wire Line
	8900 1250 8950 1250
Wire Wire Line
	9250 1050 9300 1050
Wire Wire Line
	9250 1150 9300 1150
Wire Wire Line
	9250 1250 9300 1250
Wire Wire Line
	10600 1050 10650 1050
Wire Wire Line
	10600 1150 10650 1150
Wire Wire Line
	10600 1250 10650 1250
Text Label 10000 1250 0    50   ~ 0
G1_I02
Text Label 10000 1150 0    50   ~ 0
G1_I03
Text Label 10000 1050 0    50   ~ 0
G1_I04
Wire Wire Line
	10000 1050 10300 1050
Wire Wire Line
	10000 1150 10300 1150
Wire Wire Line
	10000 1250 10300 1250
Text Label 9300 1500 0    50   ~ 0
G5_I01
$Comp
L cqd_touch_pad:C_Small C2
U 1 1 5E59ACD3
P 9100 1500
F 0 "C2" V 9000 1450 50  0000 L CNN
F 1 "22n" V 9200 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9100 1500 50  0001 C CNN
F 3 "" H 9100 1500 50  0000 C CNN
	1    9100 1500
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR08
U 1 1 5E59B462
P 8850 1500
F 0 "#PWR08" H 8850 1250 50  0001 C CNN
F 1 "GND" H 8850 1350 50  0000 C CNN
F 2 "" H 8850 1500 50  0000 C CNN
F 3 "" H 8850 1500 50  0000 C CNN
	1    8850 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1500 9000 1500
Wire Wire Line
	9200 1500 9300 1500
Text Label 10000 1500 0    50   ~ 0
G1_I01
$Comp
L cqd_touch_pad:C_Small C3
U 1 1 5E5A2BEA
P 10450 1500
F 0 "C3" V 10350 1450 50  0000 L CNN
F 1 "22n" V 10550 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10450 1500 50  0001 C CNN
F 3 "" H 10450 1500 50  0000 C CNN
	1    10450 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	10000 1500 10350 1500
$Comp
L cqd_touch_pad:GND #PWR09
U 1 1 5E5A6A55
P 10750 1500
F 0 "#PWR09" H 10750 1250 50  0001 C CNN
F 1 "GND" H 10750 1350 50  0000 C CNN
F 2 "" H 10750 1500 50  0000 C CNN
F 3 "" H 10750 1500 50  0000 C CNN
	1    10750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 1500 10750 1500
Text Label 2200 3100 0    50   ~ 0
BTN_A
Text Label 2200 3200 0    50   ~ 0
BTN_B
Text Label 2200 3300 0    50   ~ 0
BTN_C
Text Label 2200 3400 0    50   ~ 0
BTN_D
Text Label 2200 3500 0    50   ~ 0
BTN_1
Text Label 2200 3600 0    50   ~ 0
BTN_2
Text Label 2200 3700 0    50   ~ 0
BTN_3
Text Label 2200 3800 0    50   ~ 0
BTN_4
Text Label 1750 3900 0    50   ~ 0
LED_A
Text Label 1750 4000 0    50   ~ 0
LED_B
Text Label 1750 4100 0    50   ~ 0
LED_C
Text Label 1750 4200 0    50   ~ 0
LED_D
Text Label 1750 4300 0    50   ~ 0
LED_1
Text Label 1750 4400 0    50   ~ 0
LED_2
Text Label 1750 4500 0    50   ~ 0
LED_3
Text Label 1750 4600 0    50   ~ 0
LED_4
Wire Wire Line
	2200 3100 2450 3100
Wire Wire Line
	2200 3200 2450 3200
Wire Wire Line
	2200 3300 2450 3300
Wire Wire Line
	2200 3400 2450 3400
Wire Wire Line
	2200 3500 2450 3500
Wire Wire Line
	2200 3600 2450 3600
Wire Wire Line
	2200 3700 2450 3700
Wire Wire Line
	2200 3800 2450 3800
Text Label 3900 4100 0    50   ~ 0
BTN_MODE
Text Label 3900 2500 0    50   ~ 0
BTN_RUN
Text Label 3900 3100 0    50   ~ 0
BTN_MINUS
Text Label 3900 3200 0    50   ~ 0
BTN_PLUS
Text Label 3900 4200 0    50   ~ 0
LED_MODE
Text Label 3900 2600 0    50   ~ 0
LED_RUN
Wire Wire Line
	3850 2300 3900 2300
$Comp
L Memory_NVRAM:MB85RS2MT U2
U 1 1 5E62232D
P 1450 6300
F 0 "U2" H 1550 6600 50  0000 C CNN
F 1 "MB85RS2MT" H 1750 6050 50  0000 C CNN
F 2 "kicadlib:MB85RS2MT" H 1100 6250 50  0001 C CNN
F 3 "http://www.fujitsu.com/downloads/MICRO/fsa/pdf/products/memory/fram/MB85RS16-DS501-00014-6v0-E.pdf" H 1100 6250 50  0001 C CNN
	1    1450 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2400 3900 2400
Wire Wire Line
	3850 2500 3900 2500
Wire Wire Line
	3850 3100 3900 3100
Wire Wire Line
	3850 3200 3900 3200
Wire Wire Line
	3850 2600 3900 2600
Text Label 4850 1900 0    50   ~ 0
SPI1_SCK
Text Label 4850 2000 0    50   ~ 0
SPI1_MISO
Text Label 4850 2100 0    50   ~ 0
SPI1_MOSI
Wire Wire Line
	3850 1900 4850 1900
Wire Wire Line
	3850 2000 4400 2000
Wire Wire Line
	3850 2100 4550 2100
Text Label 4850 2200 0    50   ~ 0
~RAM_CS
Wire Wire Line
	3850 2200 4700 2200
Wire Wire Line
	3850 2700 4850 2700
Wire Wire Line
	4850 2700 4850 3000
Wire Wire Line
	4850 3000 5200 3000
Text Label 4450 2900 0    50   ~ 0
~OLED_CS
Wire Wire Line
	3850 2900 4400 2900
$Comp
L cqd_touch_pad:R R17
U 1 1 5E6A6688
P 4400 2500
F 0 "R17" H 4300 2500 50  0000 C CNN
F 1 "10k" V 4400 2500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4330 2500 50  0001 C CNN
F 3 "" H 4400 2500 50  0000 C CNN
	1    4400 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4400 2650 4400 2900
Connection ~ 4400 2900
Wire Wire Line
	4400 2900 4450 2900
$Comp
L power:+3.3V #PWR019
U 1 1 5E6AD72F
P 4400 2350
F 0 "#PWR019" H 4400 2200 50  0001 C CNN
F 1 "+3.3V" H 4550 2400 50  0000 C CNN
F 2 "" H 4400 2350 50  0001 C CNN
F 3 "" H 4400 2350 50  0001 C CNN
	1    4400 2350
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:R R11
U 1 1 5E6ADCDE
P 4400 1650
F 0 "R11" V 4450 1500 50  0000 C CNN
F 1 "10k" V 4400 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4330 1650 50  0001 C CNN
F 3 "" H 4400 1650 50  0000 C CNN
	1    4400 1650
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R12
U 1 1 5E6AE3BE
P 4550 1650
F 0 "R12" V 4600 1500 50  0000 C CNN
F 1 "10k" V 4550 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4480 1650 50  0001 C CNN
F 3 "" H 4550 1650 50  0000 C CNN
	1    4550 1650
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R13
U 1 1 5E6AE5C3
P 4700 1650
F 0 "R13" V 4750 1500 50  0000 C CNN
F 1 "10k" V 4700 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4630 1650 50  0001 C CNN
F 3 "" H 4700 1650 50  0000 C CNN
	1    4700 1650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4400 1800 4400 2000
Connection ~ 4400 2000
Wire Wire Line
	4400 2000 4850 2000
Wire Wire Line
	4550 1800 4550 2100
Connection ~ 4550 2100
Wire Wire Line
	4550 2100 4850 2100
Wire Wire Line
	4700 1800 4700 2200
Connection ~ 4700 2200
Wire Wire Line
	4700 2200 4850 2200
$Comp
L power:+3.3V #PWR07
U 1 1 5E6C3863
P 4400 1350
F 0 "#PWR07" H 4400 1200 50  0001 C CNN
F 1 "+3.3V" H 4550 1400 50  0000 C CNN
F 2 "" H 4400 1350 50  0001 C CNN
F 3 "" H 4400 1350 50  0001 C CNN
	1    4400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1350 4400 1400
Wire Wire Line
	4400 1400 4550 1400
Wire Wire Line
	4550 1400 4550 1500
Connection ~ 4400 1400
Wire Wire Line
	4400 1400 4400 1500
Wire Wire Line
	4550 1400 4700 1400
Wire Wire Line
	4700 1400 4700 1500
Connection ~ 4550 1400
$Comp
L cqd_touch_pad:R R35
U 1 1 5E6DA3E2
P 1000 5900
F 0 "R35" V 1050 5750 50  0000 C CNN
F 1 "10k" V 1000 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 930 5900 50  0001 C CNN
F 3 "" H 1000 5900 50  0000 C CNN
	1    1000 5900
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R34
U 1 1 5E6DA941
P 850 5900
F 0 "R34" V 900 5750 50  0000 C CNN
F 1 "10k" V 850 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 780 5900 50  0001 C CNN
F 3 "" H 850 5900 50  0000 C CNN
	1    850  5900
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 5E6DAADD
P 1450 5650
F 0 "#PWR030" H 1450 5500 50  0001 C CNN
F 1 "+3.3V" H 1600 5700 50  0000 C CNN
F 2 "" H 1450 5650 50  0001 C CNN
F 3 "" H 1450 5650 50  0001 C CNN
	1    1450 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5650 1450 6000
Wire Wire Line
	850  5750 850  5650
Wire Wire Line
	850  5650 1000 5650
Wire Wire Line
	1000 5650 1000 5750
Wire Wire Line
	1000 5650 1450 5650
Connection ~ 1000 5650
Connection ~ 1450 5650
Wire Wire Line
	1000 6050 1000 6200
Wire Wire Line
	1000 6200 1050 6200
Wire Wire Line
	850  6050 850  6300
Wire Wire Line
	850  6300 1050 6300
Text Label 700  6400 0    50   ~ 0
~RAM_CS
Wire Wire Line
	700  6400 1050 6400
$Comp
L cqd_touch_pad:C_Small C11
U 1 1 5E70B810
P 1700 5800
F 0 "C11" H 1500 5750 50  0000 L CNN
F 1 "100n" H 1750 5750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1700 5800 50  0001 C CNN
F 3 "" H 1700 5800 50  0000 C CNN
	1    1700 5800
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:GND #PWR033
U 1 1 5E70C14D
P 1700 5900
F 0 "#PWR033" H 1700 5650 50  0001 C CNN
F 1 "GND" H 1700 5750 50  0000 C CNN
F 2 "" H 1700 5900 50  0000 C CNN
F 3 "" H 1700 5900 50  0000 C CNN
	1    1700 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 5650 1700 5650
Wire Wire Line
	1700 5650 1700 5700
$Comp
L cqd_touch_pad:GND #PWR036
U 1 1 5E714BFE
P 1450 6600
F 0 "#PWR036" H 1450 6350 50  0001 C CNN
F 1 "GND" H 1450 6450 50  0000 C CNN
F 2 "" H 1450 6600 50  0000 C CNN
F 3 "" H 1450 6600 50  0000 C CNN
	1    1450 6600
	1    0    0    -1  
$EndComp
Text Label 1950 6200 0    50   ~ 0
SPI1_SCK
Text Label 1950 6300 0    50   ~ 0
SPI1_MOSI
Text Label 1950 6400 0    50   ~ 0
SPI1_MISO
Wire Wire Line
	1850 6400 1950 6400
Wire Wire Line
	1850 6300 1950 6300
Wire Wire Line
	1850 6200 1950 6200
$Comp
L Connector_Generic:Conn_01x07 J7
U 1 1 5E74849E
P 6750 2650
F 0 "J7" V 6900 2250 50  0000 R CNN
F 1 "Conn_01x07" V 6750 2250 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 6750 2650 50  0001 C CNN
F 3 "~" H 6750 2650 50  0001 C CNN
	1    6750 2650
	0    -1   -1   0   
$EndComp
Text Notes 6650 2400 0    50   ~ 0
Display
Text Notes 6500 2600 1    39   ~ 0
GND
Text Notes 6600 2600 1    39   ~ 0
VCC
Text Notes 6700 2600 1    39   ~ 0
CLK
Text Notes 6800 2600 1    39   ~ 0
MOSI
Text Notes 6900 2600 1    39   ~ 0
RES
Text Notes 7000 2600 1    39   ~ 0
DC
Text Notes 7100 2600 1    39   ~ 0
CS
Text Label 6750 3050 3    50   ~ 0
SPI1_MOSI
Wire Wire Line
	6750 2850 6750 3050
Text Label 6650 3050 3    50   ~ 0
SPI1_SCK
Wire Wire Line
	6650 3050 6650 2850
$Comp
L Device:Ferrite_Bead FB2
U 1 1 5E75F6BA
P 6250 3450
F 0 "FB2" V 5976 3450 50  0000 C CNN
F 1 "Ferrite_Bead" V 6067 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6180 3450 50  0001 C CNN
F 3 "~" H 6250 3450 50  0001 C CNN
	1    6250 3450
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 5E760798
P 5950 3450
F 0 "#PWR024" H 5950 3300 50  0001 C CNN
F 1 "+3.3V" H 5800 3500 50  0000 C CNN
F 2 "" H 5950 3450 50  0001 C CNN
F 3 "" H 5950 3450 50  0001 C CNN
	1    5950 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3450 6100 3450
$Comp
L cqd_touch_pad:C_Small C10
U 1 1 5E76ADB9
P 6550 3650
F 0 "C10" H 6642 3696 50  0000 L CNN
F 1 "22u" H 6642 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6642 3559 50  0001 L CNN
F 3 "" H 6550 3650 50  0000 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3450 6550 3450
Wire Wire Line
	6550 3450 6550 3550
Wire Wire Line
	6550 3450 6550 2850
Connection ~ 6550 3450
$Comp
L cqd_touch_pad:GND #PWR027
U 1 1 5E77F7E5
P 6550 3850
F 0 "#PWR027" H 6550 3600 50  0001 C CNN
F 1 "GND" H 6550 3700 50  0000 C CNN
F 2 "" H 6550 3850 50  0000 C CNN
F 3 "" H 6550 3850 50  0000 C CNN
	1    6550 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3850 6550 3750
$Comp
L cqd_touch_pad:GND #PWR022
U 1 1 5E789C25
P 6450 2850
F 0 "#PWR022" H 6450 2600 50  0001 C CNN
F 1 "GND" H 6450 2700 50  0000 C CNN
F 2 "" H 6450 2850 50  0000 C CNN
F 3 "" H 6450 2850 50  0000 C CNN
	1    6450 2850
	1    0    0    -1  
$EndComp
NoConn ~ 3850 1800
Text Label 3900 3600 0    50   ~ 0
OLED_DC
Wire Wire Line
	3850 3600 3900 3600
Text Label 6950 3050 3    50   ~ 0
OLED_DC
Wire Wire Line
	6950 2850 6950 3050
Text Label 4450 3900 0    50   ~ 0
~OLED_RST
Wire Wire Line
	3850 3900 4400 3900
$Comp
L cqd_touch_pad:R R18
U 1 1 5E7D3151
P 4400 3650
F 0 "R18" H 4300 3650 50  0000 C CNN
F 1 "10k" V 4400 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4330 3650 50  0001 C CNN
F 3 "" H 4400 3650 50  0000 C CNN
	1    4400 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4400 3800 4400 3900
Connection ~ 4400 3900
Wire Wire Line
	4400 3900 4450 3900
$Comp
L power:+3.3V #PWR025
U 1 1 5E7DD985
P 4400 3500
F 0 "#PWR025" H 4400 3350 50  0001 C CNN
F 1 "+3.3V" H 4550 3550 50  0000 C CNN
F 2 "" H 4400 3500 50  0001 C CNN
F 3 "" H 4400 3500 50  0001 C CNN
	1    4400 3500
	1    0    0    -1  
$EndComp
Text Label 6850 3050 3    50   ~ 0
~OLED_RST
Wire Wire Line
	6850 3050 6850 2850
Text Label 7050 2850 3    50   ~ 0
~OLED_CS
Wire Wire Line
	3850 4100 3900 4100
Wire Wire Line
	3850 4200 3900 4200
Text Label 3900 2300 0    50   ~ 0
G4_IO1
Text Label 3900 2400 0    50   ~ 0
G4_IO2
NoConn ~ 2450 2900
NoConn ~ 3850 4000
NoConn ~ 3850 3300
$Comp
L Switch:SW_Push SW1
U 1 1 5E81E54E
P 8500 3200
F 0 "SW1" H 8500 3485 50  0000 C CNN
F 1 "SW_Push" H 8500 3394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 8500 3400 50  0001 C CNN
F 3 "~" H 8500 3400 50  0001 C CNN
	1    8500 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D1
U 1 1 5E82074C
P 8200 3050
F 0 "D1" H 8200 3150 50  0000 R CNN
F 1 "1N4148" H 8400 2950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8200 3050 50  0001 C CNN
F 3 "~" V 8200 3050 50  0001 C CNN
	1    8200 3050
	0    -1   -1   0   
$EndComp
Text Label 7450 2900 0    50   ~ 0
BTN_A
Text Label 8800 2700 1    50   ~ 0
BTN_1
Wire Wire Line
	8200 3150 8200 3200
Wire Wire Line
	8200 3200 8300 3200
Wire Wire Line
	8800 2700 8800 3200
Wire Wire Line
	8800 3200 8700 3200
Wire Wire Line
	7450 2900 8200 2900
Wire Wire Line
	8200 2900 8200 2950
$Comp
L Switch:SW_Push SW2
U 1 1 5E864894
P 9250 3200
F 0 "SW2" H 9250 3485 50  0000 C CNN
F 1 "SW_Push" H 9250 3394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 9250 3400 50  0001 C CNN
F 3 "~" H 9250 3400 50  0001 C CNN
	1    9250 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D2
U 1 1 5E86489E
P 8950 3050
F 0 "D2" H 8950 3150 50  0000 R CNN
F 1 "1N4148" H 9150 2950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8950 3050 50  0001 C CNN
F 3 "~" V 8950 3050 50  0001 C CNN
	1    8950 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 3150 8950 3200
Wire Wire Line
	8950 3200 9050 3200
Wire Wire Line
	9550 2700 9550 3200
Wire Wire Line
	9550 3200 9450 3200
Wire Wire Line
	8200 2900 8950 2900
Wire Wire Line
	8950 2900 8950 2950
Connection ~ 8200 2900
$Comp
L Switch:SW_Push SW3
U 1 1 5E8720B9
P 10000 3200
F 0 "SW3" H 10000 3485 50  0000 C CNN
F 1 "SW_Push" H 10000 3394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10000 3400 50  0001 C CNN
F 3 "~" H 10000 3400 50  0001 C CNN
	1    10000 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D3
U 1 1 5E8720C3
P 9700 3050
F 0 "D3" H 9700 3150 50  0000 R CNN
F 1 "1N4148" H 9900 2950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 9700 3050 50  0001 C CNN
F 3 "~" V 9700 3050 50  0001 C CNN
	1    9700 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 3150 9700 3200
Wire Wire Line
	9700 3200 9800 3200
Wire Wire Line
	10300 2700 10300 3200
Wire Wire Line
	10300 3200 10200 3200
Wire Wire Line
	8950 2900 9700 2900
Wire Wire Line
	9700 2900 9700 2950
Connection ~ 8950 2900
$Comp
L Switch:SW_Push SW4
U 1 1 5E87F021
P 10750 3200
F 0 "SW4" H 10750 3485 50  0000 C CNN
F 1 "SW_Push" H 10750 3394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10750 3400 50  0001 C CNN
F 3 "~" H 10750 3400 50  0001 C CNN
	1    10750 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D4
U 1 1 5E87F02B
P 10450 3050
F 0 "D4" H 10450 3150 50  0000 R CNN
F 1 "1N4148" H 10650 2950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 10450 3050 50  0001 C CNN
F 3 "~" V 10450 3050 50  0001 C CNN
	1    10450 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10450 3150 10450 3200
Wire Wire Line
	10450 3200 10550 3200
Wire Wire Line
	11050 2700 11050 3200
Wire Wire Line
	11050 3200 10950 3200
Wire Wire Line
	9700 2900 10450 2900
Wire Wire Line
	10450 2900 10450 2950
Connection ~ 9700 2900
Text Label 9550 2700 1    50   ~ 0
BTN_2
Text Label 10300 2700 1    50   ~ 0
BTN_3
Text Label 11050 2700 1    50   ~ 0
BTN_4
$Comp
L Switch:SW_Push SW5
U 1 1 5E8AFED8
P 8500 3700
F 0 "SW5" H 8500 3985 50  0000 C CNN
F 1 "SW_Push" H 8500 3894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 8500 3900 50  0001 C CNN
F 3 "~" H 8500 3900 50  0001 C CNN
	1    8500 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D5
U 1 1 5E8AFEE2
P 8200 3550
F 0 "D5" H 8200 3650 50  0000 R CNN
F 1 "1N4148" H 8400 3450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8200 3550 50  0001 C CNN
F 3 "~" V 8200 3550 50  0001 C CNN
	1    8200 3550
	0    -1   -1   0   
$EndComp
Text Label 7450 3400 0    50   ~ 0
BTN_B
Wire Wire Line
	8200 3650 8200 3700
Wire Wire Line
	8200 3700 8300 3700
Wire Wire Line
	8800 3200 8800 3700
Wire Wire Line
	8800 3700 8700 3700
Wire Wire Line
	7450 3400 8200 3400
Wire Wire Line
	8200 3400 8200 3450
$Comp
L Switch:SW_Push SW6
U 1 1 5E8AFEF3
P 9250 3700
F 0 "SW6" H 9250 3985 50  0000 C CNN
F 1 "SW_Push" H 9250 3894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 9250 3900 50  0001 C CNN
F 3 "~" H 9250 3900 50  0001 C CNN
	1    9250 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D6
U 1 1 5E8AFEFD
P 8950 3550
F 0 "D6" H 8950 3650 50  0000 R CNN
F 1 "1N4148" H 9150 3450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8950 3550 50  0001 C CNN
F 3 "~" V 8950 3550 50  0001 C CNN
	1    8950 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 3650 8950 3700
Wire Wire Line
	8950 3700 9050 3700
Wire Wire Line
	9550 3200 9550 3700
Wire Wire Line
	9550 3700 9450 3700
Wire Wire Line
	8200 3400 8950 3400
Wire Wire Line
	8950 3400 8950 3450
Connection ~ 8200 3400
$Comp
L Switch:SW_Push SW7
U 1 1 5E8AFF0E
P 10000 3700
F 0 "SW7" H 10000 3985 50  0000 C CNN
F 1 "SW_Push" H 10000 3894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10000 3900 50  0001 C CNN
F 3 "~" H 10000 3900 50  0001 C CNN
	1    10000 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D7
U 1 1 5E8AFF18
P 9700 3550
F 0 "D7" H 9700 3650 50  0000 R CNN
F 1 "1N4148" H 9900 3450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 9700 3550 50  0001 C CNN
F 3 "~" V 9700 3550 50  0001 C CNN
	1    9700 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 3650 9700 3700
Wire Wire Line
	9700 3700 9800 3700
Wire Wire Line
	10300 3200 10300 3700
Wire Wire Line
	10300 3700 10200 3700
Wire Wire Line
	8950 3400 9700 3400
Wire Wire Line
	9700 3400 9700 3450
Connection ~ 8950 3400
$Comp
L Switch:SW_Push SW8
U 1 1 5E8AFF29
P 10750 3700
F 0 "SW8" H 10750 3985 50  0000 C CNN
F 1 "SW_Push" H 10750 3894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10750 3900 50  0001 C CNN
F 3 "~" H 10750 3900 50  0001 C CNN
	1    10750 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D8
U 1 1 5E8AFF33
P 10450 3550
F 0 "D8" H 10450 3650 50  0000 R CNN
F 1 "1N4148" H 10650 3450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 10450 3550 50  0001 C CNN
F 3 "~" V 10450 3550 50  0001 C CNN
	1    10450 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10450 3650 10450 3700
Wire Wire Line
	10450 3700 10550 3700
Wire Wire Line
	11050 3200 11050 3700
Wire Wire Line
	11050 3700 10950 3700
Wire Wire Line
	9700 3400 10450 3400
Wire Wire Line
	10450 3400 10450 3450
Connection ~ 9700 3400
Connection ~ 8800 3200
Connection ~ 9550 3200
Connection ~ 10300 3200
Connection ~ 11050 3200
$Comp
L Switch:SW_Push SW9
U 1 1 5E8C108F
P 8500 4200
F 0 "SW9" H 8500 4485 50  0000 C CNN
F 1 "SW_Push" H 8500 4394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 8500 4400 50  0001 C CNN
F 3 "~" H 8500 4400 50  0001 C CNN
	1    8500 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D9
U 1 1 5E8C1099
P 8200 4050
F 0 "D9" H 8200 4150 50  0000 R CNN
F 1 "1N4148" H 8400 3950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8200 4050 50  0001 C CNN
F 3 "~" V 8200 4050 50  0001 C CNN
	1    8200 4050
	0    -1   -1   0   
$EndComp
Text Label 7450 3900 0    50   ~ 0
BTN_C
Wire Wire Line
	8200 4150 8200 4200
Wire Wire Line
	8200 4200 8300 4200
Wire Wire Line
	8800 3700 8800 4200
Wire Wire Line
	8800 4200 8700 4200
Wire Wire Line
	7450 3900 8200 3900
Wire Wire Line
	8200 3900 8200 3950
$Comp
L Switch:SW_Push SW10
U 1 1 5E8C10AA
P 9250 4200
F 0 "SW10" H 9250 4485 50  0000 C CNN
F 1 "SW_Push" H 9250 4394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 9250 4400 50  0001 C CNN
F 3 "~" H 9250 4400 50  0001 C CNN
	1    9250 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D10
U 1 1 5E8C10B4
P 8950 4050
F 0 "D10" H 8950 4150 50  0000 R CNN
F 1 "1N4148" H 9150 3950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8950 4050 50  0001 C CNN
F 3 "~" V 8950 4050 50  0001 C CNN
	1    8950 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 4150 8950 4200
Wire Wire Line
	8950 4200 9050 4200
Wire Wire Line
	9550 3700 9550 4200
Wire Wire Line
	9550 4200 9450 4200
Wire Wire Line
	8200 3900 8950 3900
Wire Wire Line
	8950 3900 8950 3950
Connection ~ 8200 3900
$Comp
L Switch:SW_Push SW11
U 1 1 5E8C10C5
P 10000 4200
F 0 "SW11" H 10000 4485 50  0000 C CNN
F 1 "SW_Push" H 10000 4394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10000 4400 50  0001 C CNN
F 3 "~" H 10000 4400 50  0001 C CNN
	1    10000 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D11
U 1 1 5E8C10CF
P 9700 4050
F 0 "D11" H 9700 4150 50  0000 R CNN
F 1 "1N4148" H 9900 3950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 9700 4050 50  0001 C CNN
F 3 "~" V 9700 4050 50  0001 C CNN
	1    9700 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 4150 9700 4200
Wire Wire Line
	9700 4200 9800 4200
Wire Wire Line
	10300 3700 10300 4200
Wire Wire Line
	10300 4200 10200 4200
Wire Wire Line
	8950 3900 9700 3900
Wire Wire Line
	9700 3900 9700 3950
Connection ~ 8950 3900
$Comp
L Switch:SW_Push SW12
U 1 1 5E8C10E0
P 10750 4200
F 0 "SW12" H 10750 4485 50  0000 C CNN
F 1 "SW_Push" H 10750 4394 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10750 4400 50  0001 C CNN
F 3 "~" H 10750 4400 50  0001 C CNN
	1    10750 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D12
U 1 1 5E8C10EA
P 10450 4050
F 0 "D12" H 10450 4150 50  0000 R CNN
F 1 "1N4148" H 10650 3950 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 10450 4050 50  0001 C CNN
F 3 "~" V 10450 4050 50  0001 C CNN
	1    10450 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10450 4150 10450 4200
Wire Wire Line
	10450 4200 10550 4200
Wire Wire Line
	11050 3700 11050 4200
Wire Wire Line
	11050 4200 10950 4200
Wire Wire Line
	9700 3900 10450 3900
Wire Wire Line
	10450 3900 10450 3950
Connection ~ 9700 3900
Connection ~ 8800 3700
Connection ~ 9550 3700
Connection ~ 10300 3700
Connection ~ 11050 3700
$Comp
L Switch:SW_Push SW13
U 1 1 5E8D572D
P 8500 4700
F 0 "SW13" H 8500 4985 50  0000 C CNN
F 1 "SW_Push" H 8500 4894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 8500 4900 50  0001 C CNN
F 3 "~" H 8500 4900 50  0001 C CNN
	1    8500 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D13
U 1 1 5E8D5737
P 8200 4550
F 0 "D13" H 8200 4650 50  0000 R CNN
F 1 "1N4148" H 8400 4450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8200 4550 50  0001 C CNN
F 3 "~" V 8200 4550 50  0001 C CNN
	1    8200 4550
	0    -1   -1   0   
$EndComp
Text Label 7450 4400 0    50   ~ 0
BTN_D
Wire Wire Line
	8200 4650 8200 4700
Wire Wire Line
	8200 4700 8300 4700
Wire Wire Line
	8800 4200 8800 4700
Wire Wire Line
	8800 4700 8700 4700
Wire Wire Line
	7450 4400 8200 4400
Wire Wire Line
	8200 4400 8200 4450
$Comp
L Switch:SW_Push SW14
U 1 1 5E8D5748
P 9250 4700
F 0 "SW14" H 9250 4985 50  0000 C CNN
F 1 "SW_Push" H 9250 4894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 9250 4900 50  0001 C CNN
F 3 "~" H 9250 4900 50  0001 C CNN
	1    9250 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D14
U 1 1 5E8D5752
P 8950 4550
F 0 "D14" H 8950 4650 50  0000 R CNN
F 1 "1N4148" H 9150 4450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 8950 4550 50  0001 C CNN
F 3 "~" V 8950 4550 50  0001 C CNN
	1    8950 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 4650 8950 4700
Wire Wire Line
	8950 4700 9050 4700
Wire Wire Line
	9550 4200 9550 4700
Wire Wire Line
	9550 4700 9450 4700
Wire Wire Line
	8200 4400 8950 4400
Wire Wire Line
	8950 4400 8950 4450
Connection ~ 8200 4400
$Comp
L Switch:SW_Push SW15
U 1 1 5E8D5763
P 10000 4700
F 0 "SW15" H 10000 4985 50  0000 C CNN
F 1 "SW_Push" H 10000 4894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10000 4900 50  0001 C CNN
F 3 "~" H 10000 4900 50  0001 C CNN
	1    10000 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D15
U 1 1 5E8D576D
P 9700 4550
F 0 "D15" H 9700 4650 50  0000 R CNN
F 1 "1N4148" H 9900 4450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 9700 4550 50  0001 C CNN
F 3 "~" V 9700 4550 50  0001 C CNN
	1    9700 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 4650 9700 4700
Wire Wire Line
	9700 4700 9800 4700
Wire Wire Line
	10300 4200 10300 4700
Wire Wire Line
	10300 4700 10200 4700
Wire Wire Line
	8950 4400 9700 4400
Wire Wire Line
	9700 4400 9700 4450
Connection ~ 8950 4400
$Comp
L Switch:SW_Push SW16
U 1 1 5E8D577E
P 10750 4700
F 0 "SW16" H 10750 4985 50  0000 C CNN
F 1 "SW_Push" H 10750 4894 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 10750 4900 50  0001 C CNN
F 3 "~" H 10750 4900 50  0001 C CNN
	1    10750 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D16
U 1 1 5E8D5788
P 10450 4550
F 0 "D16" H 10450 4650 50  0000 R CNN
F 1 "1N4148" H 10650 4450 50  0000 R CNN
F 2 "kicadlib:SOD-123_mod2" V 10450 4550 50  0001 C CNN
F 3 "~" V 10450 4550 50  0001 C CNN
	1    10450 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10450 4650 10450 4700
Wire Wire Line
	10450 4700 10550 4700
Wire Wire Line
	11050 4200 11050 4700
Wire Wire Line
	11050 4700 10950 4700
Wire Wire Line
	9700 4400 10450 4400
Wire Wire Line
	10450 4400 10450 4450
Connection ~ 9700 4400
Connection ~ 8800 4200
Connection ~ 9550 4200
Connection ~ 10300 4200
Connection ~ 11050 4200
$Comp
L cqd_touch_pad:R R19
U 1 1 5E900153
P 2250 3900
F 0 "R19" V 2300 4050 50  0000 C CNN
F 1 "100" V 2250 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 3900 50  0001 C CNN
F 3 "" H 2250 3900 50  0000 C CNN
	1    2250 3900
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R20
U 1 1 5E900AA7
P 2250 4000
F 0 "R20" V 2300 4150 50  0000 C CNN
F 1 "100" V 2250 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4000 50  0001 C CNN
F 3 "" H 2250 4000 50  0000 C CNN
	1    2250 4000
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R24
U 1 1 5E900C4F
P 2250 4100
F 0 "R24" V 2300 4250 50  0000 C CNN
F 1 "100" V 2250 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4100 50  0001 C CNN
F 3 "" H 2250 4100 50  0000 C CNN
	1    2250 4100
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R25
U 1 1 5E900D9E
P 2250 4200
F 0 "R25" V 2300 4350 50  0000 C CNN
F 1 "100" V 2250 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4200 50  0001 C CNN
F 3 "" H 2250 4200 50  0000 C CNN
	1    2250 4200
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R26
U 1 1 5E9010A4
P 2250 4300
F 0 "R26" V 2300 4450 50  0000 C CNN
F 1 "100" V 2250 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4300 50  0001 C CNN
F 3 "" H 2250 4300 50  0000 C CNN
	1    2250 4300
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R28
U 1 1 5E90149A
P 2250 4400
F 0 "R28" V 2300 4550 50  0000 C CNN
F 1 "100" V 2250 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4400 50  0001 C CNN
F 3 "" H 2250 4400 50  0000 C CNN
	1    2250 4400
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R30
U 1 1 5E9016A5
P 2250 4500
F 0 "R30" V 2300 4650 50  0000 C CNN
F 1 "100" V 2250 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4500 50  0001 C CNN
F 3 "" H 2250 4500 50  0000 C CNN
	1    2250 4500
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R32
U 1 1 5E901AA8
P 2250 4600
F 0 "R32" V 2300 4750 50  0000 C CNN
F 1 "100" V 2250 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2180 4600 50  0001 C CNN
F 3 "" H 2250 4600 50  0000 C CNN
	1    2250 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1750 3900 2100 3900
Wire Wire Line
	2400 3900 2450 3900
Wire Wire Line
	1750 4000 2100 4000
Wire Wire Line
	1750 4100 2100 4100
Wire Wire Line
	1750 4200 2100 4200
Wire Wire Line
	1750 4300 2100 4300
Wire Wire Line
	1750 4400 2100 4400
Wire Wire Line
	1750 4500 2100 4500
Wire Wire Line
	1750 4600 2100 4600
Wire Wire Line
	2400 4000 2450 4000
Wire Wire Line
	2400 4100 2450 4100
Wire Wire Line
	2400 4200 2450 4200
Wire Wire Line
	2400 4300 2450 4300
Wire Wire Line
	2400 4400 2450 4400
Wire Wire Line
	2400 4500 2450 4500
Wire Wire Line
	2400 4600 2450 4600
$Comp
L Device:LED D17
U 1 1 5EA9C87C
P 8250 5400
F 0 "D17" H 8200 5500 50  0000 C CNN
F 1 "LED" H 8350 5500 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8250 5400 50  0001 C CNN
F 3 "~" H 8250 5400 50  0001 C CNN
	1    8250 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 5300 8100 5400
Text Label 8500 5100 1    50   ~ 0
LED_1
Wire Wire Line
	8500 5100 8500 5400
Wire Wire Line
	8500 5400 8400 5400
Wire Wire Line
	7600 5300 8100 5300
Text Label 7600 5300 0    50   ~ 0
LED_A
$Comp
L Device:LED D18
U 1 1 5EB2AEC7
P 8750 5400
F 0 "D18" H 8700 5500 50  0000 C CNN
F 1 "LED" H 8850 5500 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8750 5400 50  0001 C CNN
F 3 "~" H 8750 5400 50  0001 C CNN
	1    8750 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 5300 8600 5400
Wire Wire Line
	9000 5100 9000 5400
Wire Wire Line
	9000 5400 8900 5400
Wire Wire Line
	8100 5300 8600 5300
Connection ~ 8100 5300
$Comp
L Device:LED D19
U 1 1 5EB42A49
P 9250 5400
F 0 "D19" H 9200 5500 50  0000 C CNN
F 1 "LED" H 9350 5500 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9250 5400 50  0001 C CNN
F 3 "~" H 9250 5400 50  0001 C CNN
	1    9250 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9100 5300 9100 5400
Wire Wire Line
	9500 5100 9500 5400
Wire Wire Line
	9500 5400 9400 5400
Wire Wire Line
	8600 5300 9100 5300
Connection ~ 8600 5300
$Comp
L Device:LED D20
U 1 1 5EB5B2F6
P 9750 5400
F 0 "D20" H 9700 5500 50  0000 C CNN
F 1 "LED" H 9850 5500 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9750 5400 50  0001 C CNN
F 3 "~" H 9750 5400 50  0001 C CNN
	1    9750 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 5300 9600 5400
Wire Wire Line
	10000 5100 10000 5400
Wire Wire Line
	10000 5400 9900 5400
Wire Wire Line
	9100 5300 9600 5300
Connection ~ 9100 5300
Text Label 9000 5100 1    50   ~ 0
LED_2
Text Label 9500 5100 1    50   ~ 0
LED_3
Text Label 10000 5100 1    50   ~ 0
LED_4
$Comp
L Device:LED D21
U 1 1 5EB8EDDE
P 8250 5700
F 0 "D21" H 8200 5800 50  0000 C CNN
F 1 "LED" H 8350 5800 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8250 5700 50  0001 C CNN
F 3 "~" H 8250 5700 50  0001 C CNN
	1    8250 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 5600 8100 5700
Wire Wire Line
	8500 5400 8500 5700
Wire Wire Line
	8500 5700 8400 5700
Wire Wire Line
	7600 5600 8100 5600
$Comp
L Device:LED D22
U 1 1 5EB8EDEC
P 8750 5700
F 0 "D22" H 8700 5800 50  0000 C CNN
F 1 "LED" H 8850 5800 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8750 5700 50  0001 C CNN
F 3 "~" H 8750 5700 50  0001 C CNN
	1    8750 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 5600 8600 5700
Wire Wire Line
	9000 5400 9000 5700
Wire Wire Line
	9000 5700 8900 5700
Wire Wire Line
	8100 5600 8600 5600
Connection ~ 8100 5600
$Comp
L Device:LED D23
U 1 1 5EB8EDFB
P 9250 5700
F 0 "D23" H 9200 5800 50  0000 C CNN
F 1 "LED" H 9350 5800 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9250 5700 50  0001 C CNN
F 3 "~" H 9250 5700 50  0001 C CNN
	1    9250 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9100 5600 9100 5700
Wire Wire Line
	9500 5400 9500 5700
Wire Wire Line
	9500 5700 9400 5700
Wire Wire Line
	8600 5600 9100 5600
Connection ~ 8600 5600
$Comp
L Device:LED D24
U 1 1 5EB8EE0A
P 9750 5700
F 0 "D24" H 9700 5800 50  0000 C CNN
F 1 "LED" H 9850 5800 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9750 5700 50  0001 C CNN
F 3 "~" H 9750 5700 50  0001 C CNN
	1    9750 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 5600 9600 5700
Wire Wire Line
	10000 5400 10000 5700
Wire Wire Line
	10000 5700 9900 5700
Wire Wire Line
	9100 5600 9600 5600
Connection ~ 9100 5600
Connection ~ 8500 5400
Connection ~ 9000 5400
Connection ~ 9500 5400
Connection ~ 10000 5400
$Comp
L Device:LED D25
U 1 1 5EBAB91A
P 8250 6000
F 0 "D25" H 8200 6100 50  0000 C CNN
F 1 "LED" H 8350 6100 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8250 6000 50  0001 C CNN
F 3 "~" H 8250 6000 50  0001 C CNN
	1    8250 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 5900 8100 6000
Wire Wire Line
	8500 5700 8500 6000
Wire Wire Line
	8500 6000 8400 6000
Wire Wire Line
	7600 5900 8100 5900
$Comp
L Device:LED D26
U 1 1 5EBAB928
P 8750 6000
F 0 "D26" H 8700 6100 50  0000 C CNN
F 1 "LED" H 8850 6100 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8750 6000 50  0001 C CNN
F 3 "~" H 8750 6000 50  0001 C CNN
	1    8750 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 5900 8600 6000
Wire Wire Line
	9000 5700 9000 6000
Wire Wire Line
	9000 6000 8900 6000
Wire Wire Line
	8100 5900 8600 5900
Connection ~ 8100 5900
$Comp
L Device:LED D27
U 1 1 5EBAB937
P 9250 6000
F 0 "D27" H 9200 6100 50  0000 C CNN
F 1 "LED" H 9350 6100 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9250 6000 50  0001 C CNN
F 3 "~" H 9250 6000 50  0001 C CNN
	1    9250 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	9100 5900 9100 6000
Wire Wire Line
	9500 5700 9500 6000
Wire Wire Line
	9500 6000 9400 6000
Wire Wire Line
	8600 5900 9100 5900
Connection ~ 8600 5900
$Comp
L Device:LED D28
U 1 1 5EBAB946
P 9750 6000
F 0 "D28" H 9700 6100 50  0000 C CNN
F 1 "LED" H 9850 6100 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9750 6000 50  0001 C CNN
F 3 "~" H 9750 6000 50  0001 C CNN
	1    9750 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 5900 9600 6000
Wire Wire Line
	10000 5700 10000 6000
Wire Wire Line
	10000 6000 9900 6000
Wire Wire Line
	9100 5900 9600 5900
Connection ~ 9100 5900
$Comp
L Device:LED D29
U 1 1 5EBAB955
P 8250 6300
F 0 "D29" H 8200 6400 50  0000 C CNN
F 1 "LED" H 8350 6400 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8250 6300 50  0001 C CNN
F 3 "~" H 8250 6300 50  0001 C CNN
	1    8250 6300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 6200 8100 6300
Wire Wire Line
	8500 6000 8500 6300
Wire Wire Line
	8500 6300 8400 6300
Wire Wire Line
	7600 6200 8100 6200
$Comp
L Device:LED D30
U 1 1 5EBAB963
P 8750 6300
F 0 "D30" H 8700 6400 50  0000 C CNN
F 1 "LED" H 8850 6400 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 8750 6300 50  0001 C CNN
F 3 "~" H 8750 6300 50  0001 C CNN
	1    8750 6300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8600 6200 8600 6300
Wire Wire Line
	9000 6000 9000 6300
Wire Wire Line
	9000 6300 8900 6300
Wire Wire Line
	8100 6200 8600 6200
Connection ~ 8100 6200
$Comp
L Device:LED D31
U 1 1 5EBAB972
P 9250 6300
F 0 "D31" H 9200 6400 50  0000 C CNN
F 1 "LED" H 9350 6400 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9250 6300 50  0001 C CNN
F 3 "~" H 9250 6300 50  0001 C CNN
	1    9250 6300
	-1   0    0    1   
$EndComp
Wire Wire Line
	9100 6200 9100 6300
Wire Wire Line
	9500 6000 9500 6300
Wire Wire Line
	9500 6300 9400 6300
Wire Wire Line
	8600 6200 9100 6200
Connection ~ 8600 6200
$Comp
L Device:LED D32
U 1 1 5EBAB981
P 9750 6300
F 0 "D32" H 9700 6400 50  0000 C CNN
F 1 "LED" H 9850 6400 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 9750 6300 50  0001 C CNN
F 3 "~" H 9750 6300 50  0001 C CNN
	1    9750 6300
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 6200 9600 6300
Wire Wire Line
	10000 6000 10000 6300
Wire Wire Line
	10000 6300 9900 6300
Wire Wire Line
	9100 6200 9600 6200
Connection ~ 9100 6200
Connection ~ 8500 6000
Connection ~ 9000 6000
Connection ~ 9500 6000
Connection ~ 10000 6000
Connection ~ 8500 5700
Connection ~ 9000 5700
Connection ~ 9500 5700
Connection ~ 10000 5700
Text Label 7600 5600 0    50   ~ 0
LED_B
Text Label 7600 5900 0    50   ~ 0
LED_C
Text Label 7600 6200 0    50   ~ 0
LED_D
$Comp
L Switch:SW_Push SW18
U 1 1 5EFBD403
P 5700 5650
F 0 "SW18" H 5700 5935 50  0000 C CNN
F 1 "SW_Push" H 5700 5844 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 5700 5850 50  0001 C CNN
F 3 "~" H 5700 5850 50  0001 C CNN
	1    5700 5650
	1    0    0    -1  
$EndComp
Text Label 5150 5650 0    50   ~ 0
BTN_RUN
$Comp
L cqd_touch_pad:GND #PWR032
U 1 1 5EFBDE53
P 5900 5700
F 0 "#PWR032" H 5900 5450 50  0001 C CNN
F 1 "GND" H 5900 5550 50  0000 C CNN
F 2 "" H 5900 5700 50  0000 C CNN
F 3 "" H 5900 5700 50  0000 C CNN
	1    5900 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 5650 5900 5700
Wire Wire Line
	5150 5650 5500 5650
$Comp
L Switch:SW_Push SW17
U 1 1 5F01F34B
P 4800 5650
F 0 "SW17" H 4800 5935 50  0000 C CNN
F 1 "SW_Push" H 4800 5844 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 4800 5850 50  0001 C CNN
F 3 "~" H 4800 5850 50  0001 C CNN
	1    4800 5650
	1    0    0    -1  
$EndComp
Text Label 4250 5650 0    50   ~ 0
BTN_MODE
$Comp
L cqd_touch_pad:GND #PWR031
U 1 1 5F01F356
P 5000 5700
F 0 "#PWR031" H 5000 5450 50  0001 C CNN
F 1 "GND" H 5000 5550 50  0000 C CNN
F 2 "" H 5000 5700 50  0000 C CNN
F 3 "" H 5000 5700 50  0000 C CNN
	1    5000 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5650 5000 5700
Wire Wire Line
	4250 5650 4600 5650
$Comp
L Switch:SW_Push SW20
U 1 1 5F04083F
P 5700 6250
F 0 "SW20" H 5700 6535 50  0000 C CNN
F 1 "SW_Push" H 5700 6444 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 5700 6450 50  0001 C CNN
F 3 "~" H 5700 6450 50  0001 C CNN
	1    5700 6250
	1    0    0    -1  
$EndComp
Text Label 5150 6250 0    50   ~ 0
BTN_PLUS
$Comp
L cqd_touch_pad:GND #PWR035
U 1 1 5F04084A
P 5900 6300
F 0 "#PWR035" H 5900 6050 50  0001 C CNN
F 1 "GND" H 5900 6150 50  0000 C CNN
F 2 "" H 5900 6300 50  0000 C CNN
F 3 "" H 5900 6300 50  0000 C CNN
	1    5900 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 6250 5900 6300
Wire Wire Line
	5150 6250 5500 6250
$Comp
L Switch:SW_Push SW19
U 1 1 5F040856
P 4800 6250
F 0 "SW19" H 4800 6535 50  0000 C CNN
F 1 "SW_Push" H 4800 6444 50  0000 C CNN
F 2 "kicadlib:SW_PUSH_SMD" H 4800 6450 50  0001 C CNN
F 3 "~" H 4800 6450 50  0001 C CNN
	1    4800 6250
	1    0    0    -1  
$EndComp
Text Label 4250 6250 0    50   ~ 0
BTN_MINUS
$Comp
L cqd_touch_pad:GND #PWR034
U 1 1 5F040861
P 5000 6300
F 0 "#PWR034" H 5000 6050 50  0001 C CNN
F 1 "GND" H 5000 6150 50  0000 C CNN
F 2 "" H 5000 6300 50  0000 C CNN
F 3 "" H 5000 6300 50  0000 C CNN
	1    5000 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 6250 5000 6300
Wire Wire Line
	4250 6250 4600 6250
Text Label 9300 1850 0    50   ~ 0
G4_IO1
$Comp
L cqd_touch_pad:C_Small C7
U 1 1 5F084229
P 9100 1850
F 0 "C7" V 9000 1800 50  0000 L CNN
F 1 "22n" V 9200 1800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9100 1850 50  0001 C CNN
F 3 "" H 9100 1850 50  0000 C CNN
	1    9100 1850
	0    1    1    0   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR015
U 1 1 5F0844F4
P 8850 1850
F 0 "#PWR015" H 8850 1600 50  0001 C CNN
F 1 "GND" H 8850 1700 50  0000 C CNN
F 2 "" H 8850 1850 50  0000 C CNN
F 3 "" H 8850 1850 50  0000 C CNN
	1    8850 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1850 9000 1850
Wire Wire Line
	9200 1850 9300 1850
$Comp
L cqd_touch_pad:R R16
U 1 1 5F0C9419
P 10450 1850
F 0 "R16" V 10500 1700 50  0000 C CNN
F 1 "1k" V 10450 1850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10380 1850 50  0001 C CNN
F 3 "" H 10450 1850 50  0000 C CNN
	1    10450 1850
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5F0C9BCE
P 10850 1850
F 0 "J6" H 10930 1892 50  0000 L CNN
F 1 "TOUCH_LOGO" H 10500 1700 50  0000 L CNN
F 2 "kicadlib:TEST_PAD_Small" H 10850 1850 50  0001 C CNN
F 3 "~" H 10850 1850 50  0001 C CNN
	1    10850 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 1850 10650 1850
Text Label 10000 1850 0    50   ~ 0
G4_IO2
Wire Wire Line
	10000 1850 10300 1850
Wire Notes Line
	8500 2200 11050 2200
Wire Notes Line
	11050 650  11050 2200
Wire Notes Line
	8500 650  8500 2200
Text Label 4250 6850 0    50   ~ 0
LED_RUN
Text Label 4250 7050 0    50   ~ 0
LED_MODE
$Comp
L Device:LED D33
U 1 1 5F133C10
P 5300 6850
F 0 "D33" H 5250 6950 50  0000 C CNN
F 1 "LED" H 5400 6950 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 5300 6850 50  0001 C CNN
F 3 "~" H 5300 6850 50  0001 C CNN
	1    5300 6850
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:R R36
U 1 1 5F1343C6
P 4850 6850
F 0 "R36" V 4900 7000 50  0000 C CNN
F 1 "470" V 4850 6850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4780 6850 50  0001 C CNN
F 3 "" H 4850 6850 50  0000 C CNN
	1    4850 6850
	0    -1   -1   0   
$EndComp
$Comp
L cqd_touch_pad:R R37
U 1 1 5F135258
P 4850 7050
F 0 "R37" V 4900 7200 50  0000 C CNN
F 1 "470" V 4850 7050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4780 7050 50  0001 C CNN
F 3 "" H 4850 7050 50  0000 C CNN
	1    4850 7050
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D34
U 1 1 5F1353D6
P 5300 7050
F 0 "D34" H 5250 7150 50  0000 C CNN
F 1 "LED" H 5400 7150 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Castellated" H 5300 7050 50  0001 C CNN
F 3 "~" H 5300 7050 50  0001 C CNN
	1    5300 7050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 7050 4700 7050
Wire Wire Line
	4250 6850 4700 6850
Wire Wire Line
	5000 6850 5150 6850
Wire Wire Line
	5000 7050 5150 7050
$Comp
L cqd_touch_pad:GND #PWR037
U 1 1 5F1C1FFF
P 5500 6850
F 0 "#PWR037" H 5500 6600 50  0001 C CNN
F 1 "GND" H 5500 6700 50  0000 C CNN
F 2 "" H 5500 6850 50  0000 C CNN
F 3 "" H 5500 6850 50  0000 C CNN
	1    5500 6850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5450 6850 5500 6850
$Comp
L cqd_touch_pad:GND #PWR038
U 1 1 5F1E618C
P 5500 7050
F 0 "#PWR038" H 5500 6800 50  0001 C CNN
F 1 "GND" H 5500 6900 50  0000 C CNN
F 2 "" H 5500 7050 50  0000 C CNN
F 3 "" H 5500 7050 50  0000 C CNN
	1    5500 7050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5450 7050 5500 7050
Text Label 1300 1600 0    50   ~ 0
~RESET
Wire Wire Line
	1300 1400 1300 1600
Connection ~ 1300 1400
Wire Wire Line
	1300 1400 1550 1400
Text Label 4900 3100 0    50   ~ 0
~RESET
Wire Wire Line
	4900 3100 5200 3100
Text Notes 5500 3150 0    50   ~ 0
~RESET
Wire Wire Line
	6100 1600 6350 1600
$Comp
L power:+3.3V #PWR0101
U 1 1 5F291B8F
P 5150 750
F 0 "#PWR0101" H 5150 600 50  0001 C CNN
F 1 "+3.3V" H 5165 923 50  0000 C CNN
F 2 "" H 5150 750 50  0001 C CNN
F 3 "" H 5150 750 50  0001 C CNN
	1    5150 750 
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:PWR_FLAG #FLG0101
U 1 1 5F292156
P 5150 750
F 0 "#FLG0101" H 5150 845 50  0001 C CNN
F 1 "PWR_FLAG" H 5150 973 50  0000 C CNN
F 2 "" H 5150 750 50  0000 C CNN
F 3 "" H 5150 750 50  0000 C CNN
	1    5150 750 
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3VA #PWR0102
U 1 1 5F29317C
P 4650 750
F 0 "#PWR0102" H 4650 600 50  0001 C CNN
F 1 "+3.3VA" H 4665 923 50  0000 C CNN
F 2 "" H 4650 750 50  0001 C CNN
F 3 "" H 4650 750 50  0001 C CNN
	1    4650 750 
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:PWR_FLAG #FLG0102
U 1 1 5F29384D
P 4650 750
F 0 "#FLG0102" H 4650 845 50  0001 C CNN
F 1 "PWR_FLAG" H 4650 973 50  0000 C CNN
F 2 "" H 4650 750 50  0000 C CNN
F 3 "" H 4650 750 50  0000 C CNN
	1    4650 750 
	-1   0    0    1   
$EndComp
$Comp
L cqd_touch_pad:GND #PWR0103
U 1 1 5F2DD6A0
P 4250 800
F 0 "#PWR0103" H 4250 550 50  0001 C CNN
F 1 "GND" H 4250 650 50  0000 C CNN
F 2 "" H 4250 800 50  0000 C CNN
F 3 "" H 4250 800 50  0000 C CNN
	1    4250 800 
	1    0    0    -1  
$EndComp
$Comp
L cqd_touch_pad:PWR_FLAG #FLG0103
U 1 1 5F2DDA10
P 4250 800
F 0 "#FLG0103" H 4250 895 50  0001 C CNN
F 1 "PWR_FLAG" H 4250 1023 50  0000 C CNN
F 2 "" H 4250 800 50  0000 C CNN
F 3 "" H 4250 800 50  0000 C CNN
	1    4250 800 
	1    0    0    -1  
$EndComp
$EndSCHEMATC
