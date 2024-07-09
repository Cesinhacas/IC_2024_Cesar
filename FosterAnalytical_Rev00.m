% Fun��o de estima��o dos par�metros (nove) dos sensores 
% a partir do m�todo de vari�ncia m�nima FosterMarcomBatista
%
% Par�metros de entrada da fun��o:
% 1 - ParT -> Struct com os seguintes par�metros:
%    ParT.x0
%    ParT.y0
%    ParT.z0
%    ParT.a
%    ParT.b
%    ParT.c
%    ParT.rho
%    ParT.phi
%    ParT.lambda
% Est� � utilizado no caso de simula��o, sendo que ParT deve conter os 
% valores espererados da calibra��o.
% 2 - ParP -> Struct na mesma forma de ParT, n�o utilizado neste algoritmo,
% este est� presente somente para manter a chamada da fun��o como nos 
% algoritmos de vari�ncia m�nima..
% 3 - DataObs -> Matriz contendo o vetor de observa��es dos sensores,
% na forma coluna (3xM), onde M � o total de observa��es.
% 4 - sf -> Fator de Escala esperado para as medidas. Por exemplo, caso os
% dados estejam em bits, � o n�mero de bits equivalente esperado para o o
% campo magn�tico local ou campo gravitacional, caso j� esteja convertido
% em medida, � o valor esperado da medida (campo magn�tico ou acelera��o)
% 5 - simul -> Caso opt = 'simul', o algoritmo identifica se tratar de uma
% simula��o e ir� calcular os erros referente ao vetor de ParT. Caso
% contr�rio ParT � ignorado.
% 6 - opt -> Caso opt = 'full', ao final da calibra��o o algoritmo
% ainda plota os dados n�o calibrados e calibrados na esfera unit�ria
%
% Par�metros de sa�da da fun��o:
% 1 - DataCalSan -> Vetor com os dados corrigidos pelos par�metros
% encontrados.
% 2 - ParC -> Par�metros de calibra��o encontrados, mesmo formato de ParP.
% 3 - Time -> Tempo necess�rio para a execu��o do algoritmo. O tempo �
% aquele necess�rio para a estima��o e corre��o dos dados, sem considera os
% plotes (caso habilitado) e etapas auxiliares;
% 4 - Est -> Structure com o res�duo em rela��o a medida esperada (sf) para
% cada uma das itera��es e tamb�m o Log dos valores estimados para ParC ao
% longos das itera��es;
% 5 - Erros -> Vetor com os erros encontrados ao longo das itera��es 
% (Esta op��o s� vale para o caso de simula��o);

function [ParC] = FosterAnalytical_Rev00(ParT, ParP, DataObs, sf, simul, opt)

% Vetoriza��o dos dados de entrada:
ux = DataObs(1,:);
uy = DataObs(2,:);
uz = DataObs(3,:);

% Fator de Escala da medida
%N = sf;

% In�cio do Timer da estima��o:
tic

%Adi��o do Offset no par�metro uz para evitar o ponto ao redor de zero:
%uy_Offset = 10*(max(uy)-min(uy));
%uy_off = uz + uy_Offset;
%uy = uy_off;

% Matriz de medidas:
for i = 1:length(ux)
    H(i,:) = [(ux(i)^2); ux(i)*uy(i); ux(i)*uz(i);...
               uy(i)*uz(i); uz(i)^2; ux(i); uy(i); uz(i); 1];  
    Y(i,1) = [-uy(i)^2];
end

