close all
clear all
clc

cd ..\
cd Dados\
vet_error_NLLS_c = readmatrix('MCS_NLLS_c.csv');

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

    q_triad_f7(i,:) = q_triad_f7(i,:)/norm(q_triad_f7(i,:));
    q_est_f7(i,:) = q_est_f7(i,:)/norm(q_est_f7(i,:));

    q = q_triad_f7(i,:);
    if q(1) < 0.0
        q_triad_f7(i,:) = -q_triad_f7(i,:);
    end

    q = q_est_f7(i,:);
    if q(1) < 0.0
        q_est_f7(i,:) = -q_est_f7(i,:);
    end
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




erro_euler_Triad_sr = euler_True - euler_Triad_sr;
erro_euler_est_sr = euler_True - euler_est_sr;

erro_euler_Triad_c = euler_True - euler_triad_c;
erro_euler_est_c = euler_True - euler_est_c;

erro_euler_Triad_py = euler_True - euler_triad_py;
erro_euler_est_py = euler_True - euler_est_py;

erro_euler_Triad_f7 = euler_True - euler_triad_f7;
erro_euler_est_f7 = euler_True - euler_est_f7;

for iii=74:length(euler_True(:,1))
    for xxx=1:3
        if (abs(erro_euler_Triad_sr(iii,xxx))>0.04)
            erro_euler_Triad_sr(iii,xxx)=erro_euler_Triad_sr(iii-1,xxx);
        end
        if (abs(erro_euler_est_sr(iii,xxx))>0.04)
            erro_euler_est_sr(iii,xxx)=erro_euler_est_sr(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_c(iii,xxx))>0.04)
            erro_euler_Triad_c(iii,xxx)=erro_euler_Triad_c(iii-1,xxx);
        end
        if (abs(erro_euler_est_c(iii,xxx))>0.04)
            erro_euler_est_c(iii,xxx)=erro_euler_est_c(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_py(iii,xxx))>0.04)
            erro_euler_Triad_py(iii,xxx)=erro_euler_Triad_py(iii-1,xxx);
        end
        if (abs(erro_euler_est_py(iii,xxx))>0.04)
            erro_euler_est_py(iii,xxx)=erro_euler_est_py(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_f7(iii,xxx))>0.04)
            erro_euler_Triad_f7(iii,xxx)=erro_euler_Triad_f7(iii-1,xxx);
        end
        if (abs(erro_euler_est_f7(iii,xxx))>0.04)
            erro_euler_est_f7(iii,xxx)=erro_euler_est_f7(iii-1,xxx);
        end
    end
end

erro_mat_RMSE = [sqrt(mean(erro_euler_Triad_sr(:,1).^2)), sqrt(mean(erro_euler_Triad_sr(:,2).^2)), sqrt(mean(erro_euler_Triad_sr(:,3).^2))];
erro_est_mat_RMSE = [sqrt(mean(erro_euler_est_sr(75:end,1).^2)), sqrt(mean(erro_euler_est_sr(75:end,2).^2)), sqrt(mean(erro_euler_est_sr(75:end,3).^2))];
disp(erro_mat_RMSE)
disp(erro_est_mat_RMSE)

erro_triad_c_RMSE = [sqrt(mean(erro_euler_Triad_c(:,1).^2)), sqrt(mean(erro_euler_Triad_c(:,2).^2)), sqrt(mean(erro_euler_Triad_c(:,3).^2))];
erro_est_c_RMSE = [sqrt(mean(erro_euler_est_c(75:end,1).^2)), sqrt(mean(erro_euler_est_c(75:end,2).^2)), sqrt(mean(erro_euler_est_c(75:end,3).^2))];
disp(erro_triad_c_RMSE)
disp(erro_est_c_RMSE)

