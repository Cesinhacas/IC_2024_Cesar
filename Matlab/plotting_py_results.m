clc
clear all
close all

cd ..\
cd Dados\

vet_error_ETS_c = readmatrix('MCS_ETS.csv');
vet_error_NLLS_c = readmatrix('MCS_NLLS.csv');

cd ..\
cd Matlab\

exe = length(vet_error_NLLS_c(1,:));
executions = [1:1:exe];

error_mean_NLLS = [mean(vet_error_NLLS_c(1,:)), mean(vet_error_NLLS_c(2,:)), mean(vet_error_NLLS_c(3,:)), mean(vet_error_NLLS_c(4,:)), mean(vet_error_NLLS_c(5,:)), mean(vet_error_NLLS_c(6,:)), mean(vet_error_NLLS_c(7,:)), mean(vet_error_NLLS_c(8,:)), mean(vet_error_NLLS_c(9,:))];
error_mean_ETS = [mean(vet_error_ETS_c(1,:)), mean(vet_error_ETS_c(2,:)), mean(vet_error_ETS_c(3,:)), mean(vet_error_ETS_c(4,:)), mean(vet_error_ETS_c(5,:)), mean(vet_error_ETS_c(6,:)), mean(vet_error_ETS_c(7,:)), mean(vet_error_ETS_c(8,:)), mean(vet_error_ETS_c(9,:))];

disp("Média dos erros:")
disp("ETS:" )
disp("Offset - x:")
disp(error_mean_ETS(1))
disp("Offset - y:")
disp(error_mean_ETS(2))
disp("Offset - z:")
disp(error_mean_ETS(3))
disp("Fator de escala - x:")
disp(error_mean_ETS(4))
disp("Fator de escala - y:")
disp(error_mean_ETS(5))
disp("Fator de escala - z:")
disp(error_mean_ETS(6))
disp("Ângulo Rho:")
disp(error_mean_ETS(7))
disp("Ângulo Phi:")
disp(error_mean_ETS(8))
disp("Ângulo Lambda:")
disp(error_mean_ETS(9))

disp("NLLS:" )
disp("Offset - x:")
disp(error_mean_NLLS(1))
disp("Offset - y:")
disp(error_mean_NLLS(2))
disp("Offset - z:")
disp(error_mean_NLLS(3))
disp("Fator de escala - x:")
disp(error_mean_NLLS(4))
disp("Fator de escala - y:")
disp(error_mean_NLLS(5))
disp("Fator de escala - z:")
disp(error_mean_NLLS(6))
disp("Ângulo Rho:")
disp(error_mean_NLLS(7))
disp("Ângulo Phi:")
disp(error_mean_NLLS(8))
disp("Ângulo Lambda:")
disp(error_mean_NLLS(9))

figure(1)
subplot(1,3,1), histogram(vet_error_ETS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(1,3,2), histogram(vet_error_ETS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(1,3,3), histogram(vet_error_ETS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")

figure(2)
title("Erro ETS - Offsets")
subplot(1,3,1), histogram(vet_error_ETS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
subplot(1,3,1), histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - x");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(1,3,2), histogram(vet_error_ETS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
subplot(1,3,2), histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(1,3,3), histogram(vet_error_ETS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")

figure(3)
title("Erro ETS - Ângulos de desalinhamento")
subplot(1,3,1), histogram(vet_error_ETS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Rho");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
subplot(1,3,2), histogram(vet_error_ETS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Phi");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
subplot(1,3,3), histogram(vet_error_ETS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
legend("ETS", "NLLS")

figure(4)
mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(1,:) + 3*std(vet_error_ETS_c(1,:)))));
subplot(1,3,1),  plot(executions, vet_error_ETS_c(1,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(2,:) + 3*std(vet_error_ETS_c(2,:)))));
subplot(1,3,2),  plot(executions, vet_error_ETS_c(2,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(3,:) + 3*std(vet_error_ETS_c(3,:)))));
subplot(1,3,3),  plot(executions, vet_error_ETS_c(3,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(5)
mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(4,:) + 3*std(vet_error_ETS_c(4,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(4,:) - 3*std(vet_error_ETS_c(4,:))));
subplot(1,3,1),  plot(executions, vet_error_ETS_c(4,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(5,:) + 3*std(vet_error_ETS_c(5,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(5,:) - 3*std(vet_error_ETS_c(5,:))));
subplot(1,3,2),  plot(executions, vet_error_ETS_c(5,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(6,:) + 3*std(vet_error_ETS_c(6,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(6,:) - 3*std(vet_error_ETS_c(6,:))));
subplot(1,3,3),  plot(executions, vet_error_ETS_c(6,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(6)
mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(7,:) + 3*std(vet_error_ETS_c(7,:)))));
subplot(1,3,1),  plot(executions, vet_error_ETS_c(7,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Rho")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(8,:) + 3*std(vet_error_ETS_c(8,:)))));
subplot(1,3,2),  plot(executions, vet_error_ETS_c(8,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Phi")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(9,:) + 3*std(vet_error_ETS_c(9,:)))));
subplot(1,3,3),  plot(executions, vet_error_ETS_c(9,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Lambda")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(7)
mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(1,:) + 3*std(vet_error_NLLS_c(1,:)))));
subplot(1,3,1),  plot(executions, vet_error_NLLS_c(1,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(2,:) + 3*std(vet_error_NLLS_c(2,:)))));
subplot(1,3,2),  plot(executions, vet_error_NLLS_c(2,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(3,:) + 3*std(vet_error_NLLS_c(3,:)))));
subplot(1,3,3),  plot(executions, vet_error_NLLS_c(3,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Offset - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(8)
mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(4,:) + 3*std(vet_error_NLLS_c(4,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(4,:) - 3*std(vet_error_NLLS_c(4,:))));
subplot(1,3,1),  plot(executions, vet_error_NLLS_c(4,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(5,:) + 3*std(vet_error_NLLS_c(5,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(5,:) - 3*std(vet_error_NLLS_c(5,:))));
subplot(1,3,2),  plot(executions, vet_error_NLLS_c(5,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(6,:) + 3*std(vet_error_NLLS_c(6,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(6,:) - 3*std(vet_error_NLLS_c(6,:))));
subplot(1,3,3),  plot(executions, vet_error_NLLS_c(6,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(9)
mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(7,:) + 3*std(vet_error_NLLS_c(7,:)))));
subplot(1,3,1),  plot(executions, vet_error_NLLS_c(7,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Rho")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(8,:) + 3*std(vet_error_NLLS_c(8,:)))));
subplot(1,3,2),  plot(executions, vet_error_NLLS_c(8,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Phi")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(9,:) + 3*std(vet_error_NLLS_c(9,:)))));
subplot(1,3,3),  plot(executions, vet_error_NLLS_c(9,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Lambda")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")