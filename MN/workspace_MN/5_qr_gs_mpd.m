function [v] = OrthogonalProjection(v, Q)
   # Orthogonal projection
    m = size(Q, 2);
    for k = 1:m
        c = Q(:,k)' * v;
        for j = 1 : size(v, 1)
            v(j) -= c * Q(j,k);
        endfor
    endfor
endfunction

function [v] = OrthogonalPowerIteration(v, Q, A)
   # Do Power iteration, while projecting:
    m = size(Q, 2);
    for k = 1:1000
        v = OrthogonalProjection(A * v, Q);
        v = v / norm(v);
    endfor
endfunction

function [v] = PowerIteration(v, A)
   # Do power iteration while projecting:
   v;
   A;
    for k = 1:1000
        v = A * v;
        v = v / norm(v);
    endfor
endfunction

function [eigs] = GramSchmidtBasedQRAlgorithm(A)
    # Use Gram-Schmidt and power iteration to compute the eigenvalues of A:
    n = size(A, 1);
    v = rand(n, 1);
    Q = PowerIteration(v, A);
    for k = 2:n
        k
        v = rand(n, 1);
        v = OrthogonalPowerIteration(v, Q, A);
        Q = [Q, v];
    endfor
    eigs = mean((A*Q)./Q,1)';
    eigs = sort(eigs);
end

# Random matrix:
A = rand(10, 10);
A = A'*A;
# True eigenvectors and eigenvalues.
eigs = sort(eig(A));
# Compute eigenvalues of A via power iteration and Gram-Schmidt: 
qr_eigs = GramSchmidtBasedQRAlgorithm(A);
norm(eigs - qr_eigs)