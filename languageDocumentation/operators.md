
# Operators and Specials

This page documents operators and specials in OstraCode.

## Operators

Supose that `$num1` and `$num2` are expressions with type `numT`. The type of the following expressions is also `numT`:

* `$num1 + $num2` = Sum of `$num1` and `$num2`
* `$num1 - $num2` = Difference between `$num1` and `$num2`
* `-$num1` = Negation of `$num1`
* `$num1 * $num2` = Product of `$num1` and `$num2`
* `$num1 / $num2` = Quotient when dividing `$num1` by `$num2`
* `$num1 % $num2` = Remainder when dividing `$num1` by `$num2`
* `$num1 ** $num2` = `$num1` raised to the power of `$num2`
* `~$num1` = Bitwise NOT of `$num1`
* `$num1 | $num2` = Bitwise OR of `$num1` and `$num2`
* `$num1 & $num2` = Bitwise AND of `$num1` and `$num2`
* `$num1 ^ $num2` = Bitwise XOR of `$num1` and `$num2`
* `$num1 #sl $num2` = `$num1` shifted left by `$num2` bits
* `$num1 #sr $num2` = `$num1` shifted right by `$num2` bits
* `$num1 #srz $num2` = `$num1` shifted right by `$num2` bits with zero fill

The plus operator (`+`) may also be used for string concatenation. The expression `$str1 + $str2` returns `$str1` concatenated with `$str2`. `$str1` and `$str2` are expressions with type `(*ToStringT)`, and the type of `$str1 + $str2` is `strT`.

Supose that `$num1` and `$num2` are expressions with type `numT`. The type of the following expressions is `boolT`:

* `$num1 #lt $num2` = Whether `$num1` is less than `$num2`
* `$num1 #gt $num2` = Whether `$num1` is greater than `$num2`
* `$num1 #lte $num2` = Whether `$num1` is less than or equal to `$num2`
* `$num1 #gte $num2` = Whether `$num1` is greater than or equal to `$num2`

OstraCode has the following equality operators:

* `$item1 #eq $item2` = Whether `$item1` is equal to `$item2`
    * `$item1` and `$item2` are expressions with type `itemT`
    * The type of `$item1 #eq $item2` is `boolT`
* `$item1 #neq $item2` = Whether `$item1` is not equal to `$item2`
    * `$item1` and `$item2` are expressions with type `itemT`
    * The type of `$item1 #neq $item2` is `boolT`

Supose that `$bool1` and `$bool2` are expressions with type `boolT`. The type of the following expressions is also `boolT`:

* `!$bool1` = Logical NOT of `$bool1`
* `$bool1 || $bool2` = Logical OR of `$bool1` and `$bool2`
* `$bool1 && $bool2` = Logical AND of `$bool1` and `$bool2`
* `$bool1 ^^ $bool2` = Logical XOR of `$bool1` and `$bool2`

OstraCode has the following member access operators:

* `$item.$identifier` = Field of feature in `$item` with name `$identifier`
    * `$item` is an expression with type `itemT`
    * `$identifier` is an identifier
* `$module@$identifier` = Member of `$module` with name `$identifier`
    * `$module` is an expression with type `moduleT`
    * `$identifier` is an identifier
* `$collection@$identifier` = Member of `$collection` with name `$identifier`
    * `$collection` is an expression with type `(*SubscriptGetT+:(strT, $memberType))`
    * `$identifier` is an identifier
    * The type of `$collection@$identifier` is `$memberType`
* `$collection@($subscript)` = Member of `$collection` located at `$subscript`
    * `$collection` is an expression with type `(*SubscriptGetT+:($subscriptType, $memberType))`
    * `$subscript` is an expression with type `$subscriptType`
    * The type of `$collection@($subscript)` is `$memberType`

OstraCode has the following type operators:

* `$item:<$type>` = Cast of `$item` to `$type`
    * `$item` is an expression with type `itemT`
    * `$type` is an expression with type `typeT`
    * The type of `$item:<$type>` is `$type`
* `$item::<$type>` = Force cast of `$item` to `$type`
    * `$item` is an expression with type `itemT`
    * `$type` is an expression with type `typeT`
    * The type of `$item::<$type>` is `$type`
