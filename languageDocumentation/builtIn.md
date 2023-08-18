
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
    fields [
        length (intT) [public, vis (2)]
    ]
]>
```

The `length` field stores the number of members in the parent item. Buffers, strings, lists, and dictionaries implement `LengthT`.

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

The `getMember` method retrieves the member located at `subscript`. Buffers, strings, lists, and dictionaries implement `SubscriptGetT`. The `SubscriptGetT` interface interoperates with the subscript operator (`@`).

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

The `setMember` method modifies the member located at `subscript`. Buffers, lists, and dictionaries implement `SubscriptSetT`. The `SubscriptSetT` interface interoperates with the subscript operator (`@`).

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

The `deleteMember` method deletes the member located at `subscript`. Buffers, lists, and dictionaries implement `SubscriptDeleteT`.

### Iterator Interface:

```
prep IteratorT = <genericT [
    args [memberT = (itemT)]
] (interfaceT [
    fields [
        isFinished (boolT) [public, vis (2)]
    ]
    sharedFields [
        getNext (methodT [
            returns (memberT)
        ]) [public, vis (2)]
    ]
])>
```

The `isFinished` field stores whether the iteration has finished. The `getNext` method retrieves the next member in the iteration. The `IteratorT` interface interoperates with the `IterableT` interface.

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

The `createIterator` method creates a new iterator which iterates over members in the parent item. Buffers, strings, lists, and dictionaries implement `IterableT`. The `IterableT` interface interoperates with the `for` statement.

### Base Error Interface:

```
prep BaseErrorT = <interfaceT [
    fields [
        message (strT) [public, vis (2)]
        stackTrace (*StackTraceT) [public, vis (2)]
    ]
]>
```

The `message` field stores an error message, and the `stackTrace` field stores a stack trace from when the error was thrown. The `ErrorT` factor type includes `BaseErrorT`. The `BaseErrorT` interface interoperates with the `throw` statement.

## Built-In Factors

OstraCode has the following built-in factors:

### Stack Trace Factor:

The `StackTraceT` factor type represents a stack trace, and includes `ToStringT`. In the future, `StackTraceT` may include more feature types.

### Error Factors:

The `BaseError` factor implements `BaseErrorT`, and provides the following additional fields:

* `$baseError.init($message)` initializes the error with string message `$message`.

The `ErrorT` factor type includes `BaseErrorT` and `ToStringT`. All errors thrown by `throw` statements and caught by `try` statements conform to `ErrorT`.

The `Error` factor implements `ErrorT`, including `BaseError` and an implementation of `ToStringT`.

## Built-In Modules

Built-in modules are imported with the `importBuiltIn` statement. OstraCode has the following built-in modules:

### Math Module:

The math module has the name string `"math"`, and exports the following members:

* `$mathModule@random()` returns a random floating-point number between 0 and 1.


