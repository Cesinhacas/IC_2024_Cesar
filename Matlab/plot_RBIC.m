close all
clear all
clc

cd ..\
cd Dados\
vet_error_NLLS_c = readmatrix('MCS_ETS_c.csv');

vet_error_NLLS_p = readmatrix('MCS_NLLS.csv');

vet_error_NLLS_m = readmatrix('MCS_NLLS_Matlab.csv');

vet_error_NLLS_f7 = readmatrix('MTS_NLLS_f7_FPU.csv');

vet_error_NLLS_f7_nofpu = readmatrix('MTS_NLLS_f7_NOFPU.csv');
cd ..\
cd Matlab

cd Dados_simula_atitude\10prop1est\
%%%%%%%% Validação individual C%%%%%%%
x_est_val_only = readmatrix("validacao_estimador_only.csv");
x_prop_val_only = readmatrix("validacao_propagador_only.csv");

%%%%%%%% Validação individual Python%%%%%%%
x_est_val_only_py = readmatrix("validacao_estimador_python.csv");
x_prop_val_only_py = readmatrix("validacao_propagador_python.csv");

%%%%%%%% Parâmetros MATLAB %%%%%%%
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("x_prop.csv");
q_est_sr = readmatrix("x_est.csv");

%%%%%% Parâmetros C %%%%%%%%%%%%
q_est_c = readmatrix("estados_estimados_c.csv");
q_prop_c = readmatrix("estados_propagados_c.csv");
q_triad_c = readmatrix("quaternion_c.csv");

%%%%%% Parâmetros Python %%%%%%%%%
q_est_py = readmatrix("estados_estimados_py.csv");
q_prop_py = readmatrix("estados_propagados_py.csv");
q_triad_py = readmatrix("quaternion_py.csv");

qTrue = readmatrix("qTrue.csv");
cd RES\
q_triad_f7 = readmatrix("q.txt");
q_est_f7 = readmatrix("x_est.txt");
cd ..\..\..\

q_est_sr = [q_est_sr(:,4), q_est_sr(:,1), q_est_sr(:,2), q_est_sr(:,3), q_est_sr(:,5), q_est_sr(:,6), q_est_sr(:,7)];
q_est_c = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3), q_est_c(:,5), q_est_c(:,6), q_est_c(:,7)];
q_est_py = [q_est_py(:,4), q_est_py(:,1), q_est_py(:,2), q_est_py(:,3)];
q_est_f7 = [q_est_f7(:,4), q_est_f7(:,1), q_est_f7(:,2), q_est_f7(:,3)];

q_prop_sr = [q_prop_sr(:,4), q_prop_sr(:,1), q_prop_sr(:,2), q_prop_sr(:,3)];
q_prop_c = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];
q_prop_py = [q_prop_py(:,4), q_prop_py(:,1), q_prop_py(:,2), q_prop_py(:,3)];

x_est_val_only = [x_est_val_only(:,4), x_est_val_only(:,1), x_est_val_only(:,2), x_est_val_only(:,3)];
x_est_val_only_py = [x_est_val_only_py(:,4), x_est_val_only_py(:,1), x_est_val_only_py(:,2), x_est_val_only_py(:,3)];

x_prop_val_only = [x_prop_val_only(:,4), x_prop_val_only(:,1), x_prop_val_only(:,2), x_prop_val_only(:,3)];
x_prop_val_only_py = [x_prop_val_only_py(:,4), x_prop_val_only_py(:,1), x_prop_val_only_py(:,2), x_prop_val_only_py(:,3)];

