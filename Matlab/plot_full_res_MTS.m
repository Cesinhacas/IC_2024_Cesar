clear all
close all
clc

cd ..\
cd Dados\

vet_error_ETS_c = readmatrix('MCS_ETS_c.csv');
vet_error_NLLS_c = readmatrix('MCS_NLLS_c.csv');

vet_error_ETS_p = readmatrix('MCS_ETS.csv');
vet_error_NLLS_p = readmatrix('MCS_NLLS.csv');

vet_error_ETS_c_64 = readmatrix('MCS_ETS_c_64.csv');
vet_error_NLLS_c_64 = readmatrix('MCS_NLLS_c_64.csv');

vet_error_ETS_m = readmatrix('MCS_ETS_Matlab.csv');
vet_error_NLLS_m = readmatrix('MCS_NLLS_Matlab.csv');

vet_error_NLLS_ST = readmatrix('MCS_NLLS_ST_Matlab.csv');
vet_error_NLLS_ST2 = readmatrix('MCS_NLLS_ST2_Matlab.csv');

vet_error_ETS_f7 = readmatrix('MTS_ETS_f7_FPU.csv'); % FPU on e 1112 medidas
vet_error_NLLS_f7 = readmatrix('MTS_NLLS_f7_FPU.csv');

vet_error_ETS_f4 = readmatrix('MTS_ETS_f4.csv'); % FPU on e 1112 medidas
vet_error_NLLS_f4 = readmatrix('MTS_NLLS_f4.csv');

vet_error_ETS_f7_nofpu = readmatrix('MTS_ETS_f7_NOFPU.csv'); %FPU off e 1112 medidas
vet_error_NLLS_f7_nofpu = readmatrix('MTS_NLLS_f7_NOFPU.csv');

vet_error_ETS_f7_double = readmatrix('MTS_ETS_f7_double.csv');
vet_error_NLLS_f7_double = readmatrix('MTS_NLLS_f7_double.csv');

vet_error_ETS_f7_reduzido = readmatrix('MTS_ETS_f7_reduzidos.csv'); % FPU on e 556 medidas
vet_error_NLLS_f7_reduzido = readmatrix('MTS_NLLS_f7_reduzidos.csv');

vet_error_ETS_f7_reduzido_nofpu = readmatrix('MTS_ETS_f7_reduzidos_NOFPU.csv'); % FPU off e 556 medidas
vet_error_NLLS_f7_reduzido_nofpu = readmatrix('MTS_NLLS_f7_reduzidos_NOFPU.csv');

vet_error_ETS_f7_short = readmatrix('MTS_ETS_f7_short.csv'); % FPU on e 278 medidas
vet_error_NLLS_f7_short = readmatrix('MTS_NLLS_f7_short.csv');

vet_error_ETS_f7_short_nofpu = readmatrix('MTS_ETS_f7_short_NOFPU.csv'); % FPU of e 278 medidas
vet_error_NLLS_f7_short_nofpu = readmatrix('MTS_NLLS_f7_short_NOFPU.csv');

vet_error_NLLS_ST_f7 = readmatrix('MTS_NLLS_f7_ST_primeiro.csv');
vet_error_NLLS_ST2_f7 = readmatrix('MTS_NLLS_f7_ST_segundo.csv');

cd ..\
cd Matlab\


%%%%%%%%%%%%%%% Plots comparação ETS C Vs. Python Vs. Matlab
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
subplot(3,3,1), histogram(vet_error_ETS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,2), histogram(vet_error_ETS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,3), histogram(vet_error_ETS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,4), histogram(vet_error_ETS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,5), histogram(vet_error_ETS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,6), histogram(vet_error_ETS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,7), histogram(vet_error_ETS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,8), histogram(vet_error_ETS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,9), histogram(vet_error_ETS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_p(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_m(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

%%%%%%%%%%%%%%% Plots comparação NLLS C Vs. Python Vs. Matlab
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(2)
subplot(3,3,1), histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,2), histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,3), histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")

subplot(3,3,4), histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,5), histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,6), histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,7), histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,8), histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

subplot(3,3,9), histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")

%%%%%%%%%%%%%%% Plots comparação ETS F7 Vs. F4 Vs. Matlab
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(3)
subplot(3,3,1), histogram(vet_error_ETS_m(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,2), histogram(vet_error_ETS_m(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,3), histogram(vet_error_ETS_m(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,4), histogram(vet_error_ETS_m(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,5), histogram(vet_error_ETS_m(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,6), histogram(vet_error_ETS_m(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,7), histogram(vet_error_ETS_m(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,8), histogram(vet_error_ETS_m(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,9), histogram(vet_error_ETS_m(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f4(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

%%%%%%%%%%%%%%% Plots comparação NLLS F7 Vs. F4 Vs. Matlab
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(4)
subplot(3,3,1), histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,2), histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,3), histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,4), histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,5), histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,6), histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,7), histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,8), histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

subplot(3,3,9), histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f4(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F4 - float - FPU on")

%%%%%%%%%%%%%%% Plots comparação ETS F7 - execuções diverssas - FPU on
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(5)
subplot(3,3,1), histogram(vet_error_ETS_f7(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,2), histogram(vet_error_ETS_f7(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,3), histogram(vet_error_ETS_f7(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,4), histogram(vet_error_ETS_f7(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,5), histogram(vet_error_ETS_f7(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,6), histogram(vet_error_ETS_f7(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,7), histogram(vet_error_ETS_f7(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,8), histogram(vet_error_ETS_f7(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,9), histogram(vet_error_ETS_f7(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_ETS_f7_reduzido(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_ETS_f7_short(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

%%%%%%%%%%%%%%% Plots comparação NLLS F7 - execuções diverssas - FPU on
%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(6)
subplot(3,3,1), histogram(vet_error_NLLS_f7(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,2), histogram(vet_error_NLLS_f7(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,3), histogram(vet_error_NLLS_f7(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,4), histogram(vet_error_NLLS_f7(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,5), histogram(vet_error_NLLS_f7(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,6), histogram(vet_error_NLLS_f7(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,7), histogram(vet_error_NLLS_f7(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,8), histogram(vet_error_NLLS_f7(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")

subplot(3,3,9), histogram(vet_error_NLLS_f7(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7_reduzido(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_short(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("F7 - 1112 dados", "F7 - 556", "F7 - 278")



% figure(1)
% subplot(3,3,1), histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
% hold on
% histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
% grid on;
% title("Offset - eixo x");
% ylabel("Distribuição de probabilidade")
% xlabel("Adimensional")
% subplot(3,3,2), histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
% hold on
% histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
% grid on;
% title("Offset - eixo y");
% ylabel("Distribuição de probabilidade")
% xlabel("Adimensional")
% subplot(3,3,3), histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
% hold on
% histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
% grid on;
% title("Offset - eixo z");
% ylabel("Distribuição de probabilidade")
% xlabel("Adimensional")
% legend("ETS", "NLLS")