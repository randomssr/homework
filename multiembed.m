function out = multiembed(cover,secret,gray)
imcover = imread(cover);
imcoverR = imcover(:,:,1);
imcoverG = imcover(:,:,2);
imcoverB = imcover(:,:,3);
imsecret = imread(secret);
if(gray == 0)
    imgray = rgb2gray(imsecret);
else
    imgray = imsecret;
end
[r1,c1] = size(imcover(:,:,1));
[r2,c2] = size(imgray)
len(128) = 0;
r2b = de2bi(r2);
c2b = de2bi(c2);
len(1:length(r2b)) = r2b;
len(65:64+length(c2b)) = c2b
len2 = reshape(len,8,16);
len2 = len2'
len3 = bi2de(logical(len2))


if (r1*c1 < r2*c2+128)
    error('too many message');
end
out = imcover;
outR = out(:,:,1);
outG = out(:,:,2);
outB = out(:,:,3);
for i = 1:16
    tempc = bitand(imcoverR(i),248);
    temps = bitshift(len3(i),-5);
    outR(i) = bitor(tempc,temps);
        
    tempc = bitand(imcoverG(i),248);
    temps = bitand(len3(i),28);
    temps2 = bitshift(temps,-2);
    outG(i) = bitor(tempc,temps2);
    
    tempc = bitand(imcoverB(i),252);
    temps = bitand(len3(i),3);
    outB(i) = bitor(tempc,temps);
end
for i = 1:c2*r2
    tempc = bitand(imcoverR(i+16),248);
    temps = bitshift(imgray(i),-5);
    outR(i+16) = bitor(tempc,temps);
    
    tempc = bitand(imcoverG(i+16),248);
    temps = bitand(imgray(i),28);
    temps2 = bitshift(temps,-2);
    outG(i+16) = bitor(tempc,temps2);
    
    tempc = bitand(imcoverB(i+16),252);
    temps = bitand(imgray(i),3);
    outB(i+16) = bitor(tempc,temps);
end
out(:,:,1) = outR;
out(:,:,2) = outG;
out(:,:,3) = outB;
imwrite(out,'stago1.bmp');                    
end  
    
