%% Código 01a - Gera vetor de 572 (passo = 10) 1112 (passo = 5) pontos similar ao do teste da bobina:
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
    cd 'Dados'
    save Dados_Teoricos.mat
    cd ../
end

%% Gera dados corrompidos
% OFFSET => -0.2 ~ 0.2
% Fs => 0.8 ~ 1.2
% Ang => -3 ~ 3 ** transformar de grau para radiano.

Data_Simul = Dados_Teoricos;

for i=1:1000
    offset = (rand(3,1)*0.4)-0.2;
    Escala = (rand(3,1)*0.4)+0.8;
    Ang = (rand(3,1)*6 - 3) * (pi/180);

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
    
    ParT.x0 = 0;
    ParT.y0 = 0;
    ParT.z0 = 0;
    ParT.a = 1;
    ParT.b = 1;
    ParT.c = 1;
    ParT.rho = 0;
    ParT.phi = 0;
    ParT.lambda = 0;
    ParP = ParT;

    p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0];
    [p1] = test1(Dados_Corrompido);
    [p] = test2(Dados_Corrompido, p0);
    [ParC] = FosterAnalytical_Rev00(0, 0, Dados_Corrompido, 1, 0, 0);
    [ParC2] = NLLS_9Dcalib(ParT, ParP, Dados_Corrompido, 1, 0, 0);
    p2 = [ParC.a; ParC.b; ParC.c; ParC.x0; ParC.y0; ParC.z0; ParC.rho; ParC.phi; ParC.lambda];
    p3 = [ParC2.a; ParC2.b; ParC2.c; ParC2.x0; ParC2.y0; ParC2.z0; ParC2.rho; ParC2.phi; ParC2.lambda];
    
    vet_error_ETS_c(:,i) = e-p1;
    vet_error_NLLS_c(:,i) = e-p;
    vet_error_ETS_d(:,i) = e-p2;
    vet_error_NLLS_d(:,i) = e-p3;
end
executions = [1:1:i];
figure(1)
subplot(3,1,1), plot(executions, vet_error_ETS_c(1,:),'r',executions, vet_error_ETS_d(1,:), 'g');
grid on;
title("Offset - eixo x");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_ETS_c(2,:),'r', executions, vet_error_ETS_d(2,:), 'g');
grid on;
title("Offset - eixo y");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_ETS_c(3,:),'r', executions, vet_error_ETS_d(3,:), 'g');
grid on;
title("Offset - eixo z");
ylabel("Error");
xlabel("Monte Carlo run");

figure(2)
subplot(3,1,1), plot(executions, vet_error_ETS_c(4,:),'r', executions, vet_error_ETS_d(4,:), 'g');
grid on;
title("Fator de escala - x");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_ETS_c(5,:),'r', executions, vet_error_ETS_d(5,:), 'g');
grid on;
title("Fator de escala - y");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_ETS_c(6,:),'r', executions, vet_error_ETS_d(6,:), 'g');
grid on;
title("Fator de escala - z");
ylabel("Error");
xlabel("Monte Carlo run");

figure(3)
subplot(3,1,1), plot(executions, vet_error_ETS_c(7,:),'r', executions, vet_error_ETS_d(7,:), 'g');
grid on;
title("Ângulo Rho");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_ETS_c(8,:),'r', executions, vet_error_ETS_d(8,:), 'g');
grid on;
title("Ângulo Phi");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_ETS_c(9,:),'r', executions, vet_error_ETS_d(9,:), 'g');
grid on;
title("Ângulo Lambda");
ylabel("Error");
xlabel("Monte Carlo run");

figure(4)
subplot(3,1,1), plot(executions, vet_error_NLLS_c(1,:),'r', executions, vet_error_NLLS_d(1,:), 'g');
grid on;
title("Offset - eixo x");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_NLLS_c(2,:),'r', executions, vet_error_NLLS_d(2,:), 'g');
grid on;
title("Offset - eixo y");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_NLLS_c(3,:),'r', executions, vet_error_NLLS_d(3,:), 'g');
grid on;
title("Offset - eixo z");
ylabel("Error");
xlabel("Monte Carlo run");

figure(5)
subplot(3,1,1), plot(executions, vet_error_NLLS_c(4,:),'r', executions, vet_error_NLLS_d(4,:), 'g');
grid on;
title("Fator de escala - x");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_NLLS_c(5,:),'r', executions, vet_error_NLLS_d(5,:), 'g');
grid on;
title("Fator de escala - y");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_NLLS_c(6,:),'r', executions, vet_error_NLLS_d(6,:), 'g');
grid on;
title("Fator de escala - z");
ylabel("Error");
xlabel("Monte Carlo run");

figure(6)
subplot(3,1,1), plot(executions, vet_error_NLLS_c(7,:),'r', executions, vet_error_NLLS_d(7,:), 'g');
grid on;
title("Ângulo Rho");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,2), plot(executions, vet_error_NLLS_c(8,:),'r', executions, vet_error_NLLS_d(8,:), 'g');
grid on;
title("Ângulo Phi");
ylabel("Error");
xlabel("Monte Carlo run");
subplot(3,1,3), plot(executions, vet_error_NLLS_c(9,:),'r', executions, vet_error_NLLS_d(9,:), 'g');
grid on;
title("Ângulo Lambda");
ylabel("Error");
xlabel("Monte Carlo run");