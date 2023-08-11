
# Feature System

This page documents the feature system in OstraCode.

## Features and Interfaces

Every object in OstraCode includes one or more "features". A feature defines fields which may be accessed from the parent object. Fields declared in `fields` are stored in each instance of the object. Fields declared in `sharedFields` are shared between all objects which include the feature. The example below declares a feature and creates two objects which include the feature:

```
// Define the feature `MyFeature`.
prep MyFeature = <feature [
    fields [
        myInstanceField <strT> [public]
    ]
    sharedFields [
        mySharedField <strT> [public]
    ]
]>

entryPoint <func {
    
    // Creates two objects which include `MyFeature`.
    var myObj1 = (obj (MyFeature))
    var myObj2 = (obj (MyFeature))
    
    // Assigns values to `myInstanceField` in each object.
    (myObj1.myInstanceField = "Hello!")
    (myObj2.myInstanceField = "Hi!")
    // Prints "Hello!".
    (print(myObj1.myInstanceField))
    // Prints "Hi!".
    (print(myObj2.myInstanceField))
    
    // Assigns a value to `mySharedField`. Note that both `myObj1`
    // and `myObj2` share the same value of `mySharedField`.
    (myObj1.mySharedField = "Goodbye!")
    // Prints "Goodbye!".
    (print(myObj1.mySharedField))
    // Also prints "Goodbye!".
    (print(myObj2.mySharedField))
}>
```

Feature fields can store methods which manipulate other fields in the parent object. When a method is invoked, `self` becomes bound to the instance of the parent object. The example below demonstrates usage of methods:

```
prep Counter = <feature [
    fields [
        count <intT> [public] = (0)
    ]
    sharedFields [
        increment [public] = (method {
            (self.count += 1)
        })
    ]
]>

entryPoint <func {
    var myCounter = (obj (Counter))
    // Invokes the `increment` method.
    (myCounter.increment())
    // Prints "1".
    (print(myCounter.count))
}>
```

An "interface" defines field types without providing default values. Every feature may implement a single interface. Features which implement the same interface may be used interchangeably. The example below declares two features which implement the same interface:

```
// Declares an interface with one method.
prep SpeakT = <interfaceT [
    sharedFields [
        speak (methodT [returns (strT)]) [public]
    ]
]>

// Declares a feature which implements `SpeakT`.
prep DogSpeak = <feature [
    implements <SpeakT>
    sharedFields [
        speak [public] = (method [returns <strT>] {
            return ("Woof!")
        })
    ]
]>

// Declares another feature which implements `SpeakT`.
prep CatSpeak = <feature [
    implements <SpeakT>
    sharedFields [
        speak [public] = (method [returns <strT>] {
            return ("Meow!")
        })
    ]
]>

entryPoint <func {
    // `mySpeaker` can store any object which includes a feature that implements `SpeakT`.
    var mySpeaker <*SpeakT>
    // Assign an object which includes the `DogSpeak` feature.
    (mySpeaker = obj (DogSpeak))
    // Prints "Woof!".
    (print(mySpeaker.speak())
    // Assign an object which includes the `CatSpeak` feature.
    (mySpeaker = obj (CatSpeak))
    // Prints "Meow!".
    (print(mySpeaker.speak())
}>
```

If a feature does not implement an interface, the feature cannot be used in a context which requires the interface, even if the feature defines the same fields as the interface. The example below demonstrates how structural compatibility does not suffice for type compatibility:

```
prep SizeT = <interfaceT [
    fields [size (intT) [public]]
]>

// Note how `CargoSize` and `ShirtSize` do not have `implements` statements.

prep CargoSize = <feature [
    fields [size <intT> [public]]
]>

prep ShirtSize = <feature [
    fields [size <intT> [public]]
]>

// Throws an error, because `CargoSize` does not implement `SizeT`.
prep sizeObj1 <*SizeT> = <obj (CargoSize)>
// Throws an error, because `ShirtSize` does not implement `SizeT`.
prep sizeObj2 <*SizeT> = <obj (ShirtSize)>

// Does not throw an error.
prep myCargo <*?CargoSize> = <obj (CargoSize)>
// Throws an error, because `<*?CargoSize>` does not conform to `<*?ShirtSize>`.
prep myShirt <*?ShirtSize> = <obj (CargoSize)>
```