%C�lculo de x atrav�s da pseudo inversa:
x = inv(H'*H)*H'*Y;

%Solucao Manual

x1 = x(1);
x2 = x(2);
x3 = x(3);
x4 = x(4);
x5 = x(5);
x6 = x(6);
x7 = x(7);
x8 = x(8);
x9 = x(9);

e7 = 2*(x5*x2^2-x2*x3*x4+x3^2+x1*x4^2-4*x1*x5);

bx = - (x4^2*x6 +2*x3*x8 -4*x5*x6 -x2*x4*x8 +2*x2*x5*x7 -x3*x4*x7)/e7;

by = - (x3^2*x7 +2*x1*x4*x8 -4*x1*x5*x7 -x2*x3*x8 +2*x2*x5*x6 -x3*x4*x6)/e7;

bz = - (x2^2*x8 -4*x1*x8 +2*x3*x6 +2*x1*x4*x7 -x2*x3*x7 -x2*x4*x6)/e7;


e8 = -x2^2*x8^2 + 4*x5*x9*x2^2 - 4*x9*x2*x3*x4 + 2*x2*x3*x7*x8 + 2*x2*x4*x6*x8 - 4*x5*x2*x6*x7 - x3^2*x7^2 + 4*x9*x3^2 + 2*x3*x4*x6*x7...
    - 4*x3*x6*x8 - x4^2*x6^2 + 4*x1*x9*x4^2 + 4*x5*x6^2 + 4*x1*x5*x7^2+4*x1*x8^2-16*x1*x5*x9-4*x1*x4*x7*x8;

sx = -  (x5^3)*sqrt(e8*(-x4^2+4*x5)) / (2*abs(x5^3)*(x5*x2^2-x2*x3*x4+x3^2+x1*x4^2-4*x1*x5) );

sy = - (x5^3)*sqrt(e8*(-x3^2+4*x1*x5)) / (2*abs(x5^3)*(x5*x2^2-x2*x3*x4+x3^2+x1*x4^2-4*x1*x5) );

sz = - (x5^3)*sqrt(e8*(-x2^2+4*x1)) / (2*abs(x5^3)*(x5*x2^2-x2*x3*x4+x3^2+x1*x4^2-4*x1*x5) );



n1 = -x2^2*x8^2 + 4*x2^2*x5*x9 - 4*x2*x3*x4*x9 + 2*x2*x3*x7*x8 + 2*x2*x4*x6*x8 - 4*x2*x5*x6*x7 - x3^2*x7^2 + 2*x3*x4*x6*x7 +...
    4*x3^2*x9 - 4*x3*x6*x8 - x4^2*x6^2 + 4*x2*x4^2*x9 - 4*x1*x4*x7*x8 +4*x5*x6^2 +4*x1*x5*x7^2 + 4*x1*x8^2 - 16*x1*x5*x9;
n2 = x2^2*x5 - x2*x3*x4 + x3^2+x1*x4^2 - 4*x1*x5;
n3 = 2*x2^2*x4^2*x5 - 4*x2^2*x5^2 - x2*x3*x4^3 + x3^2*x4^2 + x1*x4^4 - 8*x1*x4^2*x5 + 16*x1*x5^2;
n4 = 4*x5-x4^2;
n5 = 4*x1*x5-x3^2;
n6 = 4*x1-x2^2;

rho = -atan( (2*x2*x5-x3*x4) / (2*x5^2*sqrt(- (n2)/(x5^3) ) ) );

phi = -atan( (abs(x5)*sqrt(n1*n5)*(2*x3-x2*x4)*sqrt((x5*n4*n6)/(n3)) / ( x5^2*sqrt(-n2/x5)*sqrt(n1*n6)*sqrt(-n2*n4/n3)*sqrt(-n4*n5/(x5*n2) ) ) ) );

lambda = -atan( (x4/x5)* sqrt(- (x5^2*(n2))/(n3) )  );

% Atualiza��o dos par�metros obtidos em ParC:
ParC.x0 = bx;
ParC.y0 = by;
ParC.z0 = bz;
ParC.a = sx/sf;
ParC.b = sy/sf;
ParC.c = sz/sf;
ParC.rho = rho;
ParC.phi = phi;
ParC.lambda = lambda;


% A patir dos dados com erros e dos par�metros de calibra��o
% montamos uma matriz com os dados corrigidos:
% DataCalFos(1,:) =  (DataObs(1,:) - ParC.x0)/ParC.a;
% DataCalFos(2,:) = ((DataObs(2,:) - ParC.y0)/ParC.b - DataCalFos(1,:)*sin(ParC.rho))/cos(ParC.rho);
% % DataCalFos(3,:) = ((DataObs(3,:) - ParC.z0)/ParC.c - DataCalFos(1,:)*sin(ParC.phi)*cos(ParC.lambda) - DataCalFos(2,:)*sin(ParC.lambda)*cos(ParC.phi))/(cos(ParC.phi)*cos(ParC.lambda));
% DataCalFos(3,:) = ((DataObs(3,:) - ParC.z0)/ParC.c - DataCalFos(1,:)*sin(ParC.phi)*cos(ParC.lambda) - DataCalFos(2,:)*sin(ParC.lambda))/(cos(ParC.phi)*cos(ParC.lambda));

% Final do timer:
Time = toc;

%Calcula o Desvio Padr�o de DataCalSan em rela��o ao valor espesrado:
% for i=1:length(DataCalFos(1,:))
%     aux(i) = norm(DataCalFos(:,i));
% end
% aux = (sf - aux).^2;
% DataCalFos_Std = sqrt( (1/(length(DataCalFos)))*sum(aux));

%Par�metros de retorno do Res�duo e ParC ao longos das itera��es
Est.Vetor_Res = 'null';
Est.ParC = 'null';
Est.Res_std = 'null';
%Est.DataCalFos_Std = DataCalFos_Std;

% Caso a op��o seja 'full', o algoritmo realiza o plote
% dos dados sem calibra��o e posterior com calibra��o na 
% esfera unit�ria (novamente os dados est�o normalizados
if (strcmp(opt,'plot') == 1)
    figure;
    subplot(2,1,1)
    e = 1.5;
    [x,y,z] = sphere;
    s2 = surf(x,y,z)
    set(s2,'FaceColor','none')
    set(s2,'EdgeColor',[0.7 0.7 0.7])
    hold off
    axis([-e e -e e -e e])
    set(gca,'PlotBoxAspectRatioMode','manual')
    set(gca,'FontSize',12)
    hold on
    %mx = DataCalFos(1,:)/sf;
    %my = DataCalFos(2,:)/sf;
    %mz = DataCalFos(3,:)/sf;
    %plot3(mx,my,mz,'r.')
    %title('Data Calibrada');
    
    subplot(2,1,2)
    e = 1.5;
    [x,y,z] = sphere;
    s2 = surf(x,y,z)
    set(s2,'FaceColor','none')
    set(s2,'EdgeColor',[0.7 0.7 0.7])
    hold off
    axis([-e e -e e -e e])
    set(gca,'PlotBoxAspectRatioMode','manual')
    set(gca,'FontSize',12)
    hold on    
    mx = DataObs(1,:)/sf;
    my = DataObs(2,:)/sf;
    mz = DataObs(3,:)/sf;
    plot3(mx,my,mz,'r.')
    title('Data Sem Calibra��o');
end

if (simul == 1)
% Erro dos par�metros comparados com verdadeiros

    Errop(1,1) = (ParC.x0  -  ParT.x0)/ParT.x0;
    Errop(2,1) = (ParC.y0  -  ParT.y0)/ParT.y0;
    Errop(3,1) = (ParC.z0  -  ParT.z0)/ParT.z0;
    Errop(4,1) = (ParC.a   -  ParT.a)/ParT.a;
    Errop(5,1) = (ParC.b   -  ParT.b)/ParT.b;
    Errop(6,1) = (ParC.c   -  ParT.c)/ParT.c;
    Errop(7,1) = (ParC.lambda - ParT.lambda)/ParT.lambda;
    Errop(8,1) = (ParC.rho - ParT.rho)/ParT.rho;
    Errop(9,1) = (ParC.phi - ParT.phi)/ParT.phi;

    Erros.e_log = Errop;
    Erros.eTot =  norm(Errop(1:9,1));

else
    %Erros = ('null');
end