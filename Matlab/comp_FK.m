clear all
close all
clc

cd Dados_simula_atitude\
cd 10prop1est\
estados_prop_mat = readmatrix("x_prop.csv");
cov_triad_prop_mat = readmatrix("PT_prop.csv");

estados_est_mat = readmatrix("x_est.csv");
covT_est_mat = readmatrix("PT_est.csv");
cd ..\
estados_prop_c = readmatrix("estados_propagados_c_tudo_menos_PT_prop.csv");
cov_triad_prop_c = readmatrix("cov_triad_prop_c_tudo_menos_PT_prop.csv");

estados_est_c = readmatrix("estados_estimados_c_tudo_menos_PT_prop.csv");
covT_est_c = readmatrix("cov_triadT_est_c_tudo_menos_PT_prop.csv");
cov_est_c = readmatrix("cov_triad_est_c_tudo_menos_PT_prop.csv");
cd ..\

cov_triad_prop_mat = reshape(cov_triad_prop_mat, 6,6,[]);
cov_triad_prop_shape = zeros(6,6, 201);
PT_prop_error = zeros(6,6);
for i=1:1:201
    cov_triad_prop_shape(:,:,i) = reshape(cov_triad_prop_c(i,:), 6, 6);
    PT_prop_error(:,:) = PT_prop_error + (cov_triad_prop_mat(:,:,i) - cov_triad_prop_shape(:,:,i));
end

PT_prop_error = PT_prop_error/201;

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

erro_x_est = estados_est_mat - estados_est_c;

disp("Erro médio q_0 estimado:")
disp(mean(erro_x_est(1)))

disp("Erro médio q_1 estimado:")
disp(mean(erro_x_est(2)))

disp("Erro médio q_2estimado:")
disp(mean(erro_x_est(3)))

disp("Erro médio q_3 estimado:")
disp(mean(erro_x_est(4)))

disp("Erro médio b_x estimado:")
disp(mean(erro_x_est(5)))

disp("Erro médio b_y estimado:")
disp(mean(erro_x_est(6)))

disp("Erro médio b_x estimado:")
disp(mean(erro_x_est(7)))

exe = 1:1:i;

figure(1)
plot(exe, estados_prop_c),

figure(2)
plot(exe, estados_prop_mat)

figure(3)
plot(exe, estados_est_c),

figure(4)
plot(exe, estados_est_mat)
