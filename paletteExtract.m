function out = paletteExtract(stago)
[index,color] = imread(stago);
len = length(color);

strlength = zeros(1,7);
for i = 1:7
    strlength(i) = comp(color(i*2-1,:),color(i*2,:));
end
%strlength
%strlength2 = reshape(strlength,7,1);
%strlength2 = strlength2';
strlength3 = bi2de(strlength);
out = zeros(1,strlength3);
for i = 8:7+strlength3
    out(i-7) = comp(color(i*2-1,:),color(i*2,:));
end
out1 = reshape(out,7,strlength3/7);
out2 = out1';
out3 = bi2de(out2);
out4 = char(out3);
out = out4';

end