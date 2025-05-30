clc
clear all
close all

cd ..\
cd Dados\

vet_error_ETS_c = readmatrix('MTS_ETS_f7_FPU.csv');
vet_error_NLLS_c = readmatrix('MTS_NLLS_f7_FPU.csv');

cd ..\
cd Matlab\

exe = length(vet_error_NLLS_c(1,:));
executions = [1:1:exe];

exe_time_ETS = 0;
exe_time_NLLS = 0;
passos_NLLS = 0;

for i = 1:1:exe
    exe_time_ETS = exe_time_ETS + vet_error_ETS_c(10,i);
    exe_time_NLLS = exe_time_NLLS + vet_error_NLLS_c(10,i);
    
    if i < 781
        passos_NLLS = passos_NLLS + vet_error_ETS_c(11,i);
    else
        passos_NLLS = passos_NLLS + vet_error_NLLS_c(11,i);
    end


end

exe_time_ETS = exe_time_ETS/3000;
exe_time_NLLS = exe_time_NLLS/3000;
passos_NLLS = passos_NLLS/3000;

time_ratio = exe_time_NLLS/exe_time_ETS;

disp("Tempo de execução do ETS:")
disp(exe_time_ETS)

disp("Tempo de execução do NLLS:")
disp(exe_time_NLLS)

disp("Passos do NLLS:")
disp(passos_NLLS)

disp("Relação entre os tempos (NLLS/ETS):")
disp(time_ratio)

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

subplot(3,3,4), histogram(vet_error_ETS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - x");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(3,3,5), histogram(vet_error_ETS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
subplot(3,3,6), histogram(vet_error_ETS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")


subplot(3,3,7), histogram(vet_error_ETS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Rho");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
subplot(3,3,8), histogram(vet_error_ETS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Phi");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
subplot(3,3,9), histogram(vet_error_ETS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Ângulo Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Graus")
legend("ETS", "NLLS")

figure(2)
mean_3std_pos =(ones(4,exe)*mean(vet_error_ETS_c(4,:) + 3*std(vet_error_ETS_c(4,:))));
mean_3std_neg =(ones(4,exe)*mean(vet_error_ETS_c(4,:) - 3*std(vet_error_ETS_c(4,:))));
subplot(3,3,1),  plot(executions, vet_error_ETS_c(4,:),executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(5,exe)*mean(vet_error_ETS_c(5,:) + 3*std(vet_error_ETS_c(5,:))));
mean_3std_neg =(ones(5,exe)*mean(vet_error_ETS_c(5,:) - 3*std(vet_error_ETS_c(5,:))));
subplot(3,3,2),  plot(executions, vet_error_ETS_c(5,:),executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(6,exe)*mean(vet_error_ETS_c(6,:) + 3*std(vet_error_ETS_c(6,:))));
mean_3std_neg =(ones(6,exe)*mean(vet_error_ETS_c(6,:) - 3*std(vet_error_ETS_c(6,:))));
subplot(3,3,3),  plot(executions, vet_error_ETS_c(6,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(1,:) + 3*std(vet_error_ETS_c(1,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(1,:) - 3*std(vet_error_ETS_c(1,:))));
subplot(3,3,4),  plot(executions, vet_error_ETS_c(1,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(2,:) + 3*std(vet_error_ETS_c(2,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(2,:) - 3*std(vet_error_ETS_c(2,:))));
subplot(3,3,5),  plot(executions, vet_error_ETS_c(2,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_ETS_c(3,:) + 3*std(vet_error_ETS_c(3,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_ETS_c(3,:) - 3*std(vet_error_ETS_c(3,:))));
subplot(3,3,6),  plot(executions, vet_error_ETS_c(3,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(7,:) + 3*std(vet_error_ETS_c(7,:)))));
subplot(3,3,7),  plot(executions, vet_error_ETS_c(7,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Rho")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(8,:) + 3*std(vet_error_ETS_c(8,:)))));
subplot(3,3,8),  plot(executions, vet_error_ETS_c(8,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Phi")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_ETS_c(9,:) + 3*std(vet_error_ETS_c(9,:)))));
subplot(3,3,9),  plot(executions, vet_error_ETS_c(9,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Lambda")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

figure(3)
mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(4,:) + 3*std(vet_error_NLLS_c(4,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(4,:) - 3*std(vet_error_NLLS_c(4,:))));
subplot(3,3,1),  plot(executions, vet_error_NLLS_c(4,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(5,:) + 3*std(vet_error_NLLS_c(5,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(5,:) - 3*std(vet_error_NLLS_c(5,:))));
subplot(3,3,2),  plot(executions, vet_error_NLLS_c(5,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(6,:) + 3*std(vet_error_NLLS_c(6,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(6,:) - 3*std(vet_error_NLLS_c(6,:))));
subplot(3,3,3),  plot(executions, vet_error_NLLS_c(6,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Offset - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(1,:) + 3*std(vet_error_NLLS_c(1,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(1,:) - 3*std(vet_error_NLLS_c(1,:))));
subplot(3,3,4),  plot(executions, vet_error_NLLS_c(1,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - X")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(2,:) + 3*std(vet_error_NLLS_c(2,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(2,:) - 3*std(vet_error_NLLS_c(2,:))));
subplot(3,3,5),  plot(executions, vet_error_NLLS_c(2,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Y")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std_pos =(ones(1,exe)*mean(vet_error_NLLS_c(3,:) + 3*std(vet_error_NLLS_c(3,:))));
mean_3std_neg =(ones(1,exe)*mean(vet_error_NLLS_c(3,:) - 3*std(vet_error_NLLS_c(3,:))));
subplot(3,3,6),  plot(executions, vet_error_NLLS_c(3,:), executions, mean_3std_pos, '--r', executions, mean_3std_neg, '--r')
hold on
title("Fator de escala - Z")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(7,:) + 3*std(vet_error_NLLS_c(7,:)))));
subplot(3,3,7),  plot(executions, vet_error_NLLS_c(7,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Rho")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(8,:) + 3*std(vet_error_NLLS_c(8,:)))));
subplot(3,3,8),  plot(executions, vet_error_NLLS_c(8,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Phi")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

mean_3std = abs((ones(1,exe)*mean(vet_error_NLLS_c(9,:) + 3*std(vet_error_NLLS_c(9,:)))));
subplot(3,3,9),  plot(executions, vet_error_NLLS_c(9,:), executions, mean_3std, '--r', executions, -mean_3std, '--r')
hold on
title("Lambda")
ylabel("Error");
xlabel("Monte Carlo run");
hold off

legend("Run error","Mean plus 3 standard deviaton")