%Comparação dos resultados de calibração com parte dos dados, parte dos
%dados2 e com todos os dados
clear all
close all
clc

cd coletas_mag_real_22_09_25\
data = readmatrix('magnetometro_half_filtred1_22_09_25.csv');

mx = [];
my = [];
mz = [];

for i=2:1:length(data (:, 1))
    vet = data(i,:);
    if norm(vet) ~= 0
        mx(length(mx)+1) = vet(1);
        my(length(my)+1) = vet(2);
        mz(length(mz)+1) = vet(3);
    end
end

Dados_Corrompido1 = [mx;my;mz];

data = readmatrix('magnetometro_half_filtred2_22_09_25.csv');


mx = [];
my = [];
mz = [];

for i=2:1:length(data (:, 1))
    vet = data(i,:);
    if norm(vet) ~= 0
        mx(length(mx)+1) = vet(1);
        my(length(my)+1) = vet(2);
        mz(length(mz)+1) = vet(3);
    end
end

Dados_Corrompido2 = [mx;my;mz];

data = readmatrix('magnetometro_full_filtred2_22_09_25.csv');


mx = [];
my = [];
mz = [];

for i=2:1:length(data (:, 1))
    vet = data(i,:);
    if norm(vet) ~= 0
        mx(length(mx)+1) = vet(1);
        my(length(my)+1) = vet(2);
        mz(length(mz)+1) = vet(3);
    end
end

Dados_Corrompido_full_filtred = [mx;my;mz];

data = readmatrix('magnetometro_data_20250922_105055.csv');

mx = data(:,2);
my = data(:,3);
mz = data(:,4);

Dados_Corrompido_full = [mx,my,mz]';

data = readmatrix('magnetometro_data_20250922_104421.csv');

mx = data(:,2);
my = data(:,3);
mz = data(:,4);

Dados_Corrompido_ref = [mx,my,mz]';

cd ..\

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(2,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_Corrompido_full_filtred(1,:);
my = Dados_Corrompido_full_filtred(2,:);
mz = Dados_Corrompido_full_filtred(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'FontSize',17)

subplot(2,2,2)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_Corrompido_full(1,:);
my = Dados_Corrompido_full(2,:);
mz = Dados_Corrompido_full(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'FontSize',17)

subplot(2,2,3)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_Corrompido1(1,:);
my = Dados_Corrompido1(2,:);
mz = Dados_Corrompido1(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(c)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'FontSize',17)

subplot(2,2,4)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_Corrompido2(1,:);
my = Dados_Corrompido2(2,:);
mz = Dados_Corrompido2(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(d)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'FontSize',17)

[Time_full,p_full] = test1(Dados_Corrompido_full, 0.224);
[Time_full_filtred,p_full_filtred] = test1(Dados_Corrompido_full_filtred, 0.224);
[Time_half1,p_half1] = test1(Dados_Corrompido1, 0.224);
[Time_half2,p_half2] = test1(Dados_Corrompido2, 0.224);

p0 = [1; 1; 1; (max(Dados_Corrompido_full(1,:)) + min(Dados_Corrompido_full(1,:)))/2; (max(Dados_Corrompido_full(2,:)) + min(Dados_Corrompido_full(2,:)))/2; (max(Dados_Corrompido_full(3,:)) + min(Dados_Corrompido_full(3,:)))/2; 0; 0; 0];
H = 0.224*ones(1, length(Dados_Corrompido_full(1,:)))';
[tempo, passo,p1_full] = test2(Dados_Corrompido_full, p0, H);

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_Corrompido_ref(1,:);
my = Dados_Corrompido_ref(2,:);
mz = Dados_Corrompido_ref(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'FontSize',17)

Dados_rest_full(1,:) =  (Dados_Corrompido_ref(1,:) - p_full(4))/p_full(1);
Dados_rest_full(2,:) = ((Dados_Corrompido_ref(2,:) - p_full(5))/p_full(2) - Dados_rest_full(1,:)*sin(p_full(7)))/cos(p_full(7));
Dados_rest_full(3,:) = ((Dados_Corrompido_ref(3,:) - p_full(6))/p_full(3) - Dados_rest_full(1,:)*sin(p_full(8))*cos(p_full(9)) - Dados_rest_full(2,:)*sin(p_full(9)))/(cos(p_full(8))*cos(p_full(9)));

Dados_rest_full_filtred(1,:) =  (Dados_Corrompido_ref(1,:) - p_full_filtred(4))/p_full_filtred(1);
Dados_rest_full_filtred(2,:) = ((Dados_Corrompido_ref(2,:) - p_full_filtred(5))/p_full_filtred(2) - Dados_rest_full_filtred(1,:)*sin(p_full_filtred(7)))/cos(p_full_filtred(7));
Dados_rest_full_filtred(3,:) = ((Dados_Corrompido_ref(3,:) - p_full_filtred(6))/p_full_filtred(3) - Dados_rest_full_filtred(1,:)*sin(p_full_filtred(8))*cos(p_full_filtred(9)) - Dados_rest_full_filtred(2,:)*sin(p_full_filtred(9)))/(cos(p_full_filtred(8))*cos(p_full_filtred(9)));

Dados_rest_half1(1,:) =  (Dados_Corrompido_ref(1,:) - p_half1(4))/p_half1(1);
Dados_rest_half1(2,:) = ((Dados_Corrompido_ref(2,:) - p_half1(5))/p_half1(2) - Dados_rest_half1(1,:)*sin(p_half1(7)))/cos(p_half1(7));
Dados_rest_half1(3,:) = ((Dados_Corrompido_ref(3,:) - p_half1(6))/p_half1(3) - Dados_rest_half1(1,:)*sin(p_half1(8))*cos(p_half1(9)) - Dados_rest_half1(2,:)*sin(p_half1(9)))/(cos(p_half1(8))*cos(p_half1(9)));

Dados_rest_half2(1,:) =  (Dados_Corrompido_ref(1,:) - p_half2(4))/p_half2(1);
Dados_rest_half2(2,:) = ((Dados_Corrompido_ref(2,:) - p_half2(5))/p_half2(2) - Dados_rest_half2(1,:)*sin(p_half2(7)))/cos(p_half2(7));
Dados_rest_half2(3,:) = ((Dados_Corrompido_ref(3,:) - p_half2(6))/p_half2(3) - Dados_rest_half2(1,:)*sin(p_half2(8))*cos(p_half2(9)) - Dados_rest_half2(2,:)*sin(p_half2(9)))/(cos(p_half2(8))*cos(p_half2(9)));

%Falta implementar a comparação de cada reconstrução com o raio de 0.224
hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(2,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_rest_full_filtred(1,:);
my = Dados_rest_full_filtred(2,:);
mz = Dados_rest_full_filtred(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

subplot(2,2,2)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_rest_full(1,:);
my = Dados_rest_full(2,:);
mz = Dados_rest_full(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

subplot(2,2,3)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_rest_half1(1,:);
my = Dados_rest_half1(2,:);
mz = Dados_rest_half1(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(c)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

subplot(2,2,4)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.224;
 a = 1.1*e;
[x,y,z] = sphere;
x = e*x;
y = e*y;
z = e*z;
s2 = surf(x,y,z);
set(s2,'FaceColor','none')
set(s2,'EdgeColor',[0.7 0.7 0.7])
hold on
axis([-a a -a a -a a])
axis equal
set(gca,'PlotBoxAspectRatioMode','manual')
set(gca,'FontSize',12)
hold on
mx = Dados_rest_half2(1,:);
my = Dados_rest_half2(2,:);
mz = Dados_rest_half2(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(d)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
