
# Built-In Constants

This page documents built-in constants in OstraCode.

## Built-In Items

OstraCode includes the following built-in items:

* `null` = Null value
* `true` = True boolean value
* `false` = False boolean value
* `itemT`, `typeT`, `valueT`, `nullT`, `boolT`, `intT`, `floatT`, `numT`, `strT`, `symbolT`, `factorT`, and `moduleT` = Types as described earlier in this documentation
* `this` = Current object whose factor type is specified by the `thisFactor` statement
* `self` = Current object whose factor type is the parent feature type

## Built-In Functions

OstraCode has the following built-in functions:

* `print($item)` prints item `$item` to standard output.
* `symbol($name)` creates a new symbol. Every symbol is globally unique. `$name` is optional, and must be a string if provided. `$name` is used in the `toString` representation of the symbol, but otherwise does not affect the uniqueness of the symbol.
* `getType($item)` returns the type of item `$item` known during flow-phase.
* `nominalT($type)` creates a subtype of type `$type`. The subtype defines the same data structure as `$type`, but is distinguished through the nominal type system.
* `literalT($item)` creates a type which only contains items equal to `$item`. For example, `literalT(16)` is the type of all numbers which are equal to 16.

## Built-In Interfaces

OstraCode has the following built-in interfaces:

### To String Interface:

```
prep ToStringT = <interfaceT [
    sharedFields [
        toString (methodT [
            returns (strT)
        ]) [public, vis (2)]
    ]
]>
```

The `toString` method converts the parent item to a string. Every non-object item implements `ToStringT`. The `ToStringT` interface interoperates with the string concatenation operator (`;`).

### Length Interface:

```
prep LengthT = <interfaceT [
    itemFields [
        length (intT) [public, vis (2)]
    ]
]>
```

The `length` field stores the number of members in the parent item. Strings, lists, and dictionaries implement `LengthT`.

### Conforms To Interface:

```
prep ConformsToT = <interfaceT [
    sharedFields [
        conformsTo (methodT [
            args [type (typeT)]
            returns (boolT)
        ]) [public, vis (2)]
    ]
]>
```

The `conformsTo` method determines whether the parent item conforms to the given type. Every type implements `ConformsToT`.

### Subscript Get Interface:

```
prep SubscriptGetT = <genericT [
    args [subscriptT <typeT>, memberT = (itemT)]
] (interfaceT [
    sharedFields [
        getMember (methodT [
            args [subscript (subscriptT)]
            returns (memberT)
        ]) [public, vis (2)]
    ]
])>
```

The `getMember` method retrieves the member located at `subscript`. Strings, lists, and dictionaries implement `SubscriptGetT`. The `SubscriptGetT` interface interoperates with the subscript operator (`@`).

### Subscript Set Interface:

```
prep SubscriptSetT = <genericT [
    args [subscriptT <typeT>, memberT = (itemT)]
] (interfaceT [
    sharedFields [
        setMember (methodT [
            args [subscript (subscriptT), item (memberT)]
        ]) [public, vis (2)]
    ]
])>
```

The `setMember` method modifies the member located at `subscript`. Lists and dictionaries implement `SubscriptSetT`. The `SubscriptSetT` interface interoperates with the subscript operator (`@`).

### Subscript Delete Interface:

```
prep SubscriptDeleteT = <genericT [
    args [subscriptT <typeT>]
] (interfaceT [
    sharedFields [
        deleteMember (methodT [
            args [subscript (subscriptT)]
        ]) [public, vis (2)]
    ]
])>
```

The `deleteMember` method deletes the member located at `subscript`. Lists and dictionaries implement `SubscriptDeleteT`.

### Iterator Interface:

```
prep IteratorT = <genericT [
    args [memberT = (itemT)]
] (interfaceT [
    sharedFields [
        getNext (methodT [
            returns (memberT)
        ]) [public, vis (2)]
        isFinished (methodT [
            returns (boolT)
        ]) [public, vis (2)]
    ]
])>
```

The `getNext` method retrieves the next member in the iteration. The `isFinished` method returns whether the iteration has finished. The `IteratorT` interface interoperates with the `IterableT` interface.

### Iterable Interface:

```
prep IterableT = <genericT [
    args [memberT = (itemT)]
] (interfaceT [
    sharedFields [
        createIterator (methodT [
            returns (*IteratorT+:(memberT))
        ]) [public, vis (2)]
    ]
])>
```

The `createIterator` method creates a new iterator which iterates over members in the parent item. Strings, lists, and dictionaries implement `IterableT`. The `IterableT` interface interoperates with the `for` statement.

### Error Message Interface:

```
prep ErrorMessageT = <interfaceT [
    itemFields [
        message (strT) [public, vis (2)]
    ]
]>
```

The `message` field stores an error message. The `Error` factor implements `ErrorMessageT`.

## Built-In Factors

OstraCode has the following built-in factors:

### Error Factor:

`Error` stores an error. `Error` implements the `ToStringT` and `ErrorMessageT` interfaces. `Error` also provides the following methods:

* `$error.init($message)` initializes the error with string message `$message`.

## Built-In Modules

OstraCode has the following built-in modules:

### Math Utils:

The `mathUtils` module exports the following members:

* `mathUtils@random()` returns a random floating-point number between 0 and 1.


