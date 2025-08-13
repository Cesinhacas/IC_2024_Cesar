close all
clear all
clc

data = readmatrix('magnetometro_data_20250813_155734.csv');
mx = data(:,2);
my = data(:,3);
mz = data(:,4);

Dados_Corrompido = [mx,my,mz]';
[Time,p0] = test1(Dados_Corrompido, 0.23);
disp(Time)
disp(p0)

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(2,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = r;
 a = 1*e;
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
mx = Dados_Teoricos(1,:);
my = Dados_Teoricos(2,:);
mz = Dados_Teoricos(3,:);
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
 e = r;
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
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

data = readmatrix('acelerometro_data_20250813_155734.csv');

for i=1:1:length(data)
    vet = [data(i, 2), data(i,3), data(i,4)];
    if norm(vet) > 1.2
        mx = data(:,2);
        my = data(:,3);
        mz = data(:,4);
    end

end

Dados_Corrompido = [mx,my,mz]';
[Time,p1] = test1(Dados_Corrompido, 1);
disp(Time)
disp(p1)

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(2,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = r;
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
mx = Dados_Teoricos(1,:);
my = Dados_Teoricos(2,:);
mz = Dados_Teoricos(3,:);
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
 e = r;
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
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');