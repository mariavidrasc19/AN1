 % Exercitiu 1
 n = 10; % nr de ecuatii si de necunoscute
 A = zeros(n); 
 b = zeros(n,1);
 x = zeros(n,1);
 A=[1 -1 0 0 0 0 0 0 1 0;0 0 1 -1 0 0 0 0 0 -1;0 1 -1 0 0 1 0 0 0 0;0 0 0 1 -1 -1 0 0 0 0;0 0 0 0 1 0 0 0 -1 0; 0 0 0 100*j/(50*j-2) 0 1 0 0 0 0;0 0 0 100*j/(50*j-2) 0 0 -1 0 0 0 ; 0 0 0 100*j/(50*j-2) 0 0 0 0 (1+10*j) 0 ;0 0 0 0 0 0 0 1 0 0;0 0 0 0 0 0 0 0 0 14];
 B=[sqrt(2)*(1+j); -sqrt(2)*(1+j);j;0;j;3*sqrt(2)/2*(1+j);3*sqrt(2)/2*(1+j)-4*j;5+3*sqrt(2)/2*(1+j)-4*j;5+3*sqrt(2)/2*(1+j);3*sqrt(2)/2*(1+j)+3*sqrt(2)*(1+j)+5];
 x = A\B;
% pentru calculul bilantului
 S_c = 100*j/(50*j-2)*(abs(x(4))^2)+1*(abs(x(6))^2)+(abs(x(10))^2)+(1+10*j)*(abs(x(9))^2);
 S_g = 3*sqrt(2)*(1+j)*x(1)'+3*sqrt(2)*(1+j)/2*x(3)' +5*x(2)'-4*j*x(5)'-j*x(7)'-sqrt(2)*(1+j)*x(8)';
% pentru graficul ce arata evolutia in timp
J8 = sqrt(2)*(1+j);
time = 0:0.001:0.3;
J8_plot = abs(J8)*sqrt(2)*sin(100*pi.*time + angle(J8));
plot(time,J8_plot);
