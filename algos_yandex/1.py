p,v,q,m=0,0,0,0

p, v = map(int, input().split())
q, m = map(int, input().split())

max_l=0
max_r=0
min_l=0
min_r=0

otv=0

if (max(p-v, p+v)>=max(q-m, q+m)):
    max_l=p-v
    max_r=p+v
    min_l=q-m
    min_r=q+m
else:
    max_l=q-m
    max_r=q+m
    min_l=p-v
    min_r=p+v


if(max_l<=min_l):
    otv=max_r-max_l+1
elif (min_r>=max_l):
    otv=max_r-min_l+1
else:
    otv=max_r-max_l+1
    otv+=min_r-min_l+1

print(otv)
