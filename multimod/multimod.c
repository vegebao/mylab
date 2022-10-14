#include <stdint.h>

uint64_t mod(uint64_t a, uint64_t b)
{
  while(a>b)
	{
		a=a-b;
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
		for(int i=0;i<a;i++)
		{
			it=it*2;
		}
		return it;
	}
}

uint64_t mod_add(uint64_t a, uint64_t b, uint64_t m)
{
  uint64_t rest=power_of_2(32)-a;
	if(rest>=b)
	{
		uint64_t c=a+b;
		uint64_t x=mod(c,m);
		uint64_t y=mod(power_of_2(32),m);
		return x+y;
	}
	else{
		return mod(a+b,m);
	}
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  unsigned char[64] a_bit;
	unsigned char[64] b_bit;
	uint64_t c=mod(a,m);
	uint64_t d=mod(b,m);
  for(int i=0;i<64;i++)
	{
    a_bit[i]=(c>>i)&1;
		b_bit[i]=(d>>i)&1;
	}
	uint64_t base=0;
  for(int i=0;i<64;i++)
	{
		if(a_bit[i]==1)
		{
			uint64_t times=power_of_2(i);
			for(int i=0;i<times;i++)
			{
				base=mod_add(base,b,m);
			}
		}

	}


	return base
}
