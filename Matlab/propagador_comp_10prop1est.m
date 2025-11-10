clear all
close all
clc

cd Dados_simula_atitude\
cd 10prop1est\
estados_prop_mat = readmatrix("x_prop.csv");
cov_triad_prop_mat = readmatrix("PT_prop.csv");
cd ..\
estados_prop_c = readmatrix("estados_propagados_est_c_10prop1est");
cov_triad_prop_c = readmatrix("cov_triad_prop_est_c_10prop1est.csv");
cd ..\

cov_triad_prop_mat = reshape(cov_triad_prop_mat, 6,6,[]);
cov_triad_prop_shape = zeros(6,6, 1201);
PT_prop_error = zeros(6,6);
for i=1:1:1201
    cov_triad_prop_shape(:,:,i) = reshape(cov_triad_prop_c(i,:), 6, 6);
    PT_prop_error(:,:) = PT_prop_error + (cov_triad_prop_mat(:,:,i) - cov_triad_prop_shape(:,:,i));
end

PT_prop_error = PT_prop_error/1201;

disp("Erro na covariância propagada:")
disp(PT_prop_error)

erro_x_prop = estados_prop_mat - estados_prop_c;
disp('Erro médio q_0 propagado')
disp(mean(erro_x_prop(1)))

disp('Erro médio q_1 propagado')
disp(mean(erro_x_prop(2)))

disp('Erro médio q_2 propagado')
disp(mean(erro_x_prop(3)))

disp('Erro médio q_3 propagado')
disp(mean(erro_x_prop(4)))

disp('Erro médio b_x prop')
disp(mean(erro_x_prop(5)))

disp('Erro médio b_y prop')
disp(mean(erro_x_prop(6)))

disp('Erro médio b_z prop')
disp(mean(erro_x_prop(7)))

exe = 1:1:i;

figure(1)
plot(exe, estados_prop_c)
hold on
grid on
title("Propagação dos estados em C - apenas Propagador")
xlim([0,1201])
set(gca,'fontsize', 17)

figure(2)
plot(exe, estados_prop_mat)
hold on
grid on
title("Propagação dos estados Matlab")
xlim([0,1201])
set(gca,'fontsize', 17)