In order to access fields of a feature, the feature must have a "discerned" type. The `feature` special returns a feature with a discerned type, but `featureT` does not return a discerned type. The `discern` special helps in the case when a feature does not have a discerned type. The `discern` special accepts a feature, and returns the same feature with a discerned type. The example below demonstrates usage of the `discern` special:

```
// The output of `createCoinFeature` has a constraint type which is not discerned.
prep createCoinFeature = <func [
    args [probability <floatT>]
    returns <featureT [sharedFields [
        flip (methodT [returns (boolT)]) [public]
    ]]>
] {
    return (feature [sharedFields [
        flip [public] = (method [returns <boolT>] {
            return (mathUtils@random() < probability)
        })
    ]])
}>

entryPoint <func {
    // `AmbiguousCoin` does not have a discerned type.
    var AmbiguousCoin = (createCoinFeature(0.7))
    // `DiscernedCoin` has a discerned type.
    var DiscernedCoin = (discern (AmbiguousCoin))
    var coin1 = (obj (AmbiguousCoin))
    var coin2 = (obj (DiscernedCoin))
    // Throws an error, because the feature of `coin1` does not have a discerned type.
    (print(coin1.flip()))
    // Does not throw an error.
    (print(coin2.flip()))
}>
```

## Bundles and Factors

A "bundle" is a data structure which can group several features together. When an object includes a bundle, the fields of all features in the bundle belong to the object. Fields may be selected from individual features by casting the object to a type. The example below declares a bundle and creates an object which includes the bundle:

```
prep AddFive = <feature [
    sharedFields [
        addFive [public] = (method [
            args [num <intT>]
            returns <intT>
        ] {
            return (num + 5)
        })
    ]
]>

prep Nameable = <feature [
    fields [
        name <strT> [public]
    ]
]>

// Declares a bundle which contains `AddFive` and `Nameable`.
prep MyBundle = <bundle [
    factors [(AddFive), (Nameable)]
]>

entryPoint <func {
    // Creates an object which includes `MyBundle`.
    var myObj = (obj (MyBundle))
    // Prints "15".
    (print(myObj:<*?AddFive>.addFive(10)))
    // Assigns "Steve" to the `name` field in the `Nameable` feature of `myObj`.
    (myObj:<*?Nameable>.name = "Steve")
}>
```

Features and bundles are both considered to be "factors". A bundle contains one or more factors, which means that a bundle may store features, other bundles, or a mixture of features and bundles. The example below declares a bundle which contains another bundle:

```
prep AFeature = <feature [
    fields [a <intT> [public] = (10)]
]>
prep BFeature = <feature [
    fields [b <intT> [public] = (20)]
]>
prep CFeature = <feature [
    fields [c <intT> [public] = (30)]
]>

prep BcBundle = <bundle [factors [(BFeature), (CFeature)]]>

prep AbcBundle = <bundle [factors [(AFeature), (BcBundle)]]>

entryPoint <func {
    var myAbc = (obj (AbcBundle))
    (print(myAbc:<*?AFeature>.a)) // Prints "10".
    (print(myAbc:<*?BFeature>.b)) // Prints "20".
    (print(myAbc:<*?CFeature>.c)) // Prints "30".
}>
```

## Field Visibility

Every factor field is associated with an integer "visiblity". A field is only visible from the member access operator (`.`) if the field's visibility is greater than zero. By default, the visibility of every field is 1, but a different visibility may be specified with the `vis` statement. When a factor is included in a bundle, the visibility of all factor fields is decreased by 1. In order to be visible in the bundle, the factor fields must specifiy visibility 2 or higher. The example below demonstrates usage of visibility:

