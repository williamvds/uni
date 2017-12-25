double x    = x + x
quadruple x = double (double x)

smallest x y    = if x < y then x else y
largest x y     = if x > y then x else y

diff x y    = l - s
            where
                l = largest x y
                s = smallest x y
