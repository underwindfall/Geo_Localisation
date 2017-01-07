clear all
%calculate for variance and average

lat = xlsread('data/dansbatimentlat.xls');
lon = xlsread('data/dansbatimentlon.xls');
alt = xlsread('data/dansbatimentalt.xls');

% % % avglat=mean(lat);
% % % avglon=mean(lon);
% % % avgalt=mean(alt);
avglat=lat(1);
avglon=lon(1);
avgalt=alt(1);

%transform geodetic to gencentric coordinates EST,NORD,HAUT
wgs84=wgs84Ellipsoid('meters');
[tmpx,tmpy,tmpz]=geodetic2ecef(wgs84,48.269494,4.0680,105.56678);
[normx,normy,normz]=ecef2enu(tmpx,tmpy,tmpz,avglat,avglon,avgalt,wgs84);
for i=1:1:3000
  [x,y,z]=geodetic2ecef(wgs84,lat(i),lon(i),alt(i));
  X(i)=x;
  Y(i)=y;
  Z(i)=z;
end
for i=1:1:3000
  [xEast,yNorth,zUp]=ecef2enu(X(i),Y(i),Z(i),avglat,avglon,avgalt,wgs84);
  XEast(i)=xEast;
  YNorth(i)=yNorth;
  ZUp(i)=zUp;
end

for i=1:1:3000
    distance(i)= Distance_2points(lat(i),lon(i),avglat, avglon);
    distance3d(i)=Distance3d_2points(XEast(i),YNorth(i),ZUp(i),XEast(1),YNorth(1),ZUp(1));
   
end


avg_distance = mean(distance);
var_distance = var(distance);
avg_distance3d = mean(distance3d);
var_distance3d = var(distance3d);

plot3(XEast,YNorth,ZUp,'.');
xlabel('xEast') % x-axis label
ylabel('yNorth') % y-axis label
zlabel('zUp')   % z-axis labelhold on
title('dans la baitment','FontName','Times New Roman' ,'FontSize',10)
hold on
plot3(normx,normy,normz,'s','MarkerFaceColor','g','MarkerEdgeColor','k')
hold off

