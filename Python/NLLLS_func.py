def NLLS_func(mx, my, mz):
    import numpy as np

    passo = 0
    loop = 1
    p0 = [1, 1, 1, 0, 0, 0, 0, 0, 0]
    Be = np.ones_like(mx)
    Be = list(map(lambda x: x**2, Be))
    e = Be
    error_vet = []

    while loop == 1:
        sx = p0[0]
        sy = p0[1]
        sz = p0[2]
        bx = p0[3]
        by = p0[4]
        bz = p0[5]
        rho = p0[6]
        phi = p0[7]
        lambida = p0[8]
        
        f = (((mx-bx)**2)/(sx)**2) + (((sx*(my-by) - sy*np.sin(rho)*(mx-bx))**2)/((sx*sy*np.cos(rho))**2)) + (((sx*sy*np.cos(rho)*(mz-bz) - sx*sz*np.sin(lambida)*(my-by) + sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(rho)*np.sin(phi)*np.cos(lambida))*(mx-bx))**2)/((sx*sy*sz*np.cos(rho)*np.cos(phi)*np.cos(lambida))**2))
        
        
        e = Be - f
        
        J = (e.transpose()@e)
        J = J*0.5
        
    
        e_std = (2*J*(1/len(e)))**0.5
        
        if passo < 3:
            error_vet.append(J)
        else:
            error_vet.append(J)
            delta_J = 100*np.abs(error_vet[passo]-error_vet[passo-1])/error_vet[passo]
            if delta_J < 0.1:
                loop = 0

        
        sin_rho = np.sin(rho)
        cos_rho = np.cos(rho)
        sin_phi = np.sin(phi)
        cos_phi = np.cos(phi)
        sin_lambida = np.sin(lambida)
        cos_lambida = np.cos(lambida)

        h1 = (2*(sx*(by - my) - sy*sin_rho*(bx - mx))*(by - my))/(sx**2*sy**2*cos_rho**2) - (2*(sx*(by - my) - sy*sin_rho*(bx - mx))**2)/(sx**3*sy**2*cos_rho**2) - (2*(bx - mx)**2)/sx**3 - (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**3*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2) + (2*(sy*cos_rho*(bz - mz) - sz*sin_lambida*(by - my))*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2)

        h2 = -(2*(by - my)*(by*sx*sz*sin_lambida**2 - my*sx*sz*sin_lambida**2 + by*sx*sz*cos_lambida**2*cos_phi**2 - my*sx*sz*cos_lambida**2*cos_phi**2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida**2*sin_rho + mx*sy*sz*sin_lambida**2*sin_rho - bx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + mx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))/(sx*sy**3*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

        h3 = -(2*(bz - mz)*(bz*sx*sy*cos_rho - by*sx*sz*sin_lambida - mz*sx*sy*cos_rho + my*sx*sz*sin_lambida + bx*sy*sz*sin_lambida*sin_rho - mx*sy*sz*sin_lambida*sin_rho - bx*sy*sz*cos_lambida*cos_rho*sin_phi + mx*sy*sz*cos_lambida*cos_rho*sin_phi))/(sx*sy*sz**3*cos_lambida**2*cos_phi**2*cos_rho)

        h4 = (2*bx - 2*mx)/sx**2 - (2*sin_rho*(sx*(by - my) - sy*sin_rho*(bx - mx)))/(sx**2*sy*cos_rho**2) + (2*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

        h5 = (2*(sx*(by - my) - sy*sin_rho*(bx - mx)))/(sx*sy**2*cos_rho**2) - (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx*sy**2*sz*cos_lambida**2*cos_phi**2*cos_rho**2)

        h6 = (2*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx*sy*sz**2*cos_lambida**2*cos_phi**2*cos_rho)

        h7 = -(2*(bx*sy - mx*sy - by*sx*sin_rho + my*sx*sin_rho)*(by*sx*sz*sin_lambida**2 - my*sx*sz*sin_lambida**2 + by*sx*sz*cos_lambida**2*cos_phi**2 - my*sx*sz*cos_lambida**2*cos_phi**2 - bz*sx*sy*cos_rho*sin_lambida + mz*sx*sy*cos_rho*sin_lambida - bx*sy*sz*sin_lambida**2*sin_rho + mx*sy*sz*sin_lambida**2*sin_rho - bx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + mx*sy*sz*cos_lambida**2*cos_phi**2*sin_rho + bx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi - mx*sy*sz*cos_lambida*cos_rho*sin_lambida*sin_phi))/(sx**2*sy**2*sz*cos_lambida**2*cos_phi**2*cos_rho**3)

        h8 = (2*sin_phi*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**3*cos_rho**2) - (2*(bx - mx)*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy*sz*cos_lambida*cos_phi*cos_rho)

        h9 = (2*sin_lambida*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my))**2)/(sx**2*sy**2*sz**2*cos_lambida**3*cos_phi**2*cos_rho**2) + (2*(sy*sz*(cos_lambida*sin_rho + cos_rho*sin_lambida*sin_phi)*(bx - mx) - sx*sz*cos_lambida*(by - my))*(sy*sz*(sin_lambida*sin_rho - cos_lambida*cos_rho*sin_phi)*(bx - mx) + sx*sy*cos_rho*(bz - mz) - sx*sz*sin_lambida*(by - my)))/(sx**2*sy**2*sz**2*cos_lambida**2*cos_phi**2*cos_rho**2)

        H_t = np.array([h1, h2, h3, h4, h5, h6, h7, h8, h9])
        H = H_t.transpose()

        deltap = np.linalg.pinv(H) @ e

        p0 = p0 + deltap

        passo += 1

    
    #P = e_std*np.linalg.inv(H.transpose()@H)
    return p0