```
prep IsBig = <feature [
    sharedFields [
        isBig [public, vis <2>] = (method [
            args [value <numT>]
            returns <boolT>
        ] {
            return (value #gt 100)
        })
    ]
]>

prep IsSmall = <feature [
    sharedFields [
        isSmall [public, vis <2>] = (method [
            args [value <numT>]
            returns <boolT>
        ] {
            return (value #lt 0.1)
        })
        // The visibility of `isTiny` is 1, because 1 is the default
        // visibility when a `vis` statement is not provided.
        isTiny [public] = (method [
            args [value <numT>]
            returns <boolT>
        ] {
            return (value #lt 0.001)
        })
    ]
]>

// Within the `SizeCheck` bundle, `isBig` and `isSmall` have
// visibility 1, while `isTiny` has visibility 0.
prep SizeCheck = <bundle [factors [(IsBig), (IsSmall)]]>

entryPoint <func {
    var sizeChecker = (obj (SizeCheck))
    // Does not throw an error, because the visibility of
    // `isBig` in `SizeCheck` is greater than 0.
    (print(sizeChecker.isBig(1000)))
    // Does not throw an error, because the visibility of
    // `isSmall` in `SizeCheck` is greater than 0.
    (print(sizeChecker.isSmall(1000)))
    // Throws an error, because the visibility of `isTiny`
    // in `SizeCheck` is not greater than 0.
    (print(sizeChecker.isTiny(1000)))
    // Does not throw an error, because the visibility of
    // `isTiny` in `IsSmall` is greater than 0.
    (print(sizeChecker:<*?IsSmall>.isTiny(1000)))
}>
```

In certain cases, it may be desirable to decrease factor visibility in a bundle by a different amount than 1. The `shield` statement may be used to decrease factor visibility by a custom amount. The example below demonstrates usage of the `shield` statement:

```
prep Age = <feature [
    fields [age <intT> [public]]
]>
prep Height = <feature [
    fields [height <intT> [public]]
]>

// Within the `Profile` bundle, the visibility of `age` is 1,
// while the visibility of `height` is 0.
prep Profile = <bundle [factors [
    // The visibility of fields in `Age` will decrease by 0.
    (Age) [shield <0>]
    // The visibility of fields in `Height` will decrease by 1, because that is the
    // default amount when a `shield` statement is not provided.
    (Height)
]]>

entryPoint <func {
    var myProfile = (obj (Profile))
    // Does not throw an error.
    (myProfile.age = 30)
    // Throws an error, because `height` is not visibile in `Profile`.
    (myProfile.height = 180)
    // Does not throw an error.
    (myProfile:<*?Height>.height = 180)
}>
```

A "name collision" occurs when two fields with the same name are visible in a bundle. The interpreter will throw an error when trying to access a field with a name collision. Effective management of field visibility can prevent this issue. The example below demonstrates a name collision:

```
prep VideoManager = <feature [
    sharedFields [
        play [public, vis <2>] = (method {
            (print("I will play the video!"))
        })
    ]
]>

prep Athlete = <feature [
    sharedFields [
        play [public] = (method {
            (print("I will play the sportsball!"))
        })
    ]
]>

entryPoint <func {
    var steve = (obj (bundle [
        factors [(VideoManager), (Athlete) [shield <0>]]
    ]))
    // Throws an error, because `play` has a name collision.
    (steve.play())
    // Does not throw an error.
    (steve:<*?VideoManager>.play())
    // Does not throw an error.
    (steve:<*?Athlete>.play())
}>
```

## This and Self

The `thisFactor` statement determines the type of `this` when referenced in a method. By using the `thisFactor` statement, factors within the same bundle may interact with each other. The example below demonstrates usage of the `thisFactor` statement:

```
prep Count = <feature [
    fields [
        count <intT> [public, vis <2>] = (0)
    ]
]>

prep Increment = <feature [
    // The type of `this` in methods of `Increment` will be `objT <?Count>`.
    thisFactor <?Count>
    sharedFields [
        increment [public, vis <2>] = (method {
            (this.count += 1)
        })
    ]
]>

entryPoint <func {
    var counter = (obj (bundle [
        factors [(Count), (Increment)]
    ]))
    (counter.increment())
    (print(counter.count)) // Prints "1".
}>
```

A `thisFactor` statement is "unresolved" when the feature is not included in a bundle with the required factor. The interpreter will throw an error when creating an object with an unresolved `thisFactor` statement. The example below demonstrates an unresolved `thisFactor` statement:

```
prep CreateGreeting = <feature [
    sharedFields [
        createGreeting [public] = (method [
            args [name <strT>]
            returns <strT>
        ] {
            return ("Hello, " ; name ; "!")
        })
    ]
]>

prep GreetWorld = <feature [
    thisFactor <?CreateGreeting>
    sharedFields [
        greetWorld [public] = (method {
            (print(this.createGreeting("world")))
        })
    ]
]>

// Throws an error, because `CreateGreeting` must be
// included in the same object as `GreetWorld`.
prep badGreeter = <obj (GreetWorld)>
// Does not throw an error.
prep goodGreeter = <obj (bundle [
    factors[(CreateGreeting), (GreetWorld)]
])>
```

