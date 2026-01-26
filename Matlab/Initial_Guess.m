function [p0, Time] = Initial_Guess(Dados_corrompido, Be)
    mx = Dados_corrompido(1,:)';
    my = Dados_corrompido(2,:)';
    mz = Dados_corrompido(3,:)';
    tic;
    y_offset = Be.^2 - mx.^2 - my.^2 - mz.^2;
    
    H_offset = [-2*mx, -2*my, -2*mz, ones(length(mx), 1)];

    x_offset = (H_offset'*H_offset)\H_offset'*y_offset;

    y_sf = Be.^2;

    H_sf = [(mx - x_offset(1)).^2, (my - x_offset(2)).^2, (mz - x_offset(3)).^2];
    
    x_sf = (H_sf'*H_sf)\H_sf'*y_sf;
    
    p0 = [x_sf(1)^(-1/2); x_sf(2)^(-1/2); x_sf(3)^(-1/2); x_offset(1:3); 0; 0; 0];
    Time = toc;
end