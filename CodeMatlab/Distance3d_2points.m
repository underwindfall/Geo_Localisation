function [d] = Distance3d_2points(X,Y,Z,XL,YL,ZL)
d=sqrt((X-XL)^2+(Y-YL)^2+(Z-ZL)^2);
end