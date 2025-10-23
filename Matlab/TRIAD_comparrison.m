clear all
close all
clc

cd Dados_simula_atitude\
matlab_TRIAD = readmatrix("TRIAD_out.csv");
C_TRIAD = readmatrix("quaternion.csv");
cov_matlab = readmatrix("R_triad_matlab.csv");
cov_c = readmatrix("cov_triad_c.csv");
estados_prop_c = readmatrix("estados_propagados_c.csv");
cov_triad_prop_c = readmatrix("cov_triad_prop_c.csv");
estados_prop_mat = readmatrix("x_prop.csv");
cov_triad_prop_mat = readmatrix("PT_prop.csv");
estados_est_mat = readmatrix("x_est.csv");
covT_est_mat = readmatrix("PT_est.csv");
cov_est_mat = readmatrix("P_est.csv");
estados_est_c = readmatrix("estados_estimados_c.csv");
cov_est_c = readmatrix("cov_triad_est_c.csv");
covT_est_c = readmatrix("covT_triad_est_c.csv");
cd ..\

covT_est_mat = reshape(covT_est_mat, 6,6, []);
cov_est_mat = reshape(cov_est_mat, 7,7, []);
covT_est_c = reshape(covT_est_c, 6,6, []);
cov_est_c = reshape(cov_est_c, 7,7, []);
R_cov_matlab = reshape(cov_matlab, 3, 3, []);
R_cov_C = zeros(3,3, 201);
error_R_cov = zeros(3,3);

cov_triad_prop_mat = reshape(cov_triad_prop_mat, 6,6,[]);
cov_triad_prop_shape = zeros(6,6, 201);
PT_prop_error = zeros(6,6);
x_est_error = zeros(1,7);
PT_est_error = zeros(6,6);
P_est_error = zeros(7,7);
for i=1:1:201
    R_cov_C(:,:,i) = [cov_c(i, 1), cov_c(i, 2), cov_c(i, 3); cov_c(i, 4), cov_c(i, 5), cov_c(i, 6); cov_c(i, 7), cov_c(i, 8), cov_c(i, 9)];
    error_R_cov = error_R_cov + (R_cov_matlab(:,:,i) - R_cov_C(:,:,i));

    cov_triad_prop_shape(:,:,i) = reshape(cov_triad_prop_c(i,:), 6, 6);
    PT_prop_error(:,:) = cov_triad_prop_mat(:,:,i) - cov_triad_prop_shape(:,:,i);

    x_est_error = x_est_error + (estados_est_mat(i,:) - estados_est_c(i,:));

    PT_est_error(:,:) = PT_est_error(:,:) + (covT_est_mat(:,:,i) - covT_est_c(:,:,i));
    P_est_error(:,:) = P_est_error(:,:) + (cov_est_mat(:,:,i) - cov_est_c(:,:,i));
end

x_est_error = x_est_error/201;
PT_est_error = PT_est_error/201;
P_est_error = P_est_error/201;

disp("Erro médio nos estados estimados:")
disp(x_est_error)

disp("Erro médio na matriz de covariânciaT:")
disp(PT_est_error)

disp("Erro médio na matriz de covariância:")
disp(P_est_error)

error_R_cov = error_R_cov/201;

disp("Matriz R TRIAD:")
disp(error_R_cov)

PT_prop_error = PT_prop_error/201;

disp("Erro na covariância propagada:")
disp(PT_prop_error)

erro_TRIAD = matlab_TRIAD - C_TRIAD;

disp('Erro médio q_0')
disp(mean(erro_TRIAD(1)))

disp('Erro médio q_1')
disp(mean(erro_TRIAD(2)))

disp('Erro médio q_2')
disp(mean(erro_TRIAD(3)))

disp('Erro médio q_3')
disp(mean(erro_TRIAD(4)))

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
