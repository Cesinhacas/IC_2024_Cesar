close all
clear all
clc

%%%%%%%% Validação individual %%%%%%%
x_est_val_only = readmatrix("validacao_estimador_only.csv");
x_prop_val_only = readmatrix("validacao_propagador_only.csv");

%%%%%%%% validação FK %%%%%%%%%%
x_est_val_FK = readmatrix("estados_est_only_FK.csv");
x_prop_val_FK = readmatrix("estados_prop_only_FK.csv");

x_est = readmatrix("x_est.csv");
x_prop = readmatrix("x_prop.csv");

%%%%%%%% validação completa %%%%%%%%%%
x_est_completo = readmatrix("estados_estimados_c.csv");
x_prop_completo = readmatrix("estados_propagados_c.csv");

tempo = 0:0.05:60;

figure(1)
sgtitle("Comparação estados propagados - apenas propagador em C")

subplot(1,3,1)
plot(tempo,x_prop)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_prop_val_only)
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
plot(tempo,(x_prop-x_prop_val_only))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_propagador_only.pdf","ContentType","vector")

figure(2)
sgtitle("Comparação estados estimados - apenas estimador em C")

subplot(1,3,1)
plot(tempo,x_est)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_est_val_only)
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
plot(tempo,(x_est-x_est_val_only))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_estimador_only.pdf","ContentType","vector")

%%%%%%%%%%%%%%%%

figure(3)
sgtitle("Comparação estados propagados - EKF completo")

subplot(1,3,1)
plot(tempo,x_prop)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_prop_val_FK)
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
plot(tempo,(x_prop-x_prop_val_FK))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_propagador_FK_completo.pdf","ContentType","vector")

figure(4)
sgtitle("Comparação estados estimados - EKF completo")

subplot(1,3,1)
plot(tempo,x_est)
hold on
title("(a) Estados propagados - Matlab")
grid on
xlim([0,60])
ylabel("Magnitude de cada componente do estado");
xlabel("Segundos");

subplot(1,3,2)
plot(tempo,x_est_val_FK)
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
plot(tempo,(x_est-x_est_val_FK))
hold on
grid on
xlim([0,60])
title("(c) Diferença")
legend('q0','q1','q2','q3','bx', 'by','bz')
ylabel("Erro de cada componente do quatérnion");
xlabel("Segundos");
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Comparacao_estimador_FK_completo.pdf","ContentType","vector")

%%%%%%%%%%
figure(5)
sgtitle("Comparação estados propagados - sistema completo")

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
exportgraphics(gcf,"Comparacao_propagador_sis_completo.pdf","ContentType","vector")

figure(6)
sgtitle("Comparação estados estimados - sistema completo")

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
exportgraphics(gcf,"Comparacao_estimador_sis_completo.pdf","ContentType","vector")