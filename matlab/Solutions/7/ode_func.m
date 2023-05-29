function yder = ode_func(t,y,e,a,g)
    yder=zeros(2,1);
    yder(1)=(1-e*y(1))*y(1)-y(1)*y(2)/(1+a*y(1));
    yder(2)=g*(y(1)/(1+a*y(1))-1)*y(2);
end