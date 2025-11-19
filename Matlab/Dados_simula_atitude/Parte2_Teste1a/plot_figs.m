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

for i=1:1:1201
    q = q_est_c_sr(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || 1040
        q_est_c_sr(i,:) = -q_est_c_sr(i,:);
    end
    q = q_prop_c_sr(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || 1040
        q_prop_c_sr(i,:) = -q_prop_c_sr(i,:);
    end
    q = q_triad_c(i,:);
    if q(1) < 0.0 || i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || 1040
        q_triad_c(i,:) = -q_triad_c(i,:);
    end
    if i ==117 || i==118 || i==405 || i==406 || i==578 || i==579 || i==580 || i==755 || i==756 || i==575 || i==901 || i==902 || i == 1038 || i ==1039 || 1040
        q_Triad_sr(i,:) = -q_Triad_sr(i,:);
        q_est_sr(i,:) = -q_est_sr(i,:);
        q_prop_sr(i,:) = -q_prop_sr(i,:);
    end
end

figure(1)
sgtitle("Comparação quatérnion verdadeiro e quatérnion do TRIAD - Matlab")
set(gca,'fontsize', 20)

subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

plot(q_Triad_sr)
subplot(1,3,3)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

plot(qTrue-q_Triad_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_TRIAD_True_m.pdf","ContentType","vector")

figure(2)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - Matlab")
set(gca,'fontsize', 22)
subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_est_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(qTrue-q_est_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_est_True_m.pdf","ContentType","vector")

figure(3)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - Matlab")
set(gca,'fontsize', 22)

subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_prop_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(qTrue-q_prop_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_prop_True_m.pdf","ContentType","vector")

figure(4)
sgtitle("Diferença entre os quatérnions")
set(gca,'fontsize', 22)
subplot(1,3,1)
title("(a) TRIAD")
plot(qTrue-q_Triad_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
title("(b) Propagado - Matlab")
plot(qTrue-q_prop_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
title("(c) Estimado - Matlab")
plot(qTrue-q_est_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_TRIAD_prop_est_True_m.pdf","ContentType","vector")

figure(5)
sgtitle("Comparação quatérnion verdadeiro e quatérnion propagado - C")
set(gca,'fontsize', 22)
subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_prop_c_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(qTrue-q_prop_c_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_TRIAD_prop_c.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação quatérnion propagado - Matlab e quatérnion propagado - C")
set(gca,'fontsize', 22)

subplot(1,3,1)
plot(q_prop_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_prop_c_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(q_prop_sr-q_prop_c_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_prop_prop.pdf","ContentType","vector")

figure(7)
sgtitle("Comparação quatérnion verdadeiro e quatérnion estimado - C")
set(gca,'fontsize', 22)

subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_est_c_sr)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(qTrue-q_est_c_sr)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_est_True_c.pdf","ContentType","vector")

figure(8)
sgtitle("Comparação quatérnion verdadeiro e quatérnion TRIAD - C")
set(gca,'fontsize', 22)

subplot(1,3,1)
plot(qTrue)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,2)
plot(q_triad_c)
hold on
grid on
xlim([0,1201])
set(gca,'fontsize', 15)

subplot(1,3,3)
plot(qTrue-q_triad_c)
hold on
grid on
xlim([0,1201])
legend('q0','q1','q2','q3')
set(gca,'fontsize', 15)
exportgraphics(gcf,"Comparacao_TRIAD_True_c.pdf","ContentType","vector")