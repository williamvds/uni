e1 :: [Bool]
e1 = [True,False,True]

e2 :: [[Int]]
e2 = [[1,2],[3,4]]

e3 :: (Char,Bool)
e3 = ('a',True)

e4 :: [(String,Int)]
e4 = [("ABC",0)]

e5 :: (Num t) => t -> t
e5 n = n*2

e6 :: (Num t) => t -> t -> t
e6 x y = y + x

e7 :: (a,b) -> (b,a)
e7 (x,y) = (y,x)

e8 :: t -> (t,t)
e8 x = (x,x)

nums :: [Int]
nums = [1,2,3,4,5]

table :: [(Bool,Int)]
table = [(False,1),(True,2),(False,3)]

one :: t -> [t]
one x = [x]

three :: t -> (t,t,t)
three x = (x,x,x)

first :: a -> b -> a
first x y = x

mult :: (Num a) => a -> a -> a
mult m n = m*n

v3 :: ([Int], Int)
id :: t -> t
inc :: Num t => t -> t
