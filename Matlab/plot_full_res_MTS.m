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


figure(1)
subplot(3,3,1), histogram(vet_error_ETS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(3,3,2), histogram(vet_error_ETS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(3,3,3), histogram(vet_error_ETS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")