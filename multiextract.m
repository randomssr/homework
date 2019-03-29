function out = multiextract(stago)
im = imread(stago);
imR = im(:,:,1);
imG = im(:,:,2);
imB = im(:,:,3);
%[r1,c1] = size(imR);
len = uint8(zeros(16,1));
%out = uint8(zeros(r1,c1));
for i = 1:16
    temp1 = bitshift(imR(i),5);
    len(i) = bitor(len(i),temp1);
    temp1 = bitshift(imG(i),5);
    temp1 = bitshift(temp1,-3);
    len(i) = bitor(len(i),temp1);
    temp1 = bitand(imB(i),3);
    len(i) = bitor(len(i),temp1);
end
%len
%size(len)

len2 = zeros(16,8);
len1 = de2bi(uint8(len));
[r,c]= size(len1);
len2(1:r,1:c) = len1;
len3 = zeros(2,64);
len3(1,1:8) = len2(1,1:8);
len3(1,9:16) = len2(2,1:8);
len3(1,17:24) = len2(3,1:8);
len3(1,25:32) = len2(4,1:8);
len3(1,33:40) = len2(5,1:8);
len3(1,41:48) = len2(6,1:8);
len3(1,49:56) = len2(7,1:8);
len3(1,57:64) = len2(8,1:8);
len3(2,1:8) = len2(9,1:8);
len3(2,9:16) = len2(10,1:8);
len3(2,17:24) = len2(11,1:8);
len3(2,25:32) = len2(12,1:8);
len3(2,33:40) = len2(13,1:8);
len3(2,41:48) = len2(14,1:8);
len3(2,49:56) = len2(15,1:8);
len3(2,57:64) = len2(16,1:8);

%size(len1)
%len2 = len2(:);
%len2 = reshape(len2,2,64)
len3 = bi2de(len3);
r2 = len3(1);
c2 = len3(2);
out = uint8(zeros(r2,c2));
for i = 1:r2*c2
    temp1 = bitshift(imR(i+16),5);
    out(i) = bitor(out(i),temp1);
    temp1 = bitshift(imG(i+16),5);
    temp1 = bitshift(temp1,-3);
    out(i) = bitor(out(i),temp1);
    temp1 = bitand(imB(i+16),3);
    out(i) = bitor(out(i),temp1);
end
out = uint8(out);
imwrite(out,'secret1.bmp')
end