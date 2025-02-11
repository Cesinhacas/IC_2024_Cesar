param = zeros(9,3000);

for i=1:1:3000
    offset = (rand(3,1)*0.4)-0.2;
    Escala = (rand(3,1)*0.4)+0.8;
    Ang = (rand(3,1)*6 - 3) * (pi/180);
    param(:,i) = [Escala; offset; Ang]; 
end

cd ../
cd 'Dados'
writematrix(param, 'commum_param.csv');
cd ../
cd 'Matlab'