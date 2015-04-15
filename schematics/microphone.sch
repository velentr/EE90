<Qucs Schematic 0.0.18>
<Properties>
  <View=0,0,1000,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=microphone.dat>
  <DataDisplay=microphone.dpl>
  <OpenDisplay=1>
  <Script=microphone.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
  <.PortSym 40 20 2 0>
  <.PortSym 40 60 1 0>
  <.PortSym 40 100 3 0>
  <.PortSym 40 140 4 0>
  <.PortSym 40 180 5 0>
  <.PortSym 40 220 6 0>
</Symbol>
<Components>
  <Port uPhonePower 1 380 250 -23 12 0 0 "2" 0 "analog" 0>
  <GND * 1 460 420 0 0 0 0>
  <Port uPhoneGND 1 380 350 -23 12 0 0 "1" 0 "analog" 0>
  <Port Vcc 1 460 140 -36 -23 0 3 "3" 0 "analog" 0>
  <R R1 1 460 190 15 -26 0 1 "2.2 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <C C1 1 510 250 -26 17 0 0 "1 uF" 1 "" 0 "neutral" 0>
  <Diode D2 1 590 250 -26 15 1 2 "1e-15 A" 0 "1" 0 "10 fF" 0 "0.5" 0 "0.7 V" 0 "0.5" 0 "0.0 fF" 0 "0.0" 0 "2.0" 0 "0.0 Ohm" 0 "0.0 ps" 0 "0" 0 "0.0" 0 "1.0" 0 "1.0" 0 "0" 0 "1 mA" 0 "26.85" 0 "3.0" 0 "1.11" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "26.85" 0 "1.0" 0 "normal" 0>
  <OpAmp OP1 1 670 270 -26 42 0 0 "1e6" 0 "15 V" 0>
  <R R2 1 610 390 15 -26 0 1 "1 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <R R3 1 720 350 -26 15 0 0 "50 Ohm" 0 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <GND * 1 610 420 0 0 0 0>
  <Port Vtrig 1 800 140 -45 -23 0 3 "4" 0 "analog" 0>
  <Port Ain 1 900 270 4 12 1 2 "6" 0 "analog" 0>
  <GND * 1 800 420 0 0 0 0>
  <Diode D1 1 800 350 15 -26 0 1 "1e-15 A" 0 "1" 0 "10 fF" 0 "0.5" 0 "0.7 V" 0 "0.5" 0 "0.0 fF" 0 "0.0" 0 "2.0" 0 "0.0 Ohm" 0 "0.0 ps" 0 "0" 0 "0.0" 0 "1.0" 0 "1.0" 0 "0" 0 "1 mA" 0 "26.85" 0 "3.0" 0 "1.11" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "0.0" 0 "26.85" 0 "1.0" 0 "normal" 0>
  <Port Trigger 1 900 190 4 -31 0 2 "5" 0 "analog" 0>
  <OpAmp OP2 1 850 190 -26 -56 1 0 "1e6" 0 "15 V" 0>
</Components>
<Wires>
  <380 250 460 250 "" 0 0 0 "">
  <460 350 460 420 "" 0 0 0 "">
  <380 350 460 350 "" 0 0 0 "">
  <460 140 460 160 "" 0 0 0 "">
  <460 220 460 250 "" 0 0 0 "">
  <460 250 480 250 "" 0 0 0 "">
  <610 290 640 290 "" 0 0 0 "">
  <610 290 610 350 "" 0 0 0 "">
  <610 350 610 360 "" 0 0 0 "">
  <610 350 690 350 "" 0 0 0 "">
  <750 270 750 350 "" 0 0 0 "">
  <710 270 750 270 "" 0 0 0 "">
  <750 270 800 270 "" 0 0 0 "">
  <800 270 900 270 "" 0 0 0 "">
  <800 270 800 320 "" 0 0 0 "">
  <800 380 800 420 "" 0 0 0 "">
  <890 190 900 190 "" 0 0 0 "">
  <800 210 800 270 "" 0 0 0 "">
  <800 210 820 210 "" 0 0 0 "">
  <800 140 800 170 "" 0 0 0 "">
  <800 170 820 170 "" 0 0 0 "">
  <540 250 560 250 "" 0 0 0 "">
  <620 250 640 250 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
