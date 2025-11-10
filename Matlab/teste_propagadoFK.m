clear all
close all
clc

cd Dados_simula_atitude\
dados_gyro = readmatrix('gyro_cinematica.csv');
cd ../

x_prop = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]';
PT_prop = zeros(6, 6);
PT_est = 1e6*eye(6);
x_est = [0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0]';

Dt = 0.05;

Q = diag([0.005^2 0.005^2 0.005^2 0.1^2 0.1^2 0.1^2]);

for i=1:1:201
    u_gyro = dados_gyro(i,:);
    i_in = i;
    [x_prop, PT_prop, i_out] = propagador_FK(u_gyro, Dt, PT_est, x_est, Q, i_in);
    PT_est = PT_prop;
    x_est = x_prop;
end