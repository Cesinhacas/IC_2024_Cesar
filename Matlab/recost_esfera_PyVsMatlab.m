cd ..\
cd Dados\
Dados_Corrompido = readmatrix('Dados_Corrompido.csv');
p = readmatrix('Calib_param_ETS.csv');
p0 = readmatrix('Calib_param_NLLS.csv');
p1 = readmatrix('Calib_param_TW.csv')';
p_m = readmatrix('Calib_param_ETS_m.csv');
p0_m = readmatrix('Calib_param_NLLS_m.csv');
p1_m = readmatrix('Calib_param_TW_m.csv');
p1_c = readmatrix('Calib_param_TW_c.csv');
p_c = readmatrix('Calib_param_ETS_c.csv');
p0_c = readmatrix('Calib_param_NLLS_c.csv');
cd ..\
cd Matlab\

ETS = p_m - p;
NLLS = p0_m - p0;
TW = p1_m - p1;

ETS_ = p_m - p_c;
NLLS_ = p0_m - p0_c;
TW_ = p1_m - p1_c;

Dados_rest(1,:) =  (Dados_Corrompido(1,:) - p(4))/p(1);
Dados_rest(2,:) = ((Dados_Corrompido(2,:) - p(5))/p(2) - Dados_rest(1,:)*sin(p(7)))/cos(p(7));
Dados_rest(3,:) = ((Dados_Corrompido(3,:) - p(6))/p(3) - Dados_rest(1,:)*sin(p(8))*cos(p(9)) - Dados_rest(2,:)*sin(p(9)))/(cos(p(8))*cos(p(9)));

Dados_rest1(1,:) =  (Dados_Corrompido(1,:) - p_m(4))/p_m(1);
Dados_rest1(2,:) = ((Dados_Corrompido(2,:) - p_m(5))/p_m(2) - Dados_rest(1,:)*sin(p_m(7)))/cos(p_m(7));
Dados_rest1(3,:) = ((Dados_Corrompido(3,:) - p_m(6))/p_m(3) - Dados_rest(1,:)*sin(p_m(8))*cos(p_m(9)) - Dados_rest(2,:)*sin(p_m(9)))/(cos(p_m(8))*cos(p_m(9)));

Dados_rest2(1,:) =  (Dados_Corrompido(1,:) - p_c(4))/p_c(1);
Dados_rest2(2,:) = ((Dados_Corrompido(2,:) - p_c(5))/p_c(2) - Dados_rest(1,:)*sin(p_c(7)))/cos(p_c(7));
Dados_rest2(3,:) = ((Dados_Corrompido(3,:) - p_c(6))/p_c(3) - Dados_rest(1,:)*sin(p_c(8))*cos(p_c(9)) - Dados_rest(2,:)*sin(p_c(9)))/(cos(p_c(8))*cos(p_c(9)));

Dados_rest_NLLS(1,:) =  (Dados_Corrompido(1,:) - p0(4))/p0(1);
Dados_rest_NLLS(2,:) = ((Dados_Corrompido(2,:) - p0(5))/p0(2) - Dados_rest(1,:)*sin(p0(7)))/cos(p0(7));
Dados_rest_NLLS(3,:) = ((Dados_Corrompido(3,:) - p0(6))/p0(3) - Dados_rest(1,:)*sin(p0(8))*cos(p0(9)) - Dados_rest(2,:)*sin(p0(9)))/(cos(p0(8))*cos(p0(9)));

Dados_rest_NLLS1(1,:) =  (Dados_Corrompido(1,:) - p0_m(4))/p0_m(1);
Dados_rest_NLLS1(2,:) = ((Dados_Corrompido(2,:) - p0_m(5))/p0_m(2) - Dados_rest(1,:)*sin(p0_m(7)))/cos(p0_m(7));
Dados_rest_NLLS1(3,:) = ((Dados_Corrompido(3,:) - p0_m(6))/p0_m(3) - Dados_rest(1,:)*sin(p0_m(8))*cos(p0_m(9)) - Dados_rest(2,:)*sin(p0_m(9)))/(cos(p0_m(8))*cos(p0_m(9)));

Dados_rest_NLLS2(1,:) =  (Dados_Corrompido(1,:) - p0_c(4))/p0_c(1);
Dados_rest_NLLS2(2,:) = ((Dados_Corrompido(2,:) - p0_c(5))/p0_c(2) - Dados_rest(1,:)*sin(p0_c(7)))/cos(p0_c(7));
Dados_rest_NLLS2(3,:) = ((Dados_Corrompido(3,:) - p0_c(6))/p0_c(3) - Dados_rest(1,:)*sin(p0_c(8))*cos(p0_c(9)) - Dados_rest(2,:)*sin(p0_c(9)))/(cos(p0_c(8))*cos(p0_c(9)));

Dados_rest_TW = zeros(3,length(Dados_Corrompido(1,:)));
Dados_rest_TW1 = zeros(3,length(Dados_Corrompido(1,:)));
Dados_rest_TW2 = zeros(3,length(Dados_Corrompido(1,:)));

b = p1(:,1);
b_c = p1_c(:,1);
b_m = p1_m(:,1);

D = p1(:,2:end);
D_m = p1_m(:,2:end);
D_c = p1_c(:,2:end);


for i=1:length(Dados_Corrompido(1,:))
    Dados_rest_TW(:,i) = (eye(3)+D)*Dados_Corrompido(:,i) - b;
    Dados_rest_TW1(:,i) = (eye(3)+D_m)*Dados_Corrompido(:,i) - b_m;
    Dados_rest_TW2(:,i) = (eye(3)+D_c)*Dados_Corrompido(:,i) - b_c;
end

dif_dados_NLLS = Dados_rest_NLLS1 - Dados_rest_NLLS;
dif_dados_NLLS_ = Dados_rest_NLLS1 - Dados_rest_NLLS2;

dif_dados_ETS = Dados_rest1 - Dados_rest;
dif_dados_ETS_ = Dados_rest1 - Dados_rest2;

dif_dados_TW = Dados_rest_TW1 - Dados_rest_TW;
dif_dados_TW_ = Dados_rest_TW1 - Dados_rest_TW2;