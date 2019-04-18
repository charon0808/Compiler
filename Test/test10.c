#include <stdio.h>

int fun(long n, long *hw)
{
	long l, m = 0;
	long nn = n;
	while (nn != 0)
	{
		l = nn % 10;
		m = m + l;
		nn = nn / 10;
		if (nn != 0)
			m = 10 * m;
	}
	*hw = m;
	if (m == n)
		return 0;
	else
	{
		int count = fun(m + n, hw) + 1;
		if (count > 10000)
			return -1;
		else
			return count;
	}
}
int main()
{
	static long a = 0, b = 0, c = 0;
	long *p = &b;
	int flag = 1;
	scanf("%ld", &a);
	int count = fun(a, p);
	if (count == -1)
	{
		printf("error");
	}
	else
		return printf("%d,%d", *p, count);
}
