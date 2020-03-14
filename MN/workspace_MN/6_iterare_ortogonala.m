function [Q] = OrthogonalIteration(A)
    # Orthogonal iteration on A:
    n = size(A, 1);
    U = rand(n, n);
    for k = 1:10000
        [Q, R] = qr(U);
        U = A * Q;
    end
end

A = rand(3, 3);
U = OrthogonalIteration(A);
disp('||diag(U_T * A * U) - eig(A)|| = ')
norm(sort(diag(U' * A * U)) - sort(eig(A)))