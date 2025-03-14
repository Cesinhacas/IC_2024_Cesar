%% C�digo 01a - Gera vetor de 572 (passo = 10) 1112 (passo = 5) pontos similar ao do teste da bobina:
clear all
close all
clc

save_data = 1;

phi(1) = 0;
theta(1) = 0;
it(1) = 1;
k = 2;
passo = 5;

for i=0:passo:180
    for j=6:12:354
        phi(k) = j;
        theta(k) = i; 
        it(k) = k;
        k = k + 1;
    end
end
phi(k) = 180;
theta(k) = 0;
it(k) = k;

phi_Rad = pi/180*phi; 
theta_Rad = pi/180*theta;

r = 1;

x = r.*cos(theta_Rad).*sin(phi_Rad);
y = r.*sin(theta_Rad).*sin(phi_Rad);
z = r.*cos(phi_Rad);

Dados = [x; y; z];

if save_data==1
    Dados_Teoricos = Dados;
    clearvars -except Dados_Teoricos 
    cd ../
    cd 'Dados'
    save Dados_Teoricos.mat
    cd ../
    cd 'Matlab'
end

%% Gera dados corrompidos
% OFFSET => -0.2 ~ 0.2
% Fs => 0.8 ~ 1.2
% Ang => -3 ~ 3 ** transformar de grau para radiano.

Data_Simul = Dados_Teoricos;

exe = 3000;
vet_error_NLLS_c = zeros(9,exe);
vet_error_ETS_c = zeros(9,exe);
tempo_exe_NLLS = 0;
tempo_exe_ETS = 0;

cd ../
cd 'Dados'
param = readmatrix('commum_param.csv');
cd ../
cd 'Matlab'

for i=1:exe
    offset = [param(4,i);param(5,i);param(6,i)];
    Escala = [param(1,i);param(2,i);param(3,i)];
    Ang = [param(7,i);param(8,i);param(9,i)];

    rho = Ang(1);
    phi = Ang(2);
    lambda = Ang(3);
    
    e = [Escala; offset; Ang];

    scale = diag(Escala);

    T = [1 0 0; sin(rho) cos(rho) 0; sin(phi)*cos(lambda) sin(lambda) cos(phi)*cos(lambda)];

    for j=1:length(Data_Simul(1,:))
        Ruido(:,j) = 0.006*(rand(3,1));
        Dados_Corrompido(:,j) = scale*T*Data_Simul(:,j) + offset + Ruido(:,j); 
    end
    
%     ParT.x0 = 0;
%     ParT.y0 = 0;
%     ParT.z0 = 0;
%     ParT.a = 1;
%     ParT.b = 1;
%     ParT.c = 1;
%     ParT.rho = 0;
%     ParT.phi = 0;
%     ParT.lambda = 0;
%     ParP = ParT;

    p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0];
    [Time,p1] = test1(Dados_Corrompido, 1);
    H = ones(1, length(Dados_Corrompido(1,:)))';
    [tempo, passo,p] = test2(Dados_Corrompido, p0, H);

    tempo_exe_ETS = tempo_exe_ETS + Time;
    tempo_exe_NLLS = tempo_exe_NLLS + tempo;


   
    vet_error_ETS_c(:,i) = e-p1;
    vet_error_NLLS_c(:,i) = e-p;
end

tempo_exe_NLLS = (tempo_exe_NLLS / exe)*1000;
tempo_exe_ETS = (tempo_exe_ETS / exe)*1000;
ratio_time = tempo_exe_NLLS/tempo_exe_ETS;

disp('Tempo de execu��o ETS em ms:')
disp(tempo_exe_ETS)

disp('Tempo de execu��o NLLS em ms:')
disp(tempo_exe_NLLS)

disp('Raz�o entre ETS e NLLS (NLLS/ETS):')
disp(ratio_time)

executions = [1:1:i];

% M�dia dos erros
error_mean_NLLS = [mean(vet_error_NLLS_c(1,:)), mean(vet_error_NLLS_c(2,:)), mean(vet_error_NLLS_c(3,:)), mean(vet_error_NLLS_c(4,:)), mean(vet_error_NLLS_c(5,:)), mean(vet_error_NLLS_c(6,:)), mean(vet_error_NLLS_c(7,:)), mean(vet_error_NLLS_c(8,:)), mean(vet_error_NLLS_c(9,:))];
error_mean_ETS = [mean(vet_error_ETS_c(1,:)), mean(vet_error_ETS_c(2,:)), mean(vet_error_ETS_c(3,:)), mean(vet_error_ETS_c(4,:)), mean(vet_error_ETS_c(5,:)), mean(vet_error_ETS_c(6,:)), mean(vet_error_ETS_c(7,:)), mean(vet_error_ETS_c(8,:)), mean(vet_error_ETS_c(9,:))];

disp("M�dia dos erros:")
disp("ETS:" )
disp("Offset - x:")
disp(error_mean_ETS(4))
disp("Offset - y:")
disp(error_mean_ETS(5))
disp("Offset - z:")
disp(error_mean_ETS(6))
disp("Fator de escala - x:")
disp(error_mean_ETS(1))
disp("Fator de escala - y:")
disp(error_mean_ETS(2))
disp("Fator de escala - z:")
disp(error_mean_ETS(3))
disp("�ngulo Rho:")
disp(error_mean_ETS(7))
disp("�ngulo Phi:")
disp(error_mean_ETS(8))
disp("�ngulo Lambda:")
disp(error_mean_ETS(9))

disp("NLLS:" )
disp("Offset - x:")
disp(error_mean_NLLS(4))
disp("Offset - y:")
disp(error_mean_NLLS(5))
disp("Offset - z:")
disp(error_mean_NLLS(6))
disp("Fator de escala - x:")
disp(error_mean_NLLS(1))
disp("Fator de escala - y:")
disp(error_mean_NLLS(2))
disp("Fator de escala - z:")
disp(error_mean_NLLS(3))
disp("�ngulo Rho:")
disp(error_mean_NLLS(7))
disp("�ngulo Phi:")
disp(error_mean_NLLS(8))
disp("�ngulo Lambda:")
disp(error_mean_NLLS(9))

figure(1)
subplot(3,3,1), histogram(vet_error_ETS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo x");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
subplot(3,3,2), histogram(vet_error_ETS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo y");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
subplot(3,3,3), histogram(vet_error_ETS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Offset - eixo z");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")

subplot(3,3,4), histogram(vet_error_ETS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - x");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
subplot(3,3,5), histogram(vet_error_ETS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - y");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
subplot(3,3,6), histogram(vet_error_ETS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("Fator de escala - z");
ylabel("Distribui��o de probabilidade")
xlabel("Adimensional")
legend("ETS", "NLLS")


subplot(3,3,7), histogram(vet_error_ETS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("�ngulo Rho");
ylabel("Distribui��o de probabilidade")
xlabel("Graus")
subplot(3,3,8), histogram(vet_error_ETS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("�ngulo Phi");
ylabel("Distribui��o de probabilidade")
xlabel("Graus")
subplot(3,3,9), histogram(vet_error_ETS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
grid on;
title("�ngulo Lambda");
ylabel("Distribui��o de probabilidade")
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