erro_triad_py_RMSE = [sqrt(mean(erro_euler_Triad_py(:,1).^2)), sqrt(mean(erro_euler_Triad_py(:,2).^2)), sqrt(mean(erro_euler_Triad_py(:,3).^2))];
erro_est_py_RMSE = [sqrt(mean(erro_euler_est_py(75:end,1).^2)), sqrt(mean(erro_euler_est_py(75:end,2).^2)), sqrt(mean(erro_euler_est_py(75:end,3).^2))];
disp(erro_triad_py_RMSE)
disp(erro_est_py_RMSE)

erro_triad_f7_RMSE = [sqrt(mean(erro_euler_Triad_f7(:,1).^2)), sqrt(mean(erro_euler_Triad_f7(:,2).^2)), sqrt(mean(erro_euler_Triad_f7(:,3).^2))];
erro_est_f7_RMSE = [sqrt(mean(erro_euler_est_f7(75:end,1).^2)), sqrt(mean(erro_euler_est_f7(75:end,2).^2)), sqrt(mean(erro_euler_est_f7(75:end,3).^2))];
disp(erro_triad_f7_RMSE)
disp(erro_est_f7_RMSE)


% erro_mat_RMSE = [rmse(euler_True(:,1)', euler_Triad_sr(:,1)'), rmse(euler_True(:, 2)', euler_Triad_sr(:,2)'), rmse(euler_True(:,3)', euler_Triad_sr(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
% disp(erro_mat_RMSE)
% 
% erro_est_mat_RMSE = [rmse(euler_True(:,1)', euler_est_sr(:,1)'), rmse(euler_True(:, 2)', euler_est_sr(:,2)'), rmse(euler_True(:,3)', euler_est_sr(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
% disp(erro_est_mat_RMSE)
% 
% erro_triad_c_RMSE = [rmse(euler_True(:,1)', euler_triad_c(:,1)'), rmse(euler_True(:, 2)', euler_triad_c(:,2)'), rmse(euler_True(:,3)', euler_triad_c(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
% disp(erro_triad_c_RMSE)
% 
% erro_est_c_RMSE = [rmse(euler_True(:,1)', euler_est_c(:,1)'), rmse(euler_True(:, 2)', euler_est_c(:,2)'), rmse(euler_True(:,3)', euler_est_c(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
% disp(erro_est_c_RMSE)
% 
% erro_triad_py = [rmse(euler_True(:,1)', euler_triad_py(:,1)'), rmse(euler_True(:, 2)', euler_triad_py(:,2)'), rmse(euler_True(:,3)', euler_triad_py(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
% disp(erro_triad_py_RMSE)
% 
% erro_est_py_RMSE = [rmse(euler_True(:,1)', euler_est_py(:,1)'), rmse(euler_True(:, 2)', euler_est_py(:,2)'), rmse(euler_True(:,3)', euler_est_py(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
% disp(erro_est_py_RMSE)
% 
% erro_f7_triad_RMSE = [rmse(euler_True(:,1)', euler_triad_f7(:,1)'), rmse(euler_True(:, 2)', euler_triad_f7(:,2)'), rmse(euler_True(:,3)', euler_triad_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
% disp(erro_f7_triad_RMSE)
% 
% erro_f7_est_RMSE = [rmse(euler_True(:,1)', euler_est_f7(:,1)'), rmse(euler_True(:, 2)', euler_est_f7(:,2)'), rmse(euler_True(:,3)', euler_est_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador embarcado (radianos)")
% disp(erro_f7_est_RMSE)


% figure(1)
% subplot(3,1,1)
% plot(tempo, euler_est_c-euler_est_f7)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");
% 
% subplot(3,1,2)
% plot(tempo, euler_True-euler_est_f7)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");
% 
% subplot(3,1,3)
% plot(tempo, euler_True-euler_est_c)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");
% 
% 
% figure(2)
% subplot(3,1,1)
% plot(tempo, euler_est_c-euler_est_f7)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");
% 
% subplot(3,1,2)
% plot(tempo, erro_euler_est_f7)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");
% 
% subplot(3,1,3)
% plot(tempo, erro_euler_est_c)
% hold on
% lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
% lgd.FontSize = 15;
% lgd.ItemTokenSize = [10 6];
% ylabel("Ângulo (rad)");
% xlabel("Tempo (s)");

cd ..\Figuras\RBIC\
%%%%%%%%%%%% NLLS computador %%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(3,3,1)
histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Dist. de prob.")
xlabel("Gauss")
set(gca,'fontsize', 8)

subplot(3,3,2)
histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Dist. de prob.")
xlabel("Gauss")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 8)

subplot(3,3,3)
histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Dist. de prob.")
xlabel("Gauss")
lgd = legend("Matlab", "C");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)

subplot(3,3,4)
histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Dist. de prob.")
xlabel("Adimensional")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 8)

subplot(3,3,5)
histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
 histogram(vet_error_NLLS_c(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Dist. de prob.")
xlabel("Adimensional")
%legend("C", "Python", "Matlab")
set(gca,'fontsize', 8)

subplot(3,3,6)
histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Dist. de prob.")
xlabel("Adimensional")
lgd = legend("Matlab", "C");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)

subplot(3,3,7),
histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)
%legend("C", "Python", "Matlab")

subplot(3,3,8)
histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)
%legend("C", "Python", "Matlab")

subplot(3,3,9)
histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
%histogram(vet_error_NLLS_p(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_c(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Dist. de prob.")
xlabel("Adimensional")
lgd = legend("Matlab", "C");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura4.png","ContentType","vector")

%%%%%%%%%%%%%% NLLS embarcado Vs. Matlab %%%%%%%%%%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(3,3,1), histogram(vet_error_NLLS_m(4,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(4,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo x");
ylabel("Dist. de prob.")
xlabel("Gauss")
set(gca,'fontsize', 8)

subplot(3,3,2), histogram(vet_error_NLLS_m(5,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(5,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo y");
ylabel("Dist. de prob.")
xlabel("Gauss")
set(gca,'fontsize', 8)

subplot(3,3,3), histogram(vet_error_NLLS_m(6,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(6,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Offset - eixo z");
ylabel("Dist. de prob.")
xlabel("Gauss")
lgd = legend("Matlab", "F7 FPU on", "F7 FPU off");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)

subplot(3,3,4), histogram(vet_error_NLLS_m(1,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(1,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala X");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)

subplot(3,3,5), histogram(vet_error_NLLS_m(2,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(2,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Y");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)

subplot(3,3,6), histogram(vet_error_NLLS_m(3,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(3,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Fator de escala Z");
ylabel("Dist. de prob.")
xlabel("Adimensional")
lgd = legend("Matlab", "F7 FPU on", "F7 FPU off");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)

subplot(3,3,7), histogram(vet_error_NLLS_m(7,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(7,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Rho");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)

subplot(3,3,8), histogram(vet_error_NLLS_m(8,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(8,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Phi");
ylabel("Dist. de prob.")
xlabel("Adimensional")
set(gca,'fontsize', 8)

subplot(3,3,9), histogram(vet_error_NLLS_m(9,:), 50, 'FaceAlpha', 1, 'Normalization','probability','FaceColor', "b");
hold on
grid on
histogram(vet_error_NLLS_f7(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "g");
histogram(vet_error_NLLS_f7_nofpu(9,:), 50, 'FaceAlpha', 0.4, 'Normalization','probability','FaceColor', "r");
title("Lambda");
ylabel("Dist. de prob.")
xlabel("Adimensional")
lgd = legend("Matlab", "F7 FPU on", "F7 FPU off");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
set(gca,'fontsize', 8)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura5.png","ContentType","vector")

%%%%%%%%%% Validação TRIAD computador %%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - MATLAB")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_Triad_sr)
hold on
title("TRIAD - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_Triad_sr))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - MATLAB)")
lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
lgd.FontSize = 4;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,4)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - C")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_triad_c)
hold on
title("TRIAD - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
plot(tempo,(euler_True-euler_triad_c))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - C)")
%legend('Roll','Pitch','Yaw','Orientation','horizontal');
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

set(findall(gcf,'-property','FontSize'),'FontSize',9)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura6.png","ContentType","vector")

%%%%%%%%%%%%%%%% Validação propagador Computador %%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - MATLAB")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_prop_sr)
hold on
title("Propagador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_prop_sr))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - MATLAB)")
lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
lgd.FontSize = 4;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,4)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - C")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_prop_c_val)
hold on
title("Propagador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
plot(tempo,(euler_True-euler_prop_c_val))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - C)")
%legend('Roll','Pitch','Yaw','Orientation','horizontal');
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',9)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura7.png","ContentType","vector")

%%%%%%%%%%%%%%% Validação Estimador computador %%%%%%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - MATLAB")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_est_sr)
hold on
title("Estimador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_est_sr))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - MATLAB)")
lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
lgd.FontSize = 4;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,4)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - C")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_est_c_val)
hold on
title("Estimador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
plot(tempo,(euler_True-euler_est_c_val))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - C)")
%legend('Roll','Pitch','Yaw','Orientation','horizontal');
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',9)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura8.png","ContentType","vector")

%%%%%%%%%%%%%% Validação completa do sistema de atitude %%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - MATLAB")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_est_sr)
hold on
title("Estimador - MATLAB")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_est_sr))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - MATLAB)")
lgd = legend('Roll','Pitch','Yaw','Orientation','horizontal');
lgd.FontSize = 4;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,4)
plot(tempo,euler_True)
hold on
title("Atitude verdadeira - C")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_est_c)
hold on
title("Estimador - C")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
plot(tempo,(euler_True-euler_est_c))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("Erro (Verdadeira - C)")
%legend('Roll','Pitch','Yaw','Orientation','horizontal');
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',9)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura9.png","ContentType","vector")

%%%%%%%%%% Comparação dos estados estimados %%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(1,3,1)
plot(tempo, q_est_sr, 'LineWidth',1.5)
hold on
title("(a) Estimado - MATLAB")
grid on
xlim([0,60])
ylabel("Quatérnions (adimensional) e bias girômetro (rad/s)");
xlabel("Tempo (s)");


subplot(1,3,2)
plot(tempo, q_est_c, 'LineWidth',1.5)
hold on
title("(b) Estimado - C")
grid on
xlim([0,60])
ylabel("Quatérnions (adimensional) e bias girômetro (rad/s)");
xlabel("Tempo (s)");


subplot(1,3,3)
plot(tempo, q_est_sr-q_est_c, 'LineWidth',1.5)
hold on
title("(c) Diferença")
grid on
xlim([0,60])
lgd = legend('q0','q1','q2','q3','bx','by','bz');
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Erro de cada componente do vetor de estados");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',11)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura10.png","ContentType","vector")

%%%%%%%%%%% Validação TRIAD embarcado %%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True)
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("(c) Erro (Verdadeiro - TRIAD)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

%%%%%%% Validação EKF embarcado %%%%%%%%%%
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,4)
plot(tempo,euler_True)
hold on
title("(d) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_est_f7)
hold on
title("(e) EKF (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
xlim([0,60])
plot(tempo,(euler_True-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-2e-3,2e-3])
title("(f) Erro (Verdadeiro - EKF)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',11)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura11.png","ContentType","vector")

cd ..\..\Matlab

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
erro_euler_Triad_sr = euler_True(1:1201,:) - euler_Triad_sr(1:1201,:);
erro_euler_est_sr = euler_True(1:1201,:) - euler_est_sr(1:1201,:);

erro_euler_Triad_c = euler_True(1:1201,:) - euler_triad_c(1:1201,:);
erro_euler_est_c = euler_True(1:1201,:) - euler_est_c(1:1201,:);

erro_euler_Triad_py = euler_True(1:1201,:) - euler_triad_py(1:1201,:);
erro_euler_est_py = euler_True(1:1201,:) - euler_est_py(1:1201,:);

erro_euler_Triad_f7 = euler_True(1:1201,:) - euler_triad_f7(1:1201,:);
erro_euler_est_f7 = euler_True(1:1201,:) - euler_est_f7(1:1201,:);

for iii=74:length(euler_True(1:1201,1))
    for xxx=1:3
        if (abs(erro_euler_Triad_sr(iii,xxx))>0.04)
            erro_euler_Triad_sr(iii,xxx)=erro_euler_Triad_sr(iii-1,xxx);
        end
        if (abs(erro_euler_est_sr(iii,xxx))>0.04)
            erro_euler_est_sr(iii,xxx)=erro_euler_est_sr(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_c(iii,xxx))>0.04)
            erro_euler_Triad_c(iii,xxx)=erro_euler_Triad_c(iii-1,xxx);
        end
        if (abs(erro_euler_est_c(iii,xxx))>0.04)
            erro_euler_est_c(iii,xxx)=erro_euler_est_c(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_py(iii,xxx))>0.04)
            erro_euler_Triad_py(iii,xxx)=erro_euler_Triad_py(iii-1,xxx);
        end
        if (abs(erro_euler_est_py(iii,xxx))>0.04)
            erro_euler_est_py(iii,xxx)=erro_euler_est_py(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_f7(iii,xxx))>0.04)
            erro_euler_Triad_f7(iii,xxx)=erro_euler_Triad_f7(iii-1,xxx);
        end
        if (abs(erro_euler_est_f7(iii,xxx))>0.04)
            erro_euler_est_f7(iii,xxx)=erro_euler_est_f7(iii-1,xxx);
        end
    end
end

erro_mat_RMSE = [sqrt(mean(erro_euler_Triad_sr(:,1).^2)), sqrt(mean(erro_euler_Triad_sr(:,2).^2)), sqrt(mean(erro_euler_Triad_sr(:,3).^2))];
erro_est_mat_RMSE = [sqrt(mean(erro_euler_est_sr(75:end,1).^2)), sqrt(mean(erro_euler_est_sr(75:end,2).^2)), sqrt(mean(erro_euler_est_sr(75:end,3).^2))];
disp(erro_mat_RMSE)
disp(erro_est_mat_RMSE)

erro_triad_c_RMSE = [sqrt(mean(erro_euler_Triad_c(:,1).^2)), sqrt(mean(erro_euler_Triad_c(:,2).^2)), sqrt(mean(erro_euler_Triad_c(:,3).^2))];
erro_est_c_RMSE = [sqrt(mean(erro_euler_est_c(75:end,1).^2)), sqrt(mean(erro_euler_est_c(75:end,2).^2)), sqrt(mean(erro_euler_est_c(75:end,3).^2))];
disp(erro_triad_c_RMSE)
disp(erro_est_c_RMSE)

erro_triad_py_RMSE = [sqrt(mean(erro_euler_Triad_py(:,1).^2)), sqrt(mean(erro_euler_Triad_py(:,2).^2)), sqrt(mean(erro_euler_Triad_py(:,3).^2))];
erro_est_py_RMSE = [sqrt(mean(erro_euler_est_py(75:end,1).^2)), sqrt(mean(erro_euler_est_py(75:end,2).^2)), sqrt(mean(erro_euler_est_py(75:end,3).^2))];
disp(erro_triad_py_RMSE)
disp(erro_est_py_RMSE)

erro_triad_f7_RMSE = [sqrt(mean(erro_euler_Triad_f7(:,1).^2)), sqrt(mean(erro_euler_Triad_f7(:,2).^2)), sqrt(mean(erro_euler_Triad_f7(:,3).^2))];
erro_est_f7_RMSE = [sqrt(mean(erro_euler_est_f7(75:end,1).^2)), sqrt(mean(erro_euler_est_f7(75:end,2).^2)), sqrt(mean(erro_euler_est_f7(75:end,3).^2))];
disp(erro_triad_f7_RMSE)
disp(erro_est_f7_RMSE)

% erro_mat = [rmse(euler_True(1:1201,1)', euler_Triad_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_Triad_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_Triad_sr(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
% disp(erro_mat)
% 
% erro_est_mat = [rmse(euler_True(1:1201,1)', euler_est_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_sr(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
% disp(erro_est_mat)
% 
% erro_triad_c = [rmse(euler_True(1:1201,1)', euler_triad_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_c(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
% disp(erro_triad_c)
% 
% erro_est_c = [rmse(euler_True(1:1201,1)', euler_est_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_c(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
% disp(erro_est_c)
% 
% erro_triad_py = [rmse(euler_True(1:1201,1)', euler_triad_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_py(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
% disp(erro_triad_py)
% 
% erro_est_py = [rmse(euler_True(1:1201,1)', euler_est_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_py(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
% disp(erro_est_py)
% 
% erro_f7_triad = [rmse(euler_True(1:1201,1)', euler_triad_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_triad_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_triad_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
% disp(erro_f7_triad)
% 
% erro_f7_est = [rmse(euler_True(1:1201,1)', euler_est_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_est_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_est_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
% disp(erro_f7_est)

cd ..\Figuras\RBIC\
%%%%%%%%% Medidas descalibradas - TRIAD - embarcado %%%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Erro (Verdadeiro - TRIAD)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
%set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Figura13.png","ContentType","vector")

%%%%%%% Medidas descalibradas - EKF embarcado %%%%%%%%%%
%hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,4)
plot(tempo,euler_True(1:1201,:))
hold on
title("(d) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_est_f7)
hold on
title("(e) EKF (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(f) Erro (Verdadeiro - EKF)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',11)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura12.png","ContentType","vector")

cd ..\..\Matlab

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
erro_euler_Triad_sr = euler_True(1:1201,:) - euler_Triad_sr(1:1201,:);
erro_euler_est_sr = euler_True(1:1201,:) - euler_est_sr(1:1201,:);

erro_euler_Triad_c = euler_True(1:1201,:) - euler_triad_c(1:1201,:);
erro_euler_est_c = euler_True(1:1201,:) - euler_est_c(1:1201,:);

erro_euler_Triad_py = euler_True(1:1201,:) - euler_triad_py(1:1201,:);
erro_euler_est_py = euler_True(1:1201,:) - euler_est_py(1:1201,:);

erro_euler_Triad_f7 = euler_True(1:1201,:) - euler_triad_f7;
erro_euler_est_f7 = euler_True(1:1201,:) - euler_est_f7;

for iii=74:length(euler_True(1:1201,1))
    for xxx=1:3
        if (abs(erro_euler_Triad_sr(iii,xxx))>0.04)
            erro_euler_Triad_sr(iii,xxx)=erro_euler_Triad_sr(iii-1,xxx);
        end
        if (abs(erro_euler_est_sr(iii,xxx))>0.04)
            erro_euler_est_sr(iii,xxx)=erro_euler_est_sr(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_c(iii,xxx))>0.04)
            erro_euler_Triad_c(iii,xxx)=erro_euler_Triad_c(iii-1,xxx);
        end
        if (abs(erro_euler_est_c(iii,xxx))>0.04)
            erro_euler_est_c(iii,xxx)=erro_euler_est_c(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_py(iii,xxx))>0.04)
            erro_euler_Triad_py(iii,xxx)=erro_euler_Triad_py(iii-1,xxx);
        end
        if (abs(erro_euler_est_py(iii,xxx))>0.04)
            erro_euler_est_py(iii,xxx)=erro_euler_est_py(iii-1,xxx);
        end

        if (abs(erro_euler_Triad_f7(iii,xxx))>0.04)
            erro_euler_Triad_f7(iii,xxx)=erro_euler_Triad_f7(iii-1,xxx);
        end
        if (abs(erro_euler_est_f7(iii,xxx))>0.04)
            erro_euler_est_f7(iii,xxx)=erro_euler_est_f7(iii-1,xxx);
        end
    end
end

erro_mat_RMSE = [sqrt(mean(erro_euler_Triad_sr(:,1).^2)), sqrt(mean(erro_euler_Triad_sr(:,2).^2)), sqrt(mean(erro_euler_Triad_sr(:,3).^2))];
erro_est_mat_RMSE = [sqrt(mean(erro_euler_est_sr(75:end,1).^2)), sqrt(mean(erro_euler_est_sr(75:end,2).^2)), sqrt(mean(erro_euler_est_sr(75:end,3).^2))];
disp(erro_mat_RMSE)
disp(erro_est_mat_RMSE)

erro_triad_c_RMSE = [sqrt(mean(erro_euler_Triad_c(:,1).^2)), sqrt(mean(erro_euler_Triad_c(:,2).^2)), sqrt(mean(erro_euler_Triad_c(:,3).^2))];
erro_est_c_RMSE = [sqrt(mean(erro_euler_est_c(75:end,1).^2)), sqrt(mean(erro_euler_est_c(75:end,2).^2)), sqrt(mean(erro_euler_est_c(75:end,3).^2))];
disp(erro_triad_c_RMSE)
disp(erro_est_c_RMSE)

erro_triad_py_RMSE = [sqrt(mean(erro_euler_Triad_py(:,1).^2)), sqrt(mean(erro_euler_Triad_py(:,2).^2)), sqrt(mean(erro_euler_Triad_py(:,3).^2))];
erro_est_py_RMSE = [sqrt(mean(erro_euler_est_py(75:end,1).^2)), sqrt(mean(erro_euler_est_py(75:end,2).^2)), sqrt(mean(erro_euler_est_py(75:end,3).^2))];
disp(erro_triad_py_RMSE)
disp(erro_est_py_RMSE)

erro_triad_f7_RMSE = [sqrt(mean(erro_euler_Triad_f7(:,1).^2)), sqrt(mean(erro_euler_Triad_f7(:,2).^2)), sqrt(mean(erro_euler_Triad_f7(:,3).^2))];
erro_est_f7_RMSE = [sqrt(mean(erro_euler_est_f7(75:end,1).^2)), sqrt(mean(erro_euler_est_f7(75:end,2).^2)), sqrt(mean(erro_euler_est_f7(75:end,3).^2))];
disp(erro_triad_f7_RMSE)
disp(erro_est_f7_RMSE)

% erro_mat = [rmse(euler_True(1:1201,1)', euler_Triad_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_Triad_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_Triad_sr(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Matlab (radianos)")
% disp(erro_mat)
% 
% erro_est_mat = [rmse(euler_True(1:1201,1)', euler_est_sr(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_sr(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_sr(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Matlab (radianos)")
% disp(erro_est_mat)
% 
% erro_triad_c = [rmse(euler_True(1:1201,1)', euler_triad_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_c(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do C (radianos)")
% disp(erro_triad_c)
% 
% erro_est_c = [rmse(euler_True(1:1201,1)', euler_est_c(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_c(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_c(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
% disp(erro_est_c)
% 
% erro_triad_py = [rmse(euler_True(1:1201,1)', euler_triad_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_triad_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_triad_py(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD do Python (radianos)")
% disp(erro_triad_py)
% 
% erro_est_py = [rmse(euler_True(1:1201,1)', euler_est_py(1:1201,1)'), rmse(euler_True(1:1201, 2)', euler_est_py(1:1201,2)'), rmse(euler_True(1:1201,3)', euler_est_py(1:1201,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do Python (radianos)")
% disp(erro_est_py)
% 
% erro_f7_triad = [rmse(euler_True(1:1201,1)', euler_triad_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_triad_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_triad_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - TRIAD embarcado (radianos)")
% disp(erro_f7_triad)
% 
% erro_f7_est = [rmse(euler_True(1:1201,1)', euler_est_f7(:,1)'), rmse(euler_True(1:1201, 2)', euler_est_f7(:,2)'), rmse(euler_True(1:1201,3)', euler_est_f7(:,3)')];
% disp("Erro RMS de cada ângulo de Euler - estimador do C (radianos)")
% disp(erro_f7_est)

cd ..\Figuras\RBIC\
%%%%%%%%% Medidas descalibradas - TRIAD - embarcado %%%%%%%%%%%%%%
hfig = figure;
set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,1)
plot(tempo,euler_True(1:1201,:))
hold on
title("(a) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,2)
plot(tempo,euler_triad_f7)
hold on
title("(b) TRIAD (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,3)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_triad_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(c) Erro (Verdadeiro - TRIAD)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',11)
%set(gcf, 'WindowState', 'maximized');
%exportgraphics(gcf,"Figura15.png","ContentType","vector")

%%%%%%% Medidas descalibradas - EKF embarcado %%%%%%%%%%
%hfig = figure;
%set(hfig,'Position',[0 0 54.43*20 22.4*20])
subplot(2,3,4)
plot(tempo,euler_True(1:1201,:))
hold on
title("(d) Atitude verdadeira")
grid on
xlim([0,60])
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");

subplot(2,3,5)
plot(tempo,euler_est_f7)
hold on
title("(e) EKF (F7)")
grid on
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
xlim([0,60])

subplot(2,3,6)
xlim([0,60])
plot(tempo,(euler_True(1:1201,:)-euler_est_f7))
hold on
grid on
xlim([0,60])
ylim([-0.03,0.03])
title("(f) Erro (Verdadeiro - EKF)")
lgd = legend('Roll','Pitch','Yaw', 'Orientation', "Horizontal");
lgd.FontSize = 6;
lgd.ItemTokenSize = [10 6];
ylabel("Ângulo (rad)");
xlabel("Tempo (s)");
set(findall(gcf,'-property','FontSize'),'FontSize',11)
%set(gcf, 'WindowState', 'maximized');
exportgraphics(gcf,"Figura13.png","ContentType","vector")

cd ..\..\Matlab

disp("======================")
disp("Resumo NLLS (C):")
fprintf("Bx mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_c(4,:)))
fprintf("By mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_c(5,:)))
fprintf("Bz mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_c(6,:)))
fprintf("Sx mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_c(1,:)))
fprintf("Sy mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_c(2,:)))
fprintf("Sz mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_c(3,:)))
fprintf("Rho mean error 10^(-5) %f\n", 1e5*mean(vet_error_NLLS_c(7,:)))
fprintf("Phi mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_c(8,:)))
fprintf("Lamda mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_c(9,:)))

disp("======================")

disp("Resumo NLLS (embarcado):")
fprintf("Bx mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_f7(4,:)))
fprintf("By mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_f7(5,:)))
fprintf("Bz mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_f7(6,:)))
fprintf("Sx mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_f7(1,:)))
fprintf("Sy mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_f7(2,:)))
fprintf("Sz mean error 10^(-4) %f\n", 1e4*mean(vet_error_NLLS_f7(3,:)))
fprintf("Rho mean error 10^(-5) %f\n", 1e5*mean(vet_error_NLLS_f7(7,:)))
fprintf("Phi mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_f7(8,:)))
fprintf("Lamda mean error 10^(-6) %f\n", 1e6*mean(vet_error_NLLS_f7(9,:)))
