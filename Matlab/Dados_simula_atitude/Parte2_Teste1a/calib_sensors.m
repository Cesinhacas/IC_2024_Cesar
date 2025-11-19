close all
clear all
clc

accel_data = readmatrix('accel_ruido.csv')';
mag_data = readmatrix('mag_ruido.csv')';

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(1,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 1;
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
mx = accel_data(1,:);
my = accel_data(2,:);
mz = accel_data(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'fontsize', 20)
subplot(1,2,2)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 1;
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
mx = mag_data(1,:);
my = mag_data(2,:);
mz = mag_data(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');
set(gca,'fontsize', 20)

p0 = [1,1,1,0,0,0,0,0,0]';
H = ones(1, length(accel_data(1,:)))';

[Time2, passo2, p2, fisher2] = test2(mag_data, p0, H);

[Time, passo, p, fisher] = test2(accel_data, p0, H);

disp("Parâmetros Mag")
disp(p2)

disp("Parâmetros Accel")
disp(p)