def get_k(ni,k_in_n, m):
    floors_before = (ni-1)//k_in_n
    entrance = floors_before//m + 1
    floor = floors_before%m + 1
    return entrance, floor


def check(k1, m, k2, p2, n2, k_in_n):
    entrance2, floor2 = get_k(k2, k_in_n, m)
    if entrance2 == p2 and floor2 == n2:
        return get_k(k1, k_in_n, m)
    return -1, -1


def main():
    k1, m, k2, p2, n2 = map(int, input().split())

    """
    k1 - квартира, наша
    m - количество этажей дома
    k2 - квартира, другого
    p2 - подъезд
    n2 - этаж
    """

    p1=-1
    n1=-1
    flag=False

    for k_in_n in range(1, 10**6+1):
        i_p1, i_n1 = check(k1, m, k2, p2, n2, k_in_n)
        if i_p1!=-1:
            flag=True
            if p1 == -1:
                p1, n1 = i_p1, i_n1
            elif p1 != i_p1 and p1!=0:
                p1=0
            elif n1 != i_n1 and n1!=0:
                n1=0
    if flag:
        print(p1, n1)
    else:
        print(-1, -1)

if __name__ == "__main__":
    main()