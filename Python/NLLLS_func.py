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

        
        h1 = (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx))*(by - my))/(sx**2*sy**2*np.cos(rho)**2) - (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx))**2)/(sx**3*sy**2*np.cos(rho)**2) - (2*(bx - mx)**2)/sx**3 - (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**3*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*np.cos(rho)*(bz - mz) - sz*np.sin(lambida)*(by - my))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        h2 = -(2*(by - my)*(by*sx*sz*np.sin(lambida)**2 - my*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx*sy**3*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        h3 = -(2*(bz - mz)*(bz*sx*sy*np.cos(rho) - by*sx*sz*np.sin(lambida) - mz*sx*sy*np.cos(rho) + my*sx*sz*np.sin(lambida) + bx*sy*sz*np.sin(lambida)*np.sin(rho) - mx*sy*sz*np.sin(lambida)*np.sin(rho) - bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi) + mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(phi)))/(sx*sy*sz**3*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))

        h4 = (2*bx - 2*mx)/sx**2 - (2*np.sin(rho)*(sx*(by - my) - sy*np.sin(rho)*(bx - mx)))/(sx**2*sy*np.cos(rho)**2) + (2*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        h5 = (2*(sx*(by - my) - sy*np.sin(rho)*(bx - mx)))/(sx*sy**2*np.cos(rho)**2) - (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        h6 = (2*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx*sy*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho))

        h7 = -(2*(bx*sy - mx*sy - by*sx*np.sin(rho) + my*sx*np.sin(rho))*(by*sx*sz*np.sin(lambida)**2 - my*sx*sz*np.sin(lambida)**2 + by*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - my*sx*sz*np.cos(lambida)**2*np.cos(phi)**2 - bz*sx*sy*np.cos(rho)*np.sin(lambida) + mz*sx*sy*np.cos(rho)*np.sin(lambida) - bx*sy*sz*np.sin(lambida)**2*np.sin(rho) + mx*sy*sz*np.sin(lambida)**2*np.sin(rho) - bx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + mx*sy*sz*np.cos(lambida)**2*np.cos(phi)**2*np.sin(rho) + bx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi) - mx*sy*sz*np.cos(lambida)*np.cos(rho)*np.sin(lambida)*np.sin(phi)))/(sx**2*sy**2*sz*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**3)

        h8 = (2*np.sin(phi)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**3*np.cos(rho)**2) - (2*(bx - mx)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy*sz*np.cos(lambida)*np.cos(phi)*np.cos(rho))

        h9 = (2*np.sin(lambida)*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my))**2)/(sx**2*sy**2*sz**2*np.cos(lambida)**3*np.cos(phi)**2*np.cos(rho)**2) + (2*(sy*sz*(np.cos(lambida)*np.sin(rho) + np.cos(rho)*np.sin(lambida)*np.sin(phi))*(bx - mx) - sx*sz*np.cos(lambida)*(by - my))*(sy*sz*(np.sin(lambida)*np.sin(rho) - np.cos(lambida)*np.cos(rho)*np.sin(phi))*(bx - mx) + sx*sy*np.cos(rho)*(bz - mz) - sx*sz*np.sin(lambida)*(by - my)))/(sx**2*sy**2*sz**2*np.cos(lambida)**2*np.cos(phi)**2*np.cos(rho)**2)

        H_t = np.array([h1, h2, h3, h4, h5, h6, h7, h8, h9])
        H = H_t.transpose()

        deltap = np.linalg.pinv(H) @ e

        p0 = p0 + deltap

        passo += 1

    
    #P = e_std*np.linalg.inv(H.transpose()@H)
    return p0
