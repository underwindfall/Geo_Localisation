clear all

%Draw every point

%% Cas:sur la route
%calculate for variance and average

lat = xlsread('data/routelat.xls');
lon = xlsread('data/routelon.xls');
alt = xlsread('data/routealt.xls');

% % % avglat=mean(lat);
% % % avglon=mean(lon);
% % % avgalt=mean(alt);
avglat=lat(1);
avglon=lon(1);
avgalt=alt(1);

%transform geodetic to gencentric coordinates EST,NORD,HAUT
wgs84=wgs84Ellipsoid('meters');
[tmpx,tmpy,tmpz]=geodetic2ecef(wgs84,48.269424,4.067102,127.400001);
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

plot(XEast,YNorth,'*r');
xlabel('xEast') % x-axis label
ylabel('yNorth') % y-axis label
zlabel('zUp')   % z-axis labelhold on
title('variation ensemble','FontName','Times New Roman' ,'FontSize',10)
hold on
plot(normx,normy,'s','MarkerFaceColor','g','MarkerEdgeColor','k')



%% Cas:Sous les arbres
lat = xlsread('data/lesarbeslat.xls');
lon = xlsread('data/lesarbeslon.xls');
alt = xlsread('data/lesarbesalt.xls');

% % % avglat=mean(lat);
% % % avglon=mean(lon);
% % % avgalt=mean(alt);
avglat=lat(1);
avglon=lon(1);
avgalt=alt(1);

%transform geodetic to gencentric coordinates EST,NORD,HAUT
wgs84=wgs84Ellipsoid('meters');
[tmpx,tmpy,tmpz]=geodetic2ecef(wgs84,48.270034,4.066878,105.56678);
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

plot(XEast,YNorth,'.');
xlabel('xEast') % x-axis label
ylabel('yNorth') % y-axis label
zlabel('zUp')   % z-axis labelhold on
plot(normx,normy,'s','MarkerFaceColor','g','MarkerEdgeColor','k')

%% Cas: a cote des batiments
lat = xlsread('data/cotebatlat.xls');
lon = xlsread('data/cotebatlon.xls');
alt = xlsread('data/cotebatalt.xls');

% % % avglat=mean(lat);
% % % avglon=mean(lon);
% % % avgalt=mean(alt);
avglat=lat(1);
avglon=lon(1);
avgalt=alt(1);

%transform geodetic to gencentric coordinates EST,NORD,HAUT
wgs84=wgs84Ellipsoid('meters');
[tmpx,tmpy,tmpz]=geodetic2ecef(wgs84,48.270111,4.065598,130.333333);
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

plot(XEast,YNorth,'om');
xlabel('xEast') % x-axis label
ylabel('yNorth') % y-axis label
zlabel('zUp')   % z-axis labelhold on

plot(normx,normy,'s','MarkerFaceColor','g','MarkerEdgeColor','k')


%% Cas: a l'interieur des batiments
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

plot(XEast,YNorth,'+y');
xlabel('xEast') % x-axis label
ylabel('yNorth') % y-axis label
zlabel('zUp')   % z-axis labelhold on
plot(normx,normy,'s','MarkerFaceColor','g','MarkerEdgeColor','k')
legend('points observations sur la route','sample sur la route','points observations sous les arbres','sample sous les arbres','points observations a cote batiment','sample a cote batiment','points observations dans batiments','sample dans batiments')
hold off
