% Non-linear Least Square Function for the parameter calibration
%
% The algorithm uses the sensor model of Foster and has a linear solution
% to find the starting offset parameters.
%
% Function input arguments:
% 1 - ParT -> True parameters (for simulation case)
%    ParT.x0
%    ParT.y0
%    ParT.z0
%    ParT.a
%    ParT.b
%    ParT.c
%    ParT.rho
%    ParT.phi
%    ParT.lambda
% 2 - ParP -> Structure with the starting parameters. Note this version of
% the algorithm overrides the x0, y0 and z0 parameters.
% 3 - DataObs -> 3xM matrix with the sensor measurements, where M is the
% total number of observations.
% 4 - sf -> Refers to the expected magnitude of each measurement. If sf is
% a scalar number, the algorithm considers that all measurements have the
% same expected magnetic field magnitude (or acceleration, in cases the
% algorithm is used for three-axial accelerometer calibration)
% 5 - simul -> Case this variable is a strig of chars: opt = 'simul', the
% algorithm identifies its an simulation, and uses ParT to calculate the
% error between the estimated parameters and the true values. Otherwire
% ParT is ignored.
% 6 - opt -> If (opt = 'plot'), the algoritm plots the raw data (input) and
% the calibrated one over the attitude sphere.
%
% Function return parameters
% 1 - DataNLLS -> The data corrected by the final estimated parameters. 
% 2 - ParC -> Estimated parameters.
% 3 - Time -> Time taken to the algorithm. Simulation and auxiliary
% variables calculated after the estimation proccess does not count, such
% as the attitude sphere plot.
% 4 - Est -> Structure returning additional information of the calibration.
% 5 - Erros -> if opt = 'simul', the algorithm calculates the estimated
% parameters error compared to ParT.

function [DataIG, ParC, Time, Est, Erros] =...
    Batista_InitialGuess(ParT, ParP, DataObs, sf, simul, opt)


% Vectorization of ParT to pT:
pT(1) = ParT.x0;
pT(2) = ParT.y0;
pT(3) = ParT.z0;
pT(4) = ParT.a;
pT(5) = ParT.b;
pT(6) = ParT.c;
pT(7) = ParT.rho;
pT(8) = ParT.phi;
pT(9) = ParT.lambda;

% Vectorization of ParP to pP:
pP(1) = ParP.x0;
pP(2) = ParP.y0;
pP(3) = ParP.z0;
pP(4) = ParP.a;
pP(5) = ParP.b;
pP(6) = ParP.c;
pP(7) = ParP.rho;
pP(8) = ParP.phi;
pP(9) = ParP.lambda;

% Initiate the parameters as pP:
p = pP';

% Adaptação para rodar
vx = DataObs(1,:);
vy = DataObs(2,:);
vz = DataObs(3,:);

% Verifies if sf is a scalar and creats the vector based on the number of
% measurements M (M=length(vx)):
M = length(vx);

if(length(sf)==1)
    sf(1:M) = sf;
elseif (iscolumn(sf)==1)
    sf = sf';
end

% if (exist('stop_perc','var')==0)
%     stop_perc = 0.1;
% end

% Início do Timer:
tic;

% Calculates the initial offset value of the Nonlinear Least Square:
Hoffset = [-2*vx; -2*vy; -2*vz; ones(1,M)]';
yoffset = (sf.^2 - vx.^2 - vy.^2 - vz.^2)';
offset_est = inv(Hoffset'*Hoffset)*Hoffset'*yoffset;
% Updates p with the estimated offset values and saves it in Est.offset:
p(1) = offset_est(1);
p(2) = offset_est(2);
p(3) = offset_est(3);
Est.offset = offset_est;

% Calculates the initial scale factor value of the Nonlinear Least Square:
vx_sf = vx - offset_est(1);
vy_sf = vy - offset_est(2);
vz_sf = vz - offset_est(3);

% Hsf = Mx3
Hsf = [vx_sf.^2; vy_sf.^2; vz_sf.^2]';

% ysf = Mx1
for i=1:M
    ysf(i,:) = sf(i)^2;
end

x_sf_est = inv(Hsf'*Hsf)*Hsf'*ysf;
a_sf_est = sqrt(1/x_sf_est(1));
b_sf_est = sqrt(1/x_sf_est(2));
c_sf_est = sqrt(1/x_sf_est(3));

p(4) = a_sf_est;
p(5) = b_sf_est;
p(6) = c_sf_est;
sf_est = [a_sf_est b_sf_est c_sf_est];
Est.sf = sf_est;

% Vetorização de ParC
ParC.x0     = p(1);
ParC.y0     = p(2); 
ParC.z0     = p(3);
ParC.a      = p(4);
ParC.b      = p(5);
ParC.c      = p(6);
ParC.rho    = 0;
ParC.phi    = 0;
ParC.lambda = 0;

%Final do Timer, após determinar os parâmetros:
Time = toc;


% A patir dos dados com erros e dos parâmetros de calibração
% montamos uma matriz com os dados corrigidos:
DataIG(1,:) = (DataObs(1,:) - ParC.x0)/ParC.a;
DataIG(2,:) = (DataObs(2,:) - ParC.y0)/ParC.b;
DataIG(3,:) = (DataObs(3,:) - ParC.z0)/ParC.c;

%Final do Timer, após correção dos parâmetros:
% Time = toc;

%Calcula o Desvio Padrão de DataNLLS em relação ao valor espesrado:
for i=1:length(DataIG(1,:))
    aux(i) = norm(DataIG(:,i));
end
aux = (sf - aux).^2;
DataNLLS_Std = sqrt( (1/(length(DataIG)))*sum(aux));

%Parâmetros de retorno do Resíduo e ParC ao longos das iterações
Est.Vetor_Res = 0;
Est.ParC = ParC;
Est.Res_std = 0;
Est.DataNLLS_Std = DataNLLS_Std;
Est.Num_It = 1;
Est.Matrix_H = 0;
%Est.Fisher = Fisher;
%Est.P_cramer = P_cramer;

% Caso a opção seja 'full', o algoritmo realiza o plote
% dos dados sem calibração e posterior com calibração na 
% esfera unitária (novamente os dados estão normalizados
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
    mx = DataIG(1,:)./sf;
    my = DataIG(2,:)./sf;
    mz = DataIG(3,:)./sf;
    plot3(mx,my,mz,'r.')
    title('Data Calibrada');
    
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
    mx = DataObs(1,:)./sf;
    my = DataObs(2,:)./sf;
    mz = DataObs(3,:)./sf;
    plot3(mx,my,mz,'r.')
    title('Data Sem Calibração');
end

if (simul == 1) 
    % Arrumar nao tem mais i
    e_log = (p-pT')./pT';

    % Erros 
    Erros.e_log = e_log;
    Erros.eTot  = norm(e_log(:,end));
else
    Erros = ('null');
end