function out = hideSeekExtract(stago)
bitlength = 7;
[X,map] = imread(stago);
%extract the length of secret bits
len = zeros(1,64);
lenmap = length(map);
threshold = lenmap/2;
%extract the length number
for i = 1:64
    if(X(i)<=threshold)
        len(i) = 1;
    end
end
secretlen = bi2de(len);%the length of secret bits
%extract the secret bits
out = zeros(1,secretlen);
for i = 65:secretlen+64
    if(X(i)<=threshold)
        out(i-64) = 1;
    end
end
%from bits to string
outbi = reshape(out,bitlength,secretlen/bitlength);
outbi = outbi';
outde = bi2de(outbi);
outstr = char(outde);

out = outstr';

        
end