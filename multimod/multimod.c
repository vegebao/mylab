#include <stdint.h>

uint64_t mod(uint64_t a, uint64_t b)
{
    while(a>=b)
	{
		uint64_t ta=b;
		while(ta <= a-ta)
		{
			ta=ta<<1;
		}
		a=a-ta;
	}
	return a;
}

uint64_t power_of_2(uint64_t a)
{
	uint64_t it=1;
  if(a==0)
		return it;
	else
	{
		uint64_t k=it<<a;
		it = k;
		return it;
	}
}

uint64_t mod_add(uint64_t a, uint64_t b, uint64_t m)
{
    uint64_t rest=power_of_2(64)-a-1;
	if(rest<b)
	{
		uint64_t c=b-1-rest;
		uint64_t x=mod(c,m);
		uint64_t y=mod(-1ULL,m);
		return mod_add(x+1,y,m);
	}
	else{
		return mod(a+b, m);
	}
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
    unsigned char a_bit[64];	
	uint64_t c=mod(a,m);
    for(int i=0;i<64;i++)
	{
    a_bit[i]=(c>>i)&1;
	}
	uint64_t base=0;
    for(int i=0;i<64;i++)
	{
		uint64_t d=mod(b,m);
		if(a_bit[i]==1)
		{
			for(int k=0;k<i;k++)
			{
				d=mod_add(d,d,m);
			}
		}
		base=mod_add(base,d,m);

	}
	/*if(a_bit[63]==1)
	{
		uint64_t times=mod(power_of_2(63), m);
		for(int i=0;i<times;i++)
		{
			base=mod_add(base,d,m);
		}
	}*/

	return base; //(a*b)%m;
}
