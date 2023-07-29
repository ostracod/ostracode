
# Fundamentals

This page documents evaluation order and data types in OstraCode.

## Evaluation Grades

In OstraCode, each expression is associated with an "evaluation grade". The evaluation grade of an expression is determined by the brackets which enclose the expression (parentheses, angle brackets, and others). Evaluation grade influences the order in which expressions are evaluated:

* Prep-grade expressions are evaluated in advance of other expressions in their parent context.
* Flow-grade expressions are evaluated when control flow reaches the expressions.
* Never-grade expressions are never evaluated. Instead, the interpreter may derive type information from never-grade expressions.

In an analagous fashion, each variable is also associated with an evaluation grade. The evaluation grade of a variable is determined by the first keyword of the variable's declaration statement (`prepVar` or `flowVar`). Evaluation grade influences the order in which variables are initialized:

* Prep-grade variables are initialized in advance of other variables in their parent block.
* Flow-grade variables are initialized when control flow reaches their declaration statements.

## Evaluation Phases

Each OstraCode application exists in one of two "evaluation phases":

* When an application is in prep-phase, prep-grade variables at the top level of each module are initialized.
* When an application is in flow-phase, the entry-point function of the application is invoked.

Each application begins in prep-phase. Once all top-level variables are initialized, the application enters flow-phase and invokes the entry-point function.

Statement blocks also exist in one of the two evaluation phases:

* When a statement block is in prep-phase, prep-grade variables are initialized and prep-grade expressions are evaluated.
* When a statement block is in flow-phase, statements are evaluated in order from first to last.

A statement block will finish prep-phase once all prep-grade variables in the block are initialized, and all prep-grade expressions in the block are evaluated. A statement block may only enter flow-phase after prep-phase is finished. A statement block may be evaluated several times in flow-phase if the block is the body of a function or loop.

In addition, each expression exists in an evaluation phase:

* When an expression is in prep-phase, nested prep-grade expressions are evaluated.
* When an expression is in flow-phase, the operation of the expression is performed.

An expression will finish prep-phase once all nested prep-grade expressions are evaluated. An expression may only enter flow-phase after prep-phase is finished. An expression may be evaluated multiple times in flow-phase if the parent statement of the expression is evaluated multiple times in flow-phase

## Variable Access and Mutability

When a statement block is in prep-phase, prep-grade variables in the block are deeply immutable. Once the statement block enters flow-phase, the prep-grade variables may become mutable.

Variable access may be restricted depending on the evaluation grade of the variable and the evaluation phase of the variable's parent block:

* Prep-grade variables in prep-phase blocks can be directly read.
* Flow-grade variables in prep-phase blocks can only be referenced by closures.
* Prep-grade variables in flow-phase blocks can be directly written and read.
* Flow-grade variables in flow-phase blocks can be directly written and read.

Within an application, prep-grade variables may be initialized in any order, and prep-grade expressions may be evaluated in any order. If an operand of an expression is not yet known, the interpreter will defer evaluation of the expression until the operand is known.

At the top-level of each module, only prep-grade variables and prep-grade expressions are allowed. This ensures that modules may be imported in any order without runtime conflicts.

## Data Types

In OstraCode, each variable is associated with a "constraint type" which is known during prep-phase. A variable may only store items whose types conform to the variable's constraint type. Each expression also has a constraint type which is known during prep-phase. The interpreter derives the constraint type of an expression based on the operations and operands in the expression.

The interpreter validates item types during the prep-phase of statement blocks and expressions. If an operand item has an incompatible type, the interpreter will throw an error.

OstraCode has the following data types:

* `nullT` is the type of a missing item.
* `boolT` is the type of a boolean value. A boolean value is either true or false.
* `intT` is the type of a signed 64-bit integer.
* `floatT` is the type of a double-precision floating-point number.
* `strT` is the type of a string. A string is a sequence of characters.
* `symbolT` is the type of a symbol. Every symbol is globally unique.
* `listT` is the type of a list. A list is a sequence of items.
* `dictT` is the type of a dictionary. A dictionary is an associative array of items whose keys are also items.
* `funcT` is the type of a function. A function accepts argument items and return an item.
* `methodT` is the type of a method. A method behaves like a function, but references an object for behavior context.
* `interfaceT` is the type of an interface. An interface defines a set of feature field types.
* `featureT` is the type of a feature. A feature defines the set of fields which their instances will contain. Each feature may implement an interface.
* `bundleT` is the type of a bundle. A bundle contains one or more features.
* `objT` is the type of an object. An object contains one or more feature instances.
* `moduleT` is the type of a module. A module is a code file, and may export one or more variables.

Data types may be categorized into the following supertypes:

* `itemT` is the most generic type. `itemT` is a supertype of all other types.
* `typeT` is the type of a type. Items with type `typeT` may be used as variable constraint types.
* `valueT` is the type of a value. Items with type `valueT` may not be used as variable constraint types.
* `numT` is the type of a number. `numT` is a supertype of `intT` and `floatT`.
* `factorT` is the type of a factor. `factorT` is a supertype of `interfaceT`, `featureT`, and `bundleT`.
* `genericT` is the type of an item which may be qualified with one or more arguments.


