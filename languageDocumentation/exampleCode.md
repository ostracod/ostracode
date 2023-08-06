
# Example Code

This page provides example OstraCode without explaining the feature system.

## Basic Value Manipulation

The example below prints the prime numbers between 1 and 100:

```
prep isPrime = <func [
    args [value <intT>]
    returns <boolT>
] {
    var factor = (2)
    while (factor #lt value) {
        if (value % factor #eq 0) {
            return (false)
        }
        (factor += 1)
    }
    return (true)
}>

entryPoint <func {
    var value = (2)
    while (value #lte 100) {
        if (isPrime(value)) {
            (print(value))
        }
        (value += 1)
    }
}>
```

The example below performs bubble sort on a list of numbers:

```
entryPoint <func {
    
    var ints = (list (30, 15, 18, 3, 20))
    (print(ints))
    
    while (true) {
        var isSorted = (true)
        var index = (1)
        while (index #lt ints.length) {
            var int1 = (ints@(index - 1))
            var int2 = (ints@(index))
            if (int1 > int2) {
                (isSorted = false)
                (ints@(index - 1) = int2)
                (ints@(index) = int1)
            }
            (index += 1)
        }
        if (isSorted) {
            break
        }
    }
    
    (print(ints))
}>
```

The example below demonstrates usage of symbols:

```
prep symbolA = <symbol()>
prep symbolB = <symbolA>
prep symbolC = <symbol()>

entryPoint <func {
    // Prints "true", because `symbolB` holds the same symbol as `symbolA`.
    (print(symbolA #eq symbolB))
    // Prints "false", because `symbolA` and `symbolC` hold the output
    // of different `symbol()` invocations.
    (print(symbolA #eq symbolC))
    // Prints "false".
    (print(symbolB #eq symbolC))
    // Prints "false", because the names assigned to symbols do not
    // affect whether the symbols are equal to each other.
    (print(symbol("test") #eq symbol("test"))
}>
```

## Type Wrangling

The example below declares a function which creates dictionary types:

```
prep createDictType = <func [
    args [fieldName <strT>]
    returns <?dictT>
] {
    return (dictT [fields [
        (fieldName) (boolT)
    ]])
}>

// `myDictType` is equal to `dictT [fields [isCool (boolT)]]`.
prep myDictType = <createDictType("isCool")>

// Does not throw an error, because the type of `myDict1` conforms to `myDictType`.
prep myDict1 <myDictType> = <dict [fields [isCool = (true)]]>

// Throws an error, because `myDict2` is missing the field `isCool`.
prep myDict2 <myDictType> = <dict [fields [isNice = (false)]]>
```

The example below demonstrates usage of the `literalT` function:

```
// `constraintT` is equal to `intT`.
prep constraintT = <?7>
// `sevenT` is a more specific type than `constraintT`,
// and refers to numbers which are equal to 7.
prep sevenT = <literalT(7)>

// Does not throw an error, because the constraint type of `50` is `intT`.
prep myInt1 <constraintT> = <50>
// Does not throw an error, because `7` can be implicitly cast to `sevenT`.
prep myInt2 <sevenT> = <7>
// Throws an error, because 50 is not equal to 7.
prep myInt3 <sevenT> = <50>
```

The example below demonstrates usage of the `nominalT` function:

```
// `myIntT` conforms to `intT`, but `intT` does not conform to `myIntT`.
prep myIntT = <nominalT(intT)>

// Throws an error, because the constraint type of 123 is `intT`.
prep myInt1 <myIntT> = <123>
// Does not throw an error.
prep myInt2 <myIntT> = <123:<myIntT>>
```

The example below demonstrates type checking in flow-phase:

```
entryPoint <func {
    
    var myType <typeT>
    if (mathUtils@random() > 0.5) {
        (myType = intT)
    } else {
        (myType = strT)
    }
    // Prints "intT" or "strT" with equal probability.
    (print(myType))
    
    // Prints "Integer type!" or "Other type!" depending on the contents of `myType`.
    if (myType.conformsTo(intT)) {
        (print("Integer type!"))
    } else {
        (print("Other type!"))
    }
}>
```

The example below demonstrates generic qualification:

```
// Declares the type `pairT` which is a list of two elements having type `elemT`.
// Type `elemT` is determined during the qualification of `pairT`.
prep pairT = <genericT [
    args [elemT <typeT>]
] (listT (elemT, elemT))>

// Does not throw an error.
prep myPair1 <pairT+:(intT)> = <list (10, 20)>
// Throws an error, because the type of the second element does not conform to `intT`.
prep myPair2 <pairT+:(intT)> = <list (10, "Ouch")>
```

## Miscellaneous Statements

The example below demonstrates usage of the `throw` and `try` statements:

```
entryPoint <func {
    
    // This `try` statement will print the messages "No problem!" and "Clean up!".
    try {
        (print("No problem!"))
    } catch error {
        (print(error))
    } finally {
        (print("Clean up!"))
    }
    
    // This `try` statement will print the messages "Ouch!" and "Clean up!".
    try {
        throw ((obj (Error)).init("Ouch!"))
        (print("Not reached!"))
    } catch error {
        (print(error.message))
    } finally {
        (print("Clean up!"))
    }
}>
```

The example below demonstrates usage of import statements:

```
// Imports the module at path "./myModule.ostc" as `myModule`.
importPath <"./myModule.ostc"> as myModule
// Imports the member named `generateMessage` from the module at path
// "./myUtils.ostc", and renames the member to `createMessage`.
importPath <"./myUtils.ostc"> [members [
    generateMessage as createMessage
]]

entryPoint <func {
    // Invokes the member `performJob` in `myModule`.
    (myModule@performJob())
    // Prints the item returned by invoking `createMessage`.
    (print(createMessage())
}>
```