* `$type1 | $type2` = Union of `$type1` and `$type2`
    * `$type1` and `$type2` are expressions with type `typeT`
    * The type of `$type1 | $type2` is also `typeT`
* `$type1 & $type2` = Intersection of `$type1` and `$type2`
    * `$type1` and `$type2` are expressions with type `typeT`
    * The type of `$type1 & $type2` is also `typeT`

Generic items may be qualified with the `+:` operator:

* `$generic+:<$args>` = Qualification of `$generic` with `$args`
    * `$generic` is an expression with type `genericT`
    * `<$args>` is a sequence of expressions with type `itemT`
    * The type of `$generic+:<$args>` depends on the generic definition of `$generic` and the items returned by `<$args>`
* `$type+:($args)` = Qualification of `$type` with `$args`
    * `$type` is an expression with type `<?genericT>`
    * `($args)` is a sequence of expressions with type `itemT`
    * The type of `$type+:($args)` depends on the generic definition of `$type`

The expression `$ref = $item` assigns the return item of expression `$item` to reference `$ref`. The type of `$item` must conform to the type of `$ref`. `=` may be combined with various binary operators to assign the result of an operation between `$ref` and `$expr`. For example, `$ref += $item` assigns `$ref + $item` to `$ref`. The list of all composite assignment operators is below:

* `+=`, `-=`, `*=`, `/=`, `%=`, and `**=` perform assignment with arithmetic operation.
* `|=`, `&=`, and `^=` perform assignment with bitwise operation.
* `||=`, `&&=`, and `^^=` perform assignment with logical operation.
* `#sl=`, `#sr=`, and `#srz=` perform assignment with bitshift.

## Specials

OstraCode has the following specials:

### List Specials:

```
list [$attrs] ($elems)
```

Creates a list value whose elements are `$elems`. If `($elems)` is excluded, `list` creates an empty list.

```
listT [$attrs] ($elemTypes)
```

Creates a list type whose element types are `$elemTypes`. If `($elemTypes)` is excluded, then element types are determined by the `elemType` attribute statement.

### Dictionary Specials:

```
dict [$attrs]
```

Creates a dictionary value whose fields are described by `$attrs`.

```
dictT [$attrs]
```

Creates a dictionary type whose field types are described by `$attrs`.

### Function Specials:

```
func [$attrs] {$body}
```

Creates a function value whose signature is described by `$attrs`, and whose behavior is determined by `$body`.

```
funcT [$attrs]
```

Creates a function type whose signature is described by `$attrs`.

### Method Specials:

```
method [$attrs] {$body}
```

Creates a method value whose signature is described by `$attrs`, and whose behavior is determined by `$body`.

```
methodT [$attrs]
```

Creates a method type whose signature is described by `$attrs`.

### Interface Special:

```
interfaceT [$attrs]
```

Creates an interface type whose field types are described by `$attrs`.

### Feature Specials:

```
feature [$attrs]
```

Creates a feature value whose fields are described by `$attrs`. The feature value will have a discerned type.

```
featureT [$attrs]
```

Creates a feature type whose field types are described by `$attrs`. The feature type will not be discerned.

### Bundle Specials:

```
bundle [$attrs]
```

Creates a bundle value whose factors are determined by `$attrs`.

```
bundleT [$attrs]
```

Creates a bundle type whose factor types are determined by `$attrs`.

### Object Specials:

```
obj ($factor)
```

Creates an object value whose factor is `$factor`.

```
objT ($factorType)
```

Creates an object type whose factor type is `$factorType`.

### Generic Specials:

```
generic [$attrs] ($item)
```

Returns `$item` as a generic item which may be qualified with arguments described by `$attrs`. The argument variables of the generic are prep-grade.

```
genericT [$attrs] ($type)
```

Returns `$type` as a generic type which may be qualified with arguments described by `$attrs`. The argument variables of the generic are flow-grade. If `($type)` is excluded, then `genericT` returns `itemT` as a generic type.

### Module Special:

```
moduleT [$attrs]
```

Creates a module type whose member types are described by `$attrs`.

### Discern Special:

```
discern ($feature)
```

Returns `$feature` with a discerned type. The fields of a feature can only be accessed when the feature has a discerned type.


