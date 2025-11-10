clear all
close all
clc

cd Dados_simula_atitude\
estados_est_mat = readmatrix("x_est.csv");
covT_est_mat = readmatrix("PT_est.csv");
cov_est_mat = readmatrix("P_est.csv");
estados_est_c = readmatrix("estados_estimados_c_q_obs.csv");
covT_est_c = readmatrix("covT_triad_est_c_q_obs.csv");
cov_est_c = readmatrix("cov_triad_est_c_q_obs.csv");
cd ..\

covT_est_mat = reshape(covT_est_mat, 6,6,[]);
cov_est_mat = reshape(cov_est_mat, 7,7, []);

error_estados_est = zeros(1,7);
error_cov_est = zeros(7,7);
error_covT_est = zeros(6,6);



for i=1:1:201
    covT_shape = reshape(covT_est_c(i, :), 6,6, []);
    error_covT_est = error_covT_est + covT_est_mat(:,:,i) - covT_shape;

    cov_shape = reshape(cov_est_c(i, :), 7,7, []);
    error_cov_est = error_cov_est + cov_est_mat(:,:,i) - cov_shape;

    error_estados_est = error_estados_est + (estados_est_mat(i, :) - estados_est_c(i,:));
end
error_cov_est = error_cov_est/201;
error_covT_est = error_covT_est/201;
error_estados_est = error_estados_est/201;

disp("Erro PT_est")
disp(error_covT_est)

disp("Erro P_est")
disp(error_cov_est)

disp("Erro estados estimados")
disp(error_estados_est)

exe = 1:1:201;

figure(1)
plot(exe, estados_est_c)

figure(2)
plot(exe, estados_est_mat)