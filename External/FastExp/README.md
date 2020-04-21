# fastexp

fastexp is a small C++ template library that implements
fast, vectorizable approximations of the exponential function.

## Warning

The functions provided here are approximations with limited
validity. Thus always check if they suit your usecase before
using them.

Moreover, these implementation contain no safeguards against
overflows so it is up to the user to ensure the arguments are
in the right range.

## Approximations

A formal description of the two approximations available can be
found [here](spfrnd.de/posts/2018-03-10-fast-exponential.html).

### Truncated Product

This approximation expresses the exponential as an infinite
product which is evaluated up to a certain threshold. The
computation of the product is implemented using exponentiation
by squaring.

The plot below gives the error for different degrees
of the approximation of different argument ranges. This
approximation should work well when:

- The argument x is small and/or positive
- An approximation that is limited from above by the true
  exponential is desired

![img](./plots/fastexp_product_1.png)

### IEEE Manipulation

This approximation was proposed by [Schraudolph](https://www.mitpressjournals.org/doi/abs/10.1162/089976699300016467) and refined by [Malossi et al.](https://www.researchgate.net/publication/272178514_Fast_Exponential_Computation_on_SIMD_Architectures) and exploits
the definition of the IEE 754 floating point format to approximate the
exponential. The plot below displays the relative errors obtained using
the approximation. This approximation should work well if

- The absolute value of the argument x is larger than 1

![img](./plots/fastexp_schraudolph_1.png)

## Performance

So far, I was only able to run the benchmark   on an
Intel Core i7-2640M CPU (2.80GHz). The plots below show
compute times for different approximations compared
to the standard library implementations. The benchmark
scenario is the computation of the exponential function
to an array containing 100 million elements.

### Single Precision

![img](./plots/fastexp_times_single.png)

### Double Precision

![img](./plots/fastexp_times_double.png)

