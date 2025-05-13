clear all
close all
clc

serial = serialport("COM1", 115200);
configureTerminator(serial, 255, "LF");
strg_receive = 0;

while(1)
    while(strg_receive == 0)
        strg_receive = read(serial, 1, "uint8");
        disp(strg_receive)
    end
    strg_receive = 0;
    write(serial, 5.68, "uint8")
end