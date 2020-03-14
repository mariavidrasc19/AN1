n = 5;
A = triu(rand(n, n))
eig(A)
disp('||eig_A - diag_A|| = ')
norm(sort(eig(A)) - sort(diag(A)))