function [pks, loks]= local_max(x,min_dist)
    pks =[];
    loks=[];
    for i=2:length(x)-1
        if x(i) > x(i-1) && x(i) > x(i+1)
            if isempty(loks) || i - loks(end) >= min_dist
                pks(end+1)=x(i);
                loks(end+1) = i;
            end
        end
    end
end
