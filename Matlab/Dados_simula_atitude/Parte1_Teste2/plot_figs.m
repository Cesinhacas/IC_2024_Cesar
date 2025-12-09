clear all
close all
clc

qTrue = readmatrix("qTrue.csv");
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("q_prop_sr.csv");
q_est_sr = readmatrix("q_est_sr.csv");

gyro_true = readmatrix("gyro_true.csv");
gyro_out = readmatrix("gyro_out.csv");

%%%%%%%% carregar os dados da simulação em C e plotar o quatérnion e
%%%%%%%% comparar com o verdadeiro
q_est_c = readmatrix("estados_estimados_c.csv");
q_prop_c = readmatrix("estados_propagados_c.csv");
q_triad_c = readmatrix("quaternion_c.csv");

q_est_c_sr = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3)];
q_prop_c_sr = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];
%q_triad_c_sr = [q_triad_c(:,4), q_triad_c(:,1), q_triad_c(:,2), q_triad_c(:,3)];

for i=1:1:1201
    q = q_est_c_sr(i,:);
    if q(1) < 0.0 || i == 503
        q_est_c_sr(i,:) = -q_est_c_sr(i,:);
    end
    q = q_prop_c_sr(i,:);
    if q(1) < 0.0 || i == 503
        q_prop_c_sr(i,:) = -q_prop_c_sr(i,:);
    end
    q = q_triad_c(i,:);
    if q(1) < 0.0 || i == 502
        q_triad_c(i,:) = -q_triad_c(i,:);
        q_Triad_sr(i,:) = -q_Triad_sr(i,:); 
    end

    q = qTrue - q_est_sr;
     if q(2)>1 || q(3)>1 || q(4)>1
         q_Triad_sr(i,:) = [q_Triad_sr(i,1), -q_Triad_sr(i,2:4)];
         q_est_sr(i,:) = [q_est_sr(i,1), -q_est_sr(i,2:4)];
         q_prop_sr(i,:) = [q_prop_sr(i,1), -q_prop_sr(i,2:4)];
     end
end

tempo = 0:0.05:60;

exe_plus = 0.02*ones(1201,1);
exe_minus = -0.02*ones(1201,1);

figure(1)
sgtitle("Comparação quatérnion verdadeiro e quatérnion do TRIAD - Matlab")

subplot(1,3,1)
plot(tempo,qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,q_Triad_sr)
hold on
title("(b) TRIAD - Matlab")
grid on
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");
xlim([0,60])

subplot(1,3,3)
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");
xlim([0,60])
plot(tempo,(qTrue-q_Triad_sr))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_TRIAD_True_m.pdf","ContentType","vector")

figure(2)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - Matlab")
set(gca,'fontsize', 22)
subplot(1,3,1)
plot(tempo,qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo, q_est_sr)
hold on
grid on
title("(b) Quatérnion estimado - Matlab")
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,3)
plot(tempo, qTrue-q_est_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_est_True_m.pdf","ContentType","vector")

figure(3)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - Matlab")

subplot(1,3,1)
plot(tempo,qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo, q_prop_sr)
hold on
title("(b) Quatérnion propagado - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,3)
plot(tempo, qTrue-q_prop_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')

ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_prop_True_m.pdf","ContentType","vector")

figure(4)
sgtitle("Diferença")

subplot(1,3,1)
plot(tempo, qTrue-q_Triad_sr)
hold on
title("(a) TRIAD")
grid on
xlim([0,60])
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo, qTrue-q_prop_sr)
hold on
title("(b) Propagado - Matlab")
grid on
xlim([0,60])
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");

subplot(1,3,3)
plot(tempo, qTrue-q_est_sr)
hold on
title("(c) Estimado - Matlab")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_TRIAD_prop_est_True_m.pdf","ContentType","vector")

figure(5)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - C")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,3)
plot(tempo, qTrue-q_prop_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_TRIAD_prop_c.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação quatérnion propagado - Matlab e quatérnion propagado - C")

subplot(1,3,1)
plot(tempo, q_prop_sr)
hold on
title("(a) Propagado - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,3)
plot(tempo, q_prop_sr-q_prop_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_prop_prop.pdf","ContentType","vector")

figure(7)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - C")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,2)
plot(tempo, q_est_c_sr)
hold on
title("(b) Estimado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,3)
plot(tempo, qTrue-q_est_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_est_True_c.pdf","ContentType","vector")

figure(8)
sgtitle("Comparação quatérnion verdadeiro e quatérnion TRIAD - C")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,2)
plot(tempo, q_triad_c)
hold on
title("(b) TRIAD - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Segundos");


subplot(1,3,3)
plot(tempo, qTrue-q_triad_c)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_TRIAD_True_c.pdf","ContentType","vector")


figure(9)
sgtitle("Comparação velocidade angular medida e real")
set(gca,'fontsize', 22)

subplot(1,3,1)
plot(tempo, gyro_true)
hold on
title("(a) Velocidade angular verdadeira")
grid on
xlim([0,60])
ylabel("Velocidade angular de cada eixo (Graus)");
xlabel("Segundos");


subplot(1,3,2)
plot(tempo, gyro_out)
hold on
title("(b) Velocidade angular - FK")
grid on
xlim([0,60])
ylabel("Velocidade angular de cada eixo (Graus)");
xlabel("Segundos");


subplot(1,3,3)
plot(tempo, gyro_true - gyro_out)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('x','y','z')
ylabel("Erro da velocidade angular de cada eixo (Graus)");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_velocidade_angular.pdf","ContentType","vector")