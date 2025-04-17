clear all
close all
clc

Dados_Corrompido = zeros(3,1112);
serial = serialport("COM1", 115200);
strg_receive = 0;

cd Dados_com_ruido\
%for i=1:3000
strg_save = sprintf("conjunto_dados_corrompidos_1.csv");
writematrix(Dados_Corrompido, strg_save);

write(serial, 1, "uint8")

write(serial, Dados_Corrompido(1,:), "single");
while(strg_receive ~= 1)
    strg_receive = read(serial,1, "single");
end
disp("Dados enviados");

strg_receive = 0;
write(serial, Dados_Corrompido(2,:), "single");

while(strg_receive ~= 1)
    strg_receive = read(serial,1, "single");
end
disp("Dados enviados");

strg_receive = 0;
write(serial, Dados_Corrompido(3,:), "single");
while(strg_receive ~= 1)
    strg_receive = read(serial,1, "single");
end
disp("Dados enviados");
strg_receive = 0;

p = read(serial, 9, "single");
disp(p);

%end

cd ..\
clear serial