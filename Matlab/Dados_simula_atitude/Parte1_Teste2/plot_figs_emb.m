close all
clear all
clc

%% Data preparing

x_prop = readmatrix('estados_propagados_c.csv');
x_est = readmatrix('estados_estimados_c.csv');
q_Triad = readmatrix('quaternion_c.csv');
qTrue = readmatrix('qTrue.csv');

cd RES\
x_est_completo = readmatrix('x_est.txt');
x_prop_completo = readmatrix('x_prop.txt');
q_triad_c = readmatrix('q.txt');
tempo_exe = readmatrix("time.txt");
cd ..

euler_True = zeros(length(qTrue(1,:)), 3);
euler_Triad_sr = zeros(length(qTrue(1,:)), 3);
euler_prop_sr = zeros(length(qTrue(1,:)), 3);
euler_est_sr = zeros(length(qTrue(1,:)), 3);
euler_triad_c = zeros(length(qTrue(1,:)), 3);
euler_prop_c = zeros(length(qTrue(1,:)), 3);
euler_est_c = zeros(length(qTrue(1,:)), 3);

for i=1:1:1201
    q_triad_c(i,:) = q_triad_c(i,:)/norm(q_triad_c(i,:));
    if q_Triad(i,1) < 0
        q_Triad(i,:) = -q_Triad(i,:);
    end

    euler_True(i,:) = quat2eul(qTrue(i,:));
    euler_Triad_sr(i,:) = quat2eul(q_Triad_sr(i,:));
    euler_prop_sr(i,:) = quat2eul(q_prop_sr(i,:));
    euler_est_sr(i,:) = quat2eul(q_est_sr(i,:));
    euler_triad_c(i,:) = quat2eul(q_triad_c(i,:));
    euler_prop_c(i,:) = quat2eul(q_prop_c_sr(i,:));
    euler_est_c(i,:) = quat2eul(q_est_c_sr(i,:));
end

euler_True = deg2rad(euler_True);
euler_Triad_sr = deg2rad(euler_Triad_sr);
euler_prop_sr = deg2rad(euler_prop_sr);
euler_est_sr = deg2rad(euler_est_sr);
euler_triad_c = deg2rad(euler_triad_c);
euler_prop_c = deg2rad(euler_prop_c);
euler_est_c = deg2rad(euler_est_c);


%% Cálculo RMSE
disp("Tempo de execução médio da determinação e estimação de atitude")
disp(mean(tempo_exe))

erro_mat = [rmse(euler_True(:,1)', euler_triad_c(:,1)'), rmse(euler_True(:, 2)', euler_triad_c(:,2)'), rmse(euler_True(:,3)', euler_triad_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
disp(erro_mat)

erro_mat = [rmse(euler_True(:,1)', euler_prop_c(:,1)'), rmse(euler_True(:, 2)', euler_prop_c(:,2)'), rmse(euler_True(:,3)', euler_prop_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - propagador do C (radianos)")
disp(erro_mat)

erro_mat = [rmse(euler_True(:,1)', euler_est_c(:,1)'), rmse(euler_True(:, 2)', euler_est_c(:,2)'), rmse(euler_True(:,3)', euler_est_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_mat)

%% Plot figs

exe_plus = 0.02*ones(3601,1);
exe_minus = -0.02*ones(3601,1);

tempo = 0:0.05:60;

figure(5)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - Embarcado")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - F7")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, qTrue-q_prop_c_sr)
hold on
title("(c) Diferença")
grid on
plot(tempo,exe_minus, "--r")
plot(tempo,exe_plus, "--r")
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_prop_f7.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação quatérnion propagado - C e quatérnion propagado - Embarcado")

subplot(1,3,1)
plot(tempo, q_prop_sr)
hold on
title("(a) Propagado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - F7")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, q_prop_sr-q_prop_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_prop_prop_c_f7.pdf","ContentType","vector")

figure(7)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - Embarcado")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_est_c_sr)
hold on
title("(b) Estimado - F7")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, qTrue-q_est_c_sr)
hold on
title("(c) Diferença")
plot(tempo,exe_minus, "--r")
plot(tempo,exe_plus, "--r")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_f7.pdf","ContentType","vector")

figure(8)
sgtitle("Comparação quatérnion verdadeiro e quatérnion TRIAD - Embarcado")

subplot(1,3,1)
plot(tempo, qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_triad_c)
hold on
title("(b) TRIAD - F7")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, qTrue-q_triad_c)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_True_f7.pdf","ContentType","vector")

figure(13)
sgtitle("Comparação atitude verdadeira e atitude do TRIAD - Embarcado - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_triad_c)
hold on
title("(b) Atitude TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_triad_c)
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_True_f7_eul.pdf","ContentType","vector")

figure(14)
sgtitle("Comparação atitude verdadeira e atitude propagada - Embarcado - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_prop_c)
hold on
title("(b) Atitude propagada - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_prop_c)
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_prop_True_f7_eul.pdf","ContentType","vector")

figure(15)
sgtitle("Comparação atitude verdadeira e estimada - Embarcada - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_est_c)
hold on
title("(b) Atitude estimada - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_est_c)
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_f7_eul.pdf","ContentType","vector")

figure(16)
sgtitle("Comparação atitude propagada - Embarcada Vs. C - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_prop_sr)
hold on
title("(a) Atitude propagada C")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_prop_c)
hold on
title("(b) Atitude propagada - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_prop_sr-euler_prop_c)
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_c_f7_eul.pdf","ContentType","vector")