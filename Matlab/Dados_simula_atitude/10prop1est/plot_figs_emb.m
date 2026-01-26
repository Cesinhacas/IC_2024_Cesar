close all
clear all
clc

x_prop = readmatrix('x_prop.csv');
x_est = readmatrix('x_est.csv');
q_Triad = readmatrix('q_Triad.csv');
qTrue = readmatrix('qTrue.csv');

cd RES\
x_est_completo = readmatrix('x_est.txt');
x_prop_completo = readmatrix('x_prop.txt');
q_triad_c = readmatrix('q.txt');
tempo_exe = readmatrix("time.txt");
cd ..

disp("Tempo de execução médio da determinação e estimação de atitude")
disp(mean(tempo_exe))

exe_plus = 0.02*ones(3601,1);
exe_minus = -0.02*ones(3601,1);

tempo = 0:0.05:60;

figure(1)
sgtitle("Comparação estados propagados - apenas propagador embarcado")

subplot(1,3,1)
plot(tempo,x_prop)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_prop_completo)
hold on
title("(b) Estados propagados - C")
grid on
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])

subplot(1,3,3)
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])
plot(tempo,(x_prop-x_prop_completo))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_propagador_only.pdf","ContentType","vector")

figure(2)
sgtitle("Comparação estados estimados - apenas estimador embarcado")

subplot(1,3,1)
plot(tempo,x_est)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_est_completo)
hold on
title("(b) Estados propagados - C")
grid on
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])

subplot(1,3,3)
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])
plot(tempo,(x_est-x_est_completo))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_estimador_only.pdf","ContentType","vector")

figure(3)
sgtitle("Comparação TRIAD - Matlab Vs. F7")

subplot(1,3,1)
plot(tempo,q_Triad)
hold on
title("(a) Quatérnion TRIAD - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,q_triad_c)
hold on
title("(b) Quatérnion TRIAD - F7")
grid on
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])

subplot(1,3,3)
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");
xlim([0,60])
plot(tempo,(q_Triad - q_triad_c))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Comparacao_estimador_only.pdf","ContentType","vector")