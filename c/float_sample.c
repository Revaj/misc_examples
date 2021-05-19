#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#define asreal(x) (*((float *) &x))

typedef uint32_t real;

inline int extract_sign(real from)
{
    return (from & 0x80000000) != 0;
}

inline int extract_exponent(real from)
{
    return ((from >> 23) & 0xff) - 127;
}

inline int extract_mantissa(real from)
{
    if ((from & 0x7ffffff) == 0)
	return 0;
    return ((from & 0x7FFFFF) | 0x800000);
}

int extract_sign(real from);
int extract_exponent(real from);
int extract_mantissa(real from);

void shift_and_round(uint32_t *val_to_shift, int bits_to_shift)
{
    static unsigned masks[24] =
    {
	0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f,
	0xff, 0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff,
	0xffff, 0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 0x1fffff, 0x3fffff,
	0x7fffff
    };

    static unsigned ho_masks[24] =
    {
	0,
	1, 2, 4, 0x8, 0x10, 0x20, 0x40, 0x80,
	0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
	0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000
    };

    int shifted_out;
    assert(bits_to_shift <= 23);

    shifted_out = *val_to_shift & masks[bits_to_shift];

    *val_to_shift = *val_to_shift >> bits_to_shift;

    if (shifted_out > ho_masks[bits_to_shift])
    {
	*val_to_shift = *val_to_shift + 1;
    }
    else if (shifted_out == ho_masks[bits_to_shift])
    {
	*val_to_shift = val_to_shift + (*val_to_shift & 1);
    }
}

inline real pack_fp(int sign, int exponent, int mantissa)
{
    return
	(real)
	(
		(sign << 31)
	    |	((exponent + 127) << 23)
	    |	(mantissa & 0x7fffff)
	);
}

real pack_fp(int sign, int exponent, int mantissa);

void fpadd(real left, real right, real *dest);
void fpsub(real left, real right, real *dest);

void fpsub(real left, real right, real *dest)
{
    right = right ^ 0x80000000;
    fpadd(left, right, dest);   
}

void fpadd(real left, real right, real *dest)
{
    int l_exponent;
    uint32_t l_mantissa;
    int l_sign;

    int r_exponent;
    uint32_t r_mantissa;
    int r_sign;

    int d_exponent;
    uint32_t d_mantissa;
    int d_sign;

    l_exponent = extract_exponent(left);
    l_mantissa = extract_mantissa(left);
    l_sign = extract_sign(left);

    r_exponent = extract_exponent(right);
    r_mantissa = extract_mantissa(right);
    r_sign = extract_sign(right);

    if (l_exponent == 127)
    {
	if (l_mantissa == 0)
	{
	    if (r_exponent == 127)
	    {
		if (r_mantissa == 0)
		{
		    if( l_sign == r_sign)
		    {
			*dest = right;
		    }
		    else
		    {
			*dest = 0x7fc00000;
		    }
		}
		else
		{
		    *dest = right;
		}
	    }
	}
	else
	{
	    *dest = left;
	}
	return;
    }
    else if (r_exponent == 127)
    {
	*dest = right;
	return;
    }

    d_exponent = r_exponent;
    if (r_exponent > l_exponent)
    {
	shift_and_round(&l_mantissa, (r_exponent - l_exponent));
    }
    else if (r_exponent < l_exponent)
    {
	shift_and_round(&r_mantissa, (l_exponent - r_exponent));
	d_exponent = l_exponent;
    }

    if (r_sign ^ l_sign)
    {
	if (l_mantissa > r_mantissa)
	{
	    d_mantissa = l_mantissa - r_mantissa;
	    d_sign = l_sign;
	}
	else
	{
	    d_mantissa = r_mantissa - l_mantissa;
	    d_sign = r_sign;
	}
    }
    else
    {
	d_sign = l_sign;
	d_mantissa = l_mantissa + r_mantissa;
    }

    if (d_mantissa >= 0x1000000)
    {
	shift_and_round(&d_mantissa, 1);
	++d_exponent;
    }
    else
    {
	if (d_mantissa != 0)
	{
	    while((d_mantissa < 0x800000) && (d_exponent > -127))
	    {
		d_mantissa = d_mantissa << 1;

		--d_exponent;
	    }
	}
	else
	{
	    d_sign = 0;
	    d_exponent = 0;
	}
    }

    *dest = pack_fp(d_sign, d_exponent, d_mantissa);
}

int main()
{
    real l, r, d;
    asreal(l) = 1.0;
    asreal(r) = 2.0;

    fpadd(l, r, &d);
    printf("dest, = %x\n", d);
    printf("dest, = %12E\n", asreal(d));

    l = d;
    asreal(r) = 4.0;
    fpsub(l, r, &d);
    printf("dest2 = %x\n", d);
    printf("dest2 = %12E\n", asreal(d));

    return 0;
}
