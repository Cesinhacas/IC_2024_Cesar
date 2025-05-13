clear all
close all
clc

serial = serialport("COM1", 115200);
configureTerminator(serial, 255, "LF");
strg_receive = 0;

cd Dados_com_ruido\
%for i=1:3000

strg_save = sprintf("conjunto_dados_corrompidos_1.csv");
Dados_Corrompido =  readmatrix(strg_save);



while(strg_receive ~= 165)
    strg_receive = read(serial,1, "uint8");
end
strg_receive = 0;

write(serial,165, "uint8")

for i=1:length(Dados_Corrompido(1,:))
    write(serial, Dados_Corrompido(1,i), "single");
end

while(strg_receive ~= 165)
    strg_receive = read(serial,1, "uint8");
end
disp("Dados enviados");

strg_receive = 0;

for i=1:length(Dados_Corrompido(2,:))
    write(serial, Dados_Corrompido(2,i), "single");
end

while(strg_receive ~= 165)
    strg_receive = read(serial,1, "uint8");
end
disp("Dados enviados");

strg_receive = 0;

for i=1:length(Dados_Corrompido(3,:))
    write(serial, Dados_Corrompido(3,i), "single");
end

while(strg_receive ~= 165)
    strg_receive = read(serial,1, "uint8");
end
disp("Recebendo dados");
strg_receive = 0;

p = read(serial, 9, "single");
disp(p);

%end

cd ..\
clear serial