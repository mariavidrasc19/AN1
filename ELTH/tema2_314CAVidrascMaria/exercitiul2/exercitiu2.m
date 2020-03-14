% Exercitiul al 2 lea
pkg load symbolic;
syms s t;
R_c = 5000*pi /s;
r = 4*R_c/(4+R_c);
E = -18/s *r/R_c;
I = (3/pi +18/s + E-4*r/s) / (r+6+0.2*s/pi);
U = (3/s -I) * r +E;
% pentru sub b
Intensitatea_initiala = limit(s*I,s,inf);
Tensiunea_initiala = limit(s*U,s,inf);
Intensitatea_finala = limit(s*I,s,0);
Tensiunea_finala = limit(s*U,s,0);
% pentru sub c
inv_I = ilaplace(I);
ezplot(inv_I,[0, 0.2]);