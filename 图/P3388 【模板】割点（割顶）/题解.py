#没通过，不知道哪里错了
#题目P3388 【模板】割点（割顶）
#链接：https://www.luogu.com.cn/record/38344432
n, m = [int(i) for i in input().split()]
dfn = [0 for i in range(n+1)]
low = [0 for i in range(n+1)]
head = [0] * (n+1)
nex = [0] * (m * 2 + 100)
to = [0] * (m * 2 +100)
cnt = 0
root = 0
def add(a,b):
    global cnt
    cnt += 1
    to[cnt] = b
    nex[cnt] = head[a]
    head[a] = cnt
    cnt += 1
    to[cnt] = a
    nex[cnt] = head[b]
    head[b] = cnt
for i in range(m):
    a, b = [int(j) for j in input().split()]
    add(a,b)
cnt = 0
dian = set()
def tarjan(cur):
    global root
    global cnt
    cnt += 1
    dfn[cur] = cnt
    low[cur] = cnt
    i = head[cur]
    son = 0
    while i:
        want = to[i]
        if not dfn[want]:
            son += 1
            tarjan(want)
            low[cur] = min(low[cur],low[want])
            if (root==cur and son > 1) or (root != cur and low[want] >= dfn[cur]):
                dian.add(cur)
        else:
            low[cur] = min(low[cur],dfn[want])

        i = nex[i]
        
for i in range(1,n+1):
    if not dfn[i]:
        root = i
        tarjan(i)
print(len(dian))
dian = list(dian)
dian.sort(key=lambda a:a)
#print(" ".join(str(i) for i in dian))
for i in range(len(dian)):
    if i:
        print(" ",dian[i],sep="",end="")
    else:
        print(dian[i],end="")

    