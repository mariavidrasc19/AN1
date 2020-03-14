n = 50;
A = rand(n, n);
A0 = A;

for k = 1:50
    [Q, R] = qr(A);
    A = R * Q;
endfor

# 20 is the marker's width
spy(flipud(abs(A) > 1e-4), 10)
# Plot for 5 seconds
pause(5)

for k = 1:1000
    [Q, R] = qr(A);
    A = R * Q;
endfor

# 20 is the marker's width
spy(flipud(abs(A) > 1e-4), 10)
# Plot for 5 seconds
pause(5)

# Repeat the whole process for another 10000 steps
for k = 1:10000
    [Q, R] = qr(A);
    A = R * Q;
endfor

spy(flipud(abs(A) > 1e-4), 10)
pause(5)