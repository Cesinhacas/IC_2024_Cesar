function [I_fisher_bar] =...
TS_fisher_center(sigma_sq_bar,L_bar,dbsqdtheta_p)
% Calculates center informaiton matris. Used for readability
I_fisher_bar=((L_bar'-dbsqdtheta_p)'*(L_bar'-dbsqdtheta_p))/sigma_sq_bar;
end