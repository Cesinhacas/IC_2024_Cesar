clear all
close all
clc

cd ..\
cd Dados\

vet_error_ETS_c = readmatrix('MCS_ETS_c.csv');
vet_error_NLLS_c = readmatrix('MCS_NLLS_c.csv');

vet_error_ETS_c_64 = readmatrix('MCS_ETS_c_64.csv');
vet_error_NLLS_c_64 = readmatrix('MCS_NLLS_c_64.csv');

vet_error_ETS_c_no_opt = readmatrix('MCS_ETS_c_no_opt.csv');
vet_error_NLLS_c_no_opt = readmatrix('MCS_NLLS_c_no_opt.csv');

vet_error_ETS_c_64_no_opt = readmatrix('MCS_ETS_c_64_no_opt.csv');
vet_error_NLLS_c_64_no_opt = readmatrix('MCS_NLLS_c_64_no_opt.csv');

cd ..\
cd Matlab\

%%%%%%%%%%%%%%% Plots comparação ETS C 64 Vs. C 64 opt
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(3)
subplot(3,3,1), histogram(vet_error_ETS_c_64(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,2), histogram(vet_error_ETS_c_64(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,3), histogram(vet_error_ETS_c_64(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,4), histogram(vet_error_ETS_c_64(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,5), histogram(vet_error_ETS_c_64(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,6), histogram(vet_error_ETS_c_64(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,7), histogram(vet_error_ETS_c_64(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,8), histogram(vet_error_ETS_c_64(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,9), histogram(vet_error_ETS_c_64(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_64_no_opt(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

%%%%%%%%%%%%%%% Plots comparação NLLS C 64 Vs. C 64 opt
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(4)
subplot(3,3,1), histogram(vet_error_NLLS_c_64(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,2), histogram(vet_error_NLLS_c_64(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,3), histogram(vet_error_NLLS_c_64(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,4), histogram(vet_error_NLLS_c_64(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,5), histogram(vet_error_NLLS_c_64(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,6), histogram(vet_error_NLLS_c_64(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,7), histogram(vet_error_NLLS_c_64(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,8), histogram(vet_error_NLLS_c_64(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,9), histogram(vet_error_NLLS_c_64(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_64_no_opt(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

%%%%%%%%%%%%%%% Plots comparação ETS C Vs. C opt
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
subplot(3,3,1), histogram(vet_error_ETS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,2), histogram(vet_error_ETS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,3), histogram(vet_error_ETS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,4), histogram(vet_error_ETS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,5), histogram(vet_error_ETS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,6), histogram(vet_error_ETS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,7), histogram(vet_error_ETS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,8), histogram(vet_error_ETS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,9), histogram(vet_error_ETS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_c_no_opt(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

%%%%%%%%%%%%%%% Plots comparação NLLS C Vs. C opt
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2)
subplot(3,3,1), histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,2), histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,3), histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C opt", "C no opt")

subplot(3,3,4), histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,5), histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,6), histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,7), histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,8), histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")

subplot(3,3,9), histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_c_no_opt(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C opt", "C no opt")