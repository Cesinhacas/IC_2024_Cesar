clear all
close all
clc

cd Dados_simula_atitude\
cd 10prop1est\
estados_est_mat = readmatrix("x_est.csv");
covT_est_mat = readmatrix("PT_est.csv");
cov_est_mat = readmatrix("P_est.csv");

estados_prop_mat = readmatrix("x_prop.csv");
covT_prop_mat = readmatrix("PT_prop.csv");

q_true = readmatrix("q_true");
cd ..\
estados_est_c = readmatrix("estados_estimados_c_tudo_menos_PT_prop.csv");
covT_est_c = readmatrix("cov_triadT_est_c_tudo_menos_PT_prop.csv");
cov_est_c = readmatrix("cov_triad_est_c_tudo_menos_PT_prop.csv");

estados_prop_c = readmatrix("estados_propagados_c_tudo_menos_PT_prop.csv");
covT_prop_c = readmatrix("cov_triad_prop_c_tudo_menos_PT_prop.csv");
cd ..\

covT_est_mat = reshape(covT_est_mat, 6,6,[]);
cov_est_mat = reshape(cov_est_mat, 7,7, []);

covT_prop_mat = reshape(covT_prop_mat, 6,6,[]);

error_estados_est = zeros(1,7);
error_cov_est = zeros(7,7);
error_covT_est = zeros(6,6);

error_estados_prop = zeros(1,7);
error_covT_prop = zeros(6,6);

for i=1:1:1201
    covT_shape = reshape(covT_est_c(i, :), 6,6, []);
    error_covT_est = error_covT_est + covT_est_mat(:,:,i) - covT_shape;

    cov_shape = reshape(cov_est_c(i, :), 7,7, []);
    error_cov_est = error_cov_est + cov_est_mat(:,:,i) - cov_shape;

    covT_shape = reshape(covT_prop_c(i, :), 6,6, []);
    error_covT_prop = error_covT_prop + covT_prop_mat(:,:,i) - covT_shape;

    error_estados_est = error_estados_est + (estados_est_mat(i, :) - estados_est_c(i,:));
    error_estados_prop = error_estados_prop + (estados_prop_mat(i, :) - estados_prop_c(i,:));
end
error_cov_est = error_cov_est/1201;
error_covT_est = error_covT_est/1201;
error_estados_est = error_estados_est/1201;

error_covT_prop = error_covT_prop/1201;
error_estados_prop = error_estados_prop/1201;

disp("Erro PT_est")
disp(error_covT_est)

disp("Erro P_est")
disp(error_cov_est)

disp("Erro estados estimados")
disp(error_estados_est)

disp("Erro PT_prop")
disp(error_covT_prop)

disp("Erro estados propagados")
disp(error_estados_prop)

exe = 1:1:1201;

figure(1)
plot(exe, estados_est_c)
hold on
grid on
title("Estimação dos estados em C - Tudo menos PT prop em C")
xlim([0,1201])
set(gca,'fontsize', 17)

figure(2)
plot(exe, estados_est_mat)
hold on
grid on
title("Estimação dos estados em Matlab")
xlim([0,1201])
set(gca,'fontsize', 17)