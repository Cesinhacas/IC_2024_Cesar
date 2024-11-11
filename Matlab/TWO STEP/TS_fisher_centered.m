function [I_fisher_tilde,I_fishinv_tilde] =...
    TS_fisher_centered(sigma_sq,L_tilde)
% Calculates the fisher information matrix for the centered estimate, when
% given variance sigma sq and centered vectors of L tilde
% Calculate fisher information matrix
I_fisher_tilde=...
    ((L_tilde.*(ones(size(L_tilde,1),1)*(1./sigma_sq)))*L_tilde');
% Calculate inverse
I_fishinv_tilde=(I_fisher_tilde)\eye(9);
end