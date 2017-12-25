second1 xs      = head( tail xs )
second2 xs      = xs !! 1
second3 (_:x:_) = x

xor1 True  False = True
xor1 False True  = True
xor1 _     _     = False

xor2 x y =
  if x && (not y) || (not x)  && y
  then True
  else False

xor3 :: Bool -> Bool -> Bool
xor3 = (/=)

sumsqr n = sum[ n^2 | n <- [1..n] ]

grid n = [ (x,y) | x <- [0..n], y <- [0..n], x /= y ]

euclid x 0 = x
euclid x y 
  | x < 1 || y < 1 = 0
  | x == y = x
  | x < y  = euclid x ( y -x )
  | x > y  = euclid y ( x -y )

fastrev xs = rev xs []

rev []     ys = ys
rev (x:xs) ys = rev xs (x:ys)
