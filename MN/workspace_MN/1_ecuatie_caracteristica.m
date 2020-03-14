# Random 10x10 matrix
n = 10;
A = rand(n, n);

# Interpolation support for finding p(lambda) = det(A - lambda * I);
# At least n + 1 points in order to have at least the order n => n roots;
# Populate x with equidistant points in a random base e.g. (-5, 5)
x = linspace(-5, 5, n + 1);
# Populate y with p(x) values
y = [];
for i = 1:n+1
    y = [y, det(A - x(i) * eye(n))];
endfor

# Interpolate x -> y in an approximated polynomial "char_poly" of p(lambda)
char_poly = polyfit(x, y, n);
disp('||eig_p - eig_A|| = ')
norm(sort(roots(char_poly)) - sort(eig(A)), inf)