% Non-linear Least Square Function for the parameter calibration
%
% The algorithm uses the sensor model of Foster and has a linear solution
% to find the starting offset parameters.
%
% function [DataNLLS, ParC, Time, Est, Erros] =...
    %NLLS_9Dcalib(ParT, ParP, DataObs, sf, simul, opt, stop_perc)
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

function [DataNLLS, ParC, Time, Est, Erros] =...
    NLLS_9Dcalib(ParT, ParP, DataObs, sf, simul, opt, stop_perc)

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
end

if (exist('stop_perc','var')==0)
    stop_perc = 0.1;
end

% Início do Timer:
tic;

% Saves the Structures Est.offset and Est.sf with the ParP initialization.
offset_est = [p(1) p(2) p(3)];
Est.offset = offset_est;

sf_est = [p(4) p(5) p(6)];
Est.sf = sf_est;

% Start the index counter:
i = 1;
loop = 1;

while loop == 1
    
    % Assemble the variables (easy to mount the equations):
    xo = p(1);
    yo = p(2);
    zo = p(3);
    a  = p(4);
    b  = p(5);
    c  = p(6);
    ro = p(7);
    fi = p(8);
    la = p(9);
    
    % Calculates f(B,p), which is represented by 'r':
    r = ((vx-xo).^2/a^2+(-b*sin(ro).*(vx-xo)+a.*(vy-yo)).^2/a^2/b^2/cos(ro)^2+(b*c*(sin(ro)*sin(la)-cos(ro)*sin(fi)*cos(la)).*(vx-xo)-a*c*sin(la).*(vy-yo)+a*b*cos(ro).*(vz-zo)).^2/a^2/b^2/c^2/cos(ro)^2/cos(fi)^2/cos(la)^2);
    r = r';  
 
    % Calculates the residual error 'e':  
    e  = (sf.^2)' - r; % NAUM HAH MAIS O r COMO FICA A VARIAVEL Cu
    
    % Finds the residual error sum ('Cu') (loss function of the problem):
     Cu = e'*e;    
     
    % Finds the standard deviation of 'e':
    e_std = sqrt((1/(length(e)))*Cu); 
    
    %Updates the log of the parameters and residues:
    p_log(:,i) = p; 
    vetor_res_log(:,i) = e;
    res_std_log(i) = e_std;

    % Computes the residual difference between the last estimates
    % which is used as the stop criteria:
    if i==1
        res_diff_percent=101;
    else
        aux = abs(res_std_log(i) - res_std_log(i-1));
        res_diff_percent(i) = aux/res_std_log(i-1);
    end
    
    % Verifies the stop criteria:
    % If true, stops the loop
    % Else, calculates a new set of parameters:
    if (( (res_diff_percent(i)<=stop_perc/100)&&i>2 )||(i>12))
