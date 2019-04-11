function [X2,map2] = hideSeek(cover,secret)
%cover coverimage palette image
%secret secret string
%bitlength  bits per char
%if some bit equals to 1,the index doesn't change;if some bit equals to
%0,the index will be larger
%parameters 
bitlength = 7;
if(nargin ~= 2 )
    error('Usage :hideSeek(im,map,msg,bitlength)');
end
[X,map] = imread(cover);
if(~isa(X,'double'))
    X = double(X)+1;%data index starts from 0;
end
% transfrom the color map matrix
if(length(map)>128)% at most 256
    tmp = ind2rgb(X,map);
    [X,map] = rgb2ind(tmp,128);
end
lenmap = length(map);
map2 = [map;map];

maxLen = prod(size(X));
secret1 = double(secret);% char -> ASCII
secret2 = de2bi(secret1,bitlength,2);% ASCII->bits
secret2 = secret2';
secretstr = secret2(:);
len = length(secretstr);%secret bits length
%transform the length to bits
len1 = zeros(1,64);
lenbit = de2bi(len);
len1(1:length(lenbit)) = lenbit;

if(len+64>maxLen)
    sprintf('Message bits length cannot greater than %d',maxLen-64);
    error('Message is too long!');
end
%embed the length of secret 
X2 = X;
for i = 1:64
    if(len1(i)==0)
        X2(i) = X(i)+lenmap;
    end
end
%embed the secret
for i = 65:64+len
    if(secretstr(i-64)==0)
        X2(i) = X(i)+lenmap;
    end
end
imwrite(X2,map2,'stago2.gif');
end