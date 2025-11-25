close all
clear all
clc

accel_data = readmatrix('accel_ruido.csv')';
mag_data = readmatrix('mag_ruido.csv')';

cd ..\
cd Parte2_Teste2b

accel_data_c = readmatrix("param_accel_c.csv");
mag_data_c = readmatrix("param_mag_c.csv");

cd ..\
cd Parte2_Teste2a

p0 = [1,1,1,0,0,0,0,0,0]';
H = ones(1, length(accel_data(1,:)))';

[Time2, passo2, p2, fisher2] = test2(mag_data, p0, H);

[Time, passo, p, fisher] = test2(accel_data, p0, H);

disp("Parâmetros Mag - mat")
disp(p2)

disp("Parâmetros Mag - C")
disp(mag_data_c')

disp("Diferença")
disp(p2-mag_data_c')


disp("Parâmetros Accel - Mat")
disp(p)

disp("Parâmetros Accel - C")
disp(accel_data_c)

disp("Diferença")
disp(p-accel_data_c')