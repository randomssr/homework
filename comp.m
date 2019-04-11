function out = comp(a,b)
out = 0;
for i = 1:3
    if(a(i)>b(i))
        out = 1;
        break;
    elseif(a(i)<b(i))
        out = 0;
        break;
    end
end