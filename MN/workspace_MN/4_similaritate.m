n = 5;
A0 = rand(n, n)
e0 = eig(A0);

[Q R] = qr(A0);
A1 = R * Q
e1 = eig(A1);

disp('||eig(A0) - eig(A1 = R * Q)|| = ')
norm(sort(e0) - sort(e1))