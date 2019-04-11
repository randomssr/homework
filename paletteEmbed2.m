function [X2,map2] = paletteEmbed2(cover,secret)
[X,map] = imread(cover);
X2 = X;
map2 = map;
%secret = [1 0 1 1 0 0 1];
[r1,c1] = size(X);
len1 = r1*c1;
[r2,c2] = size(map);
len2 = r2;
len3 = length(secret);
if(len3 *2 +7> len2)
    error('too much message');
end
%embed len3

msgasc = double(secret);
msgbi = de2bi(msgasc);
msgbi = msgbi';
msgbi = msgbi(:);
len3 = length(msgbi);
str1 = de2bi(len3,7,2);
str1 = str1';
str1 = str1(:);
%length(str1)
for i = 1:7
    if(((str1(i) == 1)&&(comp(map(2*i-1,:),map(2*i,:))== 0))||((str1(i) == 0)&&(comp(map(2*i-1,:),map(2*i,:))== 1)))
        map2(2*i-1,:)= map(2*i,:);
        map2(2*i,:) = map(2*i-1,:);
        for j = 1:len1
            if(X(j)+1 == 2*i-1)
                X2(j) = 2*i-1;
            end
            if(X(j)+1 == 2*i)
                X2(j) = 2*i-1-1;
            end
        end
    end
end
for i = 8:len3+7
    if(((msgbi(i-7) == 1)&&(comp(map(2*i-1,:),map(2*i,:))== 0))||((msgbi(i-7) == 0)&&(comp(map(2*i-1,:),map(2*i,:))== 1)))
        map2(2*i-1,:)= map(2*i,:);
        map2(2*i,:) = map(2*i-1,:);
        for j = 1:len1
            if(X(j)+1 == 2*i-1)
                X2(j) = 2*i-1;
            end
            if(X(j)+1 == 2*i)
                X2(j) = 2*i-1-1;
            end
        end
    end
end
imwrite(X2,map2,'stago1.gif');