%     if (( (res_diff_percent(i)<=stop_perc)&&i>1 )||(i>12))
        loop = 0;
        num_it = i;
    else
        % Assemble the Gradiant Matrix H, represented here by B: 

        B1 = (2*sin(ro)*(a*(vy - yo) - b*sin(ro)*(vx - xo)))/(a^2*b*cos(ro)^2) - (2*vx - 2*xo)/a^2 - (2*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a^2*b*c*cos(fi)^2*cos(la)^2*cos(ro)^2);
        B2 = (2*sin(la)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a*b^2*c*cos(fi)^2*cos(la)^2*cos(ro)^2) - (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)))/(a*b^2*cos(ro)^2);
        B3 = -(2*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi))*(vx - xo) + a*b*cos(ro)*(vz - zo) - a*c*sin(la)*(vy - yo)))/(a*b*c^2*cos(fi)^2*cos(la)^2*cos(ro));
        B4 = (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)).*(vy - yo))./(a^2*b^2*cos(ro)^2) - (2*(a*(vy - yo) - b*sin(ro)*(vx - xo)).^2)./(a^3*b^2*cos(ro)^2) - (2*(vx - xo).^2)./a^3 - (2*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la)*(vy - yo)).^2)./(a^3*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2) + (2*(b*cos(ro).*(vz - zo) - c*sin(la)*(vy - yo)).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2);
        B5 = -(2*(vy - yo).*(a*c*vy*sin(la)^2 - a*c*yo*sin(la)^2 - a*b*vz*cos(ro)*sin(la) + a*b*zo*cos(ro)*sin(la) - b*c*vx*sin(la)^2*sin(ro) + b*c*xo*sin(la)^2*sin(ro) + a*c*vy*cos(fi)^2*cos(la)^2 - a*c*yo*cos(fi)^2*cos(la)^2 - b*c*vx*cos(fi)^2*cos(la)^2*sin(ro) + b*c*xo*cos(fi)^2*cos(la)^2*sin(ro) + b*c*vx*cos(la)*cos(ro)*sin(fi)*sin(la) - b*c*xo*cos(la)*cos(ro)*sin(fi)*sin(la)))/(a*b^3*c*cos(fi)^2*cos(la)^2*cos(ro)^2);
        B6 = -(2*(vz - zo).*(a*b*vz*cos(ro) - a*b*zo*cos(ro) - a*c*vy*sin(la) + a*c*yo*sin(la) + b*c*vx*sin(la)*sin(ro) - b*c*xo*sin(la)*sin(ro) - b*c*vx*cos(la)*cos(ro)*sin(fi) + b*c*xo*cos(la)*cos(ro)*sin(fi)))./(a*b*c^3*cos(fi)^2*cos(la)^2*cos(ro));
        B7 = -(2*(b*vx - b*xo - a*vy*sin(ro) + a*yo*sin(ro)).*(a*c*vy*sin(la)^2 - a*c*yo*sin(la)^2 - a*b*vz*cos(ro)*sin(la) + a*b*zo*cos(ro)*sin(la) - b*c*vx*sin(la)^2*sin(ro) + b*c*xo*sin(la)^2*sin(ro) + a*c*vy*cos(fi)^2*cos(la)^2 - a*c*yo*cos(fi)^2*cos(la)^2 - b*c*vx*cos(fi)^2*cos(la)^2*sin(ro) + b*c*xo*cos(fi)^2*cos(la)^2*sin(ro) + b*c*vx*cos(la)*cos(ro)*sin(fi)*sin(la) - b*c*xo*cos(la)*cos(ro)*sin(fi)*sin(la)))/(a^2*b^2*c*cos(fi)^2*cos(la)^2*cos(ro)^3);
        B8 = (2*sin(fi)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)).^2)./(a^2*b^2*c^2*cos(fi)^3*cos(la)^2*cos(ro)^2) - (2.*(vx - xo).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b*c*cos(fi)*cos(la)*cos(ro));
        B9 = (2*(b*c*(cos(la)*sin(ro) + cos(ro)*sin(fi)*sin(la)).*(vx - xo) - a*c*cos(la).*(vy - yo)).*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)))./(a^2*b^2*c^2*cos(fi)^2*cos(la)^2*cos(ro)^2) + (2*sin(la)*(b*c*(sin(la)*sin(ro) - cos(la)*cos(ro)*sin(fi)).*(vx - xo) + a*b*cos(ro).*(vz - zo) - a*c*sin(la).*(vy - yo)).^2)./(a^2*b^2*c^2*cos(fi)^2*cos(la)^3*cos(ro)^2);                                                                                                                                                                                                                           
        B = [B1' B2' B3' B4' B5' B6' B7' B8' B9']';       
    
        % Estimate the Delta parameters increment:
        q = inv(B*B')*B*e;
    
        % Calculates Fisher and P_Cramer:
        %Fisher = B*B';
        %P_cramer = inv(Fisher);

        % Update the estimated parameters:
        p = p + q;
        
        % Increment the loop counter:
        i = i + 1;
    end
    
end

% Vetorização de ParC
ParC.x0     = p(1);
ParC.y0     = p(2); 
ParC.z0     = p(3);
ParC.a      = p(4);
ParC.b      = p(5);
ParC.c      = p(6);
ParC.rho    = p(7);
ParC.phi    = p(8);
ParC.lambda = p(9);
Time = toc;

% A patir dos dados com erros e dos parâmetros de calibração
% montamos uma matriz com os dados corrigidos:
DataNLLS(1,:) =  (DataObs(1,:) - ParC.x0)/ParC.a;
DataNLLS(2,:) = ((DataObs(2,:) - ParC.y0)/ParC.b - DataNLLS(1,:)*sin(ParC.rho))/cos(ParC.rho);
% DataNLLS(3,:) = ((DataObs(3,:) - ParC.z0)/ParC.c - DataNLLS(1,:)*sin(ParC.phi)*cos(ParC.lambda) - DataNLLS(2,:)*sin(ParC.lambda)*cos(ParC.phi))/(cos(ParC.phi)*cos(ParC.lambda));
DataNLLS(3,:) = ((DataObs(3,:) - ParC.z0)/ParC.c - DataNLLS(1,:)*sin(ParC.phi)*cos(ParC.lambda) - DataNLLS(2,:)*sin(ParC.lambda))/(cos(ParC.phi)*cos(ParC.lambda));

%Final do Timer, após correção dos parâmetros:
%Time = toc;

%Calcula o Desvio Padrão de DataNLLS em relação ao valor espesrado:
for i=1:length(DataNLLS(1,:))
    aux(i) = norm(DataNLLS(:,i));
end
aux = (sf - aux).^2;
DataNLLS_Std = sqrt( (1/(length(DataNLLS)))*sum(aux));

%Parâmetros de retorno do Resíduo e ParC ao longos das iterações
Est.Vetor_Res = vetor_res_log;
Est.ParC = p_log;
Est.Res_std = res_std_log;
Est.DataNLLS_Std = DataNLLS_Std;
Est.Num_It = num_it;
Est.Matrix_H = B';
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
    s2 = surf(x,y,z);
    set(s2,'FaceColor','none')
    set(s2,'EdgeColor',[0.7 0.7 0.7])
    hold off
    axis([-e e -e e -e e])
    set(gca,'PlotBoxAspectRatioMode','manual')
    set(gca,'FontSize',12)
    hold on
    mx = DataNLLS(1,:)./sf;
    my = DataNLLS(2,:)./sf;
    mz = DataNLLS(3,:)./sf;
    plot3(mx,my,mz,'r.')
    title('Data Calibrada');
    
    subplot(2,1,2)
    e = 1.5;
    [x,y,z] = sphere;
    s2 = surf(x,y,z);
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