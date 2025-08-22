close all
clear all
clc

cd Dados_reais\
data = readmatrix('magnetometro_data_20250822_160035.csv');
cd ..\
mx = data(:,2);
my = data(:,3);
mz = data(:,4);

Dados_Corrompido = [mx,my,mz]';
[Time,p] = test1(Dados_Corrompido, 0.224);
disp(Time)
disp(p)

% Dados_Corrompido = Dados_Corrompido/0.23;
% dado = [1,1,1,0,0,0,0,0,0]';
% H = ones(1, length(Dados_Corrompido(1,:)))';

%[tempo, passo,p0] = test2(Dados_Corrompido, dado, H);

hFig = figure;
set(hFig, 'Position', [100 100 700*3/2 300])
subplot(1,2,1)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.23;
 a = e;
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
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

Dados_rest(1,:) =  (Dados_Corrompido(1,:) - p(4))/p(1);
Dados_rest(2,:) = ((Dados_Corrompido(2,:) - p(5))/p(2) - Dados_rest(1,:)*sin(p(7)))/cos(p(7));
Dados_rest(3,:) = ((Dados_Corrompido(3,:) - p(6))/p(3) - Dados_rest(1,:)*sin(p(8))*cos(p(9)) - Dados_rest(2,:)*sin(p(9)))/(cos(p(8))*cos(p(9)));

subplot(1,2,2)
set(gcf,'Units','inches');
screenposition = get(gcf,'Position');
set(gcf,...
'PaperPosition',[0 0 screenposition(3:4)],...
'PaperSize',[screenposition(3:4)]);
 e = 0.23;
 a = 0.23;
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
mx = Dados_rest(1,:);
my = Dados_rest(2,:);
mz = Dados_rest(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

cd Dados_reais\
data = readmatrix('acelerometro_data_20250822_160035.csv');
cd ..\
clear mx
clear my
clear mz
clear Dados_rest
% mx = data(:,2);
% my = data(:,3);
% mz = data(:,4);
mx = [];
my = [];
mz = [];

for i=1:1:length(data(:,2))
    vet = [data(i,2), data(i,3), data(i,4)];
    if norm(vet) < 1.1
        mx(i) = data(i,2);
        my(i) = data(i,3);
        mz(i) = data(i,4);
    end
end

Dados_Corrompido = [mx;my;mz];
[Time,p1] = test1(Dados_Corrompido, 1);
disp(Time)
disp(p1)

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
mx = Dados_Corrompido(1,:);
my = Dados_Corrompido(2,:);
mz = Dados_Corrompido(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

Dados_rest(1,:) =  (Dados_Corrompido(1,:) - p1(4))/p1(1);
Dados_rest(2,:) = ((Dados_Corrompido(2,:) - p1(5))/p1(2) - Dados_rest(1,:)*sin(p1(7)))/cos(p1(7));
Dados_rest(3,:) = ((Dados_Corrompido(3,:) - p1(6))/p1(3) - Dados_rest(1,:)*sin(p1(8))*cos(p1(9)) - Dados_rest(2,:)*sin(p1(9)))/(cos(p1(8))*cos(p1(9)));

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
mx = Dados_rest(1,:);
my = Dados_rest(2,:);
mz = Dados_rest(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(b)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');