# Acca

Assessment of categorical causal assertions.

From the perspective of logic a statement x => y is equivalent to its
contrapositive ~y => ~x.

Acca assesses a simple assertion (a statement and its contrapositive) for
identifying potentially causal relationships. A statement of the form x => y is
scored as S(x => y) := prob(y | x) prob(~x | ~y) with the conditional
probabilities estimated from a set of data. A values of S near unity is viewed
as an indictor of a good candidate for a causally-related assertion.
