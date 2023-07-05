#include <iostream>

int a[900][3000];
int b[900][3000];

int main()
{
    int n, m, l;
    std::cin >> n >> m >> l;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < l; i++)
        {
              scanf("%d", &a[k][i]);
          }
    }
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < l; i++)
        {
             scanf("%d", &b[k][i]);
        }
    }
    int q=0;
    std::cin >> q;
    int t=0;
    int i=0,j=0;
    while( t < q )
    {
        scanf("%d%d", &i, &j);
        i--;
        j--;
        int left = 0, right = l - 1;
        int ans = 0;
        int mid = (right + left) / 2;

        while ( right - left > 1 )
        {
            int m = (right + left) / 2 + (right + left) % 2;

            if (a[i][m] < b[j][m])
            {
                left = m;
            }
            else
            {
                right = m;
            }
        }

        if (std::max(a[i][left], b[j][left]) < std::max(a[i][right], b[j][right])) m=left;
        else m=right;

        printf("%d\n", m+1);
        t++;
    }
}
