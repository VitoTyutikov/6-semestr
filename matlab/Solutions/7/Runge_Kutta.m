function [t, y] = Runge_Kutta(f, y0, x_range , h)
    t=x_range(1):h:x_range(2);
    n = length(y0);
    y = zeros(n, length(t));
    y(:,1) = y0;
    for i = 1:(n-1)
        k1=f(t(i),y(:,i));
        k2=f(t(i)+h/3,y(:,i)+h/3*k1);
        k3=f(t(i)+2*h/3,y(:,i)+2*h/3*k2);
        y(:,i+1)=y(:,i)+h*(k1+3*k3)/4;
    end
end 