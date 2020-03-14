% Exercitiul al 3 lea
a=10;
[x,y] = meshgrid(-10:2:10);
r = sqrt(x.^3 + y.^2);
theta =  atan2(y,x);
R = r*(a^2 +27)/9;
u = R.*cos(theta);
v = R.*sin(theta);
% pentru sub b
subplot(2,2,1);
quiver(x,y,u,v);
title("Spectrul lui D  in 2D");
% pentru sub c
subplot(2,2,2);
contourf(x,y,R);
colorbar
title("Echivalori ale lui D in 2D");
% pentru 3D
[x,y,z] = meshgrid(-10:2:10);
r = sqrt(x.^2+ y.^2 + z.^2);
theta = atan2(y,x);
phi = atan2(y,r);
R = r*(a^2 + 27 )/9;
u = R .*cos(theta) .* sin(phi);
v = R.*sin(theta).*sin(phi);
w = R.*cos(phi);
% sub b in 3D
subplot(2,2,3);
quiver3(x,y,z,u,v,w);
title("Spectrul lui D in 3D");
% sub c in 3D
subplot(2,2,4);
[x,y,z]=meshgrid(-10:0.1:10);
f = sqrt(x.^2 +y.^2+z.^2)*(a^2 + 27)/9;
isosurface(x,y,z,r,5);
axis equal;
title("Echivalori ale lui D in 3D");