for i=1:1:1201
    q = q_triad_f7(i,:);
    if q(1) < 0.0
        q_triad_f7(i,:) = -q_triad_f7(i,:);
    end

    q = q_est_f7(i,:);
    if q(1) < 0.0
        q_est_f7(i,:) = -q_est_f7(i,:);
    end

    q = q_triad_c(i,:);
    if q(1) < 0.0
        q_triad_c(i,:) = -q_triad_c(i,:);
    end

    q = q_triad_py(i,:);
    if q(1) < 0.0
        q_triad_py(i,:) = -q_triad_py(i,:);
    end

    q = q_est_sr(i,1:4);
    if q(1) < 0.0
        q_est_sr(i,1:4) = -q_est_sr(i,1:4);
    end

    q = q_prop_sr(i,:);
    if q(1) < 0.0
        q_prop_sr(i,:) = -q_prop_sr(i,:);
    end

    q = q_prop_c(i,:);
    if q(1) < 0.0
        q_prop_c(i,:) = -q_prop_c(i,:);
    end

    q = q_prop_py(i,:);
    if q(1) < 0.0
        q_prop_py(i,:) = -q_prop_py(i,:);
    end

    q = q_est_c(i,1:4);
    if q(1) < 0.0
        q_est_c(i,1:4) = -q_est_c(i,1:4);
    end

    q = x_est_val_only(i,:);
    if q(1) < 0.0
        x_est_val_only(i,:) = -x_est_val_only(i,:);
    end

    q = x_est_val_only_py(i,:);
    if q(1) < 0.0
        x_est_val_only_py(i,:) = -x_est_val_only_py(i,:);
    end

    q = x_prop_val_only(i,:);
    if q(1) < 0.0
        x_prop_val_only(i,:) = -x_prop_val_only(i,:);
    end

    q = x_prop_val_only_py(i,:);
    if q(1) < 0.0
        x_prop_val_only_py(i,:) = -x_prop_val_only_py(i,:);
    end

    q_triad_f7(i,:) = q_triad_f7(i,:)/norm(q_triad_f7);
    q_est_f7(i,:) = q_est_f7(i,:)/norm(q_est_f7);
end

euler_triad_f7 = quat2eul(q_triad_f7);
euler_triad_f7 = deg2rad(euler_triad_f7);

euler_est_f7 = quat2eul(q_est_f7);
euler_est_f7 = deg2rad(euler_est_f7);

euler_True = quat2eul(qTrue);
euler_Triad_sr = quat2eul(q_Triad_sr);
euler_triad_c = quat2eul(q_triad_c);
euler_triad_py = quat2eul(q_triad_py);

euler_prop_c_val = quat2eul(x_prop_val_only);
euler_prop_py_val = quat2eul(x_prop_val_only_py);
euler_est_c_val = quat2eul(x_est_val_only);
euler_est_py_val = quat2eul(x_est_val_only_py);

euler_est_c = quat2eul(q_est_c(:,1:4));
euler_est_py = quat2eul(q_est_py);

euler_prop_sr = quat2eul(q_prop_sr);
euler_est_sr = quat2eul(q_est_sr(:,1:4));

euler_True = deg2rad(euler_True);
euler_Triad_sr = deg2rad(euler_Triad_sr);
euler_triad_c = deg2rad(euler_triad_c);
euler_triad_py = deg2rad(euler_triad_py);

euler_prop_c_val = deg2rad(euler_prop_c_val);
euler_prop_py_val = deg2rad(euler_prop_py_val);
euler_est_c_val = deg2rad(euler_est_c_val);
euler_est_py_val = deg2rad(euler_est_py_val);

euler_prop_sr = deg2rad(euler_prop_sr);
euler_est_sr = deg2rad(euler_est_sr);

euler_est_py = deg2rad(euler_est_py);
euler_est_c = deg2rad(euler_est_c);

tempo = 0:0.05:60;

