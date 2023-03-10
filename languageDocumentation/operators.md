
# Operators and Specials

This page documents operators and specials in OstraCode.

## Operators

Supose that `$num1` and `$num2` are expressions with constraint type `numT`. The constraint type of the following expressions is also `numT`:

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

The plus operator (`+`) may also be used for string concatenation. The expression `$str1 + $str2` returns `$str1` concatenated with `$str2`. `$str1` and `$str2` are expressions with constraint type `(*ToStringT)`, and the constraint type of `$str1 + $str2` is `strT`.

Supose that `$num1` and `$num2` are expressions with constraint type `numT`. The constraint type of the following expressions is `boolT`:

* `$num1 #lt $num2` = Whether `$num1` is less than `$num2`
* `$num1 #gt $num2` = Whether `$num1` is greater than `$num2`
* `$num1 #lte $num2` = Whether `$num1` is less than or equal to `$num2`
* `$num1 #gte $num2` = Whether `$num1` is greater than or equal to `$num2`

OstraCode has the following equality operators:

* `$item1 #eq $item2` = Whether `$item1` is equal to `$item2`
    * `$item1` and `$item2` are expressions with constraint type `itemT`
    * The constraint type of `$item1 #eq $item2` is `boolT`
* `$item1 #neq $item2` = Whether `$item1` is not equal to `$item2`
    * `$item1` and `$item2` are expressions with constraint type `itemT`
    * The constraint type of `$item1 #neq $item2` is `boolT`

Supose that `$bool1` and `$bool2` are expressions with constraint type `boolT`. The constraint type of the following expressions is also `boolT`:

* `!$bool1` = Logical NOT of `$bool1`
* `$bool1 || $bool2` = Logical OR of `$bool1` and `$bool2`
* `$bool1 && $bool2` = Logical AND of `$bool1` and `$bool2`
* `$bool1 ^^ $bool2` = Logical XOR of `$bool1` and `$bool2`

OstraCode has the following member access operators:

* `$item.$identifier` = Member of discerned feature in `$item` with name `$identifier`
    * `$item` is an expression with constraint type `itemT`
    * `$identifier` is an identifier
* `$module.$identifier` = Member of `$module` with name `$identifier`
    * `$module` is an imported module
    * `$identifier` is an identifier
* `$collection @ $subscript` = Member of `$collection` located at `$subscript`
    * `$collection` is an expression with constraint type `(*SubscriptGetT($subscriptType, $memberType))`
    * `$subscript` is an expression with constraint type `$subscriptType`
    * The constraint type of `$collection @ $subscript` is `$memberType`

OstraCode has the following type operators:

* `$item:<$type>` = Cast of `$item` to `$type`
    * `$item` is an expression with constraint type `itemT`
    * `$type` is an expression with constraint type `typeT`
    * The constraint type of `$item:<$type>` is `$type`
* `$item::<$type>` = Force cast of `$item` to `$type`
    * `$item` is an expression with constraint type `itemT`
    * `$type` is an expression with constraint type `typeT`
    * The constraint type of `$item::<$type>` is `$type`
* `$type1 | $type2` = Union of `$type1` and `$type2`
    * `$type1` and `$type2` are expressions with constraint type `typeT`
    * The constraint type of `$type1 | $type2` is also `typeT`
* `$type1 & $type2` = Intersection of `$type1` and `$type2`
    * `$type1` and `$type2` are expressions with constraint type `typeT`
    * The constraint type of `$type1 & $type2` is also `typeT`

The expression `$ref = $item` assigns the return item of expression `$item` to reference `$ref`. The constraint type of `$item` must conform to the constraint type of `$ref`. `=` may be combined with various binary operators to assign the result of an operation between `$ref` and `$expr`. For example, `$ref += $item` assigns `$ref + $item` to `$ref`. The list of all composite assignment operators is below:

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

### Method Special:

```
methodT [$attrs]
```

Creates a method type whose signature is described by `$attrs`.

### Await Special:

```
await ($promise)
```

If the return item of `$promise` conforms to `(*ThenT)`, the `await` special blocks execution until `$promise` resolves. The `await` special is only valid within asynchronous functions or at the top level of each module.

### Interface Special:

```
interfaceT [$attrs]
```

Creates an interface type whose fields and methods are described by `$attrs`.

### Feature Specials:

```
feature [$attrs]
```

Creates a feature value whose fields and methods are described by `$attrs`. The output feature has a discerned type.

```
featureT [$attrs]
```

Creates a feature type whose field types and method signatures are described by `$attrs`. The output type is not discerned.

### Bundle Specials:

```
bundle [$attrs]
```

Creates a bundle value whose factors are described by `$attrs`.

```
bundleT [$attrs]
```

Creates a bundle type whose factor types are described by `$attrs`.

### Object Specials:

```
obj ($factor)
```

Creates an object value whose factor is `$factor`.

```
objT ($factorType)
```

Creates an object type whose factor type is `$factorType`.

### Discern Special:

```
discern ($feature)
```

Accepts feature value `$feature`, and returns the same feature with a discerned type.
