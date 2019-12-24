# Acca 0.3.0-dev0

Assessment of categorical causal assertions.

From the perspective of logic a statement x => y is equivalent to its
contrapositive ~y => ~x.

Acca assesses a simple assertion (a statement and its contrapositive) for
identifying potentially causal relationships. A statement of the form x => y is
scored as S(x => y) := prob(y | x) prob(~x | ~y) with the conditional
probabilities estimated from a set of data. A value of S near unity is viewed
as an indicator of a good candidate for a causally-related assertion.

## An example

Suppose we have four weeks of observations of the weather first thing in the
morning as well as the condition of the front lawn:

| Observe | Lawn dry | Lawn wet |
|---------|----------|----------|
| Cloudy  |     6    |     5    |
| Raining |     0    |     9    |
| Sunny   |     5    |     3    |

The file [rainy.txt](ex/rainy.txt) provides this data and demonstrates
Acca input. Lines beginning with # are treated as comments.

The lawn will be wet if it's raining, but it could be wet for other reasons
such as sprinklers, nighttime rain. Acca will attempt to discover the
relationship Raining => Lawn wet.
Acca will produce the output

     Tokenset x count 3, tokenset y count 2
     1.000000 1.000000 [9.000000 17.000000] x:is_raining => y:lawn_is_wet

reporting there were three categorical values of x (is\_cloudy, is\_raining, 
is\_sunny) in the data set and two of y (lawn\_is\_dry, lawn\_is\_wet), and
that it finds the plausible relationship is\_raining => lawn\_is\_wet.
