clear all
close all
clc

qTrue = readmatrix("qTrue.csv");
q_Triad_sr = readmatrix("q_Triad_sr.csv");
q_prop_sr = readmatrix("q_prop_sr.csv");
q_est_sr = readmatrix("q_est_sr.csv");

%%%%%%%% carregar os dados da simulação em C e plotar o quatérnion e
%%%%%%%% comparar com o verdadeiro
q_est_c = readmatrix("estados_estimados_c.csv");
q_prop_c = readmatrix("estados_propagados_c.csv");
q_triad_c = readmatrix("quaternion_c.csv");

q_est_c_sr = [q_est_c(:,4), q_est_c(:,1), q_est_c(:,2), q_est_c(:,3)];
q_prop_c_sr = [q_prop_c(:,4), q_prop_c(:,1), q_prop_c(:,2), q_prop_c(:,3)];

euler_True = zeros(length(qTrue(1,:)), 3);
euler_Triad_sr = zeros(length(qTrue(1,:)), 3);
euler_prop_sr = zeros(length(qTrue(1,:)), 3);
euler_est_sr = zeros(length(qTrue(1,:)), 3);
euler_triad_c = zeros(length(qTrue(1,:)), 3);
euler_prop_c = zeros(length(qTrue(1,:)), 3);
euler_est_c = zeros(length(qTrue(1,:)), 3);

for i=1:1:3601
    q = q_est_c_sr(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || i==1040
        q_est_c_sr(i,:) = -q_est_c_sr(i,:);
    end
    q = q_prop_c_sr(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || i==1040
        q_prop_c_sr(i,:) = -q_prop_c_sr(i,:);
    end
    q = q_triad_c(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || i==1040
        q_triad_c(i,:) = -q_triad_c(i,:);
    end

    q = qTrue - q_Triad_sr;
    if q(2)>1 || q(3)>1 || q(4)>1
        q_Triad_sr(i,:) = [q_Triad_sr(i,1), -q_Triad_sr(i,2:4)];
        q_est_sr(i,:) = [q_est_sr(i,1), -q_est_sr(i,2:4)];
        q_prop_sr(i,:) = [q_prop_sr(i,1), -q_prop_sr(i,2:4)];
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

exe_plus = 0.02*ones(3601,1);
exe_minus = -0.02*ones(3601,1);

tempo = 0:0.05:180;

figure(1)
sgtitle("Comparação quatérnion verdadeiro e quatérnion do TRIAD - Matlab")

subplot(1,3,1)
plot(tempo,qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,q_Triad_sr)
hold on
title("(b) TRIAD - Matlab")
grid on
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");
xlim([0,60])
plot(tempo,(qTrue-q_Triad_sr))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_True_m.pdf","ContentType","vector")

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
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo, q_est_sr)
hold on
grid on
title("(b) Quatérnion estimado - Matlab")
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,3)
plot(tempo, qTrue-q_est_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_m.pdf","ContentType","vector")

figure(3)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - Matlab")

subplot(1,3,1)
plot(tempo,qTrue)
hold on
title("(a) Quatérnion verdadeiro")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo, q_prop_sr)
hold on
title("(b) Quatérnion propagado - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,3)
plot(tempo, qTrue-q_prop_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')

ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_prop_True_m.pdf","ContentType","vector")

figure(4)
sgtitle("Diferença")

subplot(1,3,1)
plot(tempo, qTrue-q_Triad_sr)
hold on
title("(a) TRIAD")
grid on
xlim([0,60])
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo, qTrue-q_prop_sr)
hold on
title("(b) Propagado - Matlab")
grid on
xlim([0,60])
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");

subplot(1,3,3)
plot(tempo, qTrue-q_est_sr)
hold on
title("(c) Estimado - Matlab")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_prop_est_True_m.pdf","ContentType","vector")

figure(5)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - C")

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
title("(b) Propagado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, qTrue-q_prop_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_prop_c.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação quatérnion propagado - Matlab e quatérnion propagado - C")

subplot(1,3,1)
plot(tempo, q_prop_sr)
hold on
title("(a) Propagado - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_prop_c_sr)
hold on
title("(b) Propagado - C")
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
exportgraphics(gcf,"Comparacao_prop_prop.pdf","ContentType","vector")

figure(7)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - C")

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
title("(b) Estimado - C")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do quatérnion");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, qTrue-q_est_c_sr)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_c.pdf","ContentType","vector")

figure(8)
sgtitle("Comparação quatérnion verdadeiro e quatérnion TRIAD - C")

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
title("(b) TRIAD - C")
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
exportgraphics(gcf,"Comparacao_TRIAD_True_c.pdf","ContentType","vector")

figure(10)
sgtitle("Comparação atitude verdadeira e atitude do TRIAD - MATLAB - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_Triad_sr)
hold on
title("(b) Atitude TRIAD - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_Triad_sr)
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_True_m_eul.pdf","ContentType","vector")

figure(11)
sgtitle("Comparação atitude verdadeira e atitude propagada - MATLAB - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_prop_sr)
hold on
title("(b) Atitude propagada - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_prop_sr)
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_prop_True_m_eul.pdf","ContentType","vector")

figure(12)
sgtitle("Comparação atitude verdadeira e estimada - MATLAB - Ângulos de Euler")

subplot(1,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(1,3,2)
plot(tempo,euler_est_sr)
hold on
title("(b) Atitude estimada - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(1,3,3)
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
plot(tempo,euler_True-euler_est_sr)
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_m_eul.pdf","ContentType","vector")

figure(13)
sgtitle("Comparação atitude verdadeira e atitude do TRIAD - C - Ângulos de Euler")

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
title("(b) Atitude TRIAD - C")
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
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_TRIAD_True_c_eul.pdf","ContentType","vector")

figure(14)
sgtitle("Comparação atitude verdadeira e atitude propagada - C - Ângulos de Euler")

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
title("(b) Atitude propagada - C")
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
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_prop_True_c_eul.pdf","ContentType","vector")

figure(15)
sgtitle("Comparação atitude verdadeira e estimada - C - Ângulos de Euler")

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
title("(b) Atitude estimada - C")
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
ylim([-0.03,0.03])
title("(c) Diferença")
legend('Yaw','Pitch','Roll')
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_est_True_c_eul.pdf","ContentType","vector")

figure(16)
sgtitle("Comparação atitude propagada - C Vs. MATLAB - Ângulos de Euler")

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
title("(b) Atitude propagada - C")
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
exportgraphics(gcf,"Comparacao_est_m_c_eul.pdf","ContentType","vector")