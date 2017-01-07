function [d] = Distance_2points(lat1,lon1,lat2,lon2)
R = 6378;
dlon = lon2 - lon1 ;
d=acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(dlon));
end