erro_mat = [rmse(euler_True(:,1)', euler_Triad_sr(:,1)'), rmse(euler_True(:, 2)', euler_Triad_sr(:,2)'), rmse(euler_True(:,3)', euler_Triad_sr(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
disp(erro_mat)

erro_est_mat = [rmse(euler_True(:,1)', euler_est_sr(:,1)'), rmse(euler_True(:, 2)', euler_est_sr(:,2)'), rmse(euler_True(:,3)', euler_est_sr(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
disp(erro_est_mat)

erro_triad_c = [rmse(euler_True(:,1)', euler_triad_c(:,1)'), rmse(euler_True(:, 2)', euler_triad_c(:,2)'), rmse(euler_True(:,3)', euler_triad_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
disp(erro_triad_c)

erro_est_c = [rmse(euler_True(:,1)', euler_est_c(:,1)'), rmse(euler_True(:, 2)', euler_est_c(:,2)'), rmse(euler_True(:,3)', euler_est_c(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_est_c)

erro_triad_py = [rmse(euler_True(:,1)', euler_triad_py(:,1)'), rmse(euler_True(:, 2)', euler_triad_py(:,2)'), rmse(euler_True(:,3)', euler_triad_py(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
disp(erro_triad_py)

erro_est_py = [rmse(euler_True(:,1)', euler_est_py(:,1)'), rmse(euler_True(:, 2)', euler_est_py(:,2)'), rmse(euler_True(:,3)', euler_est_py(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
disp(erro_est_py)

erro_f7_triad = [rmse(euler_True(:,1)', euler_triad_f7(:,1)'), rmse(euler_True(:, 2)', euler_triad_f7(:,2)'), rmse(euler_True(:,3)', euler_triad_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
disp(erro_f7_triad)

erro_f7_est = [rmse(euler_True(:,1)', euler_est_f7(:,1)'), rmse(euler_True(:, 2)', euler_est_f7(:,2)'), rmse(euler_True(:,3)', euler_est_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_f7_est)

%%%%%%%%%%%% NLLS computador %%%%%%%%%%%%
figure(3)
sgtitle("Distribuição dos erros na estimação dos prâmetros - computador dedicado")
subplot(3,3,1), histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,2), histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,3), histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,4), histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,5), histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,6), histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)

subplot(3,3,7), histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)
%legend("C", "Python", "Matlab")

subplot(3,3,8), histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)
%legend("C", "Python", "Matlab")

subplot(3,3,9), histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_p(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("C", "Python", "Matlab")
set(gca,'fontsize', 13)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%%%%%% NLLS embarcado Vs. Matlab %%%%%%%%%%%%%%%%%%%%%
figure(4)
sgtitle("Distribuição dos erros na estimação dos prâmetros - MATLAB Vs. embarcado")
subplot(3,3,1), histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
set(gca,'fontsize', 13)

subplot(3,3,2), histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
set(gca,'fontsize', 13)

subplot(3,3,3), histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Distribuição de probabilidade")
xlabel("Gauss")
legend("Matlab", "F7 - float - FPU on", "F7 - float - FPU off")
set(gca,'fontsize', 13)

subplot(3,3,4), histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)

subplot(3,3,5), histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)

subplot(3,3,6), histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F7 - float - FPU off")
set(gca,'fontsize', 13)

subplot(3,3,7), histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)

subplot(3,3,8), histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
set(gca,'fontsize', 13)

subplot(3,3,9), histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Distribuição de probabilidade")
xlabel("Adimensional")
legend("Matlab", "F7 - float - FPU on", "F7 - float - FPU off")
set(gca,'fontsize', 13)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%% Validação TRIAD computador %%%%%%%%%%%%
figure(5)
sgtitle("Validação do TRIAD")

subplot(3,3,1)
plot(tempo,euler_True)
hold on
title("(a1) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,2)
plot(tempo,euler_Triad_sr)
hold on
title("(b1) TRIAD - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_Triad_sr))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c1) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,4)
plot(tempo,euler_True)
hold on
title("(a2) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,5)
plot(tempo,euler_triad_py)
hold on
title("(b2) TRIAD - Python")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,6)
xlim([0,60])
plot(tempo,(euler_True-euler_triad_py))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c2) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,7)
plot(tempo,euler_True)
hold on
title("(a3) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,8)
plot(tempo,euler_triad_c)
hold on
title("(b3) TRIAD - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,9)
plot(tempo,(euler_True-euler_triad_c))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c3) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%%%%%%%% Validação propagador Computador %%%%%%%%%%%%%
figure(6)
sgtitle("Validação do propagador - EKF")

subplot(3,3,1)
plot(tempo,euler_True)
hold on
title("(a1) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,2)
plot(tempo,euler_prop_sr)
hold on
title("(b1) Propagador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_prop_sr))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c1) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,4)
plot(tempo,euler_True)
hold on
title("(a2) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,5)
plot(tempo,euler_prop_py_val)
hold on
title("(b2) Propagador - Python")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,6)
xlim([0,60])
plot(tempo,(euler_True-euler_prop_py_val))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c2) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,7)
plot(tempo,euler_True)
hold on
title("(a3) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,8)
plot(tempo,euler_prop_c_val)
hold on
title("(b3) Propagador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,9)
plot(tempo,(euler_True-euler_prop_c_val))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c3) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%%%%%%% Validação Estimador computador %%%%%%%%%%%%%%%%%
figure(7)
sgtitle("Validação do estimador - EKF")

subplot(3,3,1)
plot(tempo,euler_True)
hold on
title("(a1) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,2)
plot(tempo,euler_est_sr)
hold on
title("(b1) Estimador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_est_sr))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c1) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,4)
plot(tempo,euler_True)
hold on
title("(a2) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,5)
plot(tempo,euler_est_py_val)
hold on
title("(b2) Estimador - Python")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,6)
xlim([0,60])
plot(tempo,(euler_True-euler_est_py_val))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c2) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,7)
plot(tempo,euler_True)
hold on
title("(a3) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,8)
plot(tempo,euler_est_c_val)
hold on
title("(b3) Estimador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,9)
plot(tempo,(euler_True-euler_est_c_val))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c3) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%%%%%% Validação completa do sistema de atitude %%%%%%
figure(8)
sgtitle("Validação completa - EKF")

subplot(3,3,1)
plot(tempo,euler_True)
hold on
title("(a1) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,2)
plot(tempo,euler_est_sr)
hold on
title("(b1) Estimador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_est_sr))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c1) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,4)
plot(tempo,euler_True)
hold on
title("(a2) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,5)
plot(tempo,euler_est_py)
hold on
title("(b2) Estimador - Python")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,6)
xlim([0,60])
plot(tempo,(euler_True-euler_est_py))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c2) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

subplot(3,3,7)
plot(tempo,euler_True)
hold on
title("(a3) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(3,3,8)
plot(tempo,euler_est_c)
hold on
title("(b3) Estimador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(3,3,9)
plot(tempo,(euler_True-euler_est_c))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c3) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%% Comparação dos estados estimados %%%%%%%%%%%%%
figure(9)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - C")

subplot(1,3,1)
plot(tempo, q_est_sr)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do vetor de estados");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_est_c)
hold on
title("(b) Estimado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do vetor de estados");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, q_est_sr-q_est_c)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3','bx','by','bz')
ylabel("Erro de cada componente do vetor de estados");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%%%%%% Validação TRIAD embarcado %%%%%%%%%
figure(10)
sgtitle("Validação TRIAD - embarcado")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%% Validação EKF embarcado %%%%%%%%%%
figure(11)
sgtitle("Validação EKF - embarcado")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_est_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-1e-3,1e-3])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

cd Dados_simula_atitude\Parte2_Teste1a\
%%%%%%%% Parâmetros MATLAB %%%%%%%
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("x_prop.csv");
q_est_sr = readmatrix("x_est.csv");

%%%%%% Parâmetros C %%%%%%%%%%%%
q_est_c = readmatrix("estados_estimados_c.csv");
q_prop_c = readmatrix("estados_propagados_c.csv");
q_triad_c = readmatrix("quaternion_c.csv");

%%%%%% Parâmetros Python %%%%%%%%%
q_est_py = readmatrix("estados_estimados_py.csv");
q_prop_py = readmatrix("estados_propagados_py.csv");
q_triad_py = readmatrix("quaternion_py.csv");

qTrue = readmatrix("qTrue.csv");
cd RES\
q_triad_f7 = readmatrix("q.txt");
q_est_f7 = readmatrix("x_est.txt");
cd ..\..\..\

q_est_sr = [q_est_sr(:,4), q_est_sr(:,1), q_est_sr(:,2), q_est_sr(:,3), q_est_sr(:,5), q_est_sr(:,6), q_est_sr(:,7)];
q_est_c = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3), q_est_c(:,5), q_est_c(:,6), q_est_c(:,7)];
q_est_py = [q_est_py(:,4), q_est_py(:,1), q_est_py(:,2), q_est_py(:,3)];
q_est_f7 = [q_est_f7(:,4), q_est_f7(:,1), q_est_f7(:,2), q_est_f7(:,3)];

q_prop_sr = [q_prop_sr(:,4), q_prop_sr(:,1), q_prop_sr(:,2), q_prop_sr(:,3)];
q_prop_c = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];
q_prop_py = [q_prop_py(:,4), q_prop_py(:,1), q_prop_py(:,2), q_prop_py(:,3)];


for i=1:1:1201
    q = q_triad_f7(i,:);
    if q(1) < 0.0
        q_triad_f7(i,:) = -q_triad_f7(i,:);
    end

    q = q_est_f7(i,:);
    if q(1) < 0.0
        q_est_f7(i,:) = -q_est_f7(i,:);
    end

    q = q_triad_c(i,:);
    if q(1) < 0.0
        q_triad_c(i,:) = -q_triad_c(i,:);
    end

    q = q_triad_py(i,:);
    if q(1) < 0.0
        q_triad_py(i,:) = -q_triad_py(i,:);
    end

    q = q_est_sr(i,1:4);
    if q(1) < 0.0
        q_est_sr(i,1:4) = -q_est_sr(i,1:4);
    end

    q = q_prop_sr(i,:);
    if q(1) < 0.0
        q_prop_sr(i,:) = -q_prop_sr(i,:);
    end

    q = q_prop_c(i,:);
    if q(1) < 0.0
        q_prop_c(i,:) = -q_prop_c(i,:);
    end

    q = q_prop_py(i,:);
    if q(1) < 0.0
        q_prop_py(i,:) = -q_prop_py(i,:);
    end

    q = q_est_c(i,1:4);
    if q(1) < 0.0
        q_est_c(i,1:4) = -q_est_c(i,1:4);
    end

    q = x_est_val_only(i,:);
    if q(1) < 0.0
        x_est_val_only(i,:) = -x_est_val_only(i,:);
    end

    q = x_est_val_only_py(i,:);
    if q(1) < 0.0
        x_est_val_only_py(i,:) = -x_est_val_only_py(i,:);
    end

    q = x_prop_val_only(i,:);
    if q(1) < 0.0
        x_prop_val_only(i,:) = -x_prop_val_only(i,:);
    end

    q = x_prop_val_only_py(i,:);
    if q(1) < 0.0
        x_prop_val_only_py(i,:) = -x_prop_val_only_py(i,:);
    end

    q_triad_f7(i,:) = q_triad_f7(i,:)/norm(q_triad_f7);
    q_est_f7(i,:) = q_est_f7(i,:)/norm(q_est_f7);
end

euler_triad_f7 = quat2eul(q_triad_f7);
euler_triad_f7 = deg2rad(euler_triad_f7);

euler_est_f7 = quat2eul(q_est_f7);
euler_est_f7 = deg2rad(euler_est_f7);

euler_True = quat2eul(qTrue);
euler_Triad_sr = quat2eul(q_Triad_sr);
euler_triad_c = quat2eul(q_triad_c);
euler_triad_py = quat2eul(q_triad_py);

euler_est_c = quat2eul(q_est_c(:,1:4));
euler_est_py = quat2eul(q_est_py);

euler_est_sr = quat2eul(q_est_sr(:,1:4));

euler_True = deg2rad(euler_True);
euler_Triad_sr = deg2rad(euler_Triad_sr);
euler_triad_c = deg2rad(euler_triad_c);
euler_triad_py = deg2rad(euler_triad_py);

euler_est_sr = deg2rad(euler_est_sr);

euler_est_py = deg2rad(euler_est_py);
euler_est_c = deg2rad(euler_est_c);

tempo = 0:0.05:60;

disp("====== MEDIDAS DESCALIBRADAS =========")

erro_mat = [rmse(euler_True(1:1201,1)', euler_Triad_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_Triad_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_Triad_sr(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
disp(erro_mat)

erro_est_mat = [rmse(euler_True(1:1201,1)', euler_est_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_sr(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
disp(erro_est_mat)

erro_triad_c = [rmse(euler_True(1:1201,1)', euler_triad_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_c(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
disp(erro_triad_c)

erro_est_c = [rmse(euler_True(1:1201,1)', euler_est_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_c(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_est_c)

erro_triad_py = [rmse(euler_True(1:1201,1)', euler_triad_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_py(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
disp(erro_triad_py)

erro_est_py = [rmse(euler_True(1:1201,1)', euler_est_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_py(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
disp(erro_est_py)

erro_f7_triad = [rmse(euler_True(1:1201,1)', euler_triad_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_triad_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_triad_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
disp(erro_f7_triad)

erro_f7_est = [rmse(euler_True(1:1201,1)', euler_est_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_est_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_est_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_f7_est)

%%%%%%%%% Medidas descalibradas - TRIAD - embarcado %%%%%%%%%%%%%%
figure(12)
sgtitle("Medidas descalibradas TRIAD - embarcado")

subplot(1,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%% Medidas descalibradas - EKF embarcado %%%%%%%%%%
figure(13)
sgtitle("Medidas descalibradas EKF - embarcado")

subplot(1,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_est_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

cd Dados_simula_atitude\Parte2_Teste1b\
%%%%%%%% Parâmetros MATLAB %%%%%%%
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("x_prop.csv");
q_est_sr = readmatrix("x_est.csv");

%%%%%% Parâmetros C %%%%%%%%%%%%
q_est_c = readmatrix("estados_estimados_c.csv");
q_prop_c = readmatrix("estados_propagados_c.csv");
q_triad_c = readmatrix("quaternion_c.csv");

%%%%%% Parâmetros Python %%%%%%%%%
q_est_py = readmatrix("estados_estimados_py.csv");
q_prop_py = readmatrix("estados_propagados_py.csv");
q_triad_py = readmatrix("quaternion_py.csv");

cd RES\
q_triad_f7 = readmatrix("q.txt");
q_est_f7 = readmatrix("x_est.txt");
cd ..\..\..\

q_est_sr = [q_est_sr(:,4), q_est_sr(:,1), q_est_sr(:,2), q_est_sr(:,3), q_est_sr(:,5), q_est_sr(:,6), q_est_sr(:,7)];
q_est_c = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3), q_est_c(:,5), q_est_c(:,6), q_est_c(:,7)];
q_est_py = [q_est_py(:,4), q_est_py(:,1), q_est_py(:,2), q_est_py(:,3)];
q_est_f7 = [q_est_f7(:,4), q_est_f7(:,1), q_est_f7(:,2), q_est_f7(:,3)];

q_prop_sr = [q_prop_sr(:,4), q_prop_sr(:,1), q_prop_sr(:,2), q_prop_sr(:,3)];
q_prop_c = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];
q_prop_py = [q_prop_py(:,4), q_prop_py(:,1), q_prop_py(:,2), q_prop_py(:,3)];

x_est_val_only = [x_est_val_only(:,4), x_est_val_only(:,1), x_est_val_only(:,2), x_est_val_only(:,3)];
x_est_val_only_py = [x_est_val_only_py(:,4), x_est_val_only_py(:,1), x_est_val_only_py(:,2), x_est_val_only_py(:,3)];

x_prop_val_only = [x_prop_val_only(:,4), x_prop_val_only(:,1), x_prop_val_only(:,2), x_prop_val_only(:,3)];
x_prop_val_only_py = [x_prop_val_only_py(:,4), x_prop_val_only_py(:,1), x_prop_val_only_py(:,2), x_prop_val_only_py(:,3)];

for i=1:1:1201
    q = q_triad_f7(i,:);
    if q(1) < 0.0
        q_triad_f7(i,:) = -q_triad_f7(i,:);
    end

    q = q_est_f7(i,:);
    if q(1) < 0.0
        q_est_f7(i,:) = -q_est_f7(i,:);
    end

    q = q_triad_c(i,:);
    if q(1) < 0.0
        q_triad_c(i,:) = -q_triad_c(i,:);
    end

    q = q_triad_py(i,:);
    if q(1) < 0.0
        q_triad_py(i,:) = -q_triad_py(i,:);
    end

    q = q_est_sr(i,1:4);
    if q(1) < 0.0
        q_est_sr(i,1:4) = -q_est_sr(i,1:4);
    end

    q = q_prop_sr(i,:);
    if q(1) < 0.0
        q_prop_sr(i,:) = -q_prop_sr(i,:);
    end

    q = q_prop_c(i,:);
    if q(1) < 0.0
        q_prop_c(i,:) = -q_prop_c(i,:);
    end

    q = q_prop_py(i,:);
    if q(1) < 0.0
        q_prop_py(i,:) = -q_prop_py(i,:);
    end

    q = q_est_c(i,1:4);
    if q(1) < 0.0
        q_est_c(i,1:4) = -q_est_c(i,1:4);
    end

    q = x_est_val_only(i,:);
    if q(1) < 0.0
        x_est_val_only(i,:) = -x_est_val_only(i,:);
    end

    q = x_est_val_only_py(i,:);
    if q(1) < 0.0
        x_est_val_only_py(i,:) = -x_est_val_only_py(i,:);
    end

    q = x_prop_val_only(i,:);
    if q(1) < 0.0
        x_prop_val_only(i,:) = -x_prop_val_only(i,:);
    end

    q = x_prop_val_only_py(i,:);
    if q(1) < 0.0
        x_prop_val_only_py(i,:) = -x_prop_val_only_py(i,:);
    end

    q_triad_f7(i,:) = q_triad_f7(i,:)/norm(q_triad_f7);
    q_est_f7(i,:) = q_est_f7(i,:)/norm(q_est_f7);
end

euler_triad_f7 = quat2eul(q_triad_f7);
euler_triad_f7 = deg2rad(euler_triad_f7);

euler_est_f7 = quat2eul(q_est_f7);
euler_est_f7 = deg2rad(euler_est_f7);

euler_True = quat2eul(qTrue);
euler_Triad_sr = quat2eul(q_Triad_sr);
euler_triad_c = quat2eul(q_triad_c);
euler_triad_py = quat2eul(q_triad_py);

euler_prop_c_val = quat2eul(x_prop_val_only);
euler_prop_py_val = quat2eul(x_prop_val_only_py);
euler_est_c_val = quat2eul(x_est_val_only);
euler_est_py_val = quat2eul(x_est_val_only_py);

euler_prop_c = quat2eul(q_prop_c);
euler_prop_py = quat2eul(q_prop_py);
euler_est_c = quat2eul(q_est_c(:,1:4));
euler_est_py = quat2eul(q_est_py);

euler_prop_sr = quat2eul(q_prop_sr);
euler_est_sr = quat2eul(q_est_sr(:,1:4));

euler_True = deg2rad(euler_True);
euler_Triad_sr = deg2rad(euler_Triad_sr);
euler_triad_c = deg2rad(euler_triad_c);
euler_triad_py = deg2rad(euler_triad_py);

euler_prop_c_val = deg2rad(euler_prop_c_val);
euler_prop_py_val = deg2rad(euler_prop_py_val);
euler_est_c_val = deg2rad(euler_est_c_val);
euler_est_py_val = deg2rad(euler_est_py_val);

euler_prop_sr = deg2rad(euler_prop_sr);
euler_est_sr = deg2rad(euler_est_sr);

euler_est_py = deg2rad(euler_est_py);
euler_est_c = deg2rad(euler_est_c);

tempo = 0:0.05:60;

disp("====== MEDIDAS CALIBRADAS =========")

erro_mat = [rmse(euler_True(1:1201,1)', euler_Triad_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_Triad_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_Triad_sr(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
disp(erro_mat)

erro_est_mat = [rmse(euler_True(1:1201,1)', euler_est_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_sr(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
disp(erro_est_mat)

erro_triad_c = [rmse(euler_True(1:1201,1)', euler_triad_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_c(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
disp(erro_triad_c)

erro_est_c = [rmse(euler_True(1:1201,1)', euler_est_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_c(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_est_c)

erro_triad_py = [rmse(euler_True(1:1201,1)', euler_triad_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_py(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
disp(erro_triad_py)

erro_est_py = [rmse(euler_True(1:1201,1)', euler_est_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_py(1:1201,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
disp(erro_est_py)

erro_f7_triad = [rmse(euler_True(1:1201,1)', euler_triad_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_triad_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_triad_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
disp(erro_f7_triad)

erro_f7_est = [rmse(euler_True(1:1201,1)', euler_est_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_est_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_est_f7(:,3)')];
disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
disp(erro_f7_est)


%%%%%%%%% Medidas descalibradas - TRIAD - embarcado %%%%%%%%%%%%%%
figure(14)
sgtitle("Medidas calibradas TRIAD - embarcado")

subplot(1,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');

%%%%%%% Medidas descalibradas - EKF embarcado %%%%%%%%%%
figure(15)
sgtitle("Medidas calibradas EKF - embarcado")

subplot(1,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_est_f7)
hold on
title("(b) TRIAD - F7")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Roll','Pitch','Yaw')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');