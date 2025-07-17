%% Código 01a - Gera vetor de 572 (passo = 10) 1112 (passo = 5) pontos similar ao do teste da bobina:

clear all
close all
clc

save_data = 0;

rotate = 0;
% rotate = 1;
% rotate = 2;


phi(1) = 0;
theta(1) = 0;
it(1) = 1;
k = 2;
passo = 5;

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

if rotate==0
    Dados = [x; y; z];
end
if rotate ==1
    Dados = [z; x; y];
end
 if rotate==2
     Dados = [y; z; x];
 end
    
    % figure
% plot(it, Dados,'o')
% 
% norm(Dados(:,60));
% figure 
% plot3(x,y,z,'.')
% grid on
% 
% hFig = figure
% set(hFig, 'Position', [100 100 700 300])
% subplot(1,2,1)
% set(gcf,'Units','inches');
% screenposition = get(gcf,'Position');
% set(gcf,...
% 'PaperPosition',[0 0 screenposition(3:4)],...
% 'PaperSize',[screenposition(3:4)]);
%  e = 0.5;
%  a = 1.1*e;
% [x,y,z] = sphere;
% x = e*x;
% y = e*y;
% z = e*z;
% s2 = surf(x,y,z);
% set(s2,'FaceColor','none')
% set(s2,'EdgeColor',[0.7 0.7 0.7])
% hold on
% axis([-a a -a a -a a])
% axis equal
% set(gca,'PlotBoxAspectRatioMode','manual')
% set(gca,'FontSize',12)
% hold on
% mx = Dados(1,:);
% my = Dados(2,:);
% mz = Dados(3,:);
% plot3(mx,my,mz,'r.','linewidth',1.5)
% title('(a)'); 
% xlabel('x axis (G)');
% ylabel('y axis (G)');
% zlabel('z axis (G)');
% 
% Dados_Paper_Ref_Norm = [Dados];


if save_data==1
    Dados_Teoricos = Dados;
    clearvars -except Dados_Teoricos
    cd ../
    cd 'Dados'
    save Dados_Teoricos.mat
    cd ../
    cd 'Matlab'
end


%% Trecho de código 01b: Mantido similar ao resultado do Paper

clear all
clc

r = 1;
save_data = 0;

cd ../
cd 'Dados'
load Dados_Teoricos.mat
writematrix(Dados_Teoricos', 'transpose_dados.csv');
cd ../
cd 'Matlab'

sf = 1;

Data_Simul = sf*Dados_Teoricos;

offset = [-0.1723; -0.0741; 0.1342];
% offset = [-0.4723; -0.3741; 0.6342];
Escala = [0.9213 0.7634 1.1834];
% Ang = [-13.4532*pi/180; 14.567*pi/180; -12.9674*pi/180];
% Ang = [-0.02*pi/180; 0.03*pi/180; -0.05*pi/180];
Ang = [-0.173*pi/180; 0.091*pi/180; -0.201*pi/180];

rho = Ang(1);
phi = Ang(2);
lambda = Ang(3);

scale = diag(Escala);

T = [1 0 0; sin(rho) cos(rho) 0; sin(phi)*cos(lambda) sin(lambda) cos(phi)*cos(lambda)];
mean = [0 0 0];
sigma = [0.006^2 0 0;0 0.006^2 0;0 0 0.006^2];
for i=1:length(Data_Simul(1,:))
    Ruido(:,i) = mvnrnd(mean,sigma,1)';
    Dados_Corrompido(:,i) = scale*T*Data_Simul(:,i) + offset + Ruido(:,i); 
end

cd ..\
cd Dados\
save Dados_Corrompido
writematrix(Dados_Corrompido, 'Dados_Corrompido.csv');
Dados_Corrompido = readmatrix('Dados_Corrompido.csv');
cd ..\
cd Matlab\

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

% Reconstrução da esfera
[Time,p] = test1(Dados_Corrompido, r); % ETS

Dados_rest(1,:) =  (Dados_Corrompido(1,:) - p(4))/p(1);
Dados_rest(2,:) = ((Dados_Corrompido(2,:) - p(5))/p(2) - Dados_rest(1,:)*sin(p(7)))/cos(p(7));
Dados_rest(3,:) = ((Dados_Corrompido(3,:) - p(6))/p(3) - Dados_rest(1,:)*sin(p(8))*cos(p(9)) - Dados_rest(2,:)*sin(p(9)))/(cos(p(8))*cos(p(9)));

subplot(2,2,3)
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
mx = Dados_rest(1,:);
my = Dados_rest(2,:);
mz = Dados_rest(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(c)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

H = r*ones(length(Dados_Corrompido(1,:)),1);
p0 = [1; 1; 1; 0; 0; 0; 0; 0; 0;];
[Tempo,passo,p1] = test2(Dados_Corrompido, p0, H); %NLLS

Dados_rest1(1,:) =  (Dados_Corrompido(1,:) - p1(4))/p1(1);
Dados_rest1(2,:) = ((Dados_Corrompido(2,:) - p1(5))/p1(2) - Dados_rest1(1,:)*sin(p1(7)))/cos(p1(7));
Dados_rest1(3,:) = ((Dados_Corrompido(3,:) - p1(6))/p1(3) - Dados_rest1(1,:)*sin(p1(8))*cos(p1(9)) - Dados_rest1(2,:)*sin(p1(9)))/(cos(p1(8))*cos(p1(9)));


subplot(2,2,4)
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
mx = Dados_rest1(1,:);
my = Dados_rest1(2,:);
mz = Dados_rest1(3,:);
plot3(mx,my,mz,'r.','linewidth',1.5)
title('(d)'); 
xlabel('x axis (G)');
ylabel('y axis (G)');
zlabel('z axis (G)');

% 
% noise = .006^2*ones(3,1112);
% [Tiempo,n,D,b] = TWOSTEP(Dados_Corrompido, H ,noise);
% 
% for i=1:length(Dados_Corrompido(1,:))
%     Dados_rest2(:,i) = (eye(3)+D)*Dados_Corrompido(:,i) - b;
% end

% subplot(2,3,5)
% set(gcf,'Units','inches');
% screenposition = get(gcf,'Position');
% set(gcf,...
% 'PaperPosition',[0 0 screenposition(3:4)],...
% 'PaperSize',[screenposition(3:4)]);
%  e = r;
%  a = 1.1*e;
% [x,y,z] = sphere;
% x = e*x;
% y = e*y;
% z = e*z;
% s2 = surf(x,y,z);
% set(s2,'FaceColor','none')
% set(s2,'EdgeColor',[0.7 0.7 0.7])
% hold on
% axis([-a a -a a -a a])
% axis equal
% set(gca,'PlotBoxAspectRatioMode','manual')
% set(gca,'FontSize',12)
% hold on
% mx = Dados_rest2(1,:);
% my = Dados_rest2(2,:);
% mz = Dados_rest2(3,:);
% plot3(mx,my,mz,'r.','linewidth',1.5)
% title('(e)'); 
% xlabel('x axis (G)');
% ylabel('y axis (G)');
% zlabel('z axis (G)');

% param_TW = [b D];
% 
% cd ..\
% cd Dados
% writematrix(Dados_rest, 'Dados_ETS_m.csv')
% writematrix(Dados_rest1, 'Dados_NLLS_m.csv')
% writematrix(Dados_rest2, 'Dados_TW_m.csv')
% writematrix(p, 'Calib_param_ETS_m.csv')
% writematrix(p1, 'Calib_param_NLLS_m.csv')
% writematrix(param_TW, 'Calib_param_TW_m.csv')
% cd ..\
% cd Matlab