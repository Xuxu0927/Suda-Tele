function fc=sy1(x,y)
d=sqrt(x^2+y^2);
if d<=80
    fc='可以与该目标节点通信';
else
    fc='不可以与该目标节点通信';
end
end