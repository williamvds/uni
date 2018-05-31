# Functors

```haskell
class Functor f where
  fmap :: (a -> b) -> f a -> f b
```

## Examples

### Maybe

```haskell
instance Functor Maybe where
  -- fmap :: (a -> b) -> Maybe a -> Maybe b
  fmap _ Nothing  = Nothing
  fmap g (Just x) = Just (g x)
```

### Lists

```haskell
instance Functor [] where
  -- fmap :: (a -> b) -> [a] -> [b]
  fmap = map
```
- Applies a function to all elements

## Laws
```haskell
fmap id      = id
fmap (g . h) = fmap g . fmap h
```
- 1st: `fmap` preserves the identity function
- 2nd: `fmap` preserves function composition


# Applicative Functors
- Allow mapping a function with any number of arguments, rather than just ones
with a single argument

```haskell
class Functor f => Applicative f where
  pure :: a -> f a
  (<*>) :: f (a -> b) -> f a -> f b
```

## Examples 

### Maybe

```haskell
instance Applicative Maybe where
  -- pure :: a -> Maybe a
  pure = Just
  -- (<*>) :: Maybe (a -> b) -> Maybe a -> Maybe b
  Nothing  <*> _   = Nothing
  (Just g) <*> mx  = fmap g mx

> pure (+1) <*> Just 1
Just 2
> pure (+) <*> Just 1 <*> Just 2
Just 3
> pure (+) <*> Nothing <*> Just 2
Nothing
```
- Supports _exceptional_ programming - applying pure functions to arguments
which may fail

### Lists
```haskell
instance Applicative [] where
  -- pure :: a -> [a]
  pure x = [x]
  -- (<*>) :: [a -> b] -> [a] -> [b]
  gs <*> xs = [g x | g <- gs, x <- xs]

> pure (+1) <*> [1,2,3]
[2,3,4]
> pure (+) <*> [1] <*> [2]
[3]
> pure (*) <*> [1,2] <*> [3,4]
[3,4,6,8]
```
-- Applicative style for lists takes a list of functions and a list of
arguments, applying each in turn and returning a list of all results

## Laws

```haskell
pure id <*> x 	= x
pure (g x) 		  = pure g <*> pure x
x <*> pure y 	  = pure (\g -> g y) <*> x
x <*> (y <*> z) = (pure (.) <*> x <*> y) <*> z
```
- 1st: `pure` preserves the identity function - applying `pure` to it gives
an applicative version of it
- 2nd: `pure` preserves function application - it distributes over normal
function application to give applicative application
- 3rd: When an effectful function is applied to a pure argument, the order
in which the components are evaluated doesn't matter
- 4th: (Compensating for types) `<*>` is associative

# Monads
Comes from a branch of mathematics called _branch theory_.
```haskell
class Applicative m => Monad m where
  (>>=) :: m a -> (a -> m b) -> mb
  return :: a -> ma
  return = pure
```

## Examples

### Maybe
```haskell
instance Monad Maybe where
  -- (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b
  Nothing  >>= f = Nothing
  (Just x) >>= f = f x
```

### Lists
```haskell
instance Monad [] where
  -- (>>=) :: [a] -> (a -> [b]) -> [b]
  [] >>= f = []
  xs >>= f = concat $ map f xs -- (map f xs) :: [[b]], use concat to flatten
           = [y | x <- xs, y <- f x]

> pairs [1, 2] [3, 4]
[(1, 3), (1, 4), (2, 3), (2, 4)]

-- The cartesian product of two lists
pairs :: [a] -> [b] -> [(a, b)]
pairs xs ys = do x <- xs
                 y <- ys
                 return (x,y)
            = xs >>= \x ->
              ys >>= \y ->
              return (x, y)
-- similar to list comprehension [(x, y) | x <- xs, y <- ys]
```

List comprehensions are useful only to lists, whereas the do notation is general

### State
```haskell
type State = ...
type ST = State -> State -- state transformer: take current state and return new
type ST a = State -> (a, State) -- typed state transformer, of what is returned

Char -> ST Int
= Char -> State -> (Int, State)
-- ST abstracts away the state from the function type

type ST a = State -> (a, State)

-- Needs to be data in order to make a class definition
newtype ST a = S(State -> (a, State))

-- Get rid of 'dummy' constructor
app (S st) s = st s

-- TODO create functor and applicative

instance Monad ST where
  -- return :: a -> ST a
  return x = S (\s -> (x, s))
  -- s is the only State available, x is of type a

  -- (>>=) :: ST a -> (a -> ST b) -> ST b
  st >> f = S (\s -> let (x, s') = app st s
                     in app (f x) s')
  -- state transformer applied to s, returning value x and new state s'
  -- apply f to x and s', returning two new values (eg names y and s'')
```
## Laws
```haskell
return x >>= f = f x
mx >>= return  = mx
```
- Link between `return` and `>>=`
- 1st: `return`ing a value and feeding it into a monadic function = applying
the function to the value
- 2nd: Feeding the result of a monadic computation into `return` is the same
as performing the computation
- `return` is the identity for `>>=`

```haskell
(mx >>= f) >>= g = mx >>= (\x -> (f x >>= g))
```
- (Compensating for binding) `>>=` is associative
