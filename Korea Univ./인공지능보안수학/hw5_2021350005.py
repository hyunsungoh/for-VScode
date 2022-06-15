import numpy as np

S0 = np.array([[1.2], [1.2]])
S1 = np.array([[-1.2], [1]])

def func(x):
    return 100*(x[1][0]-x[0][0]**2)**2 + (1-x[0][0])**2

def g(x):
    return np.array([[-400*(x[0][0]*x[1][0]-x[0][0]**3)-2*(1-x[0][0])], [200*(x[1][0]-x[0][0]**2)]])

def h(x):
    return np.array([[-400*(x[1][0]-3*x[0][0]**2)+2, -400*x[0][0]], [-400*x[0][0], 200]])

def norm(a):
    return np.linalg.norm(a, 2)

tol = 10**(-12)
max_iter = 50000

a0 = 1.0
p = 0.5
c1 = 10**(-4)
max_ls_iter = max_iter / 4

def MinimizationLoop(x0, type, f):

    k = 0
    xk = x0

    while k < max_iter:
        if norm(g(xk)) < tol:
            break
        
        if type == 'sd':
            pk = -g(xk)
        else:
            pk = -np.linalg.inv(h(xk)).dot(g(xk))
        
        ak = Linesearch(xk, pk)

        xk = xk + ak*pk

        c = func(xk)
        d = norm(g(xk))

        f.write("Iteration %d: alp=%e, f=%e, gnorm=%e\n" %(k, ak, c, d))

        k = k+1

    return xk


def Linesearch(xk, pk):

    a = a0
    ls_iter = 0

    m1 = func(xk)
    m2 = c1*g(xk).T.dot(pk)

    while(ls_iter < max_ls_iter):
        if func(xk + a*pk) <= m1 + a*m2:
            break

        a = p*a
        ls_iter = ls_iter + 1

    return a


f1 = open("GD_S0.txt", 'w')
MinimizationLoop(S0, 'sd', f1)
f1.close()

f2 = open("GD_S1.txt", 'w')
MinimizationLoop(S1, 'sd', f2)
f2.close()

f3 = open("NT_S0.txt", 'w')
MinimizationLoop(S0, 'nt', f3)
f3.close()

f4 = open("NT_S1.txt", 'w')
MinimizationLoop(S1, 'nt', f4)
f4.close()