When referenced in a method, the type of `self` is determined by the feature in which the method is defined. Unlike `this`, the type of `self` cannot be changed with an attribute statement. `self` is used to access fields of the parent feature rather than other features in the same object. The example below demonstrates usage of `self`:

```
prep IsActive = <feature [
    fields [
        isActive <boolT> [public] = (false)
    ]
]>

prep Toggle = <feature [
    thisFactor <?IsActive>
    fields [
        toggleCount <intT> [public] = (0)
    ]
    sharedFields [
        toggle [public] = (method {
            // The type of `this` is `objT <?IsActive>`.
            (this.isActive = !this.isActive)
            // The type of `self` is `objT <?Toggle>`.
            (self.toggleCount += 1)
        })
    ]
]>

entryPoint <func {
    var toggler = (obj (bundle [
        factors [
            (IsActive) [shield <0>]
            (Toggle) [shield <0>]
        ]
    ]))
    (toggler.toggle())
    (toggler.toggle())
    (toggler.toggle())
    (print(toggler.isActive)) // Prints "true".
    (print(toggler.toggleCount)) // Prints "3".
}>
```

## Field Permission

The `public`, `protected`, and `private` statements determine the contexts in which feature fields may be written and read. Public fields have no access restrictions. Protected fields may only be accessed by methods belonging to the same object. Private fields may only be accessed by methods which are defined in the same feature. The default field permission is `private` when no permission statement is provided. The example below demonstrates usage of permission statements:

```
prep MultiCounter = <feature [
    fields [
        exposedCount <intT> [public] = (0)
        internalCount <intT> [protected] = (0)
        secretCount <intT> [private] = (0)
    ]
    sharedFields [
        incrementSecret [public, vis <2>] = (method {
            // Does not throw an error, because `secretCount` is defined in the same feature.
            (self.secretCount += 1)
        })
        getCountSum [public, vis <2>] = (method [returns <intT>] {
            return (self.exposedCount + self.internalCount + self.secretCount)
        })
    ]
]>

prep IncrementInternal = <feature [
    thisFactor <?MultiCounter>
    sharedFields [
        incrementInternal [public, vis <2>] = (method {
            // Does not throw an error, because `internalCount` belongs to the same object.
            (this.internalCount += 1)
        })
        badAccess [public, vis <2>] = (method {
            // Throws an error, because `secretCount` is defined in a different feature.
            (this.secretCount += 1)
        })
    ]
]>

entryPoint <func {
    var multiCounter = (obj (bundle [
        factors [(MultiCounter), (IncrementInternal)]
    ]))
    // Does not throw an error.
    (multiCounter.exposedCount += 1)
    // Throws an error, because `internalCount` is accessed outside of
    // a method belonging to `multiCounter`.
    (multiCounter.internalCount += 1)
    // Throws an error, because `secretCount` is accessed outside of
    // a method defined in `MultiCounter`.
    (multiCounter.secretCount += 1)
}>
```

## Generic Factors

A generic factor may be "qualified" with one or more arguments. Field types and method signatures may reference the generic arguments. Generic factors may be created by using the `generic` special. The example below demonstrates usage of generic factors:

```
// `ListNode` may be qualified with an argument named
// `contentT`, whose constraint type is `typeT`.
prep ListNode = <generic [
    args [contentT <typeT>]
] (feature [
    fields [
        // The constraint type of `content` is equal to the generic argument `contentT`.
        content <contentT> [public]
        // `next` can store another node which stores the same type of content.
        next <*?ListNode+:<contentT>> [public]
    ]
])>

entryPoint <func {
    // `node1` and `node2` include `ListNode` qualified with `intT`.
    var node1 = (obj (ListNode+:<intT>))
    var node2 = (obj (ListNode+:<intT>))
    // The type of `content` in `node1` and `node2` is `intT`.
    (node1.content = 10)
    (node2.content = 20)
    // The type of `next` in `node1` and `node2` is `<*?ListNode+:<intT>>`.
    (node1.next = node2)
}>
```


