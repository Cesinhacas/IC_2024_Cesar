clear all
close all
clc

%% Data preparing

qTrue = readmatrix("qTrue.csv");
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("q_prop_sr.csv");
q_est_sr = readmatrix("q_est_sr.csv");

gyro_true = readmatrix("gyro_true.csv");
gyro_out = readmatrix("gyro_out.csv");

%%%%%%%% carregar os dados da simulação em C e plotar o quatérnion e
%%%%%%%% comparar com o verdadeiro
q_est_c = readmatrix("estados_estimados_py.csv");
q_prop_c = readmatrix("estados_propagados_py.csv");
q_triad_c = readmatrix("quaternion_py.csv");

q_est_c_sr = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3)];
q_prop_c_sr = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];
%q_triad_c_sr = [q_triad_c(:,4), q_triad_c(:,1), q_triad_c(:,2), q_triad_c(:,3)];

euler_True = zeros(length(qTrue(1,:)), 3);
euler_Triad_sr = zeros(length(qTrue(1,:)), 3);
euler_prop_sr = zeros(length(qTrue(1,:)), 3);
euler_est_sr = zeros(length(qTrue(1,:)), 3);
euler_triad_c = zeros(length(qTrue(1,:)), 3);
euler_prop_c = zeros(length(qTrue(1,:)), 3);
euler_est_c = zeros(length(qTrue(1,:)), 3);

for i=1:1:1201
    q = q_est_c_sr(i,:);
    if q(1) < 0.0 || i == 862
        q_est_c_sr(i,:) = -q_est_c_sr(i,:);
    end
    q = q_prop_c_sr(i,:);
    if q(1) < 0.0 || i == 862
        q_prop_c_sr(i,:) = -q_prop_c_sr(i,:);
    end
    q = q_triad_c(i,:);
    if q(1) < 0.0 || i == 613 || i == 1103
        q_triad_c(i,:) = -q_triad_c(i,:);
    end

    if i == 127 || i ==862
        q_prop_sr(i,:) = -q_prop_sr(i,:);
        q_est_sr(i,:) = -q_est_sr(i,:);
    end
    if  i == 613 || i == 1103
        q_Triad_sr(i,:) = -q_Triad_sr(i,:);
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

tempo = 0:0.05:60;

exe_plus = 0.02*ones(1201,1);
exe_minus = -0.02*ones(1201,1);

%% Cálculo RMSE
erro_mat = [rmse(euler_True(:,1)', euler_triad_c(:,1)'), rmse(euler_True(:, 2)', euler_triad_c(:,2)'), rmse(euler_True(:,3)', euler_triad_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
disp(erro_mat)

erro_mat = [rmse(euler_True(:,1)', euler_prop_c(:,1)'), rmse(euler_True(:, 2)', euler_prop_c(:,2)'), rmse(euler_True(:,3)', euler_prop_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - propagador do Python (radianos)")
disp(erro_mat)

erro_mat = [rmse(euler_True(:,1)', euler_est_c(:,1)'), rmse(euler_True(:, 2)', euler_est_c(:,2)'), rmse(euler_True(:,3)', euler_est_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
disp(erro_mat)

%% Plot das figuras

figure(5)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - Python")

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
title("(b) Propagado - Python")
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
exportgraphics(gcf,"Comparacao_TRIAD_prop_py.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação quatérnion propagado - MATLAB e quatérnion propagado - Python")

subplot(1,3,1)
plot(tempo, q_prop_sr)
hold on
title("(a) Propagado - MATLAB")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - Python")
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
exportgraphics(gcf,"Comparacao_prop_prop_m_py.pdf","ContentType","vector")

figure(7)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - Python")

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
title("(b) Estimado - Python")
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
exportgraphics(gcf,"Comparacao_est_True_py.pdf","ContentType","vector")

figure(8)
sgtitle("Comparação quatérnion verdadeiro e quatérnion TRIAD - Python")

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
title("(b) TRIAD - Python")
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
exportgraphics(gcf,"Comparacao_TRIAD_True_py.pdf","ContentType","vector")

figure(13)
sgtitle("Comparação atitude verdadeira e atitude do TRIAD - Python - Ângulos de Euler")

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
title("(b) Atitude TRIAD - Python")
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
exportgraphics(gcf,"Comparacao_TRIAD_True_py_eul.pdf","ContentType","vector")

figure(14)
sgtitle("Comparação atitude verdadeira e atitude propagada - Python - Ângulos de Euler")

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
title("(b) Atitude propagada - Python")
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
exportgraphics(gcf,"Comparacao_prop_True_py_eul.pdf","ContentType","vector")

figure(15)
sgtitle("Comparação atitude verdadeira e estimada - Python - Ângulos de Euler")

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
title("(b) Atitude estimada - Python")
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
exportgraphics(gcf,"Comparacao_est_True_py_eul.pdf","ContentType","vector")

figure(16)
sgtitle("Comparação atitude propagada - Python Vs. MATLAB - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_prop_sr)
hold on
title("(a) Atitude propagada MATLAB")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_prop_c)
hold on
title("(b) Atitude propagada - Python")
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
exportgraphics(gcf,"Comparacao_est_m_py_eul.pdf","ContentType","vector")