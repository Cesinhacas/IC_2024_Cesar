%% Código 01b - Gera vetor de 572 (passo = 10) 1112 (passo = 5) pontos similar ao do teste da bobina:

clear all
close all
clc

save_data = 0;


phi(1) = 0;
theta(1) = 0;
it(1) = 1;
k = 2;
passo = 17;

for i=0:passo:180
    for j=6:12:354
% for i=6:12:354
%     for j=0:10:180
        phi(k) = j;
        theta(k) = i; 
        it(k) = k;
        k = k + 1;
    end
end
phi(k) = 180;
theta(k) = 0;
it(k) = k;

phi_Rad = pi/180*phi; 
theta_Rad = pi/180*theta;

r = 1;

x = r.*cos(theta_Rad).*sin(phi_Rad);
y = r.*sin(theta_Rad).*sin(phi_Rad);
z = r.*cos(phi_Rad);

Dados_x = [x; y; z];
Dados_z = [z; x; y];
Dados_y = [y; z; x];

Dados_distribuidos = [Dados_x Dados_y Dados_z];

Dados_distribuidos = unique(Dados_distribuidos, 'rows');

cd Dados_dist3\
writematrix(Dados_distribuidos, 'dados_distribuidos_3.csv');



Dados_distribuidos = readmatrix('conjunto_dados_corrompidos_1.csv');
cd ..\

hFig = figure;
set(hFig, 'Position', [100 100 700 300])
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
mx = Dados_distribuidos(1,:);
my = Dados_distribuidos(2,:);
mz = Dados_distribuidos(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